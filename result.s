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
	.pad	#888
	sub	sp, sp, #888
	mov	r0, #3
	mov	r1, #2
	mov	r2, #1
	str	r0, [sp, #56]
	str	r1, [sp, #52]
	str	r2, [sp, #48]
	str	r0, [sp, #12]
	stm	sp, {r0, r2}
	mov	r0, #0
	str	r1, [sp, #8]
	add	sp, sp, #888
	bx	lr
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.fnend

	.section	.init_array,"aw",%init_array
	.p2align	2
	.long	initGlobalVar(target1)
	.type	a,%object
	.local	a
	.comm	a,40,16
	.type	b,%object
	.section	.rodata,"a",%progbits
	.p2align	4, 0x0
b:
	.long	1
	.long	2
	.long	3
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.zero	80
	.long	2
	.long	3
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.zero	80
	.zero	80
	.zero	80
	.zero	80
	.zero	80
	.zero	80
	.zero	80
	.size	b, 800

	.type	c,%object
	.local	c
	.comm	c,4,4
	.type	d,%object
	.p2align	4, 0x0
d:
	.long	1
	.long	2
	.long	3
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.size	d, 40

	.type	e,%object
	.p2align	2, 0x0
e:
	.long	3
	.size	e, 4

	.section	".note.GNU-stack","",%progbits
	.eabi_attribute	30, 1
