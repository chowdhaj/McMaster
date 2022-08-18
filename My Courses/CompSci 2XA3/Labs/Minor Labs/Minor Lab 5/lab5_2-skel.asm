%include "asm_io.inc"

SECTION .data

peg1: dd 0,0,0,0,0,0,3,4,9
peg2: dd 0,0,0,0,0,0,0,2,9
peg3: dd 0,0,0,0,0,0,0,1,9

SECTION .bss

line: resb 80
N: resd 3

SECTION .text
   global  asm_main

line1:   ; subroutine line1 expects one address A on stack
         ; it uses three numbers, N1 stored at  address A, 
         ; N2 from stored at address address A+36, and 
         ; N3 stored at address A+72
         ; all three numbers N1, N2, and N3 are expected to
         ; OK and in the range 0..9
; line1 displays a line that is composed like this
; 12-N1 dots, N1 pluses, one |, N1 pluses, 12-N1 dots
; continued the same for N2 and continued the same for N3
;
; for instance if N1=4, N2=2, N3=1 the line will look likes this 
;........++++|++++..................++|++.....................+|+...........

   ; enter subroutine
   ; save all registers

   ; get address of N1
   ; get N1
   ; store it at N
   ; get address of N2
   ; get N2
   ; store it at N+4
   ; get address of N3
   ; get N3
   ; store it at N+8

   ; make ecx point to line, i.e. ecx=line

   ; N is now array of size 3, N[0]=N1, N[1]=N2, N[2]=N3

   ; in a counting loop traverse the array N
   ; use esi as a loop control, i.e. esi=0,1, and 2
   ; use edi as an address of the item of array N, i.e. edi=N,N+4,N+8
   
       ; compute 12-[edi]
       ; in a loop 1.. 12-[edi] store '.' in [ecx]      <-------------------+
       ; at the bottom of the loop increment ecx by 1                       |
                                                                            |
       ; in a loop 1..[edi] store '+' in [ecx]          <----------------+  |      
       ; at the bottom of the loop increment ecx by 1                    |  |
                                                                         |  |
       ; store '|' in [ecx]                                              |  |
       ; increment ecx by 1                                              |  |
                                                                         |  |
                               ; note you can cut and paste from above --+  |
                               ; just rename the labels                     |
       ; in a loop 1..[edi] store '+' in [ecx]                              |
       ; at the bottom of the loop increment ecx by 1                       |
                                                                            |
                               ; note you can cut and paste from above -----+
                               ; just rename the labels
       ; compute 12-[edi] or use a stored one if you stored it previoulsy
       ; in a loop 1.. 12-[edi] store '.' in [ecx]
       ; at the bottom of the loop increment ecx by 1
    
   ; bottom of the loop traversing N
   ; increment esi by 1
   ; increment edi by 4
   ; either back to the top of the loop or not

   ; the line is complete, print it
   
   ; restore all registers
   ; leave subroutine
   ; return control
   
asm_main:
   enter 0,0             ; setup routine
   pusha                 ; save all registers

   mov eax, peg1        
   ;add eax, 32          ; this does 9, 9, 9
   add eax, 28          ; this would do  4, 2, 1
   ;add eax, 24          ; this would do  3, 0, 0
   ;add eax, 20          ; this would do  0, 0, 0
   push eax
   call line1
   add esp, 4

   popa                  ; restore all registers
   mov eax, 0            ; return back to caller
   leave                     
   ret
