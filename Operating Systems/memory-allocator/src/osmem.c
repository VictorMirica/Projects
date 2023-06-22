// SPDX-License-Identifier: BSD-3-Clause

#include "osmem.h"
#include "helpers.h"

struct block_meta *head;

struct block_meta *tail;

int first = 1;

// Allocate a new block of memory using mmap
static struct block_meta *allocate_block_map(size_t size)
{
	// Call mmap to allocate a new block of memory
	struct block_meta *block = mmap(NULL, size + sizeof(struct block_meta), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	DIE((void *)block == MAP_FAILED, "mmap");

	// Initialize the block's metadata
	block->size = size;
	block->status = STATUS_MAPPED;
	block->next = NULL;

	return block;
}

// Allocate a new block of memory using brk
static struct block_meta *allocate_block_brk(size_t size)
{
	// Call sbrk to allocate a new block of memory
	struct block_meta *block = NULL;

	if (first == 0) {
		block = (struct block_meta *)sbrk(size + sizeof(struct block_meta));

		 // Initialize the block's metadata
		block->size = size;
		block->status = STATUS_ALLOC;
		block->next = NULL;
	} else {
		block = (struct block_meta *)sbrk(MMAP_THRESHOLD);
		first = 0;

		// Initialize the block's metadata
		block->size = MMAP_THRESHOLD - sizeof(struct block_meta);
		block->status = STATUS_FREE;
		block->next = NULL;
	}
	DIE((void *)block == (void *)-1, "sbrk");

	return block;
}

// Split a block into two blocks
static void split_block(struct block_meta *block, size_t size)
{
	// Create a new block metadata structure after the end of the allocated space
	struct block_meta *new_block = (struct block_meta *)((char *)block + sizeof(struct block_meta) + size);

	new_block->size = block->size - size - sizeof(struct block_meta);
	new_block->status = STATUS_FREE;
	new_block->next = block->next;

	if (new_block->next == NULL)
		tail = new_block;

	// Update the original block's metadata
	block->size = size;
	block->next = new_block;
}

// Coalesce adjacent free blocks
static void coalesce_free_blocks(void)
{
	struct block_meta *block = head;

	while (block != NULL && block->next != NULL) {
		struct block_meta *next = block->next;

		if (block->status == STATUS_FREE && next->status == STATUS_FREE) {
			// Combine the two free blocks into one
			block->size += next->size + sizeof(struct block_meta);
			block->next = next->next;
			if (next == tail)
				tail = block;
		} else {
			block = block->next;
		}
	}
}

// Coalesce current (not necessarily free) block with adjacent free blocks. Used for reallocation
static void *coalesce_blocks(struct block_meta *block, size_t size, void *ptr)
{
	struct block_meta *next = block->next;

	while (next != NULL && next->status == STATUS_FREE) {
		block->size += sizeof(struct block_meta) + next->size;
		block->next = next->next;
		if (next == tail)
			tail = block;

		if (block->size >= size) {
			if (block->size > size + sizeof(struct block_meta))
				split_block(block, size);
			return ptr;
		}

		next = next->next;
	}

	return NULL;
}

static void addToList(struct block_meta *block)
{
	if (head == NULL)
		head = block;
	else
		tail->next = block;
	tail = block;
}

static void *allocate(size_t size, size_t limit)
{
	// Round up size to a multiple of 8
	size = ((size - 1) / 8 + 1) * 8;

	// Coalesce adjacent free blocks
	coalesce_free_blocks();

	struct block_meta *bestFit = NULL;

	if (size + sizeof(struct block_meta) >= limit) {
		// If the requested size is larger than the limit, allocate a new block using mmap
		bestFit = allocate_block_map(size);
	} else {
		// Find the best fitting free block or allocate a new block using brk
		if (first == 1) {
			struct block_meta *block = allocate_block_brk(size);

			addToList(block);
		}

		// Traverse the linked list of memory blocks to find the best fitting free block
		struct block_meta *block = NULL;

		for (block = head; block != NULL; block = block->next)
			if (block->status == STATUS_FREE && block->size >= size)
				if (bestFit == NULL || block->size < bestFit->size)
					bestFit = block;

		if (bestFit == NULL && tail->status == STATUS_FREE) {
			// Expand last block if it is free
			bestFit = (struct block_meta *)sbrk(size - tail->size);
			DIE((void *)bestFit == (void *)-1, "sbrk");

			tail->size = size;
			bestFit = tail;
		}

		if (bestFit != NULL)
			bestFit->status = STATUS_ALLOC;

		// If no free block was found, allocate a new block
		if (bestFit == NULL) {
			bestFit = allocate_block_brk(size);

			addToList(bestFit);
		}

		// If the free block is larger than the requested size, split it into two blocks
		if (bestFit->size > size + sizeof(struct block_meta))
			split_block(bestFit, size);
	}

	// Mark the block as allocated and return a pointer to the allocated space
	return (void *)(bestFit + 1);
}


void *os_malloc(size_t size)
{
	/* TODO: Implement os_malloc */
	// Check if size is zero
	if (size == 0)
		return NULL;

	return allocate(size, MMAP_THRESHOLD);
}

void os_free(void *ptr)
{
	/* TODO: Implement os_free */
	// Check if ptr is NULL
	if (ptr == NULL)
		return;

	// Get the block metadata structure
	struct block_meta *block = (struct block_meta *)ptr - 1;

	// Free the block
	int status = block->status;

	block->status = STATUS_FREE;
	if (status == STATUS_MAPPED) {
		// Unmap the block if it was allocated using mmap
		int check = munmap(block, block->size + sizeof(struct block_meta));

		DIE(check < 0, "munmap");
	}
}

void *os_calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement os_calloc */
	// Check if nmemb or size is zero
	if (nmemb == 0 || size == 0)
		return NULL;

