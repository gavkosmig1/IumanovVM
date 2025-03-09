	.file	"move.c"
	.text
	.globl	exchange
	.def	exchange;	.scl	2;	.type	32;	.endef
exchange:
	movq	(%rdi), %rax
	movq	%rsi, (%rdi)
	ret
	.ident	"GCC: (x86_64-posix-seh-rev1, Built by MinGW-Builds project) 13.1.0"
