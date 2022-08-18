# RISC-V - RV32
.data
hw:	.asciiz "Hello World"

.text
main:
	la	x10, hw
	jal x1, print_str
	jal	x1, print_newline	
	li	x10, 10
	ecall
	
print_str:
	mv x11, x10
	li	x10, 4
	ecall
	jalr x0,0(x1)
	
print_newline:
	li	x11, '\n'
	li	x10, 11
	ecall
	jalr x0,0(x1)
	 	
	
	
	