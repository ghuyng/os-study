#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_malloc.h"

/*This is double linked-list to manage free-block*/
typedef struct block{
    size_t size;
    struct block *next;
    struct block *prev;
} block_t;

/*Head of the free-block linked-list*/
static block_t *head = NULL;


/*This function used to split the block pointed by *ptr                                   */
/*into 2 blocks with 1 block = size and return pointer to the split point                 */
block_t *split(block_t * ptr, size_t size)
{
    block_t *newptr = (block_t *)((size_t)ptr + size + sizeof(block_t));
    newptr->size = ptr->size - (size + sizeof(block_t));
    ptr->size = size;
    return newptr;
}

/*This function adds memory block to free_list */
void add_to_freelist(block_t *block)
{
    /*This list is order by address*/
    block->prev = NULL;
    block->next = NULL;
    if(!head || (size_t)head > (size_t)block)
    {
        /*This block should be at the head of free_list*/
        if(head)
            head->prev = block;

        block->next = head;
        head = block;
    }
    else
    {
        /*Find the position to store the block in the free_list*/
        block_t *ptr = head;
        while(ptr->next && (size_t)ptr < (size_t)block)
            ptr = ptr->next;

        block->next = ptr->next;
        block->prev = ptr;
        ptr->next = block;
    }
}

/*This function removes the memory block from the free_list*/
void remove_from_freelist(block_t *block)
{
    if (block->prev == NULL) //block is head
        head = block->next;
    else
        block->prev->next = block->next;
    if (block->next)
        block->next->prev = block->prev;
}

/*This function is used to merge the continuous free blocks in the list  */
/*and the free block that ends at the heap_brk will be returned to the OS*/
void optimize_freelist()
{
    /*Get the endpoint of the Heap*/
    size_t heap_brk = (size_t)sbrk(0);
    block_t *curr = head;

    /*Scan through the free_list and merge continuos blocks*/
    while(curr->next)
    {
        size_t curr_end = (size_t)curr + curr->size + sizeof(block_t);
        if(curr_end == (size_t)curr->next)
        {
            /*Found two continuos blocks, merge them*/
            curr->size += curr->next->size + sizeof(block_t);
            curr->next = curr->next->next;
            if(curr->next)
                curr->next->prev = curr;
            else
                break;
        }
        curr = curr->next;
    }

    /*If the last free-block is end at the heap_brk then  */
    /*we will set the brk to realease the memory to the OS*/
    size_t curr_end = (size_t)curr + curr->size + sizeof(block_t);
    if(curr_end == heap_brk)
    {
        remove_from_freelist(curr);
        if(brk((void*)curr) != 0)
        {
            printf("error while trying brk");
            return;
        }
    }
}

    

void *my_malloc(size_t size)
{
    void *block_mem;
    block_t *ptr, *newptr;

    /*We will allocate memory for user's size and block_t to store information to aligned_free*/
    size_t alloc_size = size + sizeof(block_t);
    ptr = head;

    /*Loop through the free-list to find free_block that large enough*/
    /*This is First-Fit algorithm                                    */
    while(ptr)
    {
        if(ptr->size >= size)// Found the large enough block
        { 
            remove_from_freelist(ptr);
            block_mem = (void*)((size_t)ptr + sizeof(block_t));
            if (ptr->size == size) //Found the perfect fit block
                return block_mem;

            /*If the block is bigger than needed size,         */
            /* split it and store the remain block to free_list*/
            newptr = split(ptr, size);
            add_to_freelist(newptr);
            return block_mem;
        }
        ptr = ptr->next;
    }
    
    /*No free_block that fit the requested size found*/
    /*We ask the OS for more heap_mem by using sbrk()*/
    ptr = (block_t *)sbrk(alloc_size);
    if(!ptr)
        return NULL;

    ptr->next = NULL;
    ptr->prev = NULL;
    ptr->size = size;
    return (void*)((size_t)ptr + sizeof(block_t));
    
}            

void my_free(void *ptr)
{
    if (!ptr)
        return;
    /*Get the pointer to the begin of the block*/
    void *block_ptr = (void*)((size_t)ptr - sizeof(block_t));
    add_to_freelist(block_ptr);
    optimize_freelist();
}
