#include "env.h"

int myenv(char *envp[]) {
    for (char **environ = envp; *environ != NULL; environ++) {
        printf("%s\n", *environ);
    }
}