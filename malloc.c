#include <malloc.h>

t_block		*g_base[3];

void 	*get_new_zone(t_block **last, size_t size, int type_zone)
{
	t_block		*b;

	if (size <= 0)
	{
		MALLOC_DEBUG("Can't get zone with 0 size");
		return (NULL);
	}
	else if (type_zone == TINY)
	{
		MALLOC_DEBUG("Get zone for TINY");
		size = TINY_ZONE_SIZE;
	}
	else if (type_zone == SMALL)
	{
		MALLOC_DEBUG("Get zone for SMALL");
		size = SMALL_ZONE_SIZE;
	}
	else
		MALLOC_DEBUG("Get zone for LARGE");
	b = extend_heap(last, size, type_zone);
	if (!b)
		return (NULL);
	g_base[type_zone] = b;
	return (b);
}

void *get_block(t_block **last, size_t size, int type_zone)
{
	t_block		*b;

	if (*last == NULL)
		get_new_zone(last, size, type_zone);
	b = find_block(last, size, type_zone);
	printf("find %p\n", b);
	if (b)
	{
		if ((b->size - size) >= (BLOCK_SIZE + 4))
			split_block(b, size);
		// b->flag.free = 0;
	}
	return (b);
}

void 	*malloc(size_t size)
{
	t_block		*b;
	t_block		*last;

	printf("-- %s: %ld --\n", "new malloc", size);
	if (size <= 0)
	{
		MALLOC_DEBUG("size <= 0 -> return NULL");
		return (NULL);
	}
	else if (size <= TINY_ALLOC_SIZE)
	{
		MALLOC_DEBUG("Malloc to TINY_ZONE");
		last = g_base[TINY];
		printf("last %p\n", last);
		b = get_block(&last, size, TINY);
	}
	else if (size <= SMALL_ALLOC_SIZE)
	{
		MALLOC_DEBUG("Malloc to SMALL_ZONE");
		last = g_base[SMALL];
		b = get_block(&last, size, SMALL);
	}
	else
	{
		MALLOC_DEBUG("Malloc to LARGE_ZONE");
		last = g_base[LARGE];
		return (NULL);
	}
	return (b->data);
}
