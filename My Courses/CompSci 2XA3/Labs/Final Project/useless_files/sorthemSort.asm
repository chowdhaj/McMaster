%include "asm_io.inc"

SECTION .data

arr: dd 8,7,6,5,4,3,2,1
size: dd 8
pos: dd 0
msg: db "%d, ", 0
tst: db "end",10,0

four: db "%d, %d, %d, %d, ",10, 0

SECTION .bss

SECTION .text

extern printf

global sorthem2
global asm_main

asm_main: ;; this should be sorthem2

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
	
	call sorthem2
	mov eax, 1
	int 0x80

sorthem2:

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
	call sorthem2

	; This is the return address
	pop edx
	pop ecx

	call swapthem

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
