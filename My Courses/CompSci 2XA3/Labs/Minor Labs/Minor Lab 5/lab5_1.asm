%include "asm_io.inc"

SECTION .data

arr1: dd 1,2,3,4,5,6,7,8,9,10
arr2: dd 11,12,13,14,15,16,17,18,19,20
err1: db "incorrect number of command line arguments",10,0
err2: db "incorrect command line argument",10,0

SECTION .bss

SECTION .text
   global  asm_main

; subroutine display_array
; expects one parameter on stack, either index 1 or 2
; it is assumed that the parameter is OK
; if the parameter is 1, the subroutine traverses the array
; arr1 and displays its entries separated by comma, e.g.
; 1,2,3,4,5,6,7,8,9,10
; if the parameter is 2, the subroutine traverses the array
; arr2 and displays its entries separated by comma, e.g.
; 11,12,13,14,15,16,17,18,19,20
display_array:
   enter 0,0             ; setup routine
   pusha                 ; save all registers

   mov eax, [ebp+8]      ; the parameter
   cmp eax, dword 1
   jne NOT1
   ; so it is 1
   mov ebx, arr1
   jmp display
   NOT1: 
   mov ebx, arr2

  display:
   ; ebx points to the beginning of the array
   ; we will use ecx to control the counting loop of 10
   mov ecx, dword 1
   LOOP:
   mov eax, dword [ebx]
   call print_int
   mov eax, ','
   call print_char
   inc ecx
   add ebx, 4
   cmp ecx, dword 9
   jbe LOOP
   ; so the loop is over, print the last entry
   mov eax, dword [ebx]
   call print_int
   call print_nl
   
   popa
   leave
   ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
asm_main:
   enter 0,0             ; setup routine
   pusha                 ; save all registers

   mov eax, dword [ebp+8]   ; argc
   cmp eax, dword 2         ; argc should be 2
   jne ERR1
   ; so we have the right number of arguments
   mov ebx, dword [ebp+12]  ; address of argv[]
   mov eax, dword [ebx+4]   ; argv[1]
   ; check that the string is either "1" or "2"
   ; check the first byte, should be '1' or '2'
   ; check the second byte, should be 0
   mov bl, byte [eax]       ; 1st byte of argv[1]
   try1: cmp bl, '1'
   jne try2
   ; so the first byte is '1'
   jmp byte_1_ok
   try2: cmp bl, '2'
   jne ERR2
   byte_1_ok:
   sub bl, '0'
   mov ecx,0
   mov cl, bl               ; so ecx holds either 1 or 2
   ; check the second byte
   mov bl, byte [eax+1]     ; 2nd byte of argv[1]
   cmp bl, byte 0
   jne ERR2
   ; hence the argument is correct and its numeric value
   ; stored in ecx

   push ecx
   call display_array
   add esp, 4
   jmp asm_main_end

 ERR1:
   mov eax, err1
   call print_string
   jmp asm_main_end

 ERR2:
   mov eax, err2
   call print_string
   jmp asm_main_end

 asm_main_end:
   popa                  ; restore all registers
   leave                     
   ret
