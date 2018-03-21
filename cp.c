#include "mycommands.h"

static int buffer_copy(int ifd, int ofd)
{
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

/* Usage: cp FILES... DEST */
int cp(int argc, char *argv[])
{
	int ifd, ofd, ret;

	if (argc != 3) {
		fprintf(stderr, "usage: %s input output\n", argv[0]);
		return 1;
	}

	ifd = open(argv[1], O_RDONLY);
	if (ifd < 0) {
		fprintf(stderr, "%s: %s: %s\n",
			argv[0], argv[1], strerror(errno));
		return 1;
	}
	ofd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (ofd < 0) {
		fprintf(stderr, "%s: %s: %s\n",
			argv[0], argv[2], strerror(errno));
		return 1;
	}

	// ret = mmap_copy(ifd, ofd);
	// if (ret)
		ret = buffer_copy(ifd, ofd);
	if (close(ifd) || close(ofd))
		return 1;
	return ret;
}
