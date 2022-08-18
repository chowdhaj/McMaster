%include "asm_io.inc"

SECTION .data 
fmt1: db "outer=",0
fmt2: db ",inner=",0
msg: db "done",0

SECTION .bss
outer: resd 1
inner: resd 1

SECTION .text 

global asm_main

asm_main:
  enter 0,0

  ;;; outer loop counts from 1 to 8, controlled by [outer]
  mov [outer], dword 1 
  LEVEL_LOOP: cmp [outer], dword 8   
  ja END_LEVEL_LOOP

     ;;; inner loop counts from 1 to 3, controlled by [inner]
     mov [inner], dword 1
     PEG_LOOP: cmp [inner], dword 3
     ja END_PEG_LOOP
        ;; print the values of [outer] and [inner]
        mov eax,fmt1
        call print_string
        mov eax,[outer]
        call print_int
        mov eax,fmt2
        call print_string
        mov eax,[inner]
        call print_int
        call print_nl
        ;;
     add [inner], dword 1
     jmp PEG_LOOP
     END_PEG_LOOP:

  add [outer], dword 1
  jmp LEVEL_LOOP
  END_LEVEL_LOOP:

  leave
  ret 
