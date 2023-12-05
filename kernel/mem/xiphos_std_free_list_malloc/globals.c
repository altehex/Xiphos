#include "free_list.h"


#include <stdatomic.h>


MemRegion * freeMemRegions;
MemRegion * usedMemRegions;

static MemRegion __sentinelRegion = { (U64) -1, 0, 0 };
MemRegion        * sentinelRegion = &__sentinelRegion;

atomic_flag listLock = ATOMIC_FLAG_INIT;
