# magicfix
Command-line tool to repair your file extensions

File signatures are from both [Wikipedia](https://en.wikipedia.org/wiki/List_of_file_signatures) as well as the [infer](https://github.com/bojand/infer) crate.  
The tool only depends on the C Standard Libraries, as well as `windows.h` on Windows, so it practically compiles anywhere.

## Installation
### Windows
WIP, but forget about Visual Studio and the MSVC compiler. Use UCRT GCC from MinGW and add it to your PATH, then open the project in Visual Studio Code.  
Technically Visual Studio and MSVC works too, but basically no optimizations are made there for some reason...

### Linux
WIP.