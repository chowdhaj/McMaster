%include "asm_io.inc"

SECTION .data 
msg1: db "display subroutine -- parameters obtained: ",0

SECTION .bss

SECTION .text 

global asm_main

;; subroutine display
;; expects 2 integers on stack, displays them
display:
  enter 0,0
  pusha

  mov eax,msg1       ; get message
  call print_string  ; display it
  mov eax,[ebp+8]    ; get first parameter
  call print_int     ; display it
  mov al,','         ; get comma
  call print_char    ; display it
  mov eax,[ebp+12]    ; get second parameter
  call print_int     ; display it
  call print_nl

  popa
  leave
  ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

asm_main:
  enter 0,0
 
  push dword 1
  push dword 2
  call display
  add esp,8

  push dword 2
  push dword 1
  call display
  add esp,8

  leave
  ret 
