# RISC-V factorial - RV32
.data
n: .word 5

.text
main:
    la x5, n
    lw x10, 0(x5)
    jal x1, fact
    
    addi x11, x10, 0
    addi x10, x0, 1
    ecall # Print Result
    
    addi x10, x0, 10
    ecall # Exit
    
fact:
	addi sp,sp,-8
    sw   x1,4(sp)
    sw   x10,0(sp)
    addi x5,x10,-1
    bge  x5,x0,L1
    addi x10,x0,1
    addi sp,sp,8
    jalr x0,0(x1)
L1: addi x10,x10,-1
    jal  x1,fact
    addi x6,x10,0
    lw   x10,0(sp)
    lw   x1,4(sp)
    addi sp,sp,8
    mul  x10,x10,x6
    jalr x0,0(x1)