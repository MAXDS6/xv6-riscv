#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int pid = getpid();
    int ppid = getppid();

    printf("Mi PID: %d\n", pid);
    printf("PID de mi padre: %d\n", ppid);

    for(int i = 0; i < 5; i++) {
        int anc = getancestor(i);
        printf("Ancestro %d: %d\n", i, anc);
    }

    exit(0);
}

