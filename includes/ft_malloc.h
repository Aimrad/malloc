#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# define TINY_MAX 128
# define SMALL_MAX 1024

# include <err.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

typedef enum zone_type
{
	TINY,
	SMALL,
	LARGE
} t_type;

typedef struct bloc_header
{
	bool				is_free;
	size_t				size;
	char				padding[8];
	struct bloc_header	*next;
} t_bloc;

typedef struct zone_header
{
	t_type				type;
	size_t				size;
	t_bloc				*free_list;
	struct zone_header	*next;
} t_zone;

extern t_zone *g_zone;

// # ====================================================== #
// |														|
// |					ft_malloc_alloc.c					|
// |														|
// # ====================================================== #

t_type	get_zone_type(size_t size);
size_t	round_up_page_size(size_t size);
t_bloc	*allocate_from_zone(t_type type, size_t size);
t_bloc	*allocate_large(size_t size);
t_bloc	*request_space(size_t size);

// # ====================================================== #
// |														|
// |					ft_malloc_free.c					|
// |														|
// # ====================================================== #

t_bloc *find_bloc_in_zones(void *ptr, t_zone **found_zone);

// # ====================================================== #
// |														|
// |					ft_malloc_utils.c					|
// |														|
// # ====================================================== #

size_t 	get_data_size(t_type type);
t_bloc	*split_block(t_bloc *bloc, size_t size);
void	insert_bloc(t_zone *zone, t_bloc *insert);
t_bloc	*find_free_space(size_t size);

// # ====================================================== #
// |														|
// |					ft_malloc.c							|
// |														|
// # ====================================================== #

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

#endif