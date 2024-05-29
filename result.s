	.text
	.syntax unified
	.eabi_attribute	67, "2.09"
	.eabi_attribute	6, 10
	.eabi_attribute	7, 65
	.eabi_attribute	8, 1
	.eabi_attribute	9, 2
	.fpu	vfpv3
	.eabi_attribute	34, 1
	.eabi_attribute	17, 1
	.eabi_attribute	20, 1
	.eabi_attribute	21, 0
	.eabi_attribute	23, 3
	.eabi_attribute	24, 1
	.eabi_attribute	25, 1
	.eabi_attribute	28, 1
	.eabi_attribute	38, 1
	.eabi_attribute	14, 0
	.file	"main"
	.p2align	2
	.type	initGlobalVar,%function
	.code	32
initGlobalVar:
	.fnstart
	bx	lr
.Lfunc_end0:
	.size	initGlobalVar, .Lfunc_end0-initGlobalVar
	.fnend

	.globl	main
	.p2align	2
	.type	main,%function
	.code	32
main:
	.fnstart
	.pad	#8
	sub	sp, sp, #8
	mov	r0, #0
	add	sp, sp, #8
	bx	lr
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.fnend

	.section	.init_array,"aw",%init_array
	.p2align	2
	.long	initGlobalVar(target1)
	.section	".note.GNU-stack","",%progbits
	.eabi_attribute	30, 1
