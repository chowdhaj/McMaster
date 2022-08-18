SECTION .data  ;initilized data

msg: db "2XA3 first assembler program, hurray",10,0

SECTION .text  ;assembly code

global main
extern printf

main:
  push ebp
  mov ebp, esp    ; calling convention

  push msg
  call printf     ; calling C printf function
  add esp, 4      ; fix the stack

  mov esp, ebp    ; returning convention
  pop ebp
  ret
