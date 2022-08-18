%include "asm_io.inc"

SECTION .data 
msg1: db "subroutine display -- parameters obtained: ",0

SECTION .bss

SECTION .text 

global asm_main

;; subroutine display
;; expects 2 addresses of C-strings on stack, displays them
display:
  enter 0,0
  pusha

  mov eax,msg1       ; get message
  call print_string  ; display it
  mov eax,[ebp+8]    ; get first parameter
  call print_string  ; display it
  mov al,','         ; get comma
  call print_char    ; display it
  mov eax,[ebp+12]   ; get second parameter
  call print_string  ; display it
  call print_nl

  popa
  leave
  ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

asm_main:
  enter 0,0

  mov eax, dword [ebp+8]  ; argc
  mov ebx, dword [ebp+12]  ; address of argv[]
  mov eax, dword [ebx+4]   ; get argv[1] argument -- ptr to string
  call print_string        ; display argv[1] arg
  call print_nl
  push eax                 ; push it on stack for call display
  mov eax, dword [ebx+8]   ; get argv[2] argument -- ptr to string
  call print_string        ; display argv[2] arg
  call print_nl
  push eax                 ; push it on stack for display
  call display
  add esp,8

  ;; let us see wether ebp is truly where it should be, i.e. can we
  ;; repeat it ?
  ;; let us try and swithc the order of parameters
  mov ebx, dword [ebp+12]  ; address of argv[]
  mov eax, dword [ebx+8]   ; get argv[2] argument -- ptr to string
  call print_string        ; display argv[2] arg
  call print_nl
  push eax                 ; push it on stack for call display
  mov eax, dword [ebx+4]   ; get argv[1] argument -- ptr to string
  call print_string        ; display argv[1] arg
  call print_nl
  push eax                 ; push it on stack for display
  call display
  add esp,8

  leave
  ret
