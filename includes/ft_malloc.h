#ifndef FT_MALLOC_H
# define FT_MALLOC_H

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

typedef enum zone_type
{
	TINY,
	SMALL,
	LARGE
}	t_type;

typedef struct bloc_header
{
	bool	is_free;
	size_t	size;
	t_bloc	*next;
}	t_bloc;

typedef struct zone_header
{
	t_type	type;
	size_t		size;
	t_bloc		*bloc;
	t_zone		*next;
}	t_zone;

t_zone	*zoneList = NULL;

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

#endif