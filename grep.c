#include "grep.h"

int grep(int argc, char *argv[]) {

	char *fn;
	char *pattern;
	FILE *fp;
	size_t n = 0;
	int status;

	pattern = argv[1];

	for (int i = 2; i <= argc; i++) {

		char *line;
		char *needle;
		uint32_t lineno = 1;

		fn = argv[i];

		if ((fp = fopen(fn,"r")) == NULL){
			fprintf(stderr, "file \'%s\' does not exist!\n", fn);
			return -1;
		}

		while((status = getline(&line, &n, fp)) != -1)
		{
			if((needle = strstr(line, pattern)) != NULL) {
				printf("%s, at line %d: %s", fn, lineno, needle);
			}
			lineno++;
		}
	}

	fclose(fp);
	return 0;
}
