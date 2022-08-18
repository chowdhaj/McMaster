;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;                                              ;;;;;;;;;;
;;;;;;;;;;           FINAL NASM PROJECT                 ;;;;;;;;;;
;;;;;;;;;;              BY: JATIN C.                    ;;;;;;;;;;
;;;;;;;;;;                                              ;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

;;;;;;;;;;;;;;;;
; SUB PROGRAMS ;
;;;;;;;;;;;;;;;;

; This is the main function
; It is the first function that runs
; - It sets up the stack
; - Moves arguments to registers
; - Checks number of arguments
asm_main:

	enter 0,0
	pusha

	;; mov args to register
	mov eax, DWORD[ebp+8]
	mov ebx, DWORD[ebp+12]
	mov ecx, 0

	cmp eax,2
	je argnum	
	jmp errorarg

; This function:
; - Moves the 2nd argument to the register
; - Compares the argument with chars
; - Anything less than 2 is an error
; - Anything over 9 is an error
; - Anything not between 2 and 9 is an error
argnum:  

	add ebx, 4			
	mov ecx, DWORD[ebx]
	mov [DISKS], ecx

	cmp BYTE[ecx+1], byte 0
	jne errornum

	cmp BYTE[ecx], '2'
	jb errornum

	cmp BYTE[ecx], '9'
	ja errornum

	jmp tointeger

; This function:
; - Converts the argument into an integer
; - Does this by subtracting it from '0'
; - Move result into memory
; - Then it moves the size [in bytes] of the array into memory
; - It does this by multiplying the 2nd arg by 4
; - B/c the size of the array is 'X', multiplying it by 4 = size
tointeger:

	mov al, byte [ecx]
	sub eax, dword '0'
	mov [DISKS], eax
	
	pusha

	dec eax
	mov ecx, 4
	mul ecx
	mov [SIZE], eax

	popa

	mov ecx, [DISKS]
	jmp callrconf

; This function:
; - Calls rconf
; - rconf: Takes two parameters, address of array and 2nd arg, and returns an array with random numbers
callrconf:

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

; This function prints "initial configuration"
title:

	pusha

	call print_nl
	mov eax, init
	call print_nl
	call print_string
	call print_nl

	popa
	ret

; This function prints "final configuration"
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

; This function sorts the array, recursively
sorthem: 

	enter 0,0

	mov ecx, 0
	mov edx, [DISKS]

	sub ecx, 4
	inc edx

	push ecx
	push edx
	
	call sorthem2	
	call finale

	jmp exit
	
	;mov eax, 1			; idk what this does
	;int 0x80			; i think its a syscall

; Sorts list recursively with helper functions
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

; Swaps peg[i] and peg[i+1]
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
		
		pop ecx
		pop edx
		
		pusha

		call showp
		call read_char

		popa
		ret

; Prints configuration of array with pegs
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

		call printspaces
		call printpeg
		call ppipe
		call printpeg
		call print_nl

		popa	

		add ebx, 4
		jmp prnt
	
	dones:

		call xxxhubxxx
		ret

; Prints spaces to center the tower and pegs
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

; Prints the 'o' -- the peg
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

; Prints the pipe symbol
ppipe:

	push eax
	mov eax, '|'
	call print_char
	pop eax
	ret

; Prints the "XXX.." at the bottom
xxxhubxxx:

	push eax
	mov eax, base
	call print_string
	call print_nl
	pop eax
	ret

; Prints an error message -- if the 2nd arg is not valid
errornum:

	push errorNumMsg
	call printf
	add esp, 4
	jmp exit	

; Prints an error message -- if to little or to many args
errorarg:

	push errorArgMsg
	call printf
	add esp, 4
	jmp exit

; Debugging function used to test seg faults and bad loops
; No longer used -- Gone, but not forgotten
func:

	;; print statement used for debugging
	push test		; push test to stack
	call printf		; call printf to display test
	add esp, 4		; clean the stack
	jmp exit		; uncond jump to exit

; self explanatory :)
exit:
	
	popa 
	leave	
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;                                              ;;;;;;;;;;
;;;;;;;;;;           FINAL NASM PROJECT                 ;;;;;;;;;;
;;;;;;;;;;              BY: JATIN C.                    ;;;;;;;;;;
;;;;;;;;;;                                              ;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
