#include "user/thread.h"
#define PGSIZE 4096

int thread_create(void *(*start_routine)(void*), void *arg){
  //allocate user stack in advance
    void *stack = malloc(PGSIZE);
    int size = 8;
    int tid = clone(stack, size);
  // only the child thread will launch start_routine
    if(tid == 0){
      (*start_routine)(arg);
    }
    return tid;
}

void lock_acquire(struct lock_t *lk)
{
    // On RISC-V, sync_lock_test_and_set turns into an atomic swap:
  //   a5 = 1
  //   s1 = &lk->locked
  //   amoswap.w.aq a5, a5, (s1)
  while(__sync_lock_test_and_set(&lk->locked, 1) != 0)
    ;

  // Tell the C compiler and the processor to not move loads or stores
  // past this point, to ensure that the critical section's memory
  // references happen strictly after the lock is acquired.
  // On RISC-V, this emits a fence instruction.
  __sync_synchronize();
}

void lock_release(struct lock_t *lk)
{
	// Tell the C compiler and the CPU to not move loads or stores
  // past this point, to ensure that all the stores in the critical
  // section are visible to other CPUs before the lock is released,
  // and that loads in the critical section occur strictly before
  // the lock is released.
  // On RISC-V, this emits a fence instruction.
  __sync_synchronize();

  // Release the lock, equivalent to lk->locked = 0.
  // This code doesn't use a C assignment, since the C standard
  // implies that an assignment might be implemented with
  // multiple store instructions.
  // On RISC-V, sync_lock_release turns into an atomic swap:
  //   s1 = &lk->locked
  //   amoswap.w zero, zero, (s1)
  __sync_lock_release(&lk->locked);

}

void lock_init(struct lock_t *lk)
{
	lk->locked = 0;
}