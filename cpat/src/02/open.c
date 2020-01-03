#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>

#define EXIT_HUP 2

static void catch_hup(int signo) {
	printf("got a signal HUP. program exit.\n");
	exit(EXIT_HUP);
}

int main(int argc, char **argv) {
	int fd;
	int errno;

	errno = signal(SIGHUP, catch_hup);
	if (errno == SIG_ERR) {
		perror(argv[1]);
		return EXIT_FAILURE;
	}
	errno = 0;

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

	sleep(30); //hup test timer //kill -HUP <mine process id>

	close(fd);
	return EXIT_SUCCESS;
}
