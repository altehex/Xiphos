#ifndef _XIPHOS_RES_H_
#define _XIPHOS_RES_H_


#include "attrs.h"


#define LOCK_LOCKED    1
#define LOCK_FREE      0


typedef struct __PACKED__ {
	U32     flags;
} Resource;


#endif /* ! _XIPHOS_RES_H_ */
