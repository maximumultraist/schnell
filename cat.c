#include "cat.h"

int cat (int argc, char *argv[]) {
	FILE *fp;
	char fname[NAME_MAX], ch;

		strncpy(fname, argv[argc], NAME_MAX);
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
