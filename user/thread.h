#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

struct lock_t{
    uint is_locked;
};