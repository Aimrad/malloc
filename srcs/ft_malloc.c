#include "ft_malloc.h"

void	*init_zone()
{
	size_t len = 100 * (128 + sizeof(t_bloc));
	size_t page_size = sysconf(_SC_PAGE_SIZE);

	// t_zone  newZone = mmap(NULL, 100 * (128 +));
	// mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0);
}