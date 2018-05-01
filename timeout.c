#include "timeout.h"

#include <sys/types.h>
#include <signal.h>
#include <strings.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


static struct {
	const char *argv0;
	struct timespec duration;
	pid_t pid;
} entry;


static int parse(const char *input)
{
	char *ptr;
	time_t secs;
	double dur;

	dur = strtod(input, &ptr);
	if (!*input || errno) {
		fprintf(stderr, "%s: invalid duration: %s\n",
			entry.argv0, ptr);
		return -1;
	}

	secs = (time_t)dur;
	entry.duration.tv_sec = secs; // Whole seconds
	entry.duration.tv_nsec = (dur - secs); //Nanoseconds
	return 0;
}

static void sigChild(int signum)
{
	assert(signum == SIGCHLD);
	exit(0);
}

static int new_child(char *argv[])
{
	if ((entry.pid = fork()) < 0) {
		fprintf(stderr, "%s: Cannot fork: %s\n",
			entry.argv0, strerror(errno));
		return -1;
	}
	if (!entry.pid) {
		execvp(argv[0], argv);
		fprintf(stderr, "%s: %s: Cannot exec: %s\n",
			entry.argv0, argv[0], strerror(errno));
		_exit(-1);
	}
	return 0;
}

static void kill_child(int signum)
{
	if (kill(entry.pid, signum)) {
		fprintf(stderr, "%s: unable to kill child: %s\n",
			entry.argv0, strerror(errno));
		exit(1);
	}
}

/* Usage: timeout [DURATION] [COMMAND] */
int main(int argc, char *argv[])
{
	signal(SIGCHLD, &sigChild);
	if (parse(argv[1]))
		return 1;
	if (new_child(argv + 2))
		return 1;

	/* Wait then terminate */
	if (nanosleep(&entry.duration, NULL)) {
		assert(errno == EINTR);
		kill_child(SIGINT);
	}
	kill_child(SIGTERM);

	/* Finish it off it's still around */
	entry.duration.tv_sec = 5;
	nanosleep(&entry.duration, NULL);
	kill_child(SIGKILL);
	return 0;
}