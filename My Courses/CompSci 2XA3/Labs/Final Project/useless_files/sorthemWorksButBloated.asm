%include "asm_io.inc"

SECTION .data

;;;;;;;;;;;;;;;;;;;;;;;
;; Program Variables ;;
;;;;;;;;;;;;;;;;;;;;;;;

errorArgMsg: db "Incorrect Number Of Args", 10, 0
errorNumMsg: db "Argument Not Valid!", 10, 0
peg: dd 0,0,0,0,0,0,0,0,0
init: db "           Initial Configuration", 10, 0
finy: db "            Final Configuration",10,0
base: db "          XXXXXXXXXXXXXXXXXXXXXXX", 10, 0
pipe: db "|", 0
;disk: db "o",0

;;;;;;;;;;;;;;;;;;;;
;; Test Variables ;;
;;;;;;;;;;;;;;;;;;;;

test: db "Test", 10, 0
num: db "num: %d", 10,  0
four: db "%d, %d, %d, %d", 10, 0

SECTION .bss

DISKS: resd 1

SIZE: resd 1

SECTION .text

extern printf

global asm_main:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

asm_main:

	;; create stack frame ;;
	;push ebp
	;mov ebp, esp

	enter 0,0
	pusha

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
	
	push eax
	push ebx
	push ecx
	push edx

	dec eax
	mov ecx, 4
	mul ecx
	mov [SIZE], eax

	pop edx
	pop ecx
	pop ebx
	pop eax

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
	call title
	call showp
	call read_char
	jmp sorthem

title:

	pusha

	call print_nl
	mov eax, init
	call print_nl
	call print_string
	call print_nl

	popa
	ret

finale:

	push eax
	mov eax, finy
	push eax
	call print_string
	call print_nl
	pop eax
	pop eax
	call showp
	call print_nl
	ret

sorthem: 

	enter 0,0

	mov ecx, 0
	mov edx, [DISKS]

	sub ecx, 4
	inc edx

	push ecx
	push edx

	;mov ebx, 0
	;mov eax, edx
	;dec eax
	
	call sorthem2
	
	call finale

	jmp exit
	;mov eax, 1
	;int 0x80

sorthem2:

	enter 0,0			; set up stack
   	pusha				; push all registers
  	
	mov edx, [ebp+8]
	mov ecx, [ebp+12]

	cmp edx, 1
	je exit

	add ecx, 4
	dec edx

	push ecx
	push edx
	call sorthem2

	; This is the return address
	pop edx
	pop ecx

	call swapthem
	jmp exit

swapthem:

	push ecx
	push edx

	cmp edx, 1
	je loopend

	dec edx
	mov ebx, 0

	compare:

		cmp ebx, edx
		je loopend

		push ebx
			
		mov eax, [peg+ecx]
		mov ebx, [peg+ecx+4]

		cmp eax, ebx
		jg swap
		jmp nowp

		swap:

			mov [peg+ecx], ebx
			mov [peg+ecx+4], eax

		nowp:

			pop ebx
		
			inc ebx
			add ecx, 4
			jmp compare
		

	loopend:	
		
		; print configuration	
		pop ecx
		pop edx
		
		push eax
		push ebx
		push ecx
		push edx
		call showp
		call read_char 	;; put read_char here
		pop edx
		pop ecx
		pop ebx
		pop eax
		ret

showp:

	mov ecx, [SIZE]	
	mov edx, [DISKS]

	mov ebx, 0
	add ecx, 4

	prnt:

		cmp ebx, ecx
		je dones

		mov eax, [peg+ebx]
		pusha
		;push edx
		;push ecx
		;push ebx
		;push eax
		call printspaces
		call printpeg
		call ppipe
		call printpeg
		call print_nl
		;pop eax	
		;pop ebx
		;pop ecx	
		;pop edx
		popa	

		add ebx, 4
		;jmp exit ;;; causes seg fault - used to print only 1 peg	
		jmp prnt
	dones:
		call xxxhubxxx
		;call read_char
		ret
		;jmp exit ;;; causes seg fault - used to test 1 sort iteration

printspaces:

	pusha
	mov eax, ebx
	mov eax, [peg+ebx]
	
	mov ecx, 21
	sub ecx, eax

	mov edx, 0
	
	spacey:

		cmp edx, ecx
		je gtfo

		mov eax, ' '
		push eax
		call print_char
		pop eax

		inc edx	
		jmp spacey
		
	gtfo:

		popa
		ret

printpeg:

	pusha

	mov ebx, eax
	mov edx, 0
	mov eax, 'o'	
	mov ecx, 0

	peggers:

		cmp ebx, edx
		je back

		push eax
		call print_char
		pop eax

		inc edx
		inc ecx
		jmp peggers

	back:
		popa	
		ret

ppipe:

	push eax
	mov eax, '|'
	call print_char
	pop eax
	ret

xxxhubxxx:
	push eax
	mov eax, base
	call print_string
	call print_nl
	pop eax
	ret

printfour:

	push eax
	push ebx
	push ecx
	push edx

	mov eax, [peg]
	mov ebx, [peg+4]
	mov ecx, [peg+8]
	mov edx, [peg+12]
	push eax
	push ebx
	push ecx
	push edx
	push four
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
	
	popa 
	leave	
	ret
