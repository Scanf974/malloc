#include <malloc_helpers.h>

void 	*realloc(void *ptr, size_t size)
{
	size_t	align_size;
	t_block	*b;
	void	*newp;

	align_size = ALIGN4(size);
	if (!ptr)
		return malloc(size);
	if (valid_addr(ptr))
	{
		if (size <= 0)
			return (ptr);
		b = ptr - BLOCK_SIZE;
		printf("%lu, %lu\n", align_size, b->size + b->rest);
		if (align_size <= b->size + b->rest)
		{
			b->rest = b->size + b->rest - size;
			b->size = size;
			split_block(b, size);
			return (b);
		}
		else
		{
			// copy
			newp = malloc(size);
			free(ptr);
			return (ptr);
		}
	}
	return (NULL);
}
