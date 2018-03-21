#include "mycommands.h"
#define fileNameSizeMax 255
/*
* Made fileNameSizeMac global to the function bc it 
* was unhappy declaring it in main
*/

int cat (int argc, char *argv[]) {
	FILE *fp;
	char fileName[fileNameSizeMax], ch;
	int i;

	if (argc < 1) {
		printf("Usage mycat <filename> \n");
		return 0;
	}
	for (i = 1; i <= argc; i++) {
		strncpy(fileName, argv[i], fileNameSizeMax);
		fp = fopen(fileName, "r");

		if (fp == NULL) {
			printf("%s: No such file or directory\n", fileName);
			return 0;
		}
		while((ch = fgetc(fp)) != EOF) {
			putchar(ch);
		}
		fclose(fp);
	}
	return 0;
}
