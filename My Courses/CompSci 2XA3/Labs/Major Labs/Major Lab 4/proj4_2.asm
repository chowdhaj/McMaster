%include "asm_io.inc"
global asm_main

section .data
string db "hello world hello",0
;string db "A B C D",0
msg1 db "too many characters",0
msg2 db "the length of the string is ",0
msg3 db "the number of blanks is ",0
msg4 db "string in reverse: ",0

section .bss
N resd 1   ; length counter
M resd 1   ; blank counter
E resd 1   ; address of the last element

section .text

asm_main:
  enter 0, 0

  ;; calculate the string's length by traversing it
  ;; using ebx to traverse the string
  mov ebx,string
  mov dword [N], dword 0
  mov dword [M], dword 0
  L1: 
    cmp byte [ebx], byte 0
    je L2
    mov dword [E], ebx
    cmp byte [ebx], ' '
    jne L11
    inc dword [M]
    L11:
    inc ebx
    add dword [N],1
    cmp dword [N],20
    jb L1
  mov eax,msg1       ;; string too long
  call print_string
  call print_nl
  jmp END

  L2: 
  mov eax,string     ;; printf the string
  call print_string
  call print_nl
  mov eax, msg2          ;; print length message
  call print_string
  mov eax, dword [N]     ;; print length
  call print_int
  call print_nl
  mov eax, msg3          ;; print # of blanks message
  call print_string
  mov eax, dword [M]     ;; print # of blanks
  call print_int
  call print_nl

  mov eax, msg4          ;; print message of reversed display
  call print_string
 
  mov ebx, dword [E]     ;; last letter
  S1: cmp ebx, string
    jb S2
    mov al, byte [ebx]
    call print_char
    dec ebx
    jmp S1
  S2:
    call print_nl
  END:
  leave
  ret
