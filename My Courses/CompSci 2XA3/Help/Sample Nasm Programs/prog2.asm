; Declare some external functions

extern printf                ; the C function, to be called

SECTION .data                ; Data section, initialized variables
a: dd 5                      ; int a=5;
fmt: db "a=%d, eax=%d",10,0  ; The printf format, '\n','0'

SECTION .text                ; Code section.

global main                  ; the standard gcc entry point
main:                        ; the program label for the entry point
        
   push ebp                  ; calling convention
   mov ebp, esp

   mov eax, [a]              ; put a from store into register
   add eax, 2                ; a+2
   push eax                  ; value of a+2
   push dword [a]            ; value of variable a
   push dword fmt            ; address of ctrl string
   call printf               ; Call C function
   add  esp, 12              ; pop stack 3 times = 4 bytes

   mov esp, ebp              ; returning convention
   pop ebp                   ; same as "leave" op

   mov eax,0                 ; normal (no error) return value
   ret                       ; return
