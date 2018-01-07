#include "UefiSystem.hpp"

extern "C" {
#include <Library/CpuLib.h>
}

#include "Logger.hpp"

EFI_SYSTEM_TABLE *UefiSystem::s_SystemTable = nullptr;

// ウォッチドッグタイマを解除
// これをやらないと起動後5分で再起動するらしい
void UefiSystem::ReleaseWatchdogTimer()
{
  const EFI_STATUS status = s_SystemTable->BootServices->SetWatchdogTimer(0, 0, 0, nullptr);
  if(EFI_ERROR(status))
  {
    Logger::Println_("Error: ", PrintEfiStatus(status), " on UEFI initialization.");
    SleepForever();
  }
}

void UefiSystem::Initialize(EFI_SYSTEM_TABLE *SystemTable)
{
  s_SystemTable = SystemTable;

  ReleaseWatchdogTimer();
}

EFI_SYSTEM_TABLE* UefiSystem::SystemTable()
{
  return s_SystemTable;
}

void UefiSystem::SleepForever()
{
  while(true) ::CpuSleep();
}
