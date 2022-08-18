%include "asm_io.inc"

SECTION .data

peg1: dd 1,2,3,4,5,6,7,8,9
peg2: dd 10,20,30,40,50,60,70,80,90
peg3: dd 100,200,300,400,500,600,700,800,900

SECTION .bss

level:  resd 1
peg:  resd 1
pegslot: resd 1

SECTION .text
   global  asm_main
asm_main:
   enter 0,0             ; setup routine
   pusha                 ; save all registers

   mov [pegslot], dword peg1

   ; for all levels
   mov [level], dword 0
   LEVEL_LOOP: cmp [level], dword 8
   ja LEVEL_LOOP_END

      ; for all pegs
      mov [peg], dword 1
      PEG_LOOP: cmp [peg], dword 3
      ja PEG_LOOP_END

         mov ebx, dword [pegslot]
         mov eax, dword [ebx]
         call print_int
         mov eax,' '
         call print_char

      add [peg], dword 1
      add [pegslot], dword 36
      jmp PEG_LOOP
      PEG_LOOP_END:

   call print_nl

   add [level], dword 1
   sub [pegslot], dword 104  ; -36 to compensate, -36-36+4 to position to peg1 
   jmp LEVEL_LOOP
   LEVEL_LOOP_END:

   popa                  ; restore all registers
   mov eax, 0            ; return back to caller
   leave                     
   ret
