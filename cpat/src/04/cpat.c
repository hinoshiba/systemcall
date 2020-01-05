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
	int r_fd;
	int w_fd;
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
		printf("usage : %s <source file> [<write file>]\n", argv[0]);
		return EXIT_FAILURE;
	}

	r_fd = open(argv[1], O_RDONLY);
	if (r_fd == -1) {
		errno = ENOENT;
		perror(argv[1]);
		return EXIT_FAILURE;
	}

	w_fd = STDOUT_FILENO;
	if (argc == 3) {
		w_fd = open(argv[2], O_WRONLY|O_CREAT|O_EXCL, 0600);
		if (w_fd == -1) {
			perror(argv[2]);
			return EXIT_FAILURE;
		}
	}

	while (1) {
		r_cnt = read(r_fd, buf, OS_SIZE_BLOCK);
		if (r_cnt == -1) {
			perror(argv[1]);
			return EXIT_FAILURE;
		}
		if (r_cnt == 0) {
			break;
		}

		w_cnt = write(w_fd, buf, r_cnt);
		if (w_cnt == -1) {
			perror(argv[1]);
			return EXIT_FAILURE;
		}
		if (r_cnt != w_cnt) {
			printf("%s, did not match byte of read and write.\n", argv[0]);
			return EXIT_FAILURE;
		}
	}

	close(w_fd);
	close(r_fd);
	return EXIT_SUCCESS;
}
