start: kernel.elf
	qemu-system-riscv64 -machine virt -bios none -kernel kernel.elf -serial mon:stdio

kernel.elf: kernel.o
	riscv64-unknown-elf-gcc -T linker.ld -nostdlib kernel.o entry.o -o kernel.elf

kernel.o: entry.o
	riscv64-unknown-elf-gcc -Wall -Wextra -c -mcmodel=medany kernel.c -o kernel.o -ffreestanding

entry.o:
	riscv64-unknown-elf-as -c entry.S -o entry.o



