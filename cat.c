#include "cp.h"

int cat (int argc, char *argv[]) {
	FILE *fp;
	char fileName[NAME_MAX], ch;

	if (argc < 1) {
		printf("Usage mycat <filename> \n");
		return 0;
	}
		strncpy(fileName, argv[1], NAME_MAX);
		fp = fopen(fileName, "r");

		if (fp == NULL) {
			printf("%s: No such file or directory\n", fileName);
			return 0;
		}
		while((ch = fgetc(fp)) != EOF) {
			putchar(ch);
		}
		fclose(fp);

	return 0;
}
