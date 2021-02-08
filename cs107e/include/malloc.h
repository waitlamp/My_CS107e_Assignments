#ifndef MALLOC_H
#define MALLOC_H

/*
 * Functions for dynamic allocation.
 *
 * Author: Julie Zelenski <zelenski@cs.stanford.edu>
 * Mon Feb  5 20:02:27 PST 2018
 */
#include <stddef.h> // for size_t


/*
 * Service a dynamic allocation request. Returns the
 * address of a memory block of at least `nybtes` contiguous
 * bytes or NULL if the request cannot be satisifed.
 * The block address is guaranteed to be aligned to an 8-byte boundary.
 * If `nbytes` is 0, malloc returns either NULL or a unique
 * pointer to an allocated block of some minimum size.
 *
 * @param nbytes    requested size in bytes
 * @return          address of memory block of requested size
 *                  or NULL if request cannot be satisifed
 */
void *malloc(size_t nbytes);


/*
 * Deallocate the memory block at address `ptr`.
 *
 * The `ptr` argument is expected to be an address that was
 * previously returned by malloc and has not yet been freed.
 * If this precondition is not satisified, the behavior is undefined.
 * If `ptr` is NULL, the operation does nothing.
 *
 * @param ptr       address of memory block to deallocate
 */
void free(void *ptr);


#endif
