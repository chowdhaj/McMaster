%include "asm_io.inc"
global asm_main

section .data

section .bss

section .text

asm_main:
  enter 0, 0

  mov eax, dword [ebp+8]  ; argc
  call print_int          ; display argc
  call print_nl

  mov ebx, dword [ebp+12]  ; address of argv[]
  mov eax, dword [ebx]     ; get argv[0] argument -- ptr to string
  call print_string        ; display argv[0] arg
  call print_nl
 
  mov eax, dword [ebx+4]   ; get argv[1] argument -- ptr to string
  call print_string        ; display argv[1] arg
  call print_nl

  mov eax, dword [ebx+8]   ; get argv[2] argument -- ptr to string
  call print_string        ; display argv[2] arg
  call print_nl

  leave
  ret
