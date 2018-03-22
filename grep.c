#include<stdio.h>
#include<string.h>

int main(int argc,char *argv[]) {

	char *fn;
	char *pattern;
	char *buff[200];
	FILE *fp;

	pattern = argv[1];
	fn = argv[2];

	fp=fopen(fn,"r");

	while(!feof(fp))
	{
		fgets(buff,1000,fp);
		if(strstr(buff,pattern)) {
		  printf("%s",buff);
		}
		fclose(fp);
	}
}