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


typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
  void             *a;
  EFI_STATUS (EFIAPI *OutputString)(
      IN struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
      IN CHAR16                                  *String);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct {
  char                             a[52];
  EFI_HANDLE                       ConsoleOutHandle;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *ConOut;
} EFI_SYSTEM_TABLE;

EFI_STATUS EFIAPI
EfiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable) {
  SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello World!\r\n");
  while(1);
  return EFI_SUCCESS;
}
