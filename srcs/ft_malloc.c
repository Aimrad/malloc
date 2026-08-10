#include "ft_malloc.h"
#include "libft.h"

t_zone *g_zone = NULL;

void free(void *ptr)
{
	if (!ptr)
		return ;
	// determiner la zone memoire de ptr dans g_zone
	t_bloc*	block = NULL;
	t_zone*	zone = g_zone;
	char*	zone_start = NULL;
	char*	zone_end = NULL;

	while (zone)
	{
		zone_start = (char*)zone + sizeof(t_zone);
		zone_end = (char*)zone + zone->size;

		if ((char*)ptr >= zone_start && (char*)ptr <= zone_end)
		{
			block = (t_bloc*)(char*)ptr - sizeof(t_bloc);
			break;
		}
		zone = zone->next;
	}
	
	// les cas de free :
	// si ptr est un LARGE faire munmap
	if (zone->type == LARGE)
		munmap(zone, zone->size);
	else
	{
		// sinon l'inserer dans la free list
		block->is_free = 1;
		insert_bloc(zone, block);

		// bonus : fusionner les zones libres adjacents
		// regarder si les adresses se suivent pour eviter de mettre en free_list une zone occupee
		t_bloc* curr = zone->free_list;
		t_bloc*	curr_fuse = NULL;

		while (curr)
		{
			if ((char*)curr + curr->size == curr->next)
			{
				curr->size = curr->size + sizeof(t_bloc) + curr_fuse->size + sizeof(t_bloc);
				curr_fuse = curr->next;
				while ((char*)curr + curr->size == curr_fuse->next)
				{
					curr->size = curr->size + sizeof(t_bloc) + curr_fuse->size + sizeof(t_bloc);
					curr_fuse = curr_fuse->next;
				}
				curr = curr_fuse;
			}
			else
				curr = curr->next;
		}
	}
}

void *malloc(size_t size)
{
	t_bloc *block = NULL;

	if (size == 0)
		return NULL;
	block = find_free_space(size);
	if (!block)
	{
		block = request_space(size);
		if (!block)
			return NULL;
	}
	return (void *)((char *)block + sizeof(t_bloc));
}

int main(void)
{
	char *test = malloc(42);

	if (!test)
		ft_printf("erreur");
	test[41] = 'a';
	return 0;
}
