#include "ft_malloc.h"
#include "libft.h"

t_zone *g_zone = NULL;

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

	int * ptr1 = (int *) malloc( sizeof(int) );
	assert( ptr1 != NULL );
	int * ptr2 = (int *) malloc( sizeof(int) );
	assert( ptr2 != NULL );

	(*ptr1) = 10;

	printf("ptr1=%p - ptr2=%p\n", ptr1, ptr2);

	ptr1 = (int *) realloc( ptr1, 10 * sizeof(int) );
	assert( ptr1 != NULL );

	printf( "ptr1=%p - ptr2=%p\n", ptr1, ptr2 );
	printf( "(*ptr1) = %d\n", *ptr1);

	free( ptr1 );
	free( ptr2 );

	/*
		Un petit exemple d'exécution :
			ptr1=004302D0 - ptr2=004302A0
			ptr1=00430260 - ptr2=004302A0
			(*ptr1) = 10
		Pour information, ptr2 a été alloué pour être
		certain que ptr1 ne pourra être réallouer sur place.
	*/

	return 0;
}
