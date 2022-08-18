%include "asm_io.inc"

SECTION .data

peg1: dd 0,0,0,0,0,0,3,4,9
peg2: dd 0,0,0,0,0,0,0,2,9
peg3: dd 0,0,0,0,0,0,0,1,9

SECTION .bss

line: resb 80
N: resd 3

SECTION .text
   global  asm_main

line1:   ; subroutine line1 expects one address A on stack
         ; it uses three numbers, N1 stored at  address A, 
         ; N2 from stored at address address A+36, and 
         ; N3 stored at address A+72
         ; all three numbers N1, N2, and N3 are expected to
         ; OK and in the range 0..9
; line1 displays a line that is composed like this
; 12-N1 dots, N1 pluses, one |, N1 pluses, 12-N1 dots
; continued the same for N2 and continued the same for N3
;
; for instance if N1=4, N2=2, N3=1 the line will look likes this 
;........++++|++++..................++|++.....................+|+...........

   enter 0,0                ; setup routine
   pusha                    ; save all registers
   mov ebx, [ebp+8]         ; address of N1
   mov ecx, dword [ebx]     ; ecx=N1
   mov [N], ecx             ; remember N1
   add ebx, dword 36        ; address of N2
   mov ecx, dword [ebx]     ; ecx=N2
   mov [N+4],ecx            ; remember N2
   add ebx, dword 36        ; address of N3
   mov ecx, dword [ebx]     ; ecx=N3
   mov [N+8], ecx           ; remember N3
   mov ecx, line            ; pointer to line

   ; now we need a counting loop 3x, esi will be the control
   ; edi points to the N we are working with, i.e. N1,N2,N3=[edi]
   mov edi, N
   mov esi, 0
   LOOP: 
     mov ebx, 12
     sub ebx, dword [edi]    ; ebx=number of spaces needed -- 12-N
     mov eax, 0              ; counter
     L11: cmp eax, ebx
     jae L12
     mov [ecx], byte '.'
     inc eax
     inc ecx
     jmp L11 
     ; now we need N pluses
     L12: mov eax, 0            ; counter
     L13: cmp eax, dword [edi]
     jae L14
     mov [ecx], byte '+'
     inc eax
     inc ecx
     jmp L13
     ; now we need |
     L14: mov [ecx], byte '|'
     inc ecx
     ; now we need N pluses
     mov eax, 0            ; counter
     L15: cmp eax, dword [edi]
     jae L16
     mov [ecx], byte '+'
     inc eax
     inc ecx
     jmp L15
     ; now we need 12-N spaces, we remembered the value in ebx
     L16: mov eax, 0            ; counter
     L17: cmp eax, ebx
     jae LOOP_END
     mov [ecx], byte '.'
     inc ecx
     inc eax
     jmp L17
  
   LOOP_END: 
   add esi, dword 1
   add edi, 4
   cmp esi, dword 3
   jb LOOP

   ; the line is complete, print it
   mov eax, line
   call print_string
   call print_nl
   
   popa
   leave
   ret
   
asm_main:
   enter 0,0             ; setup routine
   pusha                 ; save all registers

   mov eax, peg1        
   ;add eax, 32          ; this does 9, 9, 9
   add eax, 28          ; this would do  4, 2, 1
   ;add eax, 24          ; this would do  3, 0, 0
   ;add eax, 20          ; this would do  0, 0, 0
   push eax
   call line1
   add esp, 4

   popa                  ; restore all registers
   mov eax, 0            ; return back to caller
   leave                     
   ret
