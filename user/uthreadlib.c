#include "types.h"
#include "user.h"
#include "x86.h"

#define PGSIZE 4096

int
thread_create(void (*start_routine)(void*), void* arg)
{
  void* stack = malloc(PGSIZE*2); // allocate 2 pages of space
  if((uint)stack % PGSIZE) {
    // make sure that stack is page-aligned
    stack = stack + (PGSIZE - (uint)stack % PGSIZE);
  }
  int tid = clone(start_routine, arg, stack);
  return tid;
}

int
thread_join(int pid)
{
  int ustack;
  if ((ustack = find_ustack(pid)) < 0) {
    return -1;
  }
  free((void*)ustack);
  return join(pid);
}

void lock_acquire(lock_t* lock) {
  // xchg put value into address
  while(xchg(lock, 1) != 0);
}

void lock_release(lock_t* lock) {
  xchg(lock, 0);
}

void lock_init(lock_t* lock) {
  *lock = 0;
}
