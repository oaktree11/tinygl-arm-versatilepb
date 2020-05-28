#include <stdint.h>

//#define MB_CONTROL_PAGE_ADDRESS 0x00708000
//#include "mb/sw/control.h"

#include "lcd.h"
#include "examples/ui.h"

#define UNUSED(x) (void)(x)
extern int __heap_start;
static void* mem = (void*) &__heap_start;

void *vista_malloc(int size)
{
	void *ret = mem;
	mem += size;
	return ret;
}

// kernel main function, it all begins here
void kernel_main() {

	uart_init();
    // example of semi hosting print message
#ifdef GPU
    uprintf("*** ARM A9 OpenGL Platform - GPU ENABLED ***");
#else
    uprintf("*** ARM A9 OpenGL Platform ***");
#endif

    init_lcd();
  
    ui_loop();
}

