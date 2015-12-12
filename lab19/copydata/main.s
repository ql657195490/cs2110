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
	sub	sp, sp, #8
	add	r7, sp, #0
	mov	r3, #128
	lsl	r3, r3, #19
	ldr	r2, .L11
	strh	r2, [r3]
	mov	r3, #0
	str	r3, [r7]
	ldr	r3, .L11+4
	mov	r2, r7
	str	r2, [r3]
	ldr	r3, .L11+8
	ldr	r2, .L11+12
	ldr	r2, [r2]
	str	r2, [r3]
	ldr	r3, .L11+16
	ldr	r2, .L11+20
	str	r2, [r3]
	ldr	r3, .L11+24
	mov	r2, #0
	strh	r2, [r3]
	ldr	r3, .L11+28
	ldr	r2, .L11+32
	str	r2, [r3]
	ldr	r3, .L11+36
	mov	r2, #8
	strh	r2, [r3]
	ldr	r3, .L11+40
	ldr	r2, .L11+44
	strh	r2, [r3]
	ldr	r3, .L11+48
	mov	r2, #195
	strh	r2, [r3]
	ldr	r3, .L11+24
	mov	r2, #1
	strh	r2, [r3]
	mov	r3, #0
	str	r3, [r7, #4]
	b	.L7
.L8:
	ldr	r2, [r7, #4]
	ldr	r3, .L11+52
	mov	r0, r2
	mov	r1, r3
	ldr	r3, .L11+56
	bl	.L13
	ldr	r3, [r7, #4]
	add	r3, r3, #1
	str	r3, [r7, #4]
.L7:
	ldr	r3, [r7, #4]
	cmp	r3, #159
	ble	.L8
	ldr	r3, .L11+24
	mov	r2, #0
	strh	r2, [r3]
.L9:
	b	.L9
.L12:
	.align	2
.L11:
	.word	1027
	.word	67109076
	.word	67109080
	.word	videoBuffer
	.word	67109084
	.word	-2063578368
	.word	67109384
	.word	50364412
	.word	timeout
	.word	67109376
	.word	67109120
	.word	-512
	.word	67109122
	.word	mystery
	.word	drawrow
	.size	main, .-main
	.ident	"GCC: (GNU) 4.4.1"
	.code 16
	.align	1
.L13:
	bx	r3
