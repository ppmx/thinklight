#include <stdio.h>
#include <stdlib.h>
#include "thinklight.h"
#include <unistd.h>

int main(int argc, char **argv)
{
	int fd;
	unsigned int pause = 500000;

	if (argc != 2 && argc != 3)
		return printf("Usage: %s <string> [pause]\n", argv[0]);

	if (argc == 3)
		pause = (unsigned int) atoi(argv[2]);

	if ((fd = thinklight_open()) == -1)
		return -1;

	if (thinklight_morse(fd, argv[1], pause) == -1)
		return thinklight_close(fd);

	return thinklight_close(fd);
}

