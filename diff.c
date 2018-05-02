/* The program compares two text files specified at the command prompt.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 150

int main(int argc, char *argv[]) {

  FILE *fpread, *fpread2; /* File Pointer Read, File Pointer Read */
  char filebuff[MAXLINE];
  char filebuff2[MAXLINE];
  int var;
  

  if (argc != 3) {
    printf("Usage: %s source destination\n", argv[0]);
    exit(0);
  }

  fpread = fopen(*++argv, "r");/* opens second file which is read */
  if (fpread == NULL) {
    printf("Can't open %s for reading\n", *argv);
    exit(0);
  }

  fpread2 = fopen(*++argv, "r");/* opens third file which is also read */
  if (fpread2 == NULL) {
    printf("Can't open %s for reading\n", *argv);
    exit(0);
  }
  
  while (fgets(filebuff, MAXLINE, fpread) != NULL) { /* put the contents of fpread(second file) into filebuff */
fgets(filebuff2, MAXLINE, fpread2);          /* put the contents of fpread2(third file) into filebuff2 */
var = strcmp(filebuff, filebuff2);           /* compare the two files one line at a time */
if ((var < 0) || (var >0))
     /* var should be 0 if they are the same */
  {
  printf("\nvar:%i\n", var);
  printf("this is where the files do not match:\nfilebuff:%s\n", filebuff);
  printf("filebuff2:%s\n", filebuff2);
  exit(0);
  }
   /* fputs(filebuff, fpread2);                         write the contents of filebuff to fpread2(third file) */
   /* printf("filebuff:\n %s", filebuff);               need to compare 2nd and 3rd file */
   
    
  }
  
 
  fclose(fpread);
  fclose(fpread2);

  return(0);
}