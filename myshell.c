#include <sys/wait.h>
#include "cp.h"
#include "cat.h"
#include "ls.h"
#include "grep.h"
#include "sleep.h"
#include "cd.h"
#include "mykill.h"
#include "rmdir.h"
#include "mkdir.h"
#include "stat.h"

/* This #ifndef block is included to add asprintf() support to platforms that do not have it in their C standard library.
 * Even though asprintf() is a non-standard C function, it's extremely useful to include as it greatly simplifies and secures the allocation
 * of memory for strings. Credit goes to: https://github.com/b-k/21st-Century-Examples/blob/master/asprintf.c
 */

#ifndef HAVE_ASPRINTF
#include <stdarg.h>

int asprintf(char** str, char* fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    char one_char[1];
    int len = vsnprintf(one_char, 1, fmt, argp);
    if (len<1) {
        fprintf(stderr, "An encoding error occurred. Setting the input pointer to NULL.\n");
        *str = NULL;
        return len;
    }
    va_end(argp);

    *str = malloc((len+1)*sizeof(char));
    if (*str==NULL) {
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

void freeargs(int argc, char* argv[]); // argument array memory-freeing function

int main(void)
{   // and finally, That Good Shit
    char input[1024]; // allocate a fixed-size character array of 1024 characters for the input string

    while (1) {    // main loop
        int ac = 0;
        char* av[MAX_ARGS];

        memset(input, 0, 1024*sizeof(char)); // zero out the input string
        printf("@: "); // default shell prompt
        fgets(input, 1024, stdin); // read 1024 characters from standard input into the input string
        input[strcspn(input, "\n")] = '\0'; // strip newline character from the input string

        if (strcmp(input, "exit")==0) // exit the loop if the user enters the "exit" command
            break;

        char* temp = strtok(input, " "); // Tokenize the input string using the space character as a delimiter
        asprintf(av, "%s", input); // put first tokenized string into the zeroth position of the argument vector
        while (temp!=NULL) { // Loop to continue tokenizing the input string and filling the argument vector until the input string ends
            temp = strtok(NULL, " ");
            if (temp==NULL)
                break;

            ac++;
            if (ac>=MAX_ARGS)
                break;

            asprintf((av+ac), "%s", temp);
        }

        av[ac+1] = NULL; // null-terminate the argument vector, because C is an old-ass language with strange conventions

        if (strcmp(*av, "cat")==0) {
            cat(ac, av);
            freeargs(ac, av);
        }
        else if (strcmp(*av, "ls")==0) {
            ls(ac, av);
            freeargs(ac, av);
        }
        else if (strcmp(*av, "cp")==0) {
            cp(ac, av);
            freeargs(ac, av);
        }
        else if (strcmp(*av, "grep")==0) {
            grep(ac, av);
            freeargs(ac, av);
        }
        else if (strcmp(*av, "sleep")==0) {
            custom_sleep(ac, av);
            freeargs(ac, av);
        }
        else if (strcmp(*av, "cd") == 0) {
            cd(ac, av);
            freeargs(ac, av);
        }
        else if (strcmp(*av, "kill") == 0) {
            mykill(ac, av);
            freeargs(ac, av);
        }
        else if (strcmp(*av, "rmdir") == 0) {
            myrmdir(ac, av);
            freeargs(ac, av);
        }
        else if (strcmp(*av, "mkdir") == 0) {
            mymkdir(ac, av);
            freeargs(ac, av);
        }
        else if (strcmp(*av, "stat") == 0) {
            mystat(ac, av);
            freeargs(ac, av);
        }
        else {
            pid_t pid;
            int status;

            if ((pid = fork())==-1) { // fork() to create child process, store the status of the fork() in pid
                fprintf(stderr, "Child process creation/fork failed!\n");
            }

            if (pid==0) { // child process block; if pid == 0 then it's the child process
                execvp(av[0], av);
                perror("exec failed!"); // should only get to this point if the execvp() call fails
                exit(EXIT_FAILURE);
            }
            else { // parent process block; waits on the return value of the child
                while (1) {
                    waitpid(pid, &status, WUNTRACED);
                    if (WIFEXITED(status) || WIFSIGNALED(status))
                        break;
                }
            }
        }

    }

    exit(EXIT_SUCCESS);
}

void freeargs(int argc, char** argv)
{
    for (int i = 0; i<=argc; i++)
        free(argv[i]);
}
