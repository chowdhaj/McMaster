extern printf

SECTION .data
x1: dd 4
fmt: db "%d*%d = %d",10,0

SECTION .text

global main
main:
        
   push ebp
   mov ebp, esp

   mov eax, [x1]
   mul eax
   push eax 
   mov eax, [x1]
   push eax
   push eax
   push dword fmt
   call printf
   add  esp, 16

   mov esp, ebp
   pop ebp

   mov eax,0                 ; normal (no error) return value
   ret                       ; return
