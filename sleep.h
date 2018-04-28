#ifndef SCHNELL_SLEEP_H
#define SCHNELL_SLEEP_H

#include "mycommands.h"
#include <time.h>

int custom_sleep (int argc, char *argv[]);
static int parse(struct timespec *mytime, const char *input);

#endif //SCHNELL_SLEEP_H
