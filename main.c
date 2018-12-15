#include "efi.h"

#define FALSE   (0)
#define TRUE    (1)

static CHAR16 kNewLine[] = L"\r\n";

EFI_STATUS EFIAPI
EfiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *st) {
  EFI_STATUS status;
  status = st->ConOut->OutputString(st->ConOut, L"Hello World!\r\n");
  if (EFI_ERROR(status))
    return status;

  status = st->ConIn->Reset(st->ConIn, FALSE);
  if (EFI_ERROR(status))
    return status;

  while(1) {
    UINTN waitidx;
    st->BootServices->WaitForEvent(1, &(st->ConIn->WaitForKey), &waitidx);

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
