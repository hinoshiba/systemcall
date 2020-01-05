#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define EXIT_HUP 2
#define OS_SIZE_BLOCK 4096

static void catch_hup(int signo) {
	printf("got a signal HUP. program exit.\n");
	exit(EXIT_HUP);
}

int main(int argc, char **argv) {
	int fd;
	int err;

	int r_cnt;
	int w_cnt;
	char buf[OS_SIZE_BLOCK];

	err = signal(SIGHUP, catch_hup);
	if (err == SIG_ERR) {
		perror(argv[1]);
		return EXIT_FAILURE;
	}
	err = 0;

	if (argc < 2) {
		printf("usage : %s <filepath>\n", argv[0]);
		return EXIT_FAILURE;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		errno = ENOENT;
		perror(argv[1]);
		return EXIT_FAILURE;
	}

	while (1) {
		r_cnt = read(fd, buf, OS_SIZE_BLOCK);
		if (r_cnt == -1) {
			perror(argv[1]);
			return EXIT_FAILURE;
		}
		if (r_cnt == 0) {
			break;
		}

		w_cnt = write(STDOUT_FILENO, buf, r_cnt);
		if (w_cnt == -1) {
			perror(argv[1]);
			return EXIT_FAILURE;
		}
		if (r_cnt != w_cnt) {
			printf("%s, did not match byte of read and write.\n", argv[0]);
			return EXIT_FAILURE;
		}
	}

	close(fd);
	return EXIT_SUCCESS;
}
