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

static CHAR16 kNewLine[] = L"\r\n";

EFI_STATUS EFIAPI
EfiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *st) {
  st->ConOut->OutputString(st->ConOut, L"Hello World!\r\n");
  while(1) {
    struct EFI_INPUT_KEY key;
    st->ConIn->ReadKeyStroke(st->ConIn, &key);
    switch (key.UnicodeChar) {
    case L'\0':
      break;
    case L'\r':
      st->ConOut->OutputString(st->ConOut, kNewLine);
      break;
    default:
      {
        CHAR16 s[2];
        s[0] = key.UnicodeChar;
        s[1] = L'\0';
        st->ConOut->OutputString(st->ConOut, s);
      }
      break;
    }
  }
  return EFI_SUCCESS;
}
