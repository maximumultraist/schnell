#include <sys/wait.h>
#include "cp.h"
#include "cat.h"
#include "ls.h"
#include "grep.h"

void freeargs(char *argv[]);

int main (void) {
	char input[1024];

	 while(1) {	// main loop
		int ac = 0;
		char *av[MAX_ARGS];

		for (int i = 0; i < MAX_ARGS; i++){
			if (!(av[i] = calloc(NAME_MAX, sizeof(char)))){
                fprintf(stderr, "memory allocation failure, exiting!");
                exit(ENOMEM);
            }
		}

		memset(input, 0, 1024 * sizeof(char));
		printf("@: ");
		fgets(input, 1024, stdin);
		input[strcspn(input, "\n")] = '\0'; // strip newline character from input

         if (strcmp(input,"exit") == 0)
             break;

		char *temp = strtok(input, " ");
		strncpy(*av, temp, NAME_MAX*sizeof(char));
		while (temp != NULL) {
			temp = strtok(NULL, " ");
			if (temp == NULL)
				break;

			ac++;
            if (ac >= MAX_ARGS)
                break;

			strncpy(av[ac], temp, NAME_MAX*sizeof(char));
		}
		 av[ac+1] = NULL;

		if (strcmp(*av,"cat") == 0) {
			cat(ac, av);
			freeargs(av);
		} else if (strcmp(*av,"ls") == 0) {
			ls(ac, av);
			freeargs(av);
		} else if (strcmp(*av,"cp") == 0) {
			cp(ac, av);
			freeargs(av);
		} else if (strcmp(*av,"grep") == 0) {
			grep(ac, av);
			freeargs(av);
		} else {
			pid_t pid;

			if ((pid = fork()) == -1) { // fork() to create child process, store the status of the fork() in pid
				fprintf(stderr, "Child process creation/fork failed!\n");
			}

			if (pid == 0) { // child process block; if pid == 0 then it's the child process
				execv(av[0], av);
				perror("exec failed!");
				exit(EXIT_FAILURE);
			} else { // parent process block; waits on the return value of the child
				int status;
				waitpid(pid, &status, 0);
			}
		}

	}

	exit(EXIT_SUCCESS);
}

void freeargs(char *argv[]) {
	for (int i = 0; i < MAX_ARGS; i++)
		free(argv[i]);
}
