#ifndef _XIPHOS_ACPI_H_
#define _XIPHOS_ACPI_H_


#include "acpi_sig.h"

#include <attrs.h>
#include <types.h>


#define ACPI_SYSTEM_MEMORY          0x00
#define ACPI_SYSTEM_IO              0x01
#define ACPI_PCI_CONFIG_SPACE       0x02
#define ACPI_EMBEDDED_CONTROLLER    0x03
#define ACPI_SMBUS                  0x04
#define ACPI_SYSTEM_CMOS            0x05
#define ACPI_PCI_BAR_TARGET         0x06
#define ACPI_IPMI                   0x07
#define ACPI_GPIO                   0x08
#define ACPI_GENERIC_SERIAL_BUS     0x09
#define ACPI_PCC                    0x0A
#define ACPI_PRM                    0x0B
#define ACPI_FIXED_HARDWARE         0x7F

#define ACPI_UNDEFINED_ACCESS   0
#define ACPI_BYTE_ACCESS        1
#define ACPI_WORD_ACCESS        2
#define ACPI_DWORD_ACCESS       3
#define ACPI_QWORD_ACCESS       4


typedef struct __PACKED__ {
	CHAR8   sig[8];
	U8      checksum;
	CHAR8   oemId[6];
	U8      rev;
	U32     __unused; /* RSDT address in ACPI 1.0 */
	U32     sz;
	PTR     xsdtBase;
	U8      checksumExt;
	U8      __reserved[3];
} AcpiXsdp;

typedef struct __PACKED__ {
	CHAR8   sig[4];
	U32     sz;
	U8      rev;
	U8      checksum;
	CHAR8   oemId[6];
	CHAR8   oemTableId[8];
	U32     oemRev;
	CHAR8   aslId[4];
	U32     aslRev;
} AcpiTableDesc;

typedef struct __PACKED__ {
	AcpiTableDesc desc;
	PTR *         entries;
} AcpiXsdt;

typedef struct __PACKED__ {
	AcpiTableDesc desc;
	PTR32         __firmwareCtrl;
	PTR32         __dsdt;
	U8            __reserved1;
	U8            pmProfile;
	U16           sciInt;
	PORT32        smiCmd;
	U8            acpiEnable;
	U8            acpiDisable;
	U8            s4BiosReq;
	U8            pStateCnt;
	PORT32        __pm1aEvtBlk;
	PORT32        __pm1bEvtBlk;
	PORT32        __pm1aCntBlk;
	PORT32        __pm1bCntBlk;
	PORT32        __pm2CntBlk;
	PORT32        __pmTmrBlk;
	PORT32        __gpe0Blk;
	PORT32        __gpe1Blk;
	U8            pm1EvtSz;
	U8            pm1CntSz;
	U8            pm2CntSz;
	U8            pmTmrSz;
	U8            gpe0BlkSz;
	U8            gpe1BlkSz;
	OFFSET8       gpe1Base;
	U8            cstCnt;
	U16           pLvl2Lat;
	U16           pLvl3Lat;
	U16           flushSz;
	U16           flushStride;
	OFFSET8       dutyOffset;
	U8            dutyWidth;
	U8            dayAlarm;
	U8            monthAlarm;
	U8            century;
	U16           iapcBootArch;
	U8            __reserved2;
	U32           flags;
	U8            resetReg[12];
	U8            resetVal;
	U16           armBootArch;
	U8            fadtMinor;
	PTR           firmwareCtrl;
	PTR           dsdt;
	U8            pm1aEvtBlk[12];
	U8            pm1bEvtBlk[12];
	U8            pm1aCntBlk[12];
	U8            pm1bCntBlk[12];
	U8            pm2CntBlk[12];
	U8            pmTmrBlk[12];
	U8            gpe0Blk[12];
	U8            gpe1Blk[12];
	U8            sleepCtrlReg[12];
	U8            sleepStatusReg[12];
	CHAR8         hypervisorVendorId[8];
} AcpiFadt;

#define ACPI_GAS_PCI_SEGMENT  (U64) 0xFF << 56
#define ACPI_GAS_PCI_BUS      (U64) 0xFF << 48
#define ACPI_GAS_PCI_DEVICE   (U64) 0x1F << 43
#define ACPI_GAS_PCI_FUNCTION (U64) 0x07 << 40
#define ACPI_GAS_BAR_INDEX    (U64) 0x07 << 37
#define ACPI_GAS_BAR_OFFSET   (U64) 0x000FFFFFFFFF

typedef struct __PACKED__ {
	U8          addrSpaceId;
	U8          regSz;
	U8          regOffset;
	U8          accessSz;
	PTR         address;
} AcpiGenericAddress;


#endif /* ! _XIPHOS_ACPI_H_ */
