%include "asm_io.inc"

SECTION .data 

SECTION .bss

SECTION .text 

global asm_main

asm_main:
  enter 0,0

  ;; counting loop, controlled by eax, counting from 1 to 8
  mov eax,1
  MYLOOP: cmp eax, 8
  ja END_MYLOOP
     ; print the value of eax
     call print_int
     call print_nl
  add eax, 1
  jmp MYLOOP
  END_MYLOOP:

  leave
  ret 
