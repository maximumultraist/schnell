#include "mkdir.h"

int mymkdir(int argc, char *argv[]) {
    if (argc != 1) {
        fprintf(stderr, "Usage: mkdir <directory name>\n");
        return -1;
    }

    if (mkdir(argv[1],0776) == -1) {
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }
    return 0;
}