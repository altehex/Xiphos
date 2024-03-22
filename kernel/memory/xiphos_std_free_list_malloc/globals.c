#include "free_list.h"


#include <stdatomic.h>


xsmfl_MemRegion *  xsmfl_freeMemRegions;
xsmfl_MemRegion *  xsmfl_usedMemRegions;

xsmfl_MemRegion xsmfl_sentinelRegion = { (U64) -1, 0, 0 };

volatile atomic_flag xsmfl_listLock = ATOMIC_FLAG_INIT;
