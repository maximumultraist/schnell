#include "mykill.h"

int mykill(int argc, char *argv[]){
    int sig;
    pid_t process;
    if (argc != 2) {
        fprintf(stderr, "Usage: kill <signal number> <process id>\n");
        return -1;
    }
    sig = atoi(argv[1]);
    if (sig < 1 || sig > 34) {
        fprintf(stderr, "Error: invalid signal number specified.\n");
        return -2;
    }
    process = (pid_t)atoi(argv[2]);
    if (kill(process, sig)) {
        fprintf(stderr, "Error: could not kill pid %s\n", argv[2]);
        return -3;
    }

    return 0;
}