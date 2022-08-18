SECTION .data  ;initilized data

msg: db "STRING",10,0      ; this string has nl
fmt_x: db "'0%Xh'", 0
fmt_ui: db "%u" ,0
fmt_si: db "%d" ,0
fmt_fl: db "%f" ,0
mychar: db 'A'
myusint: dw 23
myuint: dd 23
myssint: dw  -23
mysint: dd -23
myfloat: dd 2.314

SECTION .text  ;assembly code

global main
extern putchar
extern printf

main:
  push ebp        ; push the current ebp on stack to rember
  mov ebp, esp    ; remember sp in bp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; how to print a character (must be printable)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  push 'A'        ; push the value of the character on stack
 ;push 65          the same in decimal
 ;push 41h         the same in hexadecimal
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

; print newline
  push 10         ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; how to print a character in hexadecimal
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  push 'A'        ; push the value of the character on stack
 ;push 65          the same in decimal
 ;push 41h         the same in hexadecimal
  push fmt_x     ; push address of formating string on stack
  call printf    ; printf pops stack but does not move ESP
  add  esp, 8    ; so move it yourself

; print newline
  push 10         ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; how to print a character stored in memory (must be printable)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  push dword [mychar]         ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

; print newline
  push 10         ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; how to print a character stored in memory in hexadecimal, must
; use a free register, here we are using eax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  mov eax, dword [mychar]
  push eax       ; push the value of the character on stack
  and  eax, 0FFh ; mask redundant bits
  push eax
  push fmt_x     ; push address of formating string on stack
  call printf    ; printf pops stack but does not move ESP
  add  esp, 8    ; so move it yourself

; print newline
  push 10         ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

  mov eax, 'A'
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; how to print a character stored in register (must be printable)
; the value is in register eax in ah part in this example but
; could be any register
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  push eax        ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

; print newline
  push 10         ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

  mov eax, 'A'
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; how to print a character stored in register in hexadecimal
; the value is in register eax in ah part in this example but
; could be any register
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  push eax        ; push the value of the character on stack
  push fmt_x      ; push address of formating string on stack
  call printf     ; printf pops stack but does not move ESP
  add  esp, 8     ; so move it yourself

; print newline
  push 10         ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; how to print a string  -- must be a C type string terminated by null
; this string end with newline, so we do not need to print it separately
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  push msg        ; push address of the string on stack
  call printf     ; printf pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; how to print an unsigned integer
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  push 23         ; push the value on stack
 ;push 17h        ; the same in hexadecimal
  push fmt_ui     ; push the formating string on stack
  call printf     ; printf pops stack but does not move ESP
  add  esp, 8     ; so move it yourself

; print newline
  push 10         ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; how to print an unsigned short integer stored in memory 
; need a free register, here we are using eax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  mov eax, dword [myusint]           
  and eax, 0FFFFh ; mask redundant bits
  push eax         ; push the value on stack
  push fmt_ui     ; push the formating string on stack
  call printf     ; printf pops stack but does not move ESP
  add  esp, 8     ; so move it yourself

; print newline
  push 10         ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; how to print an unsigned integer stored in memory 
; need a free register, here we are using eax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  mov eax, dword [myuint]           
  push eax         ; push the value on stack
  push fmt_ui     ; push the formating string on stack
  call printf     ; printf pops stack but does not move ESP
  add  esp, 8     ; so move it yourself

; print newline
  push 10         ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; how to print a signed integer 
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  push -23        ; push the value on stack
  push fmt_si     ; push the formating string on stack
  call printf     ; printf pops stack but does not move ESP
  add  esp, 8     ; so move it yourself

; print newline
  push 10         ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; how to print a signed short integer stored in memory
; need eax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  mov ax, word [myssint]
  cwde            ; extend the singed version from ax to eax
  push eax        ; push it on stack
  push fmt_si     ; push the formating string on stack
  call printf     ; printf pops stack but does not move ESP
  add  esp, 8     ; so move it yourself

; print newline
  push 10         ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; how to print a signed integer stored in memory
; need a free register, here we are using eax
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  mov eax, dword [mysint]
  push eax        ; push it on stack
  push fmt_si     ; push the formating string on stack
  call printf     ; printf pops stack but does not move ESP
  add  esp, 8     ; so move it yourself

; print newline
  push 10         ; push the value of the character on stack
  call putchar    ; putchar pops stack but does not move ESP
  add  esp, 4     ; so move it yourself

  mov esp, ebp    ; restore sp  remembered in bp
  pop ebp         ; pop the system stack to bp
  ret
