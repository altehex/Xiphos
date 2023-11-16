#ifndef _XIPHOS_TASK_H_
#define _XIPHOS_TASK_H_


#include "attrs.h"
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
 *  [ Core 0 ] [ Core 1 ] ... [ Core N ]
 *                  |
 *                  V
 *          [ ThreadCtrl 0 ]<--> ... <-->[ ThreadCtrl N ]
 *                  |
 *                  V
 *            [ Thread 0 ]
 */

typedef struct _ThreadCtrl ThreadCtrl;
typedef struct _Thread     Thread;

typedef struct __PACKED__ {
	U16             id;
	U16             flags;
	ThreadCtrl *    threadCtrl;
} Core;

typedef struct __PACKED__ {
	U16             id;
	U16             flags;
	ThreadCtrl *    next;
	ThreadCtrl *    prev;
	Core *          core;
	Thread *        thread;
} _ThreadCtrl;

typedef struct __PACKED__ {
	Context         context;
	FUNC            func;
	PTR             args;
	ThreadCtrl *    threadCtrl;
} _Thread;


static inline Core *
enumerate_cores(U64 coreNum)
{
	Core *     currentCore;
	Core *     corePool;

	corePool     = (Core *) malloc(sizeof(Core) * coreNum);
	
	for (; coreNum >= 0; coreNum--) {
		currentCore = &corePool[coreNum];

		currentCore->id    = (U16) coreNum;
		currentCore->flags = 0x0000;
	}

    return corePool;
}


#if 0 /* Draft */

register U16 coreId __asm__ ("es");

#define CURRENT_CORE 

#endif


#endif /* ! _XIPHOS_TASK_H_ */
