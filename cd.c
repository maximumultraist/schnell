#include "cd.h"

int cd(int argc, char *argv[]){
    if ((argv[1] == NULL) || (strcmp(argv[1], "~") == 0) || (strcmp(argv[1], "~/") == 0))
        chdir(getenv("HOME"));
    else if (chdir(argv[1]) < 0) {
        fprintf(stderr, "cd: no such directory \'%s\'", argv[1]);
        return -1;
    }
    return 0;
}