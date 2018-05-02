#include "diff.h"

#define MAXLINE 150

int diff(int argc, char *argv[]) {

  FILE *file1, *file2;
  char filebuff[MAXLINE];
  char filebuff2[MAXLINE];
  int var;
  

  if (argc != 2) {
    printf("Usage: %s source destination\n", argv[0]);
    return -1;
  }

  file1 = fopen(*++argv, "r");
  if (file1 == NULL) {
    printf("Can't open %s for reading\n", *argv);
    return -2;
  }

  file2 = fopen(*++argv, "r");
  if (file2 == NULL) {
    printf("Can't open %s for reading\n", *argv);
    return -3;
  }
  
  while (fgets(filebuff, MAXLINE, file1) != NULL) {
fgets(filebuff2, MAXLINE, file2);
var = strcmp(filebuff, filebuff2);
if ((var < 0) || (var >0))

  {
  printf("\nvar:%i\n", var);
  printf("this is where the files do not match:\nfilebuff:%s\n", filebuff);
  printf("filebuff2:%s\n", filebuff2);
  }
   
    
  }
  
 
  fclose(file1);
  fclose(file2);

  return 0;
}