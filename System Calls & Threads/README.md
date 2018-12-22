## Backtrace and ps system call
### Backtrace
Added backtrace system call to xv6.  
Interface of this system call: int backtrace();  
Specifically, if the user program invokes this new system call the system call prints all registers of the user program, and then walks the stack frame by frame printing the return addresses saved on the stack on the console.  
  
To call this system call, user program 'bt.c' is implemented.  

Changes are made to files:  
- Makefile
- syscall.h
- syscall.c
- sysproc.c
- usys.S
- user.h

### ps
Added ps tool that lists all processes running on the system.  
For ps, implemented yet another system call getprocinfo() that returns information for a process, with interface: int getprocinfo(int proc_num, struct uproc *up);  

To call this system call, user program 'ps.c' is implemented.  
Required files are updated as above.

## Thread functionality
Extended xv6 with support for POSIX threads.  
For this, three system calls were added:
- thread_create(): to create a kernel thread. Interface: int thread_create(void(*fcn)(void*), void *arg, void*stack)
- thread_join(): to wait for the thread to finish. Interface: int thread_join(void)
- thread_exit(): it allows the thread to exit. Interface: int thread_exit(void)
  
Implemented POSIX-like synchronization primitives: spinlocks and mutexes.  
  
To test thread functionality and syncronization, user program thread.c is implemented.

## References
- [System Calls](https://www.ics.uci.edu/~aburtsev/238P/hw/hw3-system-calls.html)
- [POSIX Threads](https://www.ics.uci.edu/~aburtsev/238P/hw/hw4-threads.html)
