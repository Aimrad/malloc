#include "ft_malloc.h"

#include <stdint.h>
#include <string.h>

static int check(int condition, const char *message)
{
	if (!condition)
	{
		write(STDERR_FILENO, "FAIL: ", 6);
		write(STDERR_FILENO, message, strlen(message));
		write(STDERR_FILENO, "\n", 1);
		return 0;
	}
	return 1;
}

static void free_unknown_pointer(void *pointer)
{
	free(pointer);
}

static void *realloc_unknown_pointer(void *pointer, size_t size)
{
	return realloc(pointer, size);
}

static int test_size_classes(void)
{
	size_t sizes[] = {1, TINY_MAX - 1, TINY_MAX, TINY_MAX + 1,
		SMALL_MAX - 1, SMALL_MAX, SMALL_MAX + 1};
	size_t index;
	char *memory;

	for (index = 0; index < sizeof(sizes) / sizeof(*sizes); index++)
	{
		memory = malloc(sizes[index]);
		if (!check(memory != NULL, "size class allocation"))
			return 0;
		memset(memory, 0x5a, sizes[index]);
		if (!check(memory[sizes[index] - 1] == 0x5a,
				"allocated memory is writable"))
			return 0;
		free(memory);
	}
	return 1;
}

static int test_helper_boundaries(void)
{
	size_t page_size;

	page_size = (size_t)sysconf(_SC_PAGE_SIZE);
	return check(get_zone_type(TINY_MAX) == TINY
		&& get_zone_type(TINY_MAX + 1) == SMALL
		&& get_zone_type(SMALL_MAX) == SMALL
		&& get_zone_type(SMALL_MAX + 1) == LARGE,
		"zone type boundaries")
		&& check(round_up_page_size(0) == 0,
			"page rounding zero")
		&& check(round_up_page_size(page_size) == page_size,
			"page rounding exact page")
		&& check(round_up_page_size(page_size + 1) == page_size * 2,
			"page rounding next page");
}

static int test_large_allocations(void)
{
	size_t size = SMALL_MAX + 1;
	char *memory;

	memory = malloc(size);
	if (!check(memory != NULL, "large allocation"))
		return 0;
	memory[0] = 0x11;
	memory[size - 1] = 0x22;
	if (!check(memory[0] == 0x11 && memory[size - 1] == 0x22,
			"large allocation is writable"))
	{
		free(memory);
		return 0;
	}
	free(memory);
	return 1;
}

static int test_reuse(void)
{
	void *first;
	void *second;

	first = malloc(32);
	if (!check(first != NULL, "reuse setup allocation"))
		return 0;
	free(first);
	second = malloc(32);
	if (!check(second == first, "freed block is reused"))
		return 0;
	free(second);
	return 1;
}

static int test_realloc(void)
{
	unsigned char *memory;
	unsigned char *resized;
	unsigned char expected[32];
	size_t index;

	memory = malloc(32);
	if (!check(memory != NULL, "realloc setup allocation"))
		return 0;
	for (index = 0; index < 32; index++)
	{
		memory[index] = (unsigned char)index;
		expected[index] = (unsigned char)index;
	}
	resized = realloc(memory, 2048);
	if (!check(resized != NULL, "realloc growth")
		|| !check(memcmp(resized, expected, 32) == 0,
			"realloc preserves data"))
	{
		free(resized);
		return 0;
	}
	resized = realloc(resized, 8);
	if (!check(resized != NULL, "realloc shrink")
		|| !check(resized[7] == 7, "realloc shrink preserves data"))
	{
		free(resized);
		return 0;
	}
	free(resized);
	return check(malloc(0) == NULL, "zero-sized allocation returns NULL");
}

static int test_realloc_in_place(void)
{
	unsigned char *memory;
	unsigned char *resized;
	uintptr_t original_address;
	size_t index;

	memory = malloc(32);
	if (!check(memory != NULL, "in-place realloc setup"))
		return 0;
	original_address = (uintptr_t)memory;
	for (index = 0; index < 32; index++)
		memory[index] = (unsigned char)(index + 1);
	resized = realloc(memory, TINY_MAX);
	if (!check((uintptr_t)resized == original_address,
			"realloc grows into adjacent free block"))
	{
		free(resized);
		return 0;
	}
	for (index = 0; index < 32; index++)
	{
		if (!check(resized[index] == (unsigned char)(index + 1),
				"in-place realloc preserves data"))
		{
			free(resized);
			return 0;
		}
	}
	free(resized);
	return 1;
}

static int test_realloc_with_copy(void)
{
	unsigned char *memory;
	unsigned char *blocker;
	unsigned char *resized;
	unsigned char expected[32];
	uintptr_t original_address;
	size_t index;

	memory = malloc(32);
	blocker = malloc(32);
	if (!check(memory != NULL && blocker != NULL, "copy realloc setup"))
	{
		free(memory);
		free(blocker);
		return 0;
	}
	original_address = (uintptr_t)memory;
	for (index = 0; index < sizeof(expected); index++)
	{
		expected[index] = (unsigned char)(0xa0 + index);
		memory[index] = expected[index];
	}
	resized = realloc(memory, SMALL_MAX + 1);
	if (!check(resized != NULL, "realloc with copy")
		|| !check((uintptr_t)resized != original_address,
			"realloc moves when growth is blocked")
		|| !check(memcmp(resized, expected, sizeof(expected)) == 0,
			"moved realloc preserves data"))
	{
		free(resized);
		free(blocker);
		return 0;
	}
	free(resized);
	free(blocker);
	return 1;
}

static int test_error_cases(void)
{
	volatile uintptr_t invalid_value = 1;
	void *invalid;
	void *memory;
	void *stale;

	invalid = (void *)invalid_value;

	if (!check(malloc(0) == NULL, "malloc zero returns NULL")
		|| !check(realloc(NULL, 0) == NULL,
			"realloc NULL and zero returns NULL")
		|| !check((memory = realloc(NULL, 32)) != NULL,
			"realloc NULL allocates memory"))
		return 0;
	free(memory);
	free(NULL);
	free_unknown_pointer(invalid);
	if (!check(realloc_unknown_pointer(invalid, 32) == NULL,
			"realloc rejects an external pointer"))
		return 0;
	memory = malloc(32);
	if (!check(memory != NULL, "error case setup allocation"))
		return 0;
	if (!check(realloc(memory, 0) == NULL,
			"realloc zero frees the original block"))
		return 0;
	stale = malloc(32);
	if (!check(stale != NULL, "freed pointer setup allocation"))
		return 0;
	free_unknown_pointer(stale);
	free_unknown_pointer(stale);
	return check(realloc_unknown_pointer(stale, 32) == NULL,
		"realloc rejects a freed pointer");
}

int main(void)
{
	if (!test_size_classes() || !test_helper_boundaries()
		|| !test_large_allocations() || !test_reuse()
		|| !test_realloc() || !test_realloc_in_place()
		|| !test_realloc_with_copy() || !test_error_cases())
		return 1;
	write(STDOUT_FILENO, "malloc tests: PASS\n", 19);
	return 0;
}