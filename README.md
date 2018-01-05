# Updraft

[![Build status](https://ci.appveyor.com/api/projects/status/gdgm3pft3gcovlrh?svg=true)](https://ci.appveyor.com/project/prince0203/updraft)

## Building Updraft

### Windows

#### Requirements

* [Nasm](http://www.nasm.us/)
  * Install and configure `NASM_PREFIX` env to point `C:\path\to\nasm\`. **(Don't forget the trailing backslash character!)**
* [ASL Compiler](https://acpica.org/downloads/binary-tools)
  * Download and extract zip to `C:\ASL`.
* [edk2-BaseTools-win32](https://github.com/tianocore/edk2-BaseTools-win32)
  * Clone the repository and configure `EDK_TOOLS_BIN` env to point `C:\path\to\edk2-BaseTools-win32`.

```shell
# VS2015 command prompt
> git submodule init
> git submodule update
> nmake -f Makefile.win32
```

### Linux/Unix

**TBD**
