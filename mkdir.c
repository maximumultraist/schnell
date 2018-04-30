#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> 

mode_t getUMask()
{
    mode_t uMask = umask(0);
    umask (uMask);
    return uMask;
}
int main(int argc, const char *argv[])
{
    char fileName[20];
    scanf("%s", fileName);
    if (mkdir(fileName,0776) == -1) {
        perror(argv[0]);
        exit(EXIT_FAILURE);
    }
    return 0;
}
