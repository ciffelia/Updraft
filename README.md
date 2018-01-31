# Updraft

[![Build status](https://ci.appveyor.com/api/projects/status/gdgm3pft3gcovlrh?svg=true)](https://ci.appveyor.com/project/prince0203/updraft)
[![CircleCI](https://circleci.com/gh/prince0203/Updraft.svg?style=svg)](https://circleci.com/gh/prince0203/Updraft)

## Building Updraft on Windows

### Requirements

* [Visual Studio 2015](https://www.microsoft.com/ja-jp/dev/products/visual-studio-2015.aspx) with C++ support **or** [Visual C++ 2015 Build Tools](https://landinghub.visualstudio.com/visual-cpp-build-tools)
* [Nasm](http://www.nasm.us/)
  * Install and configure `NASM_PREFIX` env to point `C:\path\to\nasm\`. **(Don't forget the trailing backslash character!)**
* [ASL Compiler](https://acpica.org/downloads/binary-tools)
  * Download and extract zip to `C:\ASL`.
* [edk2-BaseTools-win32](https://github.com/tianocore/edk2-BaseTools-win32)
  * Clone the repository and configure `EDK_TOOLS_BIN` env to point `C:\path\to\edk2-BaseTools-win32`.
* [QEMU](https://www.qemu.org/)

```shell
# VS2015 command prompt
> git submodule init
> git submodule update
> nmake -f Makefile.win32 build copy run
```

## License information

Following file contains codes from [Vec2 クラスを作る（モダンな C++ クラスデザインのためのチュートリアル） - Qiita](https://qiita.com/Reputeless/items/96226cfe1282a014b147) (Public domain).

* [Vec2.hpp](Utils/Vec2.hpp)

Following file contains codes from [OpenSiv3D](https://github.com/Siv3D/OpenSiv3D) [(MIT License)](https://github.com/Siv3D/OpenSiv3D/blob/master/LICENSE).

* [Circular.hpp](Utils/Circular.hpp)
