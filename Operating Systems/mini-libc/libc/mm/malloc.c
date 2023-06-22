// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */
    if (size == 0) {
        return NULL;
    }

	void* ret = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	mem_list_add(ret, size);

    return ret;
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
    if (nmemb == 0 || size == 0)
        return NULL;

    void* ret = malloc(nmemb * size);
    if (ret != NULL) {  
		memset(ret, 0, nmemb * size);
		return ret;
    }

	return NULL;
}

void free(void *ptr)
{
	/* TODO: Implement free(). */
	if (ptr == NULL)
        return;

    struct mem_list* item = mem_list_find(ptr);
    if (item == NULL)
        return;

    munmap(ptr, item->len);
    mem_list_del(ptr);
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
	if (ptr == NULL)
        return malloc(size);

    if (size == 0) {
        free(ptr);
        return NULL;
    }

    struct mem_list *item = mem_list_find(ptr);
    if (item == NULL)
        return NULL;

    if (size <= item->len)
        return ptr;

    void *ret = malloc(size);
    if (ret != NULL) {
		memcpy(ret, ptr, item->len);
    	free(ptr);
    	return ret;
    }

	return NULL;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
    void *ret = realloc(ptr, nmemb * size);

	if (ret != NULL)
		return ret;

	return NULL;
}
