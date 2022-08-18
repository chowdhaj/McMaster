%include "asm_io.inc"
segment .data
str1: db    "123456",0
x: dd 1,2
c: db 'A'

segment .bss
 
segment .text
        global  asm_main
asm_main:
        enter   0,0               ; setup routine
        pusha

        mov eax, str1
        call print_string
        call print_nl

        mov eax, dword [x]
        call print_int
        mov eax, ' '
        call print_char
        mov eax, ' '
        call print_char
        mov eax, dword [x+4]
        call print_int
        call print_nl

        mov eax, 0
        mov al, byte [c]
        call print_char
        call print_nl

        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        mov [str1], byte 'A'
        mov [str1+1], byte 'B'
        mov [str1+2], byte 'C'
        mov [str1+3], byte 0

        mov eax, str1
        call print_string
        call print_nl

        mov [x], dword 7
        mov [x+4], dword 8

        mov eax, dword [x]
        call print_int
        mov eax, ' '
        call print_char
        mov eax, ' '
        call print_char
        mov eax, dword [x+4]
        call print_int
        call print_nl

        mov [c], byte 'B'
        mov eax, 0
        mov al, byte [c]
        call print_char
        call print_nl
          
        popa
        mov     eax, 0            ; return back to C
        leave                     
        ret
