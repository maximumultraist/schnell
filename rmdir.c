#include "rmdir.h"

int myrmdir(int argc, char *argv[]) //mainly detects errors in inputs or directories
{
    if (argc != 2)
    {
        printf("Did not enter directory or path\n");
        exit(1);
    }
    if (nftw(argv[1], removeDirs,10, FTW_DEPTH|FTW_MOUNT|FTW_PHYS) < 0)
    {
        perror("NOT A VALID DIRECTORY");
        exit(1);
    }
    return 0;
}

static int removeDirs(const char *dirName, const struct stat *sbuf, int type, struct FTW *ftwb)
{
    if(remove(dirName) < 0) //catches errors with directory names
    {
        perror("REMOVAL ERROR");
        return -1;
    }
    return 0;
}