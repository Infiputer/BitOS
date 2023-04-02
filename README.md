# BitOS
BitOS is a basic operating system that is written in C++ and Assembly for the x86_64 architecture. The OS has been designed to run on a virtual machine, such as QEMU, and can be built on any Linux distribution with GCC and NASM installed. The OS source code is organized into a src directory, containing both C++ and Assembly files, which are compiled into object files and placed in a lib directory. The kernel.ld file is used to link the object files and generate the kernel binary kernel.elf, which can be loaded onto a bootable disk image using the make buildimg command. The OS also includes a bootloader written in GNU-EFI, which can be built using the make bootloader command. Once built, the OS can be run on QEMU using the make run command.

The BitOS kernel includes basic features such as keyboard input and output, a PS/2 mouse driver, and support for paging and interrupts. The OS also includes a basic user interface that displays a command prompt and allows the user to interact with the system via basic shell commands. The Makefile included with the OS provides a convenient way to compile and build the system, and can be easily customized to fit different use cases.
### Features
- PS/2 keyboard support
- PS/2 mouse support
- Basic memory manager
- Basic windowing system with a single desktop and window management features (move, resize, close)
### Features being worked on
- Running EXE files
- USB device interface
- Networking
### Requirements
- A Linux, WSL, or macOS environment
- QEMU
- GCC
- NASM
- GNU Binutils
### Building and Executing
To build BitOS, navigate to the root directory of the project and run the run.bat script. This will compile the kernel and bootloader, create an image file, and start QEMU to run the operating system.
 ```shell
 bash run.bat
 ```
### Problems
- A general protection occurs occasionally
- Due to double-buffering parts of the screen glitch
