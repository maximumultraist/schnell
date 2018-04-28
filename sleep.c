#include "sleep.h"

int custom_sleep(int argc, char *argv[]) {
    struct timespec mytime;
    if (argc != 1){
        fprintf(stderr, "Error: not enough arguments specified.");
        return -1;
    }

    if (parse(&mytime, argv[1]) == -1){
        fprintf(stderr, "Error: couldn't parse supplied time \'%s\'.", argv[1]);
        return -1;
    }

    if (nanosleep(&mytime, NULL)){
        fprintf(stderr, "Error: could not sleep: %s", strerror(errno));
        return -2;
    }
    return 0;
}

static int parse(struct timespec *mytime, const char *input) {
    char *end;
    time_t interval;
    int scalar;
    double val;

    val = strtod(input, &end);

    if (!*input || errno || val < 0)
        return -1;

    if (!*end || strcmp(end, "s"))
        scalar = 1;
    else if (strcmp(end, "m"))
        scalar = 60;
    else if (strcmp(end, "h"))
        scalar = 60 * 60;
    else
        return -1;

    interval = (time_t)val;
    mytime->tv_sec = interval * scalar;
    mytime->tv_nsec = (val - interval) * 1e9;

    return 0;
}

