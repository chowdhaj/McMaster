# RISC-V - Arrays and pointers - RV32
.data
X:
    .word   2
    .word   3
    .word   4
    .word   5
    .word   6
    
n:  .word   5    

.text
main:
     
    la   x10, X
    la   x5, n
    lw   x11,0(x5)
    jal  x1, clear1 
    #jal  x1, clear2
    
    addi  x10, x0, 10
    ecall # Exit

# Array indexing    
clear1:
    li   x5,0
loop1:
    slli x6, x5, 2    # x6 = i * 4
    add  x7,x10,x6    # x7 = address of array[i]
    sw   x0,0(x7)     # array[i] = 0
    addi x5,x5,1      # x5 = x5+1 
    blt  x5,x11,loop1 # if x5 < x11 goto loop1	
    jalr  x0,0(x1)	  # return

#Pointers    
clear2:
    mv   x5,x10      # p = address of array[0]
    slli x6, x11, 2    # x6 = i * 4
    add  x7,x10,x6    # x7 = address of array[n]
loop2:    
    sw   x0,0(x5)     # array[i] = 0
    addi x5,x5,4      # p = p+ 4
    bltu  x5,x7,loop2 # if x5 < x11 goto loop1	
    jalr  x0,0(x1)	  # return