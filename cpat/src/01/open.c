#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char **argv) {
	int fd;
	int errno;

	if (argc < 2) {
		printf("usage : %s <filepath>\n", argv[0]);
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		errno = ENOENT;
		perror(argv[1]);
		return 1;
	}

	close(fd);
	return 0;
}
