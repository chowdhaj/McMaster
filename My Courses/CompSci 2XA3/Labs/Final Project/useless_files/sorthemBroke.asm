%include "asm_io.inc"

SECTION .data

;;;;;;;;;;;;;;;;;;;;;;;
;; Program Variables ;;
;;;;;;;;;;;;;;;;;;;;;;;

errorArgMsg: db "Incorrect Number Of Args", 10, 0
errorNumMsg: db "Argument Not Valid!", 10, 0
peg: dd 0,0,0,0,0,0,0,0,0
init: db "           Initial Configuration", 10, 0
base: db "          XXXXXXXXXXXXXXXXXXXXXXX", 10, 0
pipe: db "|", 0
;disk: db "o",0

;;;;;;;;;;;;;;;;;;;;
;; Test Variables ;;
;;;;;;;;;;;;;;;;;;;;

test: db "Test", 10, 0
num: db "num: %d", 10, 0

SECTION .bss

DISKS: resd 1

SECTION .text

extern printf

global asm_main:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

asm_main:

	;; create stack frame ;;
	push ebp
	mov ebp, esp

	;; mov args to register
	mov eax, DWORD[ebp+8]
	mov ebx, DWORD[ebp+12]
	mov ecx, 0

	cmp eax,2 		; if 2 args are passed
	je argnum		; jump to argnum
	jmp errorarg		; else, jump to errorarg

argnum:  

	add ebx, 4		; add 4 to ebx's address
	mov ecx, DWORD[ebx]	; move value in ebx to ecx
	mov [DISKS], ecx	; move value in ecx to DISKS - memory

	cmp BYTE[ecx+1], byte 0
	jne errornum

	cmp BYTE[ecx], '2'
	jb errornum

	cmp BYTE[ecx], '9'
	ja errornum

	jmp tointeger

tointeger:

	mov al, byte [ecx]
	sub eax, dword '0'
	mov [DISKS], eax
	
	mov ecx, [DISKS]

	;push ecx		; push ecx on stack
	;push num		; push the string num on stack
	;call printf		; print ecx
	;call print_nl		; print \n
	;add esp, 8		; clean stack
	
	jmp callrconf

callrconf:

	;mov eax, 0
	;mov eax, [peg]

	;push ecx
	;push num
	;call printf
	;add esp, 8

	mov eax, peg
	push ecx
	push eax	
	call rconf
	pop eax
	pop ecx

	jmp initconfig

initconfig:

	push edx
	push ecx
	push ebx
	push eax
	push init
	call print_nl
	call print_nl
	call printf
	call print_nl
	add esp, 4
	pop eax
	pop ebx
	pop ecx
	pop edx
	jmp setreg

setreg:

       	mov edx, 0		; position in memory for array
	mov ecx, [peg+edx]	; value of element at array
        mov ebx, 0		; counter (to iterate array)
	mov eax, [DISKS]	; size of array
	jmp sorthem

showp:

	push eax
	push ebx
	push ecx
	push edx

	;;; print disk ;;;

	mov ebx, 0
	mov eax, ' '
	mov edx, 22
	sub edx, ecx

	printspace:
	
		push eax
		push ebx
		push ecx
		push edx
		call print_char
		pop edx
		pop ecx
		pop ebx
		pop eax	
	
		add ebx, 1	

		cmp ebx, edx
		jne printspace

	mov ebx, 0
	mov eax, 'o'

	printo:

		push eax
		push ebx
		push ecx
		call print_char
		pop ecx
		pop ebx
		pop eax 

		add ebx, 1
		cmp ebx, ecx

		jne printo	

	mov eax, '|'
	push eax
	push ecx
	call print_char
	pop ecx
	pop eax

	mov ebx, 0
	mov eax, 'o'

	printoo:

		push eax
		push ebx
		push ecx
		call print_char
		pop ecx
		pop ebx
		pop eax 

		add ebx, 1
		cmp ebx, ecx

		jne printoo

	call print_nl

	pop edx
	pop ecx
	pop ebx
	pop eax

	add ebx, 1
	add edx, 4

	mov ecx, [peg+edx]

	cmp eax, ebx
	jne showp
	
	; 23 spaces to 'f' in config

	push edx
	push ecx
	push ebx
	push eax
	push base
	call print_nl
	call printf
	call print_nl
	call read_char
	add esp, 4
	pop eax
	pop ebx
	pop ecx
	pop edx

	leave
	ret

sorthem: 

	enter 0,0

	mov ecx, 0
	mov edx, [DISKS]

	sub ecx, 4
	inc edx

	push ecx
	push edx

	mov ebx, 0
	mov eax, edx
	dec eax
	
	call sorthem2
	jmp exit
	;mov eax, 1
	;int 0x80

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
	call showp

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

		mov eax, [peg+ecx]
		mov ebx, [peg+ecx+4]

		cmp eax, ebx
		jg swap

			swap:
				mov [peg+ecx], ebx
				mov [peg+ecx+4], eax

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

errornum:

	push errorNumMsg
	call printf
	add esp, 4
	jmp exit	

errorarg:

	push errorArgMsg
	call printf
	add esp, 4
	jmp exit

func:

	;; print statement used for debugging
	push test		; push test to stack
	call printf		; call printf to display test
	add esp, 4		; clean the stack
	jmp exit

exit:
	;; destroy stack frame ;;
	mov esp, ebp
	pop ebp
	ret			; return to caller

