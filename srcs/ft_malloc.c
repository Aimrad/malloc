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

	g_zone->free_list = bloc->next;
	new_free_bloc->next = g_zone->free_list;
	g_zone->free_list = new_free_bloc;

	bloc->is_free = 0;
	bloc->size = total_occupied;

	return bloc;
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
	t_bloc*	curr_free_block;
	
	while (curr_zone)
	{
		if (curr_zone->type == type)
		{
			curr_free_block = curr_zone->free_list;
			while (curr_free_block)
			{
				if (curr_free_block->is_free && curr_free_block->size >= size + sizeof(t_bloc))
				{
					g_zone->free_list = curr_free_block->next;
					curr_free_block = split_block(curr_free_block, size);
					return curr_free_block;
				}
				curr_free_block = curr_free_block->next;
			}
		}
		curr_zone = curr_zone->next;
	}
	return NULL;
}

t_bloc *allocate_from_zone(t_type type)
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

	t_bloc	*new_bloc = (t_bloc*)((char*)new_zone + sizeof(t_zone));
	new_bloc->is_free = 1;
	new_bloc->next = NULL;
	new_bloc->size = data_size - sizeof(t_bloc);
	new_zone->free_list = new_bloc;

	g_zone = new_zone;
	return new_bloc;
}

t_bloc *request_space(size_t size)
{
	t_bloc* new_space;

	if (size <= TINY_MAX)
		new_space = allocate_from_zone(TINY);
	else if (size > TINY_MAX && size <= SMALL_MAX)
		new_space = allocate_from_zone(SMALL);
	else
		new_space = allocate_from_zone(LARGE);

	if (!new_space)
		return NULL;

	new_space = split_block(new_space, size);

	return new_space;
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
	
	return (void*)(block + 1);
}

int main()
{
	char* test = malloc(42);
	if (!test)
		ft_printf("erreur");
	test[0] = 'a';
	ft_printf("%c", test[0]);

	t_bloc* curr = g_zone->free_list;
	while (curr)
	{
		ft_printf("%p", curr);
		curr = curr->next;
	}
	
	return 0;
}
