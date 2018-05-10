#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include "thinklight.h"
#include <unistd.h>

static int thinklight_seek_position(int fd);
static int thinklight_morse_character(int fd, char c, unsigned int pause);
static int thinklight_write(int fd, const char value);
static int thinklight_morse_blink(int fd, unsigned int pause);

static int thinklight_morse_blink(int fd, unsigned int pause)
{
	if (thinklight_on(fd) == -1)
		return -1;

	usleep(pause);

	if (thinklight_off(fd) == -1)
		return -1;

	return 0;
}

static int thinklight_morse_sequence(int fd, char *seq, unsigned int pause)
{
	while (*seq != '\0') {
		// '0' == dot, '1' == dash
		if (*seq++ == '0') {
			if (thinklight_morse_blink(fd, pause) == -1)
				return -1;
		} else {
			if (thinklight_morse_blink(fd, 3 * pause) == -1)
				return -1;
		}

		usleep(pause);
	}

	return 0;
}

static int thinklight_morse_character(int fd, char c, unsigned int pause)
{
	char *codetable[] = {
		"01",   // character A
		"1000", // character B
		"1010", // character C
		"100",  // character D
		"0",    // character E
		"0010", // character F
		"110",  // character G
		"0000", // character H
		"00",   // character I
		"0111", // character J
		"101",  // character K
		"0100", // character L
		"11",   // character M
		"10",   // character N
		"111",  // character O
		"0110", // character P
		"1101", // character Q
		"010",  // character R
		"000",  // character S
		"1",    // character T
		"001",  // character U
		"0001", // character V
		"011",  // character W
		"1001", // character X
		"1011", // character Y
		"1100" // character Z
	};

	// Do some input validation and base it to [0, 26]
	if (c >= 'a' && c <= 'z')
		c = c - 'a';
	else if (c >= 'A' && c <= 'Z')
		c = c - 'A';
	else if (c == ' ')
		usleep(7 * pause);
	else
		return -1;

	return thinklight_morse_sequence(fd, codetable[(int) c], pause);
}

static int thinklight_seek_position(int fd)
{
	if (lseek(fd, OFFSET, SEEK_SET) != OFFSET) {
		perror("[!] lseek() failed");
		return -1;
	}

	return 0;
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

		if (c == ' ') {
			usleep(7 * pause);
			continue;
		}

		if (thinklight_morse_character(fd, c, pause) == -1)
			return -1;

		usleep(3 * pause);
	}

	return 0;
}

int thinklight_blink(int fd, unsigned int pause)
{
	if (thinklight_on(fd) == -1)
		return -1;

	usleep(pause);

	if (thinklight_off(fd) == -1)
		return -1;

	usleep(pause);

	return 0;
}

