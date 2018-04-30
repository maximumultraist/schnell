#ifndef SCHNELL_RMDIR_H
#define SCHNELL_RMDIR_H
#define _XOPEN_SOURCE 500 // For strange Linux conventions
#include "mycommands.h"
#include <ftw.h>

static int removeDirs(const char *dirName, const struct stat *sbuf, int type, struct FTW *ftwb);
int myrmdir(int argc, char *argv[]);

#endif //SCHNELL_RMDIR_H
