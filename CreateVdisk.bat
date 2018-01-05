@echo off

setlocal
  REM Check adminiatrator privileges
  net session >nul 2>&1
  if %errorLevel% == 2 (
    echo This program requires adminiatrator privileges.
    exit /b 1
  )

  pushd %~dp0

  set VDISK_FILE="%cd%\dist\Updraft.vhd"
  set VDISK_ASSIGN_LETTER=U

  REM Remove old vdisk
  if exist %VDISK_FILE% del /q %VDISK_FILE%
  if exist %VDISK_FILE% exit /b 1

  REM Create and mount vdisk
  (
  echo create vdisk file=%VDISK_FILE% maximum=128 type=expandable
  echo attach vdisk
  echo clean
  echo convert gpt
  echo create partition primary
  echo format fs=fat32 label="Updraft"
  echo assign letter=%VDISK_ASSIGN_LETTER%
  echo exit
  ) | diskpart

  REM Copy EFI files to vdisk
  xcopy /e /q dist\image\EFI %VDISK_ASSIGN_LETTER%:\EFI\

  REM Unmount vdisk
  (
  echo select vdisk file=%VDISK_FILE%
  echo select volume=%VDISK_ASSIGN_LETTER%
  echo remove letter=%VDISK_ASSIGN_LETTER%
  echo detach vdisk
  echo exit
  ) | diskpart
  
  popd
endlocal
