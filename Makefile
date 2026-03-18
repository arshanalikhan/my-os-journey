C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)
OBJ = ${C_SOURCES:.c=.o} cpu/interrupt.o cpu/task.o cpu/gdt_asm.o drivers/vga.o drivers/gui_text.o drivers/mouse.o

CC = gcc
CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector -g

all: os-image.bin

os-image.bin: boot.bin kernel.bin app.elf
	dd if=/dev/zero of=os-image.bin bs=512 count=100
	dd if=boot.bin of=os-image.bin conv=notrunc
	dd if=kernel.bin of=os-image.bin seek=1 conv=notrunc
	dd if=app.elf of=os-image.bin seek=60 conv=notrunc

kernel.bin: kernel_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x8000 $^ --oformat binary

# --- DAY 24: COMPILE THE APP WITH LIBC ---
app.elf: userland/app.c userland/libc.c
	gcc -m32 -ffreestanding -fno-pie -c userland/libc.c -o libc.o
	gcc -m32 -ffreestanding -fno-pie -c userland/app.c -o app.o
	ld -m elf_i386 -N -e main -Ttext 0x200000 app.o libc.o -o app.elf
	strip app.elf

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm -f elf $< -o $@

boot.bin: boot.asm
	nasm -f bin $< -o $@

kernel_entry.o: kernel_entry.asm
	nasm -f elf $< -o $@

cpu/interrupt.o: cpu/interrupt.asm
	nasm -f elf $< -o $@

cpu/task.o: cpu/task.asm
	nasm -f elf $< -o $@

cpu/gdt_asm.o: cpu/gdt_asm.asm
	nasm -f elf $< -o $@

run: os-image.bin
	qemu-system-i386 -hda os-image.bin

clean:
	rm -fr *.bin *.o *.elf os-image.bin
	rm -fr kernel/*.o drivers/*.o cpu/*.o
