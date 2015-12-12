	.cpu arm7tdmi
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.code	16
	.file	"main.c"
	.global	videoBuffer
	.data
	.align	2
	.type	videoBuffer, %object
	.size	videoBuffer, 4
videoBuffer:
	.word	100663296
	.text
	.align	2
	.global	timeout
	.code	16
	.thumb_func
	.type	timeout, %function
timeout:
	push	{r7, lr}
	add	r7, sp, #0
	ldr	r3, .L4
	mov	r2, #0
	strh	r2, [r3]
.L2:
	b	.L2
.L5:
	.align	2
.L4:
	.word	67109384
	.size	timeout, .-timeout
	.align	2
	.global	main
	.code	16
	.thumb_func
	.type	main, %function
main:
	push	{r7, lr}
	add	r7, sp, #0
	mov	r3, #128
	lsl	r3, r3, #19
	ldr	r2, .L9
	strh	r2, [r3]
	ldr	r3, .L9+4
	ldr	r2, .L9+8
	str	r2, [r3]
	ldr	r3, .L9+12
	ldr	r2, .L9+16
	ldr	r2, [r2]
	str	r2, [r3]
	ldr	r3, .L9+20
	ldr	r2, .L9+24
	str	r2, [r3]
	ldr	r3, .L9+28
	mov	r2, #0
	strh	r2, [r3]
	ldr	r3, .L9+32
	ldr	r2, .L9+36
	str	r2, [r3]
	ldr	r3, .L9+40
	mov	r2, #8
	strh	r2, [r3]
	ldr	r3, .L9+44
	ldr	r2, .L9+48
	strh	r2, [r3]
	ldr	r3, .L9+52
	mov	r2, #195
	strh	r2, [r3]
	ldr	r3, .L9+28
	mov	r2, #1
	strh	r2, [r3]
	ldr	r3, .L9+56
	bl	.L11
	ldr	r3, .L9+28
	mov	r2, #0
	strh	r2, [r3]
.L7:
	b	.L7
.L10:
	.align	2
.L9:
	.word	1027
	.word	67109076
	.word	mystery
	.word	67109080
	.word	videoBuffer
	.word	67109084
	.word	-2080355584
	.word	67109384
	.word	50364412
	.word	timeout
	.word	67109376
	.word	67109120
	.word	-512
	.word	67109122
	.word	clearscreen
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.1"
	.code 16
	.align	1
.L11:
	bx	r3
