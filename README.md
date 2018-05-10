# ThinkLight

This library enables interaction with the red light on the backside of
ThinkPad notebooks. It provides methods to turn the light on and off and a
function to tap out a morse code message.

![thinklight.gif](https://miks.space/dump/thinklight.gif)

## code example

```
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
```
