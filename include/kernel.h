#ifndef _XIPHOS_KERNEL_H_
#define _XIPHOS_KERNEL_H_


#include "attrs.h"
#include "mp.h"
#include "types.h"


#if 0 /* Draft */

#define SCHED_MODE_RR   0
#define SCHED_MODE_BMQ  1
#define SCHED_MODE_RBED 2

#endif


typedef struct _XiphosKernel XiphosKernel;
typedef struct _Core         Core;

struct __PACKED__
_XiphosKernel {
	U16    flags;
	U16    schedMode;
	Core * core;
};


static __USED__ XiphosKernel * xiphosKernels; /* Global kernel array */

XiphosKernel          __sentinelKernel = {0, 0, 0};
static XiphosKernel * sentinelKernel   = &__sentinelKernel;


#endif /* ! _XIPHOS_KERNEL_H_ */
