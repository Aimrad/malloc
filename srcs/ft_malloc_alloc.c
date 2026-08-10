#include "ft_malloc.h"

t_type get_zone_type(size_t size)
{
	if (size <= TINY_MAX)
		return TINY;
	if (size <= SMALL_MAX)
		return SMALL;
	return LARGE;
}

size_t round_up_page_size(size_t size)
{
	size_t page_size = sysconf(_SC_PAGE_SIZE);

	if (size % page_size != 0)
		size += page_size - (size % page_size);
	return size;
}

t_bloc *allocate_from_zone(t_type type, size_t size)
{
	size_t data_size = 0;
	size_t total_size = 0;
	t_zone *new_zone = NULL;
	t_bloc *new_bloc = NULL;
	t_bloc *free_bloc = NULL;

	data_size = get_data_size(type);
	total_size = round_up_page_size(sizeof(t_zone) + data_size);
	new_zone = mmap(NULL, total_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANON, -1, 0);
	if (new_zone == (void *)-1)
		return NULL;
	new_zone->next = g_zone;
	new_zone->size = total_size;
	new_zone->type = type;
	new_zone->free_list = NULL;
	new_bloc = (t_bloc *)((char *)new_zone + sizeof(t_zone));
	new_bloc->is_free = 1;
	new_bloc->next = NULL;
	new_bloc->size = data_size - sizeof(t_bloc);
	free_bloc = split_block(new_bloc, size);
	if (free_bloc)
		insert_bloc(new_zone, free_bloc);
	g_zone = new_zone;
	return new_bloc;
}

t_bloc *allocate_large(size_t size)
{
	size_t total_size = 0;
	t_zone *new_zone = NULL;
	t_bloc *new_bloc = NULL;

	total_size = round_up_page_size(sizeof(t_zone) + sizeof(t_bloc) + size);
	new_zone = mmap(NULL, total_size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANON, -1, 0);
	if (new_zone == (void *)-1)
		return NULL;
	new_zone->free_list = NULL;
	new_zone->next = g_zone;
	new_zone->size = total_size;
	new_zone->type = LARGE;
	new_bloc = (t_bloc *)((char *)new_zone + sizeof(t_zone));
	new_bloc->is_free = 0;
	new_bloc->next = NULL;
	new_bloc->size = size;
	g_zone = new_zone;
	return new_bloc;
}

t_bloc *request_space(size_t size)
{
	if (size <= TINY_MAX)
		return allocate_from_zone(TINY, size);
	if (size <= SMALL_MAX)
		return allocate_from_zone(SMALL, size);
	return allocate_large(size);
}
