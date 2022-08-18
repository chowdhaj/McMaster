# RISC-V factorial - RV32
.data

Y:  .asciiz	"The quick brown fox\n"
X:	.asciiz	"jumps over the lazy dog\n"
Msg1x: .asciiz	"X Before \"strcpy\": "
Msg2x: .asciiz	"X After \"strcpy\": "
Msg1y: .asciiz	"Y Before \"strcpy\": "
Msg2y: .asciiz	"Y After \"strcpy\": "

.text
main:
    la	 x10, Msg1y # Print Y before "strcpy"
    jal  x1, print_str
    la	 x10, Y
    jal  x1, print_str
    la	 x10, Msg1x # Print X before "strcpy"
    jal  x1, print_str
    la	 x10, X
    jal  x1, print_str
     
    jal  x1, print_newline
     
    la   x10, X
    la   x11, Y
    jal  x1, strcpy # Copy Y to X
    
    la	 x10, Msg2y # Print Y after "strcpy"
    jal  x1, print_str
	la	 x10, Y
    jal  x1, print_str
    la	 x10, Msg2x # Print X after "strcpy"
    jal  x1, print_str
	la	 x10, X
    jal  x1, print_str
    jal	 x1, print_newline
    
    addi  x10, x0, 10
    ecall # Exit
    
strcpy:
	addi  sp,sp,-4		# adjust stack for 1 word
    sw    x19,0(sp)     # save x19 on stack	
    add   x19,x0,x0	    # sets x19 to 0, i=0
L1: 
    add   x5,x19,x11    # x5 = addr of y[i]
    lbu   x6,0(x5)		# x6 = y[i]	
    add   x7,x19,x10	# x7 = addr of x[i]
    sb    x6,0(x7)		# x[i] = y[i]
    beq   x6,x0,L2		# if y[i] == 0 then exit
    addi  x19,x19,1	    # i = i + 1
    jal   x0,L1		    # next iteration of loop
 L2:
    lw    x19,0(sp)	    # restore saved x19
    addi  sp,sp,4		# pop 1 w from stack	
    jalr  x0,0(x1)		# and return
     
print_str:
	mv	  x11, x10
	li	  x10, 4
	ecall
	jalr  x0,0(x1)
	
print_newline:
	li	  x11, '\n'
	li	  x10, 11
	ecall
	jalr  x0,0(x1) 