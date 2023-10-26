#include <exception.h>

/* Halts the execution */
/* To-do: add debug output */
void
general_handler(void)
{
	__asm__ __volatile__ (
		 "cli; hlt"
    );
}
