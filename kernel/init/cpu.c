#include <cpu.h>


/* Relocates CpuInfo data from bootloader */
void
setup_cpuinfo(CpuInfo * cpuInfoOnBoot)
{
	xiphosCpuInfo.coreNum = cpuInfoOnBoot->coreNum;
	xiphosCpuInfo.codeSeg = cpuInfoOnBoot->codeSeg;
}