	size_t totalSize = nmemb * size;

	// Round up size to a multiple of 8
	totalSize = ((totalSize - 1) / 8 + 1) * 8;

	void *ptr = allocate(totalSize, sysconf(_SC_PAGESIZE));

	if (ptr != NULL) {
		memset(ptr, 0, totalSize);
		return ptr;
	}

	return NULL;
}

void *os_realloc(void *ptr, size_t size)
{
	/* TODO: Implement os_realloc */
	// Check if ptr is NULL
	if (ptr == NULL)
		return os_malloc(size);

	// Check if size is zero
	if (size == 0) {
		os_free(ptr);
		return NULL;
	}


	// Get the block metadata structure
	struct block_meta *block = (struct block_meta *)ptr - 1;

	// If the block is free, return NULL
	if (block->status == STATUS_FREE)
		return NULL;

	// Round up size to a multiple of 8
	size = ((size - 1) / 8 + 1) * 8;

	// If the block is mapped, allocate a new block and copy the data
	if (block->status == STATUS_MAPPED) {
		void *ret = os_malloc(size);

		if (ret != NULL) {
			if (size > block->size)
				memcpy(ret, ptr, block->size);
			os_free(ptr);
		}
		return ret;
	}

	// If the new size is smaller than the old size, truncate the block
	if (size <= block->size) {
		if (block->size > size + sizeof(struct block_meta))
			split_block(block, size);
		return ptr;
	}

	// Expand the block if possible
	void *ret  = coalesce_blocks(block, size, ptr);

	if (ret != NULL)
		return ret;

	// If the block is the last block, it can be expanded
	if (block->next == NULL)
		block->status = STATUS_FREE;

	// If the block cannot be expanded, allocate a new block and copy the data
	ret = os_malloc(size);

	if (ret != NULL) {
		memcpy(ret, ptr, block->size);
		// Do not free the last block
		if (block->next != NULL)
			os_free(ptr);
		return ret;
	}

	return NULL;
}
