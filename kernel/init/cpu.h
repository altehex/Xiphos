#ifndef _CPU_H_
#define _CPU_H_


#include <attrs.h>
#include <types.h>


typedef struct __PACKED__ {
	U16     coreNum;
	U16     codeSeg;
} CpuInfo;


static CpuInfo  xiphosCpuInfo;


/* Relocates CpuInfo data from bootloader */
void __KINIT_CPU__
setup_cpuinfo(CpuInfo *);


#endif /* ! _CPU_H_ */
