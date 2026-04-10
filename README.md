# Smile OS

a simple 32-bit x86 hobby operating system written in C. Aesthetically mimics ULTRAKILL's terminal (game by Hakita), but it's an older console-based version (at least for now).

![Screenshot](./smile-os-ss.png)

## Features
1. Working shell with commands (currently 4)
2. PS/2 Keyboard driver
3. GDT
4. IDT
5. Timer
6. VGA text mode

## Install

1. Get the ISO inside the /src directory of this repo

2. ```bash
   qemu-system-i386 -cdrom smile-os.iso
   ```

