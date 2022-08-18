%include "asm_io.inc"

section .data
msg: db "Bid a non-zero number less than 10 ",0
err1: db "The amount you bid is too low",10,0
err2: db "The amount you bid is too big",10,0
msg1: db "We raised your bid eightfold to ",0
msg2: db "The total value of the bids is ",0
win: db "Unbelievable, you win",10,0
loss: db "Ha ha ha ha, you lost",10,0

section .bss
N resb 1

section .text
global asm_main

asm_main:
    enter 0, 0

    mov byte [N], byte 0 ;; initilaize bid counter

    mov edx, dword 1
    B1: cmp edx, 4
    je B2
      mov eax, msg
      call print_string
      call read_int
      cmp eax, dword 0
      ja A1
      mov eax,err1
      call print_string
      jmp END
      A1:cmp eax,dword 10
      jb A2
      mov eax,err2
      call print_string
      jmp END
      A2: 
      mov bl, byte 8
      mul bl
      mov ebx, eax
      mov eax, msg1
      call print_string
      mov eax, ebx
      call print_int
      call print_nl
      ;; store the bid in
      add byte [N], al
      ;; display total value of the bids
      mov eax, msg2
      call print_string
      mov eax, 0
      mov al, byte [N]
      call print_int
      call print_nl
      call print_nl
      inc edx
      jmp B1
   B2: 
   mov eax, msg
   call print_string
   call read_int
   cmp eax, dword 0
   ja C1
   mov eax,err1
   call print_string
   jmp END
   C1:cmp eax,dword 10
   jb C2
   mov eax,err2
   call print_string
   jmp END
   C2: 
   mov bl, byte 8
   mul bl
   mov ebx, eax
   mov eax, msg1
   call print_string
   mov eax, ebx
   call print_int
   call print_nl
   ;; store the bid in
   add byte [N], al
   ;;
;; check the total for win ;;;;;
   cmp byte [N], byte 0
   je you_win
   mov eax, loss
   call print_string
   jmp END
you_win: mov eax, win
   call print_string
END:
    leave
    ret                       ; return
