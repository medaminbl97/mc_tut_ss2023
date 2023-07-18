#include <errno.h>

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