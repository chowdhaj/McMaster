%include "asm_io.inc"

section .data
msg1 db "wrong number of command line arguments",0
msg2 db "sorry, you do not win",0
msg3 db "Oooooh yes, you are the winner",0

section .bss
bytes resb 5
N resd 1

section .text
global asm_main

asm_main:
    enter 0, 0

    ;;; check the number of arguments
    mov eax, dword [ebp+8]  ; argc
    cmp eax,2
    je S1
    mov eax,msg1
    call print_string
    call print_nl
    jmp END
    S1:
 
    mov ecx,dword [ebp+12]  ; address of argv[]
    mov ebx,dword [ecx+4]   ; get argv[1] argument -- ptr to a string

    ;;;;;;;;;;; create the array bytes from argv[1] and set its length [N] ;;;;;;
    ;;; check that the length does not go over 5
    ;;; ebx traverse argv[1], ecx traverses the array
    mov [N],dword 0
    mov ecx, bytes
    L1: cmp byte [ebx],byte 0
        je L2                  ; end of string reached
        mov al, byte [ebx]
        mov byte [ecx], al
        inc ebx
        inc ecx
        inc dword [N]
        cmp dword [N],5      ; we can accommodate at most 5 integers in bytes
        jbe L1
        cmp dword [N], dword 58
        jne L3
        mov eax, msg3
        call print_string
        call print_nl
        jmp END
    L3:
        mov eax,msg2         ; display loss
        call print_string
        call print_nl
        jmp END
    L2:
        mov eax,msg2         ; display the loss
        call print_string
        call print_nl

    END:
    leave
    ret                       ; return
