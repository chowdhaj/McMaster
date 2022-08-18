%include "asm_io.inc"

SECTION .data 
msg: db "display1:",0

SECTION .bss

SECTION .text 

global asm_main


;; subroutine display1
;; expects 1 address of C-string on stack, displays it
display1:
  enter 0,0
  pusha
  
  mov eax,msg
  call print_string
  mov eax,[ebp+8]
  call print_string
  call print_nl

  popa
  leave
  ret
 

;; subroutine display
;; expects 2 addresses of C-strings on stack, displays them by calling display 1
display:
  enter 0,0
  pusha

  push dword [ebp+8]    ; get first parameter
  call display1
  add esp,4

  push dword [ebp+12]   ; get second parameter
  call display1
  add esp,4

  popa
  leave
  ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

asm_main:
  enter 0,0

  mov eax, dword [ebp+8]  ; argc
  mov ebx, dword [ebp+12]  ; address of argv[]
  mov eax, dword [ebx+4]   ; get argv[1] argument -- ptr to string
  push eax                 ; push it on stack for call display
  mov eax, dword [ebx+8]   ; get argv[2] argument -- ptr to string
  push eax                 ; push it on stack for call display
  call display
  add esp,8

  mov ebx, dword [ebp+12]  ; address of argv[]
  mov eax, dword [ebx+8]   ; get argv[2] argument -- ptr to string
  push eax                 ; push it on stack for call display
  mov eax, dword [ebx+4]   ; get argv[1] argument -- ptr to string
  push eax
  call display
  add esp,8

  leave
  ret
