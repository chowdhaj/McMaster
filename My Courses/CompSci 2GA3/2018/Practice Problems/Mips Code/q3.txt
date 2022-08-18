.globl main

	.text

main:
	li $a0, 0x190
	li $a1, 0x3E7
        li $t0, 0x1234567
        li $t1, 0x89ABCDEF
	li $s0, 0x10000000
	li $s1, 0x251F326D
	sw $t0, 0x10000008
	sw $t1, 0x1000000C
	lui $t0, 0xFEDC
	ori $t0, 0xBA98
	sw $t0, 0($s0)
	sw $t0, 0x10($s0)
	sw $t0, 0xA($s0)
	li $v0, 10
	syscall