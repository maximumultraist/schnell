#include <sys/wait.h>
#include "cp.h"
#include "cat.h"
#include "ls.h"
#include "grep.h"

#ifndef HAVE_ASPRINTF
#include <stdarg.h>

int asprintf(char **str, char* fmt, ...){
	va_list argp;
	va_start(argp, fmt);
	char one_char[1];
	int len = vsnprintf(one_char, 1, fmt, argp);
	if (len < 1){
		fprintf(stderr, "An encoding error occurred. Setting the input pointer to NULL.\n");
		*str = NULL;
		return len;
	}
	va_end(argp);

	*str = malloc((len+1) * sizeof(char));
	if (*str == NULL) {
		fprintf(stderr, "Couldn't allocate %i bytes.\n", len+1);
		return -1;
	}
	va_start(argp, fmt);
	vsnprintf(*str, len+1, fmt, argp);
	va_end(argp);
	return len;
}

#else
#define _GNU_SOURCE

#endif

void freeargs(int argc, char *argv[]);

int main (void) {
	char input[1024];

	 while(1) {	// main loop
		int ac = 0;
		char *av[MAX_ARGS];

		/* for (int i = 0; i < MAX_ARGS; i++){
			if (!(av[i] = calloc(NAME_MAX, sizeof(char)))){
                fprintf(stderr, "memory allocation failure, exiting!");
                exit(ENOMEM);
            }
		} */

		memset(input, 0, 1024 * sizeof(char));
		printf("@: ");
		fgets(input, 1024, stdin);
		input[strcspn(input, "\n")] = '\0'; // strip newline character from input

         if (strcmp(input,"exit") == 0)
             break;

		char *temp = strtok(input, " ");
		//strncpy(*av, temp, NAME_MAX*sizeof(char));
         asprintf(av, "%s", input);
		while (temp != NULL) {
            temp = strtok(NULL, " ");
            if (temp==NULL)
                break;

            ac++;
            if (ac>=MAX_ARGS)
                break;

            asprintf((av+ac), "%s", temp);
        }

		 av[ac+1] = NULL;

		if (strcmp(*av,"cat") == 0) {
			cat(ac, av);
			freeargs(ac, av);
		} else if (strcmp(*av,"ls") == 0) {
			ls(ac, av);
			freeargs(ac, av);
		} else if (strcmp(*av,"cp") == 0) {
			cp(ac, av);
			freeargs(ac, av);
		} else if (strcmp(*av,"grep") == 0) {
			grep(ac, av);
			freeargs(ac, av);
		} else {
			pid_t pid;
            int status;

			if ((pid = fork()) == -1) { // fork() to create child process, store the status of the fork() in pid
				fprintf(stderr, "Child process creation/fork failed!\n");
			}

			if (pid == 0) { // child process block; if pid == 0 then it's the child process
				execvp(av[0], av);
				perror("exec failed!"); // should only get to this point if the execvp() call fails
				exit(EXIT_FAILURE);
			} else { // parent process block; waits on the return value of the child
			 while (1){
			   waitpid(pid, &status, WUNTRACED);
			   if (WIFEXITED(status) || WIFSIGNALED(status))
			   	break;
			 }
			}
		}

	}

	exit(EXIT_SUCCESS);
}

void freeargs(int argc, char** argv) {
	for (int i = 0; i <= argc; i++)
		free(argv[i]);
}
