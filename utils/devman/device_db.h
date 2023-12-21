#ifndef _XDEVMAN_DEVICE_DB_H_
#define _XDEVMAN_DEVICE_DB_H_


#include "attrs.h"

#include <include/attrs.h>
#include <include/types.h>


typedef struct __PACKED__ {
	CHAR8       sig[6]; /* Should be set to "DEVMAN" */
	U16         sz;     /* Database size */
} devmanDbHdr;


__DEVMAN__ void devman_populate_db(PTR);
	

#endif /* ! _XDEVMAN_DEVICE_DB_H_ */
