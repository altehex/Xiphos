#ifndef _XDEVMAN_INIT_H_
#define _XDEVMAN_INIT_H_


#include "device_db.h"

#include <include/acpi.h>
#include <include/attrs.h>
#include <include/types.h>


static inline void
devman_init(void)
{
	/* PTR dbBase =  */
	
	devman_populate_db();
}


#endif /* ! _XDEVMAN_INIT_H_ */
