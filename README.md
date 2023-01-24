<div align="center">
<img src="https://user-images.githubusercontent.com/55928285/214344442-ce5754d7-b0a5-4f91-a04e-a29b771e6103.png" /></br>
</div>

<div align="center">
<b>DaOS is a personal project used to learn more about operating systems and how computers work in low-level area.</b>
</div>
&nbsp;

<div align="center">
<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/Davy133/DaOS">
<img alt="GitHub" src="https://img.shields.io/github/license/Davy133/DaOS">
</div>

<div>
<h1>How to Run</h1>
<p>In order to run this project you will need an x86_64 Assembler, an machine emulator (like Bochs or Qemu), and to build the OS Image.</p>
</div>


```bash
#Clone this repository.
$ git clone https://github.com/Davy133/DaOS

#Go into the repository.
$ cd DaOS

#Build boot.bin.
$ nasm .\boot.s -f bin -o boot.bin

#Make the kernel object file.
$ gcc -ffreestanding -c kernel.c -o kernel.o

#Use linker to build an bin file.
$ ld -o kernel.bin -Ttext 0x1000 kernel.o --oformat binary

#Merge them together.
$ cat boot.bin kernel.bin > os-image

#Use your CPU emulutator to run it.
$ qemu-system-x86_64.exe .\os-image
```
