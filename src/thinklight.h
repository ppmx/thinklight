/**
 * Library to handle the the red light at the backside of a ThinkPad notebook.
 *
 * Author: https://github.com/ppmx
 *
 * As preperation you need to tell the proper kernel module that you want
 * to write things to the API. This can be done with:
 *
 *   $ sudo modprobe -r ec_sys
 *   $ sudo modprobe ec_sys write_support=1
 *
 * If the ec_sys module is built in (like on Arch) append this to your boot options:
 *   'ec_sys.write_support=1'
 *
 *
 * As alternative to that lib you can also use the following lines..
 *
 *   to disable it:
 *   $ echo -n -e "\x0a" | sudo dd of="/sys/kernel/debug/ec/ec0/io" bs=1 count=1 seek=12 2> /dev/null
 *
 *   to enable it:
 *   $ echo -n -e "\x8a" | sudo dd of="/sys/kernel/debug/ec/ec0/io" bs=1 count=1 seek=12 2> /dev/null
 *
 *   to let it blink:
 *   $ echo -n -e "\xca" | sudo dd of="/sys/kernel/debug/ec/ec0/io" bs=1 count=1 seek=12 2> /dev/null
 */

#ifndef THINKLIGHT_H
#define THINKLIGHT_H

#define API    "/sys/kernel/debug/ec/ec0/io"
#define OFFSET 12

#define LIGHT_ON  '\x8a'
#define LIGHT_OFF '\x0a'


// This function opens the API file and returns the proper file descriptor
// or -1 on failure.
int thinklight_open(void);

// closes the file descriptor returned by thinklight_open and returns the
// return value of close()
int thinklight_close(int fd);

int thinklight_off(int fd);
int thinklight_on(int fd);

// This function morses the given string out by the LED using pause
// as argument to usleep()
int thinklight_morse(int fd, char *buffer, unsigned int pause);

#endif
