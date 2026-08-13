#include "ft_malloc.h"

size_t get_data_size(t_type type)
{
	if (type == TINY)
		return 100 * (TINY_MAX + sizeof(t_bloc));
	return 100 * (SMALL_MAX + sizeof(t_bloc));
}

t_bloc *split_block(t_bloc *bloc, size_t size)
{
	size_t total_occupied = size + sizeof(t_bloc);

	if (bloc->size - total_occupied <= sizeof(t_bloc))
	{
		bloc->is_free = 0;
		return NULL;
	}
	t_bloc *new_free_bloc = (t_bloc *)((char *)bloc + total_occupied);
	new_free_bloc->is_free = 1;
	new_free_bloc->size = bloc->size - total_occupied;
	bloc->is_free = 0;
	bloc->size = total_occupied;
	return new_free_bloc;
}

void insert_bloc(t_zone *zone, t_bloc *insert)
{
	t_bloc *curr = zone->free_list;
	t_bloc *prev = NULL;

	if (!curr)
	{
		zone->free_list = insert;
		insert->next = NULL;
		return ;
	}
	while (curr && insert > curr)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev == NULL)
	{
		insert->next = zone->free_list;
		zone->free_list = insert;
	}
	else
	{
		insert->next = curr;
		prev->next = insert;
	}
}

static t_bloc *find_in_zone(t_zone *zone, size_t size)
{
	t_bloc *prev = NULL;
	t_bloc *curr = zone->free_list;

	while (curr)
	{
		if (curr->is_free && curr->size >= size + sizeof(t_bloc))
		{
			if (prev)
				prev->next = curr->next;
			else
				zone->free_list = curr->next;
			return curr;
		}
		prev = curr;
		curr = curr->next;
	}
	return NULL;
}

t_bloc *find_free_space(size_t size)
{
	t_zone*	curr_zone = g_zone;
	t_bloc*	block = NULL;
	t_bloc*	new_free = NULL;
	t_type	zone_type = get_zone_type(size);

	while (curr_zone)
	{
		if (curr_zone->type == zone_type)
		{
			block = find_in_zone(curr_zone, size);

			if (block)
			{
				new_free = split_block(block, size);

				if (new_free)
					insert_bloc(curr_zone, new_free);
				return block;
			}
		}
		curr_zone = curr_zone->next;
	}
	return NULL;
}
