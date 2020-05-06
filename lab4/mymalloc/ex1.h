#ifndef ALIGNED_MALLOC_H
#define ALIGNED_MALLOC_H

void *aligned_malloc(unsigned int bytes, unsigned int align);

//void *aligned_malloc(size_t bytes, size_t align);

void aligned_free(void *ptr);

#endif
