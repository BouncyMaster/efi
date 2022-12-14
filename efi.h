#ifndef EFI_H
#define EFI_H

typedef unsigned char		UINT8;
typedef short			INT16;
typedef unsigned short		UINT16;
typedef int			INT32;
typedef unsigned int		UINT32;
typedef long long		INT64;
typedef unsigned long long	UINT64;
typedef INT64			INTN;
typedef UINT64			UINTN;
typedef UINT16			CHAR16;
typedef unsigned char		BOOLEAN;
typedef UINT64			EFI_PHYSICAL_ADDRESS;
typedef UINT64			EFI_VIRTUAL_ADDRESS;
typedef void *			EFI_HANDLE;
typedef UINTN			EFI_STATUS;
typedef void *			EFI_EVENT;
typedef UINTN			EFI_TPL;

#define TRUE	1
#define FALSE	0

#define EFI_PAGE_SHIFT	12
#define EFI_PAGE_MASK	0xFFF
#define EFI_SIZE_TO_PAGES(Size) (((Size) >> EFI_PAGE_SHIFT) + (((Size) & EFI_PAGE_MASK) ? 1 : 0))

#define MAX_BIT 0x8000000000000000ULL // 1<<63
#define EFI_ERROR(Status) (((INTN)(Status)) < 0)
#define ENCODE_ERROR(Status) ((UINTN)(MAX_BIT | (Status)))

#define EFI_SUCCESS		0
#define EFI_LOAD_ERROR		ENCODE_ERROR(1)
#define EFI_INVALID_PARAMETER	ENCODE_ERROR(2)
#define EFI_UNSUPPORTED		ENCODE_ERROR(3)
#define EFI_BAD_BUFFER_SIZE	ENCODE_ERROR(4)
#define EFI_BUFFER_TOO_SMALL	ENCODE_ERROR(5)

#define EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID \
	{0x9042a9de,0x23dc,0x4a38, {0x96,0xfb,0x7a,0xde,0xd0,0x80,0x51,0x6a}}
#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID \
	{0x0964e5b22,0x6459,0x11d2, {0x8e,0x39,0x00,0xa0,0xc9,0x69,0x72,0x3b}}

/*
 * This is the main EFI header for all of the EFI protocols.
 * UEFI 2.10 Specs PDF Page 89
 */
typedef struct {
	UINT64	Signature;
	UINT32	Revision;
	UINT32	HeaderSize;
	UINT32	CRC32;
	UINT32	Reserved;
} EFI_TABLE_HEADER;

typedef struct {
	UINT32	Data1;
	UINT16	Data2;
	UINT16	Data3;
	UINT8	Data4[8];
} EFI_GUID;


typedef struct {
	UINT16	ScanCode;
	CHAR16	UnicodeChar;
} EFI_INPUT_KEY;

// We are forward declaring this struct so that the function typedefs can operate.
struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef EFI_STATUS (*EFI_INPUT_RESET)(
		struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
		BOOLEAN ExtendedVerification);

typedef EFI_STATUS (*EFI_INPUT_READ_KEY)(
		struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, EFI_INPUT_KEY *Key);

