//Created by Priyanka Goyal

#include "types.h"
#include "stat.h"
#include "user.h"

char *p_states[] = {"UNUSED", "EMBRYO", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"};

struct uproc{
    char p_name[16];
    int pid;
    int ppid;
    uint p_memsize;
    int p_state;
    int wait_on_channel;
    int killed;
};

void
getAllProcessInfo()
{
    struct uproc upc;
    int i = 0;

    printf(1, "P_Name\tPid\tPpid\tP_MemorySize\t\tP_State\t\tWaitingOnChannel\tKilled\n");
    printf(1, "==========================================================================================\n");

    //max number of processes = NPROC which is 64
    for (i=0; i<64; i++){
        getprocinfo(i, &upc);
        printf(1, "%s\t%d\t%d\t%d\t\t\t%s\t\t%d\t\t%d\n",upc.p_name, upc.pid, upc.ppid, upc.p_memsize, p_states[upc.p_state], upc.wait_on_channel, upc.killed);
    }
    exit();
}

int
main(int argc, char *argv[])
{
  getAllProcessInfo();
  exit();
}
