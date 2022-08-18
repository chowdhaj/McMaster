.globl main

	.text

main:

	li $a0, 10 #Used to set the arg value
	li $v0, 0 #Just making sure it is 0 at the start
	j fib

fib:
	
	addi $sp, $sp, -8
	sw $ra, 4($sp)
	sw $a0, 0($sp)
	bgt $a0, $0, test2
	j rtn

test2:

	addi $t0, $0, 1	
	bne $t0, $a0, gen
	add $v0, $v0, $t0
	j rtn

gen:

	addi, $a0, -1
	jal fib
	addi, $a0, -1
	jal fib
	j rtn

rtn:

	lw $a0, 0($sp)
	lw $ra, 4($sp)
	addi $sp, $sp, 8
	sw $v0, 0x10000000 #This line just saves the value in memory at the end because when I run QtSpim it changes this register value when the program finishes
	jr $ra