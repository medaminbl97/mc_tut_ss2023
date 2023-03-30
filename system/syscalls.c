#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <cdev.h>

#ifdef USE_FREERTOS
#include <FREErtos.h>
#endif

#ifdef USE_FREERTOS
time_t time(time_t *tloc)
{
	/* 
	 * Time in sec since 1.1.1970
	 * Currently always starts at begin of epoch!
	 * Todo: Get RTC and use RTC value!
	 */
	time_t time = (time_t) (0 + (int)(xTaskGetTickCount() / 100));
	if (tloc != NULL)
		*tloc = time;
	
	return time;
}
#endif

int _open (char *path, int oflag)
{
	int fd;
	fd = device_open(path, oflag);
	if (fd < 0) {
		errno = ENODEV;
		return -1;
	}

	return fd;
}

int _write(int fd, const void *buf, size_t count)
{
	int i = 0;
	
	i = device_write(fd, (char*)buf, count);

	return i;
}


int _read(int fd, const void *buf, size_t count)
{
	int i = 0;
	i = device_read(fd, (char*)buf, count);
	if (i < 0) {
		errno = EIO;
		return -1;
	}
	
	return i;
}

/* 
 * _sbrk - We reimplement _sbrk based on newlibs _sbrk;
 * Major difference is: This version respects _heap_end,
 * which is exported by the linker script, to detect 
 * out of memory instead of smashing the stack
 */
void *_sbrk (int incr)
{ 
	/* Linker symbols */
	extern char _heap_start, _heap_end; 
	static char *heap_end; 
	char *prev_heap_end; 

	if (heap_end == 0)
		heap_end = &_heap_start; 

	prev_heap_end = heap_end; 

	if (heap_end + incr >= &_heap_end) {
		/* We're outta heap */
		errno = ENOMEM;
		return (void*) -1;
	}

	heap_end += incr; 

	return (void *) prev_heap_end; 
} 

