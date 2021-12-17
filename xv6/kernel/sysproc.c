#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include "pstat.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

/* The following code is added/modified by Mehroos Ali and mxa200089.
   system call implementation function to add/update total tickets for a process.
*/

int 
sys_settickets(void)
{
  int number_of_tickets;
  argint(0, &number_of_tickets);
  if(number_of_tickets <= 0)  
    return -1;

  proc->tickets = number_of_tickets;

  return 0;
}
/* End of added code  */

/* The following code is added/modified by Mehroos Ali and mxa200089.
   system call implementation function to get information about all running processes.
*/
int 
sys_getpinfo(void)
{
  struct proc *p;

  struct pstat *pst;
  argptr(0,(void*)&pst,sizeof(*pst));
  if(pst==NULL)
    return -1;

  acquire(&ptable.lock);

  int i = 0;
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    pst->inuse[i] = p->inuse; // whether this slot of the process table is in use (1 or 0)
    pst->tickets[i] = p->tickets; // the number of tickets this process has
    pst->pid[i] = p->pid; // the PID of each process
    pst->ticks[i] = p->ticks; // the number of ticks each process has accumulated
    i++;
  }
  release(&ptable.lock);
  return 0;
}
/* End of added code  */

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
extern int count;
int 
sys_getreadcount(void){
return count;
}
