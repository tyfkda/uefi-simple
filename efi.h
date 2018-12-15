#pragma once

#define IN
#define EFIAPI
#define EFI_SUCCESS 0

#ifndef wchar_t
#define wchar_t wchar_t
typedef __WCHAR_TYPE__ wchar_t;
#endif

typedef wchar_t CHAR16;
typedef unsigned long long EFI_STATUS;
typedef void *EFI_HANDLE;

struct EFI_INPUT_KEY {
  CHAR16 ScanCode;
  CHAR16 UnicodeChar;
};

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
  unsigned long long _buf;
  EFI_STATUS (EFIAPI *ReadKeyStroke)(IN struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
                                     IN struct EFI_INPUT_KEY *Key);
  void *WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
  void *a;
  EFI_STATUS (EFIAPI *OutputString)(IN struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
                                    IN CHAR16 *String);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct {
  char                             a[44];
  EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *ConIn;
  EFI_HANDLE                       ConsoleOutHandle;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *ConOut;
} EFI_SYSTEM_TABLE;
