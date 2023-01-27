kernel.o : kernel/kernel.c
	${HOME}/opt/cross/bin/i686-elf-gcc -ffreestanding -m32 -g -c "kernel/kernel.c"  -o "kernel.o"

kernel_entry.o : kernel/kernel_entry.s
	nasm "kernel/kernel_entry.s" -f elf -o "kernel_entry.o"

full_kernel.bin : kernel_entry.o kernel.o
	${HOME}/opt/cross/bin/i686-elf-ld -o "full_kernel.bin" -Ttext 0x1000 "kernel_entry.o" "kernel.o" --oformat binary

boot.bin : boot.s
	nasm "boot.s" -f bin -o "boot.bin"

everything.bin : boot.bin full_kernel.bin
	cat "boot.bin" "full_kernel.bin" > "everything.bin"

os-image : everything.bin padding.bin
	cat "everything.bin"  "padding.bin"> "os-image"; make clean

padding.bin : kernel/padding.s
	nasm "kernel/padding.s" -f bin -o "padding.bin"

clean:
	rm *.bin *.o 2>/dev/null