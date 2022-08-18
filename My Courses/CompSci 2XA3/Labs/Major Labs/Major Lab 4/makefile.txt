all: proj4_1 proj4_2

proj4_2: proj4_2.o asm_io.o driver.c
	 gcc -m32 -o proj4_2 driver.c proj4_2.o asm_io.o
proj4_2.o: proj4_2.asm
	nasm -f elf32 -o proj4_2.o proj4_2.asm
proj4_1: proj4_1.o asm_io.o driver.c
	 gcc -m32 -o proj4_1 driver.c proj4_1.o asm_io.o
proj4_1.o: proj4_1.asm
	nasm -f elf32 -o proj4_1.o proj4_1.asm
asm_io.o: asm_io.asm
	nasm -f elf32 -d ELF_TYPE asm_io.asm
bonus.o: bonus.asm
	nasm -f elf32 -d ELF_TYPE bonus.asm
bonus: bonus.o asm_io.o driver.c
	 gcc -m32 -o bonus driver.c bonus.o asm_io.o
