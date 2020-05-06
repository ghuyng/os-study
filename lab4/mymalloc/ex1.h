#ifndef ALIGNED_MALLOC_H
#define ALIGNED_MALLOC_H

void *aligned_malloc(unsigned int bytes, unsigned int align);

void *aligned_free(void *ptr);

#endif
