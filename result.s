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

	.p2align	2
	.type	fib,%function
	.code	32
fib:
	.fnstart
	.save	{r4, lr}
	push	{r4, lr}
	.pad	#8
	sub	sp, sp, #8
	mov	r1, r0
	str	r0, [sp, #4]
	mvn	r0, #0
	cmp	r1, #0
	ble	.LBB1_2
	ldr	r1, [sp, #4]
	mov	r0, #1
	cmp	r1, #1
	cmpne	r1, #2
	bne	.LBB1_3
.LBB1_2:
	add	sp, sp, #8
	pop	{r4, pc}
.LBB1_3:
	ldr	r0, [sp, #4]
	sub	r0, r0, #1
	bl	fib
	mov	r4, r0
	ldr	r0, [sp, #4]
	sub	r0, r0, #2
	bl	fib
	add	r0, r4, r0
	add	sp, sp, #8
	pop	{r4, pc}
.Lfunc_end1:
	.size	fib, .Lfunc_end1-fib
	.fnend

	.globl	main
	.p2align	2
	.type	main,%function
	.code	32
main:
	.fnstart
	.save	{r11, lr}
	push	{r11, lr}
	.pad	#8
	sub	sp, sp, #8
	mov	r0, #10
	str	r0, [sp, #4]
	bl	fib
	add	r0, r0, #1
	str	r0, [sp]
	mov	r0, #0
	add	sp, sp, #8
	pop	{r11, pc}
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.fnend

	.section	.init_array,"aw",%init_array
	.p2align	2
	.long	initGlobalVar(target1)
	.section	".note.GNU-stack","",%progbits
	.eabi_attribute	30, 1
