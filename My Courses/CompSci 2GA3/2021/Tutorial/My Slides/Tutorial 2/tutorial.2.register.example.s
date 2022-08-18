	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 11, 0	sdk_version 11, 3
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	-23(%rbp), %rsi
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -28(%rbp)
	movq	L___const.main.s(%rip), %rax
	movq	%rax, -23(%rbp)
	movl	L___const.main.s+8(%rip), %ecx
	movl	%ecx, -15(%rbp)
	movw	L___const.main.s+12(%rip), %dx
	movw	%dx, -11(%rbp)
	movb	L___const.main.s+14(%rip), %dil
	movb	%dil, -9(%rbp)
	movl	$9001, -32(%rbp)                ## imm = 0x2329
	movl	-32(%rbp), %edx
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	___stack_chk_guard@GOTPCREL(%rip), %rsi
	movq	(%rsi), %rsi
	movq	-8(%rbp), %rdi
	cmpq	%rdi, %rsi
	jne	LBB0_2
## %bb.1:
	xorl	%eax, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
LBB0_2:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L___const.main.s:                       ## @__const.main.s
	.asciz	"Thanks Melissa"

L_.str:                                 ## @.str
	.asciz	"%s, over %d\n"

.subsections_via_symbols
