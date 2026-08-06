#include "ft_malloc.h"
#include "libft.h"

t_bloc *split_block(t_bloc *bloc, size_t size)
{
	size_t	total_occupied = size + sizeof(t_bloc);

	if (bloc->size - total_occupied <= sizeof(t_bloc))
	{
		bloc->is_free = 0;
		return bloc;
	}

	t_bloc*	new_free_bloc = (t_bloc*)((char*)bloc + total_occupied);

	new_free_bloc->is_free = 1;
	new_free_bloc->size = bloc->size - total_occupied;

	bloc->is_free = 0;
	bloc->size = total_occupied;

	return new_free_bloc;
}

void insert_bloc(t_zone* zone, t_bloc* insert)
{
	t_bloc*	curr = zone->free_list;
	t_bloc* prev = NULL;

	while (curr && curr->next)
	{
		if (prev == NULL && insert < curr)
		{
			insert->next = curr;
			insert->prev = NULL;
			curr->prev = insert;
			zone->free_list = insert;
			return ;
		}
		else if (insert > curr && insert < curr->next)
		{
			insert->prev = curr;
			insert->next = curr->next;
			
			curr->next->prev = insert;
			curr->next = insert;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
	
	insert->prev = curr;
	insert->next = NULL;

	curr->next = insert;
}

static t_bloc *find_free_space(size_t size)
{
	if (g_zone == NULL) return NULL;

	t_type	type;

	if (size <= TINY_MAX)
		type = TINY;
	else if (size > TINY_MAX && size <= SMALL_MAX)
		type = SMALL;
	else
		type = LARGE;

	t_zone*	curr_zone = g_zone;

	while (curr_zone)
	{
		if (curr_zone->type == type)
		{
			t_bloc* prev = NULL;
			t_bloc*	curr = curr_zone->free_list;
			while (curr)
			{
				if (curr->is_free && curr->size >= size + sizeof(t_bloc))
				{
					if (prev)
						prev->next = curr->next;
					else
						curr_zone->free_list = curr->next;

					t_bloc* new_free = split_block(curr, size);
					if (new_free)
						insert_bloc(curr_zone, new_free);
					return curr;
				}
				prev = curr;
				curr = curr->next;
			}
		}
		curr_zone = curr_zone->next;
	}
	return NULL;
}

t_bloc *allocate_from_zone(t_type type, size_t size)
{
	size_t	data_size;
	size_t page_size = sysconf(_SC_PAGE_SIZE);

	if (type == TINY)
		data_size = 100 * (TINY_MAX + sizeof(t_bloc));
	else if (type == SMALL)
		data_size = 100 * (SMALL_MAX + sizeof(t_bloc));
	else
		data_size = 100 * (4096 + sizeof(t_bloc));
	
	size_t	total_size = sizeof(t_zone) + data_size;

	if (total_size % page_size != 0)
		total_size += page_size - total_size % page_size; // arrondir à la page supérieure

	t_zone	*new_zone = mmap(NULL, total_size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0);

	if (new_zone == (void *) -1)
		return NULL;

	new_zone->next = g_zone;
	new_zone->size = total_size;
	new_zone->type = type;
	new_zone->free_list = NULL;

	t_bloc	*new_bloc = (t_bloc*)((char*)new_zone + sizeof(t_zone));
	new_bloc->is_free = 1;
	new_bloc->prev = NULL;
	new_bloc->next = NULL;
	new_bloc->size = data_size - sizeof(t_bloc);
	new_zone->free_list = new_bloc;

	t_bloc* free_bloc = split_block(new_bloc, size);
	free_bloc->next = NULL;
	free_bloc->prev = NULL;
	new_zone->free_list = free_bloc;
	g_zone = new_zone;

	return new_bloc;
}

t_bloc *request_space(size_t size)
{
	if (size <= TINY_MAX)
		return allocate_from_zone(TINY, size);
	else if (size > TINY_MAX && size <= SMALL_MAX)
		return allocate_from_zone(SMALL, size);
	else
		return allocate_from_zone(LARGE, size);
}

void *malloc(size_t size)
{
	if (size == 0) return NULL;

	t_bloc	*block = find_free_space(size);
	if (!block)
	{
		block = request_space(size);
		if (!block)
			return NULL;
	}
	
	return (void*)((char*)block + sizeof(t_bloc));
}

int main()
{
	char* test = malloc(42);
	if (!test)
		ft_printf("erreur");
	test[41] = 'a';
	
	return 0;
}
