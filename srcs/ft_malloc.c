#include "ft_malloc.h"
#include "libft.h"

t_zone *g_zone = NULL;

void free(void *ptr)
{
	if (!ptr)
		return NULL;
	// determiner la zone memoire de ptr dans g_zone
	// les cas de free :
	// si ptr fais la taille d'un TINY ou SMALL faire munmap
	// si ptr est un LARGE faire munmap
	// sinon l'inserer dans la free list
	// bonus : fusionner les zones libres adjacents
	// regarder si les 
}

void *malloc(size_t size)
{
	t_bloc *block;

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
