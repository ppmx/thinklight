/**
 * This program let the red light on the backside of a thinkpad notebook
 * blinking with a frequency of 1 second.
 *
 * You have to enable write operations to the API by setting 'write_support'
 * of the kernel module. Have a look at thinklight.h.
 */

#include <stdio.h>
#include <unistd.h>
#include "thinklight.h"

int blink(int fd)
{
	for (size_t i = 0; i < 23; i++) {
		if (thinklight_off(fd) == -1)
			return -1;

		usleep(500000);

		if (thinklight_on(fd) == -1)
			return -1;

		usleep(500000);
	}

	return 0;
}

int main(void)
{
	int fd;

	if ((fd = thinklight_open()) == -1)
		return -1;

	blink(fd);

	return thinklight_close(fd);
}

