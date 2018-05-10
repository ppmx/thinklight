/**
 * This program uses the red light on the backside of Lenovo ThinkPad
 * notebooks to morse a "hello world" and let the light blinking afterwards.
 *
 * You have to enable write operations to the API by setting 'write_support'
 * of the kernel module. Have a look at thinklight.h.
 */

#include <stdio.h>
#include "thinklight.h"
#include <unistd.h>

int main(void)
{
	int fd;

	if ((fd = thinklight_open()) == -1)
		return -1;

	if (thinklight_morse(fd, "hello world", 500000) == -1)
		return thinklight_close(fd);

	for (size_t i = 0; i < 23; i++) {
		if (thinklight_blink(fd, 200000) == -1)
			break;
	}

	return thinklight_close(fd);
}

