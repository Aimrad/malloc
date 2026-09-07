#include "ft_malloc.h"
#include "libft.h"

static char *get_zone_name(t_type type)
{
	if (type == TINY)
		return "TINY";
	if (type == SMALL)
		return "SMALL";
	return "LARGE";
}

static size_t print_block(t_bloc *block)
{
	char *start = (char *)block + sizeof(t_bloc);
	char *end = (char *)block + block->size;
	size_t size = block->size - sizeof(t_bloc);

	if (!block->is_free)
		ft_printf("%p - %p : %d bytes\n", start, end, (int)size);
	return block->is_free ? 0 : size;
}

static size_t print_zone_blocks(t_zone *zone)
{
	t_bloc *block = (t_bloc *)((char *)zone + sizeof(t_zone));
	char *zone_end = (char *)zone + zone->size;
	size_t total = 0;

	while ((char *)block < zone_end)
	{
		total += print_block(block);
		block = (t_bloc *)((char *)block + block->size);
	}
	return total;
}

static size_t print_zone(t_zone *zone)
{
	ft_printf("%s : %p\n", get_zone_name(zone->type), zone);
	return print_zone_blocks(zone);
}

void show_alloc_mem(void)
{
	t_zone *zone = g_zone;
	size_t total = 0;

	while (zone)
	{
		total += print_zone(zone);
		zone = zone->next;
	}
	ft_printf("Total : %d bytes\n", (int)total);
}