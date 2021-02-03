#pragma once
#include "malloc.h"
void *ref_malloc(size_t nbytes);
void ref_free(void *ptr);
void *ref_realloc(void *ptr, size_t new_size)  __attribute__ ((warn_unused_result));
