extern printf

SECTION .data
x1: dd 2
fmt: db "%d*%d + 3*%d - 5 = %d",10,0

SECTION .text

global main
main:
        
   push ebp
   mov ebp, esp

   mov eax, [x1]
   mul eax
   mov ebx, eax   ; ebx = x*x
   mov eax, 3
   mul dword [x1] ; eax = 3*x
   mov ecx, eax   ; ecx = 3*x
   mov edx, -5    ; edx = -5
   mov eax, ebx   ; eax = x*x
   add eax, ecx   ; eax = x*x + 3*x
   add eax, edx   ; eax = x*x + 3*x - 5
   push eax 
   mov eax, [x1]
   push eax
   push eax
   push eax
   push dword fmt
   call printf
   add  esp, 16

   mov esp, ebp
   pop ebp

   mov eax,0                 ; normal (no error) return value
   ret                       ; return
