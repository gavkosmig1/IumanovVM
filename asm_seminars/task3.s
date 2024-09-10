	.file	"task3.c"
	.text
	.globl	copy
	.def	copy;	.scl	2;	.type	32;	.endef
copy:
	movl	(%rdi), %eax
	movb	%al, (%rsi)
	ret
	.ident	"GCC: (x86_64-posix-seh-rev1, Built by MinGW-Builds project) 13.1.0"
