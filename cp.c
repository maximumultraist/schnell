#include "cp.h"

static int copy_jank(int ifd, int ofd);

int cp(int argc, char *argv[])
{
	int ifd, ofd, ret;

	if ((ifd = open(argv[1], O_RDONLY)) < 0) {
		fprintf(stderr, strerror(errno));
		return -1;
	}

	if ((ofd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0777)) < 0) {
		fprintf(stderr, strerror(errno));
		return -2;
	}

	ret = copy_jank(ifd, ofd);

	if (close(ifd) || close(ofd))
		return 1;
	return ret;
}

static int copy_jank(int ifd, int ofd) {
	char buf[4096];
	ssize_t len;

	do {
		len = read(ifd, buf, sizeof(buf));
		if (len < 0)
			return 1;
		else if (len == 0)
			return 0;
		if (write(ofd, buf, len) != len)
			return 1;
	} while (len);
	return 0;
}
