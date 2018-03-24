#include "cat.h"

int cat (int argc, char *argv[]) {
	FILE *fp;
	char fname[MAX_NAME], ch;

		strncpy(fname, argv[argc], MAX_NAME);
		fp = fopen(fname, "r");

		if (fp == NULL) {
			printf("%s: No such file or directory\n", fname);
			return 0;
		}
		while((ch = (char) fgetc(fp)) != EOF) {
			putchar(ch);
		}
		fclose(fp);

	return 0;
}
