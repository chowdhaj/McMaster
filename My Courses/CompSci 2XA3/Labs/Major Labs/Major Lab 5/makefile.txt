proj5_1: proj5_1.o asm_io.o driver.c
	 gcc -m32 -o proj5_1 proj5_1.o driver.c asm_io.o
proj5_2: proj5_2.o asm_io.o driver.c
	 gcc -m32 -o proj5_2 proj5_2.o driver.c asm_io.o
bonus: bonus.o asm_io.o driver.c
	 gcc -m32 -o bonus bonus.o driver.c asm_io.o
asm_io.o: asm_io.asm
	nasm -f elf32 -d ELF_TYPE asm_io.asm
proj5_1.o: proj5_1.asm
	nasm -f elf32 -o proj5_1.o proj5_1.asm
proj5_2.o: proj5_2.asm
	nasm -f elf32 -o proj5_2.o proj5_2.asm
bonus.o: bonus.asm
	nasm -f elf32 -o bonus.o bonus.asm
