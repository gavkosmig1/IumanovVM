	.file	"mstore.c"
	.text
	.globl	multstore
	.def	multstore;	.scl	2;	.type	32;	.endef
multstore:
	pushq	%rbx
	subq	$32, %rsp
	movq	%r8, %rbx
	call	mult2
	movq	%rax, (%rbx)
	addq	$32, %rsp
	popq	%rbx
	ret
	.ident	"GCC: (x86_64-posix-seh-rev1, Built by MinGW-Builds project) 13.1.0"
	.def	mult2;	.scl	2;	.type	32;	.endef
