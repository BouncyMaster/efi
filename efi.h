#ifndef EFI_H
#define EFI_H

#define TRUE	1
#define FALSE	0

#define EFI_SUCCESS	0

typedef unsigned char		BOOLEAN;
typedef unsigned int		UINT32;
typedef int			INT32;
typedef unsigned long long	UINT64;
typedef unsigned short		CHAR16;
typedef void			*EFI_HANDLE;
typedef UINT64			UINTN;
typedef UINTN			EFI_STATUS;

/*
 * This struct is a placeholder and not usable at this time
 * The code will not compile without it though.
 */
typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

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
typedef struct SIMPLE_TEXT_OUTPUT_MODE {
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
	SIMPLE_TEXT_OUTPUT_MODE		*Mode;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

/*
 * This is the main EFI header for all of the EFI protocols.
 * UEFI 2.10 Specs PDF Page 89
 */
typedef struct EFI_TABLE_HEADER {
	UINT64	Signature;
	UINT32	Revision;
	UINT32	HeaderSize;
	UINT32	CRC32;
	UINT32	Reserved;
} EFI_TABLE_HEADER;

/*
 * EFI has a system and runtime. This system table is the first struct
 * called from the main section.
 * UEFI 2.10 Specs PDF Page 90
 */
typedef struct EFI_SYSTEM_TABLE {
	EFI_TABLE_HEADER			hrd;
	CHAR16					*FirmwareVendor;
	UINT32					FirmwareVersion;
	EFI_HANDLE				ConsoleInHandle;
	EFI_SIMPLE_TEXT_INPUT_PROTOCOL		*ConIn;
	EFI_HANDLE				ConsoleOutHandle;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL		*ConOut;
} EFI_SYSTEM_TABLE;

#endif // EFI_H
