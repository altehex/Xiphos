#ifndef _XIPHOS_TASK_H_
#define _XIPHOS_TASK_H_


#include "attrs.h"
#include "kernel.h"
#include "types.h"

#include <libc/stdlib.h>


typedef struct __PACKED__ {
	U64         rax, rbx, rcx, rdx,
		        rdi, rsi, rbp, rdp,
		        r8, r9, r10, r11,
		        r12, r13, r14, r15,
		        rip, rflsgs;

	/* TO-DO: add sse context */
} Context;

/*
 *  We use arrays for cores and kernels because we don't
 *  need to allocate more memory for them after startup.
 *  Thread lists, on the other hand, can't be statically
 *  defined.
 *  This is a subject to change because the OS might support
 *  CPU hot-plugging im the future.
 *
 *  *  What if we use this construction?
 *  * 
 *  *  [ CoreCtrl ]<-->[ CoreCtrl ]<--> ...
 *  *        |               |
 *  *  [ Initial ]     [ One hot-plugged CPU ]
 *  *  [  cores  ]     [ or an array of hot- ]
 *  *                  [     plugged CPUs    ]
 *
 *  How it looks like now:
 *
 *  [ Kern 0 ] [ Kern 1 ] ... [ Kern N ]
 *       |          |              |
 *  [ Core 0 ] [ Core 1 ] ... [ Core N ]
 *                  |
 *          [ ThreadCtrl 0 ]<--> ... <-->[ ThreadCtrl N ]
 *                  |
 *            [ Thread 0 ]
 */

typedef struct _Core         Core;
typedef struct _ThreadCtrl   ThreadCtrl;
typedef struct _Thread       Thread;

typedef struct __PACKED__ {
	unsigned  __pad: 32;
} CoreFlags;

struct __PACKED__
_Core {
	/* CoreFlags       flags; */
	XiphosKernel *  kernel;
	ThreadCtrl *    threadCtrl;
};

struct __PACKED__
_ThreadCtrl {
	U16          id;
	U16          flags;
	ThreadCtrl * next;
	ThreadCtrl * prev;
	Core *       core;
	Thread *     thread;
};

ThreadCtrl          __sentinelThreadCtrl = {0, 0, 0, 0, 0, 0};
static ThreadCtrl * sentinelThreadCtrl   = &__sentinelThreadCtrl;

struct __PACKED__
_Thread {
	Context       context;
	FUNC          func;
	PTR           args;
	ThreadCtrl *  threadCtrl;
};


static Core * xiphosCores; /* Global core array */


static inline void
enumerate_cores(U64 coreNum)
{
	xiphosCores = (Core *) malloc(sizeof(Core) * coreNum);

	for (; coreNum != MAX_U64; coreNum--) {
		xiphosCores[coreNum].kernel     = sentinelKernel;
		xiphosCores[coreNum].threadCtrl = sentinelThreadCtrl;
	}
		
	/* TBD */
}


#if 0 /* Draft */

register U16 coreId __asm__ ("es");

#define CURRENT_CORE 

#endif


#endif /* ! _XIPHOS_TASK_H_ */
