#pragma once

#define IN
#define OUT
#define OPTIONAL
#define EFIAPI
#define EFI_SUCCESS 0

#ifndef wchar_t
#define wchar_t wchar_t
typedef __WCHAR_TYPE__ wchar_t;
#endif

typedef unsigned long long UINTN;

typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef unsigned long long UINT64;
typedef void VOID;
typedef unsigned char BOOLEAN;

typedef wchar_t CHAR16;
typedef UINTN EFI_STATUS;
typedef VOID *EFI_HANDLE;

typedef UINTN EFI_PHYSICAL_ADDRESS;
typedef UINTN EFI_VIRTUAL_ADDRESS;

typedef UINTN EFI_TPL;
typedef VOID *EFI_EVENT;

#define EFI_ERROR(status)  ((status) != EFI_SUCCESS)

enum EFI_MEMORY_TYPE {
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
  EfiMaxMemoryType
};

enum EFI_TIMER_DELAY {
  TimerCancel,
  TimerPeriodic,
  TimerRelative
};

struct EFI_INPUT_KEY {
  CHAR16 ScanCode;
  CHAR16 UnicodeChar;
};

typedef struct EFI_GUID {
  UINT32 Data1;
  UINT16 Data2;
  UINT16 Data3;
  UINT8 Data4[8];
} EFI_GUID;

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
  EFI_STATUS (EFIAPI *Reset)(IN struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
                             IN BOOLEAN ExtendedVerification);
  EFI_STATUS (EFIAPI *ReadKeyStroke)(IN struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This,
                                     IN struct EFI_INPUT_KEY *Key);
  void *WaitForKey;
} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
  void *a;
  EFI_STATUS (EFIAPI *OutputString)(IN struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This,
                                    IN CHAR16 *String);
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef struct EFI_RUNTIME_SERVICES EFI_RUNTIME_SERVICES;

typedef struct EFI_MEMORY_DESCRIPTOR {
  UINT32 Type;
  EFI_PHYSICAL_ADDRESS PhysicalStart;
  EFI_VIRTUAL_ADDRESS VirtualStart;
  UINT64 NumberOfPages;
  UINT64 Attribute;
} EFI_MEMORY_DESCRIPTOR;

typedef struct EFI_DEVICE_PATH_PROTOCOL {
  UINT8 Type;
  UINT8 SubType;
  UINT8 Length[2];
} EFI_DEVICE_PATH_PROTOCOL;

typedef struct EFI_BOOT_SERVICES {
  char _buf1[24];

  //
  // Task Priority Services
  //
  unsigned long long _buf2[2];

  //
  // Memory Services
  //
  unsigned long long _buf3[2];
  EFI_STATUS (EFIAPI *GetMemoryMap)(IN OUT UINTN *MemoryMapSize,
                                    IN OUT EFI_MEMORY_DESCRIPTOR *MemoryMap,
                                    OUT UINTN *MapKey,
                                    OUT UINTN *DescriptorSize,
                                    OUT UINT32 *DescriptorVersion);
  EFI_STATUS (EFIAPI *AllocatePool)(IN enum EFI_MEMORY_TYPE PoolType,
                                    IN unsigned long long Size,
                                    OUT void **Buffer);
  EFI_STATUS (EFIAPI *FreePool)(IN VOID *Buffer);

  //
  // Event & Timer Services
  //
  EFI_STATUS (EFIAPI *CreateEvent)(IN UINT32 Type,
                                   IN EFI_TPL NotifyTpl,
                                   void (*NotifyFunction)(void *Event, void *Context),
                                   IN VOID *NotifyContext,
                                   OUT EFI_EVENT *Event);
  EFI_STATUS (EFIAPI *SetTimer)(IN EFI_EVENT Event,
                                IN enum EFI_TIMER_DELAY Type,
                                IN UINT64 TriggerTime);
  EFI_STATUS (EFIAPI *WaitForEvent)(IN UINTN NumberOfEvents,
                                    IN EFI_EVENT *Event,
                                    OUT UINTN *Index);
  unsigned long long _buf4_2[3];

  //
  // Protocol Handler Services
  //
  unsigned long long _buf5[9];

  //
  // Image Services
  //
  EFI_STATUS (EFIAPI *LoadImage)(IN BOOLEAN BootPolicy,
                                 IN EFI_HANDLE ParentImageHandle,
                                 IN EFI_DEVICE_PATH_PROTOCOL *DevicePath,
                                 IN VOID *SourceBuffer,
                                 IN UINTN SourceSize,
                                 OUT EFI_HANDLE *ImageHandle);
  EFI_STATUS (EFIAPI *StartImage)(IN EFI_HANDLE ImageHandle,
                                  OUT UINTN *ExitDataSize,
                                  OUT CHAR16 **ExitData);
  unsigned long long _buf6[2];
  EFI_STATUS (EFIAPI *ExitBootServices)(IN EFI_HANDLE ImageHandle,
                                        IN UINTN MapKey);

  //
  // Miscellaneous Services
  //
  unsigned long long _buf7[2];
  EFI_STATUS (EFIAPI *SetWatchdogTimer)(IN UINTN Timeout,
                                        IN UINT64 WatchdogCode,
                                        IN UINTN DataSize,
                                        IN CHAR16 *WatchdogData);

  //
  // DriverSupport Services
  //
  unsigned long long _buf8[2];

  //
  // Open and Close Protocol Services
  //
  EFI_STATUS (EFIAPI *OpenProtocol)(IN EFI_HANDLE Handle,
                                    IN EFI_GUID *Protocol,
                                    OUT VOID **Interface,
                                    OPTIONAL IN EFI_HANDLE AgentHandle,
                                    IN EFI_HANDLE ControllerHandle,
                                    IN UINT32 Attributes);
  unsigned long long _buf9[2];

  //
  // Library Services
  //
  unsigned long long _buf10[2];
  EFI_STATUS (EFIAPI *LocateProtocol)(IN EFI_GUID *Protocol,
                                      IN VOID *Registration,
                                      OPTIONAL OUT VOID **Interface);
  unsigned long long _buf10_2[2];

  //
  // 32-bit CRC Services
  //
  unsigned long long _buf11;

  //
  // Miscellaneous Services
  //
  VOID (EFIAPI *CopyMem)(IN VOID *Destination,
                         IN VOID *Source,
                         IN UINTN Length);
  VOID (EFIAPI *SetMem)(IN VOID *Buffer,
                        IN UINTN Size,
                        IN UINT8 Value);
  unsigned long long _buf12;
} EFI_BOOT_SERVICES;

typedef struct {
  char                             a[44];
  EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *ConIn;
  EFI_HANDLE                       ConsoleOutHandle;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *ConOut;
  EFI_HANDLE                       StandardErrorHandle;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *StdErr;
  EFI_RUNTIME_SERVICES             *RuntimeServices;
  EFI_BOOT_SERVICES                *BootServices;
} EFI_SYSTEM_TABLE;
