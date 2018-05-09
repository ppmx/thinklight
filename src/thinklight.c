#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include "thinklight.h"
#include <unistd.h>


static int thinklight_seek_position(int fd);
static int thinklight_morse_character(int fd, char c, unsigned int pause);
static int thinklight_write(int fd, const char value);
static int thinklight_state(int fd);

static int thinklight_morse_character(int fd, char c, unsigned int pause)
{
	/* not implemented yet */
	return -1;
}

static int thinklight_seek_position(int fd)
{
	if (lseek(fd, OFFSET, SEEK_SET) != OFFSET) {
		perror("[!] lseek() failed");
		return -1;
	}

	return 0;
}

static int thinklight_state(int fd)
{
	char buf;

	if (thinklight_seek_position(fd) != 0)
		return -1;

	if (read(fd, (void *) &buf, 1) != 1)
		return -1;

	return (int) buf;
}

static int thinklight_write(int fd, const char value)
{
	if (thinklight_seek_position(fd) != 0)
		return -1;

	if (write(fd, &value, 1) != 1)
		return -1;

	return 0;
}

int thinklight_close(int fd)
{
	if (close(fd) == -1) {
		perror("[!] close(fd) failed");
		return -1;
	}

	return 0;
}

int thinklight_off(int fd)
{
	return thinklight_write(fd, LIGHT_OFF);
}

int thinklight_on(int fd)
{
	return thinklight_write(fd, LIGHT_ON);
}

int thinklight_open(void)
{
	int fd;

	if ((fd = open(API, O_RDWR)) == -1) {
		perror("[!] open(API) failed");
		return -1;
	}

	return fd;
}

int thinklight_morse(int fd, char *buffer, unsigned int pause)
{
	while (*buffer != '\x00') {
		char c = *buffer++;

		if (thinklight_morse_character(fd, c, pause) == -1)
			return -1;

		usleep(pause);
	}

	return 0;
}

