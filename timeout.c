#include "timeout.h"

static struct {
	const char *argv0;
	pid_t pid;
} entry;

static void sigChild(int signum)
{
	assert(signum == SIGCHLD);
}

static int new_child(char *argv[])
{
	if ((entry.pid = fork()) < 0) {
		fprintf(stderr, "%s: Fork failed: %s\n",
			entry.argv0, strerror(errno));
		return -1;
	}
	if (!entry.pid) {
		execvp(argv[0], argv);
		fprintf(stderr, "%s: %s: Exec failed: %s\n",
			entry.argv0, argv[0], strerror(errno));
		_exit(-1);
	}
	return 0;
}

static int kill_child(int signum)
{
	if (kill(entry.pid, signum)) {
		fprintf(stderr, "%s: unable to kill child: %s\n",
			entry.argv0, strerror(errno));
		return 1;
	}
}


int timeout(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: timeout [DURATION] [COMMAND]\n");
        return -1;
    }
    uint32_t duration = (uint32_t)atoi(argv[1]) * 1000000;
	signal(SIGCHLD, &sigChild);
	if (new_child(argv + 2))
		return 1;


	if (usleep(duration)) {
		assert(errno == EINTR);
		kill_child(SIGINT);
	}
	kill_child(SIGTERM);

	return 0;
}