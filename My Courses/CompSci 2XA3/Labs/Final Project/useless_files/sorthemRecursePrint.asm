;; prints array in reverse order -- recursively ;;

%include "asm_io.inc"

SECTION .data

arr: dd 8,7,6,5,4,3,2,1
size: dd 8
pos: dd 0
msg: db "%d, ", 0
tst: db "end",10,0

four: db "%d, %d, %d, %d", 10,0
reg: db "eax: %d, ebx: %d, ecx: %d, edx: %d", 10, 0

SECTION .bss

SECTION .text

extern printf

global printarray
global asm_main

asm_main:

	enter 0,0

	mov ecx, [pos]
	mov edx, [size]

	sub ecx, 4
	inc edx

	push ecx
	push edx

	mov ebx, 0
	mov eax, edx
	dec eax
	
	call printarray

	mov eax, 1
	int 0x80


printarray:

	enter 0,0			; set up stack
   	pusha				; push all registers
  	
	mov edx, [ebp+8]
	mov ecx, [ebp+12]

	cmp edx, 1
	je end

	add ecx, 4
	dec edx

	push ecx
	push edx
	call printarray

	; ###
	pop edx
	pop ecx

	;call printreg
	call swapthem
	;call prot

	;call eprint

	;call value
	call func

	jmp end

end:

	popa
	leave
	ret

swapthem:

	cmp edx, 1
	je return

	push edx
	push ecx

	sub edx, 1
	mov ebx, 0

	bubble:

		cmp ebx, edx
		je loopend

		push ebx

		mov eax, [arr+ecx]
		mov ebx, [arr+ecx+4]

		cmp eax, ebx
		jg swap

			swap:
				mov [arr+ecx], ebx
				mov [arr+ecx+4], eax

		pop ebx

		;cmp ecx, 4
		add ecx, 4
	
		add ebx, 1
		jmp bubble

	loopend:	

		; print configuration	
		pop ecx
		pop edx
		ret

	return:

		; print config
		ret


eprint:

	push eax
	push ebx
	push ecx
	push edx

	mov eax, [arr]
	mov ebx, [arr+4]
	mov ecx, [arr+8]
	mov edx, [arr+12]
	push eax
	push ebx
	push ecx
	push edx
	push msg
	call printf
	add esp, 4
	pop edx
	pop ecx
	pop ebx
	pop eax

	mov eax, [arr+16]
	mov ebx, [arr+20]
	mov ecx, [arr+24]
	mov edx, [arr+28]
	push eax
	push ebx
	push ecx
	push edx
	push msg
	call printf
	add esp, 4
	pop edx
	pop ecx
	pop ebx
	pop eax

	pop edx
	pop ecx
	pop ebx
	pop eax

	ret

prot:


	push eax
	push ebx
	push ecx
	push edx

	mov eax, [arr]
	mov ebx, [arr+4]
	mov ecx, [arr+8]
	mov edx, [arr+12]
	push edx
	push ecx
	push ebx
	push eax
	push four
	call printf
	call print_nl
	add esp,4
	pop eax
	pop ebx
	pop ecx
	pop edx

	pop edx
	pop ecx
	pop ebx
	pop eax
	
	ret

printreg:

	push edx
	push ecx
	push ebx
	push eax
	push reg
	call printf
	call print_nl
	add esp, 4
	pop eax
	pop ebx
	pop ecx
	pop edx
	
	ret

printmsg:

	push edx
	push ecx
	push ebx
	push eax
	push tst
	call printf
	call print_nl
	add esp, 4
	pop eax
	pop ebx
	pop ecx
	pop edx
	
	ret
	


func:

	push ecx
	mov ebx, [arr+ecx]
	push edx
	push ebx
	push msg
	call printf
	add esp, 4
	pop ebx
	pop edx
	pop ecx

	ret

value:

	mov eax, [arr+ecx]
	push edx
	push ecx
	push eax
	call print_int
	call print_nl
	pop eax
	pop ecx
	pop edx

	mov eax, [arr+ecx-4]
	push edx
	push ecx
	push eax
	call print_int
	call print_nl
	pop eax
	pop ecx
	pop edx

	ret



setreg:

	mov ebx, 0
	mov edx, 0
	mov ecx, [size]
	ret	

printwholething:

	mov eax, [arr+edx]
	push edx
	push ecx
	push ebx
	push eax
	call print_int
	mov eax, ' '
	push eax
	call print_char
	pop eax
	pop eax
	pop ebx
	pop ecx
	pop edx

	add ebx, 1
	add edx, 4

	cmp ebx, ecx
	jl printwholething
	leave
	
