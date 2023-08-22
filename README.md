# magicfix
Command-line tool to repair your file extensions

File signatures are from both [Wikipedia](https://en.wikipedia.org/wiki/List_of_file_signatures) as well as [ftyps.com](https://www.ftyps.com/).  
The tool only depends on the C Standard Libraries so it practically compiles anywhere, even on your phone!

<hr>

## Usage
### Tool
```bash
magicfix /path/to/file.ext some.file.lol ../more/.dotfiles
```

### Library
This project is also designed to be used as a library. Just clone or submodule this repository into your include-Path. You should be able to access it with:
```c
#include <magicfix/magicfix.h>
```
The full documentation is available in the [Wiki](https://github.com/Stridsvagn69420/magicfix/wiki/libmagicfix).

<hr>

## Installation
This section is only about self-compilation. Check the [Release Page](https://github.com/Stridsvagn69420/magicfix/releases) for prebuilt binaries.

### Windows (MSVC)
#### Requirements:
- Visual Studio 2022
- Desktop C++ Workflow

#### Instructions
1. Open Visual Studio and clone the repository: `https://github.com/Stridsvagn69420/magicfix.git`
2. Switch to Folder View in the Project Explorer
3. Select `magicfix.exe` as the Start Element
4. (Optional) Choose your desired build target (`x64-Release` by default)
5. Build the Project with `Ctrl` + `B`
6. The tool is located at `./out/build/{build-target}/magicfix.exe`

### Windows (MSYS2) and Unix
#### Requirements:
- `cmake`
- `make`
- `gcc` or `clang`
- `git`
- UCRT recommended (Windows only)

#### Instructions:
1. Clone the repository: `git clone https://github.com/Stridsvagn69420/magicfix.git && cd magicfix`
2. Build the repository: `make` (Also define the env variable `CC_NATIVE` to optimize for your CPU)
3. Install the program on your systen: `sudo make install` (Unix only)

Or use the Linux One Line Installer™️:
```bash
git clone https://github.com/Stridsvagn69420/magicfix.git && cd magicfix && make && sudo make install && make clean && cd .. && rm -rf magicfix
```
