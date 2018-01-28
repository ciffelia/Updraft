#include "UsbKeyboard.hpp"

#include "UefiSystem.hpp"
#include "Logger.hpp"
#include "Assert.hpp"

extern "C" {
#include <Library/UefiUsbLib.h>
}

EFI_USB_IO_PROTOCOL *UsbKeyboard::s_usbIoProtocol = nullptr;

EFI_USB_INTERFACE_DESCRIPTOR UsbKeyboard::s_interfaceDescriptor;

EFI_USB_ENDPOINT_DESCRIPTOR UsbKeyboard::s_interruptEndpointDescriptor;

bool UsbKeyboard::s_modifierKeysStatus[8];

uint8 UsbKeyboard::s_pressedKeys[6];

void UsbKeyboard::GetUsbIoProtocolHandles(EFI_HANDLE **handleBuf, uintn *handleBufCount)
{
  const auto status =
      UefiSystem::SystemTable()->BootServices->LocateHandleBuffer(::ByProtocol, &gEfiUsbIoProtocolGuid, nullptr, handleBufCount, handleBuf);
  AssertEfiStatus(status, "Failed to locate EFI USB IO Protocol Handle.");
}

void UsbKeyboard::GetUsbIoProtocolFromHandle(EFI_USB_IO_PROTOCOL **usbIoProtocol, const EFI_HANDLE handle)
{
  const auto status =
      UefiSystem::SystemTable()->BootServices->HandleProtocol(handle, &gEfiUsbIoProtocolGuid, (void **)usbIoProtocol);
  AssertEfiStatus(status, "Failed to locate EFI USB IO Protocol.");
}

void UsbKeyboard::GetUsbInterfaceDescriptorFromProtocol(EFI_USB_INTERFACE_DESCRIPTOR *interfaceDescriptor, EFI_USB_IO_PROTOCOL *usbIoProtocol)
{
  const auto status = usbIoProtocol->UsbGetInterfaceDescriptor(usbIoProtocol, interfaceDescriptor);
  AssertEfiStatus(status, "Failed to get USB interface descriptor.");
}

bool UsbKeyboard::IsUsbKeyboard(const EFI_USB_INTERFACE_DESCRIPTOR interfaceDescriptor)
{
  return interfaceDescriptor.InterfaceClass == 0x03 &&
         interfaceDescriptor.InterfaceSubClass == 0x01 &&
         interfaceDescriptor.InterfaceProtocol == 0x01;
}

void UsbKeyboard::LocateUsbKeyboard()
{
  EFI_HANDLE *handleBuf;
  uintn handleBufCount;
  GetUsbIoProtocolHandles(&handleBuf, &handleBufCount);

  for (int i = 0; i < (int)handleBufCount; i++)
  {
    EFI_USB_IO_PROTOCOL *usbIoProtocol = nullptr;
    GetUsbIoProtocolFromHandle(&usbIoProtocol, handleBuf[i]);

    EFI_USB_INTERFACE_DESCRIPTOR interfaceDescriptor;
    GetUsbInterfaceDescriptorFromProtocol(&interfaceDescriptor, usbIoProtocol);

    if (IsUsbKeyboard(interfaceDescriptor))
    {
      const auto status =
          UefiSystem::SystemTable()->BootServices->DisconnectController(handleBuf[i], nullptr, nullptr);
      AssertEfiStatus(status, "Failed to disconnect controller.");

      s_usbIoProtocol = usbIoProtocol;
      s_interfaceDescriptor = interfaceDescriptor;
      break;
    }
  }

  delete[] handleBuf;

  Assert(s_usbIoProtocol != nullptr, "No USB keyboard found.");
}

bool UsbKeyboard::IsInterruptEndpoint(const EFI_USB_ENDPOINT_DESCRIPTOR endpointDescriptor)
{
  return (endpointDescriptor.Attributes & (BIT0 | BIT1)) == USB_ENDPOINT_INTERRUPT;
}

void UsbKeyboard::LocateInterruptEndpoint()
{
  for (int i = 0; i < s_interfaceDescriptor.NumEndpoints; i++)
  {
    EFI_USB_ENDPOINT_DESCRIPTOR endpointDescriptor;
    const auto status = s_usbIoProtocol->UsbGetEndpointDescriptor(s_usbIoProtocol, (uint8)i, &endpointDescriptor);
    AssertEfiStatus(status, "Failed to get endpoint descriptor.");

    if (IsInterruptEndpoint(endpointDescriptor))
    {
      s_interruptEndpointDescriptor = endpointDescriptor;
      return;
    }
  }

  Assert(false, "USB keyboard interrupt endpoint not found");
}

void UsbKeyboard::SetProtocolRequest()
{
  const auto status = ::UsbSetProtocolRequest(s_usbIoProtocol, s_interfaceDescriptor.InterfaceNumber, 0x01);
  AssertEfiStatus(status, "Failed to set USB protocol.");
}

void UsbKeyboard::SetupKeyboardHandler()
{
  const auto status = s_usbIoProtocol->UsbAsyncInterruptTransfer(
    s_usbIoProtocol,
    s_interruptEndpointDescriptor.EndpointAddress,
    true,
    s_interruptEndpointDescriptor.Interval,
    s_interruptEndpointDescriptor.MaxPacketSize,
    KeyboardHandler,
    nullptr);

  AssertEfiStatus(status, "UsbAsyncInterruptTransfer failed.");
}

EFI_STATUS UsbKeyboard::KeyboardHandler(void *data, const uintn dataLength, void *, const uint32 status)
{
  Assert(status == EFI_USB_NOERROR, "KeyboardHandler: status suggests error.");

  if (data == nullptr || dataLength == 0)
    return EFI_SUCCESS;

  Assert(dataLength == 8, "KeyboardHandler: dataLength != 8");

  const uint8 *keyCodeBuffer = (uint8 *)data;

  for (int i = 0; i < 8; i++)
  {
    if ((keyCodeBuffer[0] >> i) & 1)
      s_modifierKeysStatus[i] = true;
    else
      s_modifierKeysStatus[i] = false;
  }

  for (int i = 0; i < 6; i++)
  {
    s_pressedKeys[i] = keyCodeBuffer[i + 2];
  }

  return EFI_SUCCESS;
}

bool UsbKeyboard::IsPressed(const uint8 keyCode, const bool isModifierKey)
{
  if (isModifierKey)
    return s_modifierKeysStatus[keyCode];

  for (int i = 0; i < 6; i++)
  {
    if (s_pressedKeys[i] == keyCode)
      return true;
  }

  return false;
}

void UsbKeyboard::Initialize()
{
  for (int i = 0; i < 8; i++)
    s_modifierKeysStatus[i] = false;
  
  for (int i = 0; i < 6; i++)
    s_pressedKeys[i] = 0;

  LocateUsbKeyboard();

  LocateInterruptEndpoint();

  SetProtocolRequest();

  SetupKeyboardHandler();
}
