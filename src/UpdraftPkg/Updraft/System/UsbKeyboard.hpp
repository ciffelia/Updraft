#pragma once

extern "C" {
#include <Uefi.h>
#include <Protocol/UsbIo.h>
}

#include "../Utils/Types.hpp"

class UsbKeyboard
{
  static EFI_USB_IO_PROTOCOL *s_usbIoProtocol;

  static EFI_USB_INTERFACE_DESCRIPTOR s_interfaceDescriptor;

  static EFI_USB_ENDPOINT_DESCRIPTOR s_interruptEndpointDescriptor;

  static bool s_modifierKeysStatus[];
  
  static uint8 s_pressedKeys[];

  static void GetUsbIoProtocolHandles(EFI_HANDLE **handleBuf, uintn *handleBufCount);

  static void GetUsbIoProtocolFromHandle(EFI_USB_IO_PROTOCOL **usbIoProtocol, const EFI_HANDLE handle);

  static void GetUsbInterfaceDescriptorFromProtocol(EFI_USB_INTERFACE_DESCRIPTOR *interfaceDescriptor, EFI_USB_IO_PROTOCOL *usbIoProtocol);

  static bool IsUsbKeyboard(const EFI_USB_INTERFACE_DESCRIPTOR interfaceDescriptor);

  static void LocateUsbKeyboard();

  static bool IsInterruptEndpoint(const EFI_USB_ENDPOINT_DESCRIPTOR endpointDescriptor);

  static void SetProtocolRequest();

  static void LocateInterruptEndpoint();

  static void SetupKeyboardHandler();

  static uint8 ParseUsbKeyCode(const uint8 keyCode);

  static EFI_STATUS KeyboardHandler(void *data, const uintn dataLength, void *context, const uint32 status);

public:
  static bool IsPressed(const uint8 keyCode, const bool isModifierKey);

  static void Initialize();
};
