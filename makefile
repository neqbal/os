start: riscv.out
	qemu-system-riscv64 -machine virt -bios none -m 128M -gdb tcp::1234 -S -kernel riscv.out -serial stdio

riscv.out:
	riscv64-unknown-elf-gcc -g -mcmodel=medany -ffreestanding -O0 -Wl,--gc-sections \
    -nostartfiles -nostdlib -nodefaultlibs -Wl,-T,riscv64-virt.ld \
    crt0.s main.c ns16550a.s -o riscv.out