// UEFI 2.10 Specs PDF Page 395
typedef struct {
	EFI_INPUT_RESET		Reset;
	EFI_INPUT_READ_KEY	ReadKeyStroke;
	EFI_EVENT		WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;


// We are forward declaring this struct so that the function typedefs can operate.
struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef EFI_STATUS (*EFI_TEXT_RESET)(
		struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
		BOOLEAN ExtendedVerification);

typedef EFI_STATUS (*EFI_TEXT_STRING)(
		struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);

typedef EFI_STATUS (*EFI_TEXT_TEST_STRING)(
		struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);

typedef EFI_STATUS (*EFI_TEXT_QUERY_MODE)(
		struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
		UINTN ModeNumber, UINTN *Columns, UINTN *Rows);

typedef EFI_STATUS (*EFI_TEXT_SET_MODE)(
		struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN ModeNumber);

typedef EFI_STATUS (*EFI_TEXT_SET_ATTRIBUTE)(
		struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, UINTN Attribute);

typedef EFI_STATUS (*EFI_TEXT_CLEAR_SCREEN)(
		struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);

typedef EFI_STATUS (*EFI_TEXT_SET_CURSOR_POSITION)(
		struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
		UINTN Column, UINTN Row);

typedef EFI_STATUS (*EFI_TEXT_ENABLE_CURSOR)(
		struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, BOOLEAN Visible);

// UEFI 2.10 Specs PDF Page 399
typedef struct {
	INT32		MaxMode;
	// current settings
	INT32		Mode;
	INT32		Attribute;
	INT32		CursorColumn;
	INT32		CursorRow;
	BOOLEAN		CursorVisible;
} SIMPLE_TEXT_OUTPUT_MODE;

// UEFI 2.10 Specs PDF Page 398
typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
	EFI_TEXT_RESET			Reset;
	EFI_TEXT_STRING			OutputString;
	EFI_TEXT_TEST_STRING		TestString;
	EFI_TEXT_QUERY_MODE		QueryMode;
	EFI_TEXT_SET_MODE		SetMode;
	EFI_TEXT_SET_ATTRIBUTE		SetAttribute;
	EFI_TEXT_CLEAR_SCREEN		ClearScreen;
	EFI_TEXT_SET_CURSOR_POSITION	SetCursorPosition;
	EFI_TEXT_ENABLE_CURSOR		EnableCursor;
	SIMPLE_TEXT_OUTPUT_MODE *	Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;


typedef enum {
	PixelRedGreenBlueReserved8BitPerColor,
	PixelBlueGreenRedReserved8BitPerColor,
	PixelBitMask,
	PixelBltOnly,
	PixelFormatMax
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct {
	UINT32	RedMask;
	UINT32	GreenMask;
	UINT32	BlueMask;
	UINT32	ReservedMask;
} EFI_PIXEL_BITMASK;

typedef struct {
	UINT32				Version;
	UINT32				HorizontalResolution;
	UINT32				VerticalResolution;
	EFI_GRAPHICS_PIXEL_FORMAT	PixelFormat;
	EFI_PIXEL_BITMASK		PixelInformation;
	UINT32				PixelsPerScanLine;
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct {
	UINT8	Blue;
	UINT8	Green;
	UINT8	Red;
	UINT8	Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef enum {
	EfiBltVideoFill,
	EfiBltVideoToBltBuffer,
	EfiBltBufferToVideo,
	EfiBltVideoToVideo,
	EfiGraphicsOutputBltOperationMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

typedef struct {
	UINT32					MaxMode;
	UINT32					Mode;
	EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *	Info;
	UINTN					SizeOfInfo;
	EFI_PHYSICAL_ADDRESS			FrameBufferBase;
	UINTN					FrameBufferSize;
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

// We are forward declaring this struct so that the function typedefs can operate.
struct EFI_GRAPHICS_OUTPUT_PROTOCOL;

typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE)(
		struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
		UINT32 ModeNumber, UINTN *SizeOfInfo,
		EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info);

typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE)(
		struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This, UINT32 ModeNumber);

typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT)(
		struct EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
		EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer,
		EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation,
		UINTN SourceX, UINTN SourceY,
		UINTN DestinationX, UINTN DestinationY,
		UINTN Width, UINTN Height, UINTN Delta);

// UEFI 2.10 Specs PDF Page 427
typedef struct EFI_GRAPHICS_OUTPUT_PROTOCOL {
	EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE		QueryMode;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE		SetMode;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT		Blt;
	EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *		Mode;
} EFI_GRAPHICS_OUTPUT_PROTOCOL;


// Open Modes
#define EFI_FILE_MODE_READ	0x0000000000000001
#define EFI_FILE_MODE_WRITE	0x0000000000000002
#define EFI_FILE_MODE_CREATE	0x8000000000000000
// File Attributes
#define EFI_FILE_READ_ONLY	0x0000000000000001
#define EFI_FILE_HIDDEN		0x0000000000000002
#define EFI_FILE_SYSTEM		0x0000000000000004
#define EFI_FILE_RESERVED	0x0000000000000008
#define EFI_FILE_DIRECTORY	0x0000000000000010
#define EFI_FILE_ARCHIVE	0x0000000000000020
#define EFI_FILE_VALID_ATTR	0x0000000000000037

typedef struct {
	EFI_EVENT	Event;
	EFI_STATUS	Status;
	UINTN		BufferSize;
	void *		Buffer;
} EFI_FILE_IO_TOKEN;

// We are forward declaring this struct so that the function typedefs can operate.
struct EFI_FILE_PROTOCOL;

typedef EFI_STATUS (*EFI_FILE_OPEN)(struct EFI_FILE_PROTOCOL *This,
	struct EFI_FILE_PROTOCOL **NewHandle, CHAR16 *FileName, UINT64 OpenMode,
	UINT64 Attributes);

typedef EFI_STATUS (*EFI_FILE_CLOSE)(struct EFI_FILE_PROTOCOL *This);

typedef EFI_STATUS (*EFI_FILE_DELETE)(struct EFI_FILE_PROTOCOL *This);

typedef EFI_STATUS (*EFI_FILE_READ)(struct EFI_FILE_PROTOCOL *This,
	UINTN *BufferSize, void *Buffer);

typedef EFI_STATUS (*EFI_FILE_WRITE)(struct EFI_FILE_PROTOCOL *This,
	UINTN *BufferSize, void *Buffer);

typedef EFI_STATUS (*EFI_FILE_GET_POSITION)(struct EFI_FILE_PROTOCOL *This,
	UINT64 *Position);

typedef EFI_STATUS (*EFI_FILE_SET_POSITION)(struct EFI_FILE_PROTOCOL *This,
	UINT64 Position);

typedef EFI_STATUS (*EFI_FILE_GET_INFO)(struct EFI_FILE_PROTOCOL *This,
	EFI_GUID *InformationType, UINTN *BufferSize, void *Buffer);

typedef EFI_STATUS (*EFI_FILE_SET_INFO)(struct EFI_FILE_PROTOCOL *This,
	EFI_GUID *InformationType, UINTN BufferSize, void *Buffer);

typedef EFI_STATUS (*EFI_FILE_FLUSH)(struct EFI_FILE_PROTOCOL *This);

typedef EFI_STATUS (*EFI_FILE_OPEN_EX)(struct EFI_FILE_PROTOCOL *This,
	struct EFI_FILE_PROTOCOL **NewHandle, CHAR16 *FileName, UINT64 OpenMode,
	UINT64 Attributes, EFI_FILE_IO_TOKEN *Token);

typedef EFI_STATUS (*EFI_FILE_READ_EX)(struct EFI_FILE_PROTOCOL *This,
	EFI_FILE_IO_TOKEN *Token);

typedef EFI_STATUS (*EFI_FILE_WRITE_EX)(struct EFI_FILE_PROTOCOL *This,
	EFI_FILE_IO_TOKEN *Token);

typedef EFI_STATUS (*EFI_FILE_FLUSH_EX)(struct EFI_FILE_PROTOCOL *This,
	EFI_FILE_IO_TOKEN *Token);

// UEFI 2.10 Specs PDF Page 450
typedef struct EFI_FILE_PROTOCOL {
	UINT64			Revision;
	EFI_FILE_OPEN		Open;
	EFI_FILE_CLOSE		Close;
	EFI_FILE_DELETE		Delete;
	EFI_FILE_READ		Read;
	EFI_FILE_WRITE		Write;
	EFI_FILE_GET_POSITION	GetPosition;
	EFI_FILE_SET_POSITION	SetPosition;
	EFI_FILE_GET_INFO	GetInfo;
	EFI_FILE_SET_INFO	SetInfo;
	EFI_FILE_FLUSH		Flush;
	EFI_FILE_OPEN_EX	OpenEx;
	EFI_FILE_READ_EX	ReadEx;
	EFI_FILE_WRITE_EX	WriteEx;
	EFI_FILE_FLUSH_EX	FlushEx;
} EFI_FILE_PROTOCOL;

// We are forward declaring this struct so that the function typedefs can operate.
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;

typedef EFI_STATUS (*EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME)(
	struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This, EFI_FILE_PROTOCOL **Root);

// UEFI 2.10 Specs PDF Page 449
typedef struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
	UINT64						Revision;
	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME	OpenVolume;
} EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;


typedef struct {
	UINT32			Type;
	EFI_PHYSICAL_ADDRESS	PhysicalStart;
	EFI_VIRTUAL_ADDRESS	VirtualStart;
	UINT64			NumberOfPages;
	UINT64			Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef struct {
	UINT16	Year;
	UINT8	Month;
	UINT8	Day;
	UINT8	Hour;
	UINT8	Minute;
	UINT8	Second;
	UINT8	Pad1;
	UINT32	Nanosecond;
	INT16	TimeZone;
	UINT8	Daylight;
	UINT8	Pad2;
} EFI_TIME;

typedef struct {
	UINT32		Resolution;
	UINT32		Accuracy;
	BOOLEAN		SetsToZero;
} EFI_TIME_CAPABILITIES;

typedef enum {
	EfiResetCold,
	EfiResetWarm,
	EfiResetShutdown,
	EfiResetPlatformSpecific
} EFI_RESET_TYPE;

typedef struct {
	EFI_GUID	CapsuleGuid;
	UINT32		HeaderSize;
	UINT32		Flags;
	UINT32		CapsuleImageSize;
} EFI_CAPSULE_HEADER;

/*
 * NOTE: Some runtime services functions are wrongly defined in the spec,
 * e.g. function name is SetTime instead of EFI_SET_TIME.
 */
typedef EFI_STATUS (*EFI_GET_TIME)(EFI_TIME *Time,
	EFI_TIME_CAPABILITIES *Capabilities);

typedef EFI_STATUS (*EFI_SET_TIME)(EFI_TIME *Time);

typedef EFI_STATUS (*EFI_GET_WAKEUP_TIME)(BOOLEAN *Enabled, BOOLEAN *Pending,
	EFI_TIME *Time);

typedef EFI_STATUS (*EFI_SET_WAKEUP_TIME)(BOOLEAN Enable, EFI_TIME *Time);

typedef EFI_STATUS (*EFI_SET_VIRTUAL_ADDRESS_MAP)(UINTN MemoryMapSize,
	UINTN DescriptorSize, UINT32 DescriptorVersion,
	EFI_MEMORY_DESCRIPTOR *VirtualMap);

typedef EFI_STATUS (*EFI_CONVERT_POINTER)(UINTN DebugDisposition,
	void **Address);

typedef EFI_STATUS (*EFI_GET_VARIABLE)(CHAR16 *VariableName,
	EFI_GUID *VendorGuid, UINT32 *Attributes, UINTN *DataSize, void *Data);

typedef EFI_STATUS (*EFI_GET_NEXT_VARIABLE_NAME)(UINTN *VariableNameSize,
	CHAR16 *VariableName, EFI_GUID *VendorGuid);

typedef EFI_STATUS (*EFI_SET_VARIABLE)(CHAR16 *VariableName,
	EFI_GUID *VendorGuid, UINT32 Attributes, UINTN DataSize, void *Data);

typedef EFI_STATUS (*EFI_GET_NEXT_HIGH_MONO_COUNT)(UINT32 *HighCount);

typedef EFI_STATUS (*EFI_RESET_SYSTEM)(EFI_RESET_TYPE ResetType,
	EFI_STATUS ResetStatus, UINTN DataSize, void *ResetData);

typedef EFI_STATUS (*EFI_UPDATE_CAPSULE)(EFI_CAPSULE_HEADER **CapsuleHeaderArray,
	UINTN CapsuleCount, EFI_PHYSICAL_ADDRESS ScatterGatherList);

typedef EFI_STATUS (*EFI_QUERY_CAPSULE_CAPABILITIES)(
	EFI_CAPSULE_HEADER **CapsuleHeaderArray, UINTN CapsuleCount,
	UINT64 *MaximumCapsuleSize, EFI_RESET_TYPE *ResetType);

typedef EFI_STATUS (*EFI_QUERY_VARIABLE_INFO)(UINT32 Attributes,
	UINT64 *MaximumVariableStorageSize, UINT64 *RemainingVariableStorageSize,
	UINT64 *MaximumVariableSize);

// UEFI 2.10 Specs PDF Page 96
typedef struct {
	EFI_TABLE_HEADER		Hdr;
	EFI_GET_TIME			GetTime;
	EFI_SET_TIME			SetTime;
	EFI_GET_WAKEUP_TIME		GetWakeupTime;
	EFI_SET_WAKEUP_TIME		SetWakeupTime;
	EFI_SET_VIRTUAL_ADDRESS_MAP	SetVirtualAddressMap;
	EFI_CONVERT_POINTER		ConvertPointer;
	EFI_GET_VARIABLE		GetVariable;
	EFI_GET_NEXT_VARIABLE_NAME	GetNextVariableName;
	EFI_SET_VARIABLE		SetVariable;
	EFI_GET_NEXT_HIGH_MONO_COUNT	GetNextHighMonotonicCount;
	EFI_RESET_SYSTEM		ResetSystem;
	EFI_UPDATE_CAPSULE		UpdateCapsule;
	EFI_QUERY_CAPSULE_CAPABILITIES	QueryCapsuleCapabilities;
	EFI_QUERY_VARIABLE_INFO		QueryVariableInfo;
} EFI_RUNTIME_SERVICES;


typedef enum {
	AllocateAnyPages,
	AllocateMaxAddress,
	AllocateAddress,
	MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef enum {
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConventionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO,
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiPersistentMemory,
	EfiUnacceptedMemoryType,
	EfiMaxMemoryType
} EFI_MEMORY_TYPE;

typedef enum {
	TimerCancel,
	TimerPeriodic,
	TimerRelative
} EFI_TIMER_DELAY;

typedef enum {
	EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef enum {
	AllHandles,
	ByRegisterNotify,
	ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

typedef struct {
	UINT8	Type;
	UINT8	SubType;
	UINT8	Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef struct {
	EFI_HANDLE	AgentHandle;
	EFI_HANDLE	ControllerHandle;
	UINT32		Attributes;
	UINT32		OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

typedef EFI_TPL (*EFI_RAISE_TPL)(EFI_TPL NewTpl);
typedef void (*EFI_RESTORE_TPL)(EFI_TPL OldTpl);

typedef EFI_STATUS (*EFI_ALLOCATE_PAGES)(EFI_ALLOCATE_TYPE Type,
	EFI_MEMORY_TYPE MemoryType, UINTN Pages, EFI_PHYSICAL_ADDRESS *Memory);

typedef EFI_STATUS (*EFI_FREE_PAGES)(EFI_PHYSICAL_ADDRESS Memory, UINTN Pages);

typedef EFI_STATUS (*EFI_GET_MEMORY_MAP)(UINTN *MemoryMapSize,
	EFI_MEMORY_DESCRIPTOR *MemoryMap, UINTN *MapKey, UINTN *DescriptorSize,
	UINT32 *DescriptorVersion);

typedef EFI_STATUS (*EFI_ALLOCATE_POOL)(EFI_MEMORY_TYPE PoolType, UINTN Size,
	void **Buffer);

typedef EFI_STATUS (*EFI_FREE_POOL)(void *Buffer);

typedef void (*EFI_EVENT_NOTIFY)(EFI_EVENT Event, void *Context);

typedef EFI_STATUS (*EFI_CREATE_EVENT)(UINT32 Type, EFI_TPL NotifyTpl,
	EFI_EVENT_NOTIFY NotifyFunction, void *NotifyContext, EFI_EVENT *Event);

typedef EFI_STATUS (*EFI_SET_TIMER)(EFI_EVENT Event, EFI_TIMER_DELAY Type,
	UINT64 TriggerTime);

typedef EFI_STATUS (*EFI_WAIT_FOR_EVENT)(UINTN NumberOfEvents, EFI_EVENT *Event,
	UINTN *Index);

typedef EFI_STATUS (*EFI_SIGNAL_EVENT)(EFI_EVENT Event);
typedef EFI_STATUS (*EFI_CLOSE_EVENT)(EFI_EVENT Event);
typedef EFI_STATUS (*EFI_CHECK_EVENT)(EFI_EVENT Event);

typedef EFI_STATUS (*EFI_INSTALL_PROTOCOL_INTERFACE)(EFI_HANDLE *Handle,
	EFI_GUID *Protocol, EFI_INTERFACE_TYPE InterfaceType, void *Interface);

typedef EFI_STATUS (*EFI_REINSTALL_PROTOCOL_INTERFACE)(EFI_HANDLE Handle,
	EFI_GUID *Protocol, void *OldInterface, void *NewInterface);

typedef EFI_STATUS (*EFI_UNINSTALL_PROTOCOL_INTERFACE)(EFI_HANDLE Handle,
	EFI_GUID *Protocol, void *Interface);

typedef EFI_STATUS (*EFI_HANDLE_PROTOCOL)(EFI_HANDLE Handle, EFI_GUID *Protocol,
	void **Interface);

typedef EFI_STATUS (*EFI_REGISTER_PROTOCOL_NOTIFY)(EFI_GUID *Protocol,
	EFI_EVENT Event, void **Registration);

typedef EFI_STATUS (*EFI_LOCATE_HANDLE)(EFI_LOCATE_SEARCH_TYPE SearchType,
	EFI_GUID *Protocol, void *SearchKey, UINTN *BufferSize,
	EFI_HANDLE *Buffer);

typedef EFI_STATUS (*EFI_LOCATE_DEVICE_PATH)(EFI_GUID *Protocol,
	EFI_DEVICE_PATH_PROTOCOL **DevicePath, EFI_HANDLE *Device);

typedef EFI_STATUS (*EFI_INSTALL_CONFIGURATION_TABLE)(EFI_GUID *Guid,
	void *Table);

typedef EFI_STATUS (*EFI_IMAGE_LOAD)(BOOLEAN BootPolicy,
	EFI_HANDLE ParentImageHandle, EFI_DEVICE_PATH_PROTOCOL *DevicePath,
	void *SourceBuffer, UINTN SourceSize, EFI_HANDLE *ImageHandle);

typedef EFI_STATUS (*EFI_IMAGE_UNLOAD)(EFI_HANDLE ImageHandle);

typedef EFI_STATUS (*EFI_IMAGE_START)(EFI_HANDLE ImageHandle,
	UINTN *ExitDataSize, CHAR16 **ExitData);

typedef EFI_STATUS (*EFI_EXIT)(EFI_HANDLE ImageHandle, EFI_STATUS ExitStatus,
	UINTN ExitDataSize, CHAR16 *ExitData);

typedef EFI_STATUS (*EFI_EXIT_BOOT_SERVICES)(EFI_HANDLE ImageHandle,
	UINTN MapKey);

typedef EFI_STATUS (*EFI_GET_NEXT_MONOTONIC_COUNT)(UINT64 *Count);

typedef EFI_STATUS (*EFI_STALL)(UINTN Microseconds);

typedef EFI_STATUS (*EFI_SET_WATCHDOG_TIMER)(UINTN Timeout, UINT64 WatchdogCode,
	UINTN DataSize, CHAR16 *WatchdogData);

typedef EFI_STATUS (*EFI_CONNECT_CONTROLLER)(EFI_HANDLE ControllerHandle,
	EFI_HANDLE *DriverImageHandle,
	EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath, BOOLEAN Recursive);

typedef EFI_STATUS (*EFI_DISCONNECT_CONTROLLER)(EFI_HANDLE ControllerHandle,
	EFI_HANDLE DriverImageHandle, EFI_HANDLE ChildHandle);

typedef EFI_STATUS (*EFI_OPEN_PROTOCOL)(EFI_HANDLE Handle, EFI_GUID *Protocol,
	void **Interface, EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle,
	UINT32 Attributes);

typedef EFI_STATUS (*EFI_CLOSE_PROTOCOL)(EFI_HANDLE Handle, EFI_GUID *Protocol,
	EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle);

typedef EFI_STATUS (*EFI_CLOSE_PROTOCOL)(EFI_HANDLE Handle, EFI_GUID *Protocol,
	EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle);

typedef EFI_STATUS (*EFI_OPEN_PROTOCOL_INFORMATION)(EFI_HANDLE Handle,
	EFI_GUID *Protocol, EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer,
	UINTN *EntryCount);

typedef EFI_STATUS (*EFI_PROTOCOLS_PER_HANDLE)(EFI_HANDLE Handle,
	EFI_GUID ***ProtocolBuffer, UINTN *ProtocolBufferCount);

typedef EFI_STATUS (*EFI_LOCATE_HANDLE_BUFFER)(EFI_LOCATE_SEARCH_TYPE SearchType,
	EFI_GUID *Protocol, void *SearchKey, UINTN *NoHandles,
	EFI_HANDLE **Buffer);

typedef EFI_STATUS (*EFI_LOCATE_PROTOCOL)(EFI_GUID *Protocol, void *Registration,
	void **Interface);

typedef EFI_STATUS (*EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
	EFI_HANDLE *Handle, ...);

typedef EFI_STATUS (*EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
	EFI_HANDLE Handle, ...);

typedef EFI_STATUS (*EFI_CALCULATE_CRC32)(void *Data, UINTN DataSize,
	UINT32 *Crc32);

typedef void (*EFI_COPY_MEM)(void *Destination, void *Source, UINTN Length);

typedef void (*EFI_SET_MEM)(void *Buffer, UINTN Size, UINT8 Value);

typedef void (*EFI_CREATE_EVENT_EX)(UINT32 Type, EFI_TPL NotifyTpl,
	EFI_EVENT_NOTIFY NotifyFunction, const void *NotifyContext,
	const EFI_GUID *EventGroup, EFI_EVENT *Event);

/*
 * UEFI 2.10 Specs PDF Page 92
 * NOTE: LoadImage function type is wrongly defined in the spec - function is
 * EFI_IMAGE_UNLOAD instead of EFI_IMAGE_LOAD.
 *
 * NOTE 2: InstallMultipleProtocolInterfaces function type is wrongly defined
 * in the spec - function is EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES instead
 * of EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES.
 */
typedef struct {
	EFI_TABLE_HEADER			Hdr;
	EFI_RAISE_TPL				RaiseTPL;
	EFI_RESTORE_TPL				RestoreTPL;
	EFI_ALLOCATE_PAGES			AllocatePages;
	EFI_FREE_PAGES				FreePages;
	EFI_GET_MEMORY_MAP			GetMemoryMap;
	EFI_ALLOCATE_POOL			AllocatePool;
	EFI_FREE_POOL				FreePool;
	EFI_CREATE_EVENT			CreateEvent;
	EFI_SET_TIMER				SetTimer;
	EFI_WAIT_FOR_EVENT			WaitForEvent;
	EFI_SIGNAL_EVENT			SignalEvent;
	EFI_CLOSE_EVENT				CloseEvent;
	EFI_CHECK_EVENT				CheckEvent;
	EFI_INSTALL_PROTOCOL_INTERFACE		InstallProtocolInterface;
	EFI_REINSTALL_PROTOCOL_INTERFACE	ReinstallProtocolInterface;
	EFI_UNINSTALL_PROTOCOL_INTERFACE	UninstallProtocolInterface;
	EFI_HANDLE_PROTOCOL			HandleProtocol;
	void *					Reserved;
	EFI_REGISTER_PROTOCOL_NOTIFY		RegisterProtocolNotify;
	EFI_LOCATE_HANDLE			LocateHandle;
	EFI_LOCATE_DEVICE_PATH			LocateDevicePath;
	EFI_INSTALL_CONFIGURATION_TABLE		InstallConfigurationTable;
	EFI_IMAGE_LOAD				LoadImage;
	EFI_IMAGE_START				StartImage;
	EFI_EXIT				Exit;
	EFI_IMAGE_UNLOAD			UnloadImage;
	EFI_EXIT_BOOT_SERVICES			ExitBootServices;
	EFI_GET_NEXT_MONOTONIC_COUNT		GetNextMonotonicCount;
	EFI_STALL				Stall;
	EFI_SET_WATCHDOG_TIMER			SetWatchdogTimer;
	EFI_CONNECT_CONTROLLER			ConnectController;
	EFI_DISCONNECT_CONTROLLER		DisconnectController;
	EFI_OPEN_PROTOCOL			OpenProtocol;
	EFI_CLOSE_PROTOCOL			CloseProtocol;
	EFI_OPEN_PROTOCOL_INFORMATION		OpenProtocolInformation;
	EFI_PROTOCOLS_PER_HANDLE		ProtocolsPerHandle;
	EFI_LOCATE_HANDLE_BUFFER		LocateHandleBuffer;
	EFI_LOCATE_PROTOCOL			LocateProtocol;
	EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES InstallMultipleProtocolInterfaces;
	EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces;
	EFI_CALCULATE_CRC32			CalculateCrc32;
	EFI_COPY_MEM				CopyMem;
	EFI_SET_MEM				SetMem;
	EFI_CREATE_EVENT_EX			CreateEventEx;
} EFI_BOOT_SERVICES;

// UEFI 2.10 Specs PDF Page 98
typedef struct{
	EFI_GUID	VendorGuid;
	void *		VendorTable;
} EFI_CONFIGURATION_TABLE;

/*
 * EFI has a system and runtime. This system table is the first struct
 * called from the main section.
 * UEFI 2.10 Specs PDF Page 91
 */
typedef struct {
	EFI_TABLE_HEADER			Hdr;
	CHAR16 *				FirmwareVendor;
	UINT32					FirmwareVersion;
	EFI_HANDLE				ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL *	ConIn;
	EFI_HANDLE				ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *	ConOut;
	EFI_HANDLE				StandardErrorHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *	StdErr;
	EFI_RUNTIME_SERVICES *			RuntimeServices;
	EFI_BOOT_SERVICES *			BootServices;
	UINTN					NumberOfTableEntries;
	EFI_CONFIGURATION_TABLE *		ConfigurationTable;
} EFI_SYSTEM_TABLE;

#endif // EFI_H
