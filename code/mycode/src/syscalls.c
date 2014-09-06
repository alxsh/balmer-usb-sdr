/* balmer Bad code????? */

/* for caddr_t (typedef char * caddr_t;) */
#include <sys/types.h>
#include <errno.h>
#undef errno
extern int errno;


caddr_t _sbrk(int incr)
{
    extern void _end;
    static uint8_t *heap_pos = 0;
    uint8_t *prev_heap_pos;

    if (heap_pos == 0)
    {
        heap_pos = &_end;
    }
    prev_heap_pos = heap_pos;

    uint8_t * stack = (uint8_t*) __get_MSP();
    if (heap_pos + incr > stack)
    {
        errno = ENOMEM;
        return (caddr_t) -1;
        //abort ();
    }

    heap_pos += incr;
    return (caddr_t) prev_heap_pos;

}
