	.file	"mstore.cpp"
	.text
	.globl	_Z9multstoreyyPy
	.def	_Z9multstoreyyPy;	.scl	2;	.type	32;	.endef
_Z9multstoreyyPy:
	pushq	%rbx
	subq	$32, %rsp
	movq	%r8, %rbx
	call	_Z5mult2yy
	movq	%rax, (%rbx)
	addq	$32, %rsp
	popq	%rbx
	ret
	.ident	"GCC: (x86_64-posix-seh-rev1, Built by MinGW-Builds project) 13.1.0"
	.def	_Z5mult2yy;	.scl	2;	.type	32;	.endef
