#ifndef EFI_H
#define EFI_H

typedef unsigned char		UINT8;
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

#define TRUE	1
#define FALSE	0

#define EFI_SUCCESS	0
#define EFI_ERROR(Status) (((INTN)Status) < 0)

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
} EFI_GRAPHICS_OUTPUT_PROTCOL;


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
	INT16	TimeZone
	UINT8	Daylight;
	UINT8	Pad2;
} EFI_TIME;

typedef struct {
	UINT32		Resolution;
	UINT32		Accuracy;
	BOOLEAN		SetsToZero;
} EFI_TIME_CAPABILITIES;

typedef struct {
	UINT32	Data1;
	UINT16	Data2;
	UINT16	Data3;
	UINT8	Data4[8];
} EFI_GUID;

typedef enum {
	EfiResetCold,
	EfiResetWarm,
	EfiResetShutdown
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

// TODO: define EFI_BOOT_SERVICES && EFI_CONFIGURATION_TABLE

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
