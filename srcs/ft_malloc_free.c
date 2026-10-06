#include "ft_malloc.h"

t_bloc *find_bloc_in_zones(void *ptr, t_zone **found_zone)
{
	t_zone *zone = g_zone;
	char *zone_start;
	char *zone_end;
	t_bloc *block;

	while (zone)
	{
		zone_start = (char *)zone + sizeof(t_zone);
		zone_end = (char *)zone + zone->size;
		if ((char *)ptr >= zone_start && (char *)ptr < zone_end)
		{
			block = (t_bloc *)((char *)ptr - sizeof(t_bloc));
			*found_zone = zone;
			return block;
		}
		zone = zone->next;
	}
	*found_zone = NULL;
	return NULL;
}

static void free_large_allocation(t_zone *zone)
{
	t_zone *prev = g_zone;

	while (prev && prev->next != zone)
		prev = prev->next;
	if (prev)
		prev->next = zone->next;
	else
		g_zone = zone->next;
	munmap(zone, zone->size);
}

static void merge_free_blocks(t_zone *zone)
{
	t_bloc *curr = zone->free_list;

	while (curr && curr->next)
	{
		if ((char *)curr + curr->size == (char *)curr->next)
		{
			curr->size += curr->next->size;
			curr->next = curr->next->next;
		}
		else
			curr = curr->next;
	}
}

static void check_and_free_empty_zone(t_zone *zone)
{
	t_bloc *curr = zone->free_list;
	size_t total_data_size = zone->size - sizeof(t_zone);

	if (curr && curr->next == NULL && curr->size == total_data_size)
	{
		free_large_allocation(zone);
	}
}

static void free_small_allocation(t_zone *zone, t_bloc *block)
{
	if (block->is_free)
		return ;
	block->is_free = 1;
	insert_bloc(zone, block);
	merge_free_blocks(zone);
	check_and_free_empty_zone(zone);
}

void free(void *ptr)
{
	t_zone *zone;
	t_bloc *block;

	if (!ptr)
		return ;
	block = find_bloc_in_zones(ptr, &zone);
	if (!zone)
		return ;
	if (zone->type == LARGE)
		free_large_allocation(zone);
	else
		free_small_allocation(zone, block);
}
