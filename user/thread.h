#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int thread_create(void *(*start_routine)(void*), void*);

struct lock_t{
    uint locked;
};