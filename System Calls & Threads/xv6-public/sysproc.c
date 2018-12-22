#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

//added by Priyanka Goyal
//#include "proc.c"

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
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
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
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

//backtrace system call - added by Priyanka Goyal
int
sys_backtrace(void)
{
    int retAddrNum = 1;
    uint ebp, retAddr;  //to store ebp and return address value

    struct trapframe *tf = myproc()->tf;    //store trapframe of current process

    //printing registers pushed by pusha
    cprintf("edi: 0x%x\n", tf->edi);
    cprintf("esi: 0x%x\n", tf->esi);
    cprintf("ebp: 0x%x\n", tf->ebp);
    cprintf("oesp: 0x%x\n", tf->oesp);
    cprintf("ebx: 0x%x\n", tf->ebx);
    cprintf("edx: 0x%x\n", tf->edx);
    cprintf("ecx: 0x%x\n", tf->ecx);
    cprintf("eax: 0x%x\n", tf->eax);
    
    //printing other registers
    cprintf("eip: 0x%x\n", tf->eip);    //instruction pointer
    cprintf("eflags: 0x%x\n", tf->eflags);  
    cprintf("esp: 0x%x\n", tf->esp);    //stack pointer
    
    //print all return addresses
    ebp = tf->ebp;
    retAddr = *(uint *) (ebp+4);    //first return address on stack

    //loop till we get fake return address
    while (retAddr != (uint)-1){
        cprintf("#%d\t0x%x\n", retAddrNum, retAddr);
        retAddrNum++;
        ebp = *(uint *)ebp;
        retAddr = *(uint *) (ebp+4);
    }
    cprintf("#%d\t0x%x\n", retAddrNum, retAddr);    //print fake return address

    return 0;
}

/*
//added by Priyanka Goyal
int
getprocinfo (int process_num, struct uproc *upc)
{
    struct proc *p;

    //If process number is not valid, return -1
    if (process_num >= NPROC || process_num<0){
        return -1;
    }
    
    //store refernce of process corresponding to process_num
    p = &ptable.proc[process_num];

    memset(upc, 0, sizeof(struct uproc));
    memmove(upc->p_name, p->name, 16);  //copy p->name to upc->p_name

    //copy other process info like pid etc to uproc corresponding fields
    upc->pid = p->pid;
    upc->ppid = p->parent->pid;
    upc->p_state = p->state;
    upc->p_memsize = p->sz;
    upc->killed = p->killed;

    //If process is waiting on some channel, set wait on channel to 1, else 0
    if (p->chan){
        upc->wait_on_channel = 1;
    }
    else{
        upc->wait_on_channel = 0;
    }
    
    return 0;
}
*/

//added by Priyanka Goyal
int
sys_getprocinfo()
{
    struct uproc *upc;
    int process_num, upc_size = sizeof(struct uproc);
    
    //take arguments from user space
    if ((argint(0, &process_num) < 0) || (argptr(1, (char **)&upc, upc_size) < 0)){
        return -1;
    }
    
    //call getprocinfo with user arguments
    return getprocinfo(process_num, upc);
}

int
sys_thread_create(void)
{
  int func, arg, stack;

  if ((argint(0, &func) < 0) || (argint(1, &arg) < 0)
     || (argint(2, &stack) < 0))
     return -1;

  return thread_create((void *)func, (void *)arg, (void *)stack);
}

int sys_thread_join(void)
{

  return thread_join();
}

void sys_thread_exit(void)
{
    return thread_exit();
}
