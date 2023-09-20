#ifndef _UEFI_H_
#define _UEFI_H_

#include <uuid.h>
#include <types.h>


/* Macros
 *----------------------*/
#define __EFIAPI__ __attribute__((ms_abi))

/* EFI status codes */
#define EFI_SUCCESS  0

/* For time services */
#define EFI_TIME_ADJUST_DAYLIGHT 0x1
#define EFI_TIME_IN_DAYLIGHT     0x2
#define EFI_UNSPECIFIED_TIMEZONE 0x07ff

/* Magic numbers */
#define EFI_SYSTEM_TABLE_SIGNATURE 0x5453595320494249
#define EFI_2_100_SYSTEM_TABLE_REVISION ((2<<16) | (100))
#define EFI_SPECIFICATION_VERSION    EFI_SYSTEM_TABLE_REVISION
#define EFI_SYSTEM_TABLE_REVISION    EFI_2_100_SYSTEM_TABLE_REVISION

#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

#define EFI_RUNTIME_SERVICES_SIGNATURE 0x56524553544e5552
#define EFI_RUNTIME_SERVICES_REVISION EFI_SPECIFICATION_VERSION

/* Typedefs 
 *----------------------*/
typedef U64     UN;
typedef U8      EfiBool;
typedef U64     EfiPhysicalAddress;
typedef U64     EfiVirtualAddress;

typedef void (__EFIAPI__ *efi_event_t)();
typedef void (__EFIAPI__ *efi_event_notify_t)(efi_event_t, void *);

typedef void             *EfiHandle;
typedef UN               EfiStatus;
typedef UN               EfiTpl;    

typedef struct _EfiCapsuleHeader    EfiCapsuleHeader;
typedef struct _EfiConfigTable      EfiConfigTable;
typedef struct _EfiGenericDevPath   EfiDevPath;
typedef struct _EfiInputKey         EfiInputKey;
typedef struct _EfiMemoryDescriptor EfiMemoryDescriptor;
typedef struct _EfiSimpleTextIn     EfiSimpleTextIn;
typedef struct _EfiSimpleTextOut    EfiSimpleTextOut;
typedef struct _EfiTime             EfiTime;


/* Structs
 *----------------------*/

