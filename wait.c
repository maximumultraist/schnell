#include "wait.h"
#include <sys/wait.h>

int mywait(int argc, char *argv[]) {
    if (argc != 1) {
        fprintf(stderr, "Usage: wait <process id>\n");
        return -1;
    }
    pid_t pid = (pid_t)atoi(argv[1]);
    int status;

    while (1) {
       if (kill(pid, 0) != -1)
           usleep(200);
       else
           break;
    }

    return 0;
}