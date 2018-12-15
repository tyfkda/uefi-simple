#include "efi.h"

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
