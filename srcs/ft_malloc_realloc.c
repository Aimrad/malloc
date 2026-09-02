#include "ft_malloc.h"
#include "libft.h"

static void remove_free_block(t_zone *zone, t_bloc *block)
{
	t_bloc *previous = NULL;
	t_bloc *current = zone->free_list;

	while (current && current != block)
	{
		previous = current;
		current = current->next;
	}
	if (!current)
		return ;
	if (previous)
		previous->next = current->next;
	else
		zone->free_list = current->next;
}

static t_bloc *get_next_block(t_bloc *block, t_zone *zone)
{
	t_bloc *next_block = (t_bloc *)((char *)block + block->size);
	char *zone_end = (char *)zone + zone->size;

	if ((char *)next_block >= zone_end || !next_block->is_free)
		return NULL;
	return next_block;
}

static void *resize_in_place(t_zone *zone, t_bloc *block, size_t size)
{
	t_bloc *next_block = get_next_block(block, zone);
	t_bloc *new_free;

	if (!next_block || block->size + next_block->size < size + sizeof(t_bloc))
		return NULL;
	remove_free_block(zone, next_block);
	block->size += next_block->size;
	new_free = split_block(block, size);
	if (new_free)
		insert_bloc(zone, new_free);
	return (char *)block + sizeof(t_bloc);
}

static void *resize_with_copy(void *ptr, size_t old_size, size_t size)
{
	void *new_ptr = malloc(size);
	size_t copy_size = old_size < size ? old_size : size;

	if (!new_ptr)
		return NULL;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return new_ptr;
}

void *realloc(void *ptr, size_t size)
{
	t_zone *zone;
	t_bloc *block;
	void *new_ptr;
	size_t old_size;

	if (!ptr)
		return malloc(size);
	if (size == 0)
	{
		free(ptr);
		return NULL;
	}
	block = find_bloc_in_zones(ptr, &zone);
	if (!block || !zone || block->is_free)
		return NULL;
	old_size = block->size - sizeof(t_bloc);
	new_ptr = resize_in_place(zone, block, size);
	if (new_ptr)
		return new_ptr;
	return resize_with_copy(ptr, old_size, size);
}