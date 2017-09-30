#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  // struct proc *p;
  struct ProcessInfo* processInfoTable;
  getprocs(processInfoTable);
  
  printf(1, "lalala");
  return -1;
}
