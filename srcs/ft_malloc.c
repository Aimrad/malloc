#include "ft_malloc.h"

t_zone *g_zone = NULL;

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