/* Protocols */
#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID \
 {0x387477c1,0x69c7,0x11d2,\
  {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef struct {
	void                    *reset;
	EfiStatus   (__EFIAPI__ *read_key_stroke)(EfiSimpleTextIn *,
											 EfiInputKey *);
	efi_event_t     __EFIAPI__ wait_for_key;
} _EfiSimpleTextIn;

typedef struct {
	void                    *reset;
	EfiStatus   (__EFIAPI__ *output_string)(EfiSimpleTextOut *,
											U16 *);
	void                    *test_string;
} _EfiSimpleTextOut;

/* Misc for protocols */
typedef struct {
	EfiHandle   agentHandle;
	EfiHandle   controllerHandle;
	U32         attrs;
	U32         openCount;
} EfiOpenProtocolInfoEntry;

/* Table header */
typedef struct {
	U64  signature;
	U32  revision;
	U32  headerSize;
	U32  crc32;
	U32  reserved;
} EfiTableHeader;

/* Services */
#define EFI_BOOT_SERVICES_SIGNATURE 0x56524553544f4f42
#define EFI_BOOT_SERVICES_REVISION EFI_SPECIFICATION_VERSION

typedef struct {
	EfiTableHeader           hdr;
	EfiTpl      (__EFIAPI__ *raise_tpl)(EfiTpl);
	void        (__EFIAPI__ *restore_tpl)(EfiTpl);
	EfiStatus   (__EFIAPI__ *allocate_pages)(U32, U32, UN, EfiPhysicalAddress *);
	EfiStatus   (__EFIAPI__ *free_pages)(EfiPhysicalAddress, UN);
	EfiStatus   (__EFIAPI__ *get_memory_map)(UN *, EfiMemoryDescriptor *, UN *, UN *, U32 *);
	EfiStatus   (__EFIAPI__ *allocate_pool)(U32, UN, void **);
	EfiStatus   (__EFIAPI__ *free_pool)(void *);
	EfiStatus   (__EFIAPI__ *create_event)(U32, EfiTpl, efi_event_notify_t, void *, efi_event_t *);
	EfiStatus   (__EFIAPI__ *set_timer)(efi_event_t, U32, U64);
	EfiStatus   (__EFIAPI__ *wait_for_event)(UN, efi_event_t, UN *);
	EfiStatus   (__EFIAPI__ *signal_event)(efi_event_t);
	EfiStatus   (__EFIAPI__ *close_event)(efi_event_t);
	EfiStatus   (__EFIAPI__ *check_event)(efi_event_t);
	EfiStatus   (__EFIAPI__ *install_protocol_interface)(EfiHandle *, GUID *, U32, void *);
	EfiStatus   (__EFIAPI__ *reinstall_protocol_interface)(EfiHandle, GUID *, void *, void *);
	EfiStatus   (__EFIAPI__ *uninstall_protocol_interface)(EfiHandle, GUID *, void *);
	EfiStatus   (__EFIAPI__ *handle_protocol)(EfiHandle, GUID *, void **);
	void                    *_reserved;
	EfiStatus   (__EFIAPI__ *register_protocol_notify)(GUID *, efi_event_t, void **);
	EfiStatus   (__EFIAPI__ *locate_handle)(U32, GUID *, void *, UN *, EfiHandle *);
	EfiStatus   (__EFIAPI__ *locate_dev_path)(GUID *, EfiDevPath **, EfiHandle *);
	EfiStatus   (__EFIAPI__ *install_config_table)(GUID *, void *);
	EfiStatus   (__EFIAPI__ *load_image)(EfiBool, EfiHandle, EfiDevPath *, void *, UN, EfiHandle *);
	EfiStatus   (__EFIAPI__ *start_image)(EfiHandle, UN *, U16 **);
	EfiStatus   (__EFIAPI__ *exit)(EfiHandle, EfiStatus, UN, U16 *);
	EfiStatus   (__EFIAPI__ *unload_image)(EfiHandle);
	EfiStatus   (__EFIAPI__ *exit_boot_services)(EfiHandle, UN);
	EfiStatus   (__EFIAPI__ *get_next_mono_count)(U64 *);
	EfiStatus   (__EFIAPI__ *stall)(UN);
	EfiStatus   (__EFIAPI__ *set_watchdog_timer)(UN, U64, UN, U16 *);
	EfiStatus   (__EFIAPI__ *connect_controller)(EfiHandle, EfiHandle *, EfiDevPath *, EfiBool);
	EfiStatus   (__EFIAPI__ *disconnect_controller)(EfiHandle, EfiHandle, EfiHandle);
	EfiStatus   (__EFIAPI__ *open_protocol)(EfiHandle, GUID *, void **, EfiHandle, EfiHandle, U32);
	EfiStatus   (__EFIAPI__ *close_protocol)(EfiHandle, GUID *, EfiHandle, EfiHandle);
	EfiStatus   (__EFIAPI__ *open_protocol_info)(EfiHandle, GUID *, EfiOpenProtocolInfoEntry **, UN *);
	EfiStatus   (__EFIAPI__ *protocols_per_handle)(EfiHandle, GUID ***, UN *);
	EfiStatus   (__EFIAPI__ *locate_handle_buf)(U32, GUID *, void *, UN *, EfiHandle **);
	EfiStatus   (__EFIAPI__ *locate_protocol)(GUID *, void *, void **);
	EfiStatus   (__EFIAPI__ *install_multiple_protocol_interfaces)(EfiHandle *, ...);
	EfiStatus   (__EFIAPI__ *uninstall_multiple_protocol_interfaces)(EfiHandle, ...);
	EfiStatus   (__EFIAPI__ *calculate_crc32)(void *, UN, U32 *);
	EfiStatus   (__EFIAPI__ *copy_mem)(void *, void *, UN);
    EfiStatus   (__EFIAPI__ *set_mem)(void *, UN, U8);
	EfiStatus   (__EFIAPI__ *create_event_ex)(U32, EfiTpl, efi_event_notify_t, const void *, const GUID *, efi_event_t *);
} EfiBootServices;

typedef struct {
	EfiTableHeader           hdr;
	EfiStatus   (__EFIAPI__ *get_time)(EfiTime *);
	EfiStatus   (__EFIAPI__ *set_time)(EfiTime *);
	EfiStatus   (__EFIAPI__ *get_wakeup_time)(EfiBool *, EfiBool *, EfiTime *);
	EfiStatus   (__EFIAPI__ *set_wakeup_time)(EfiBool, EfiTime *);
	EfiStatus   (__EFIAPI__ *set_virtual_address_map)(UN, UN, U32, EfiMemoryDescriptor *);
	EfiStatus   (__EFIAPI__ *convert_ptr)(UN, void **);
	EfiStatus   (__EFIAPI__ *get_var)(U16 *, GUID *, U32 *, UN *, void *);
	EfiStatus   (__EFIAPI__ *get_next_var_name)(UN *, U16 *, GUID *);
	EfiStatus   (__EFIAPI__ *set_var)(U16 *, GUID *, U32, UN, void *);
	EfiStatus   (__EFIAPI__ *get_next_high_mono_count)(U32 *);
	EfiStatus   (__EFIAPI__ *reset_system)(U32, EfiStatus, UN, void *);
	EfiStatus   (__EFIAPI__ *update_capsule)(EfiCapsuleHeader **, UN, EfiPhysicalAddress);
	EfiStatus   (__EFIAPI__ *query_capsule_capabilities)(EfiCapsuleHeader **, UN, U64, U32);
	EfiStatus   (__EFIAPI__ *query_var_info)(U32, U64 *, U64 *, U64 *);
} EfiRuntimeServices;


/* System table */
typedef struct {
	EfiTableHeader      hdr;
	U16                 *firmwareVendor;
	U32                 firmwareRevision;
	EfiHandle           conInHandle;
	EfiSimpleTextIn     *conIn;
	EfiHandle           conOutHandle;
	EfiSimpleTextOut    *conOut;
	EfiHandle           stdErrorHandle;
	EfiSimpleTextOut    *stdErr;
	EfiRuntimeServices  *runtimeServices;
	EfiBootServices     *bootServices;
	UN                  numberOfTableEntries;
	EfiConfigTable      *configTable;
} EfiSystemTable;

/* Configuration table */
typedef struct {
	GUID    vendorGuid;
	void    *vendorTable;
} _EfiConfigTable;

/* Text I/O */
typedef struct {
	U16    scanCode;
	U16    unicodeChar;
} _EfiInputKey;

/* Time */
typedef struct {
	U16     year;
	U8      month;
	U8      day;
	U8      hour;
	U8      minute;
	U8      second;
	U8      _pad1;
	U32     nanosecond;
	I16     timeZone;
	U8      dayLight;
	U8      _pad2;
} _EfiTime;

/* Memory */
typedef struct {
	U32                 type;
	EfiPhysicalAddress  physicalStart;
	EfiVirtualAddress   virtualStart;
	U64                 numberOfPages;
	U64                 attribute;
} _EfiMemoryDescriptor;

/* Capsules */
typedef struct {
	GUID    capsuleGuid;
	U32     headerSize;
	U32     flags;
	U32     capsuleImgSize;
} _EfiCapsuleHeader;

/* Devices */
#define EFI_DEVICE_PATH_PROTOCOL_GUID \
  {0x09576e91,0x6d3f,0x11d2,\
    {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

typedef struct {
	U8      type;
	U8      subType;
	U8      length[2];
} _EfiGenericDevPath;


#endif /* !_UEFI_H_ */
