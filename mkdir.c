#include "mkdir.h"

int mymkdir(int argc, const char *argv[]) {
    if (argc != 1) {
        fprintf(stderr, "Usage: mkdir <directory name>\n");
        return -1;
    }
    char fileName[20];
    scanf("%s", fileName);
    if (mkdir(fileName,0776) == -1) {
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }
    return 0;
}

mode_t getUMask() {
    mode_t uMask = umask(0);
    umask (uMask);
    return uMask;
}