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
	.file	"mylib.c"
	.global	videoBuffer
	.data
	.align	2
	.type	videoBuffer, %object
	.size	videoBuffer, 4
videoBuffer:
	.word	100663296
	.text
	.align	2
	.global	fillScreen3
	.code	16
	.thumb_func
	.type	fillScreen3, %function
fillScreen3:
	push	{r7, lr}
	sub	sp, sp, #16
	add	r7, sp, #0
	mov	r2, r0
	add	r3, r7, #6
	strh	r2, [r3]
	add	r3, r7, #6
	ldrh	r2, [r3]
	add	r3, r7, #6
	ldrh	r3, [r3]
	lsl	r3, r3, #16
	orr	r3, r3, r2
	str	r3, [r7, #12]
	ldr	r3, .L3
	mov	r2, r7
	add	r2, r2, #12
	str	r2, [r3]
	ldr	r3, .L3+4
	ldr	r2, .L3+8
	ldr	r2, [r2]
	str	r2, [r3]
	ldr	r3, .L3+12
	ldr	r2, .L3+16
	str	r2, [r3]
	mov	sp, r7
	add	sp, sp, #16
	@ sp needed for prologue
	pop	{r7}
	pop	{r0}
	bx	r0
.L4:
	.align	2
.L3:
	.word	67109076
	.word	67109080
	.word	videoBuffer
	.word	67109084
	.word	-2063578368
	.size	fillScreen3, .-fillScreen3
	.align	2
	.global	waitForVBlank
	.code	16
	.thumb_func
	.type	waitForVBlank, %function
waitForVBlank:
	push	{r7, lr}
	add	r7, sp, #0
.L6:
	ldr	r3, .L9
	ldrh	r3, [r3]
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r3, #159
	bhi	.L6
.L7:
	ldr	r3, .L9
	ldrh	r3, [r3]
	lsl	r3, r3, #16
	lsr	r3, r3, #16
	cmp	r3, #159
	bls	.L7
	mov	sp, r7
	@ sp needed for prologue
	pop	{r7}
	pop	{r0}
	bx	r0
.L10:
	.align	2
.L9:
	.word	67108870
	.size	waitForVBlank, .-waitForVBlank
	.global	font
	.section	.rodata
	.align	2
	.type	font, %object
	.size	font, 768
font:
	.word	0
	.word	0
	.word	404232216
	.word	1572888
	.word	13878
	.word	0
	.word	914306614
	.word	3552895
	.word	1007057944
	.word	1588832
	.word	456484352
	.word	3364460
	.word	1846949404
	.word	14578491
	.word	792600
	.word	0
	.word	202119216
	.word	3151884
	.word	808458252
	.word	792624
	.word	-12818944
	.word	26172
	.word	2115508224
	.word	6168
	.word	0
	.word	202905600
	.word	2113929216
	.word	0
	.word	0
	.word	1579008
	.word	405823680
	.word	198156
	.word	2121688636
	.word	3958382
	.word	404626456
	.word	1579032
	.word	811623996
	.word	8260632
	.word	945841724
	.word	3958368
	.word	859192376
	.word	3158143
	.word	1614677630
	.word	3958368
	.word	1040583736
	.word	3958374
	.word	811622526
	.word	1579032
	.word	1013343804
	.word	3958374
	.word	2087085628
	.word	1847392
	.word	1579008
	.word	1579008
	.word	1579008
	.word	202905600
	.word	102260736
	.word	24600
	.word	8257536
	.word	126
	.word	1612187136
	.word	1560
	.word	811623996
	.word	1572888
	.word	1515873852
	.word	3933818
	.word	2120640060
	.word	6710886
	.word	1046898238
	.word	4089446
	.word	101059704
	.word	7867398
	.word	1717974558
	.word	1980006
	.word	503711358
	.word	8259078
	.word	503711358
	.word	394758
	.word	1980130876
	.word	8152678
	.word	2120640102
	.word	6710886
	.word	404232252
	.word	3938328
	.word	1616928864
	.word	3958368
	.word	253440867
	.word	6501147
	.word	101058054
	.word	8259078
	.word	1803515747
	.word	6513507
	.word	2070898531
	.word	6513523
	.word	1717986876
	.word	3958374
	.word	1046898238
	.word	394758
	.word	858993438
	.word	8272691
	.word	1046898238
	.word	6710838
	.word	1007576636
	.word	3958384
	.word	404232318
	.word	1579032
	.word	1717986918
	.word	3958374
	.word	1717986918
	.word	1588284
	.word	1801675619
	.word	6518655
	.word	406611651
	.word	12805692
	.word	406611651
	.word	1579032
	.word	202911871
	.word	8323846
	.word	202116156
	.word	3935244
	.word	403441155
	.word	12607536
	.word	808464444
	.word	3944496
	.word	6700056
	.word	0
	.word	0
	.word	4128768
	.word	3151896
	.word	0
	.word	1614544896
	.word	8152700
	.word	1715340806
	.word	4089446
	.word	104595456
	.word	3933702
	.word	1719427168
	.word	8152678
	.word	1715208192
	.word	3933822
	.word	205392952
	.word	789516
	.word	1719402496
	.word	1012956262
	.word	1715340806
	.word	6710886
	.word	404226072
	.word	3151896
	.word	808452144
	.word	506474544
	.word	912655878
	.word	6698526
	.word	404232216
	.word	3151896
	.word	2134310912
	.word	6513515
	.word	1715339264
	.word	6710886
	.word	1715208192
	.word	3958374
	.word	1715339264
	.word	101072486
	.word	1719402496
	.word	1616936038
	.word	1715339264
	.word	394758
	.word	104595456
	.word	4087868
	.word	205392908
	.word	3673100
	.word	1717960704
	.word	8152678
	.word	1717960704
	.word	1588326
	.word	1667432448
	.word	3571563
	.word	912457728
	.word	6501916
	.word	1717960704
	.word	202914918
	.word	813563904
	.word	8260632
	.word	202905648
	.word	3151896
	.word	404232216
	.word	1579032
	.word	806885388
	.word	792600
	.word	3894784
	.word	0
	.word	0
	.word	0
	.text
	.align	2
	.code	16
	.thumb_func
	.type	setPixel3, %function
setPixel3:
	push	{r7, lr}
	sub	sp, sp, #16
	add	r7, sp, #0
	str	r0, [r7, #12]
	str	r1, [r7, #8]
	add	r3, r7, #6
	strh	r2, [r3]
	ldr	r3, .L13
	ldr	r1, [r3]
	ldr	r2, [r7, #8]
	mov	r3, r2
	lsl	r3, r3, #4
	sub	r3, r3, r2
	lsl	r3, r3, #4
	mov	r2, r3
	ldr	r3, [r7, #12]
	add	r3, r2, r3
	lsl	r3, r3, #1
	add	r3, r1, r3
	add	r2, r7, #6
	ldrh	r2, [r2]
	strh	r2, [r3]
	mov	sp, r7
	add	sp, sp, #16
	@ sp needed for prologue
	pop	{r7}
	pop	{r0}
	bx	r0
.L14:
	.align	2
.L13:
	.word	videoBuffer
	.size	setPixel3, .-setPixel3
	.align	2
	.code	16
	.thumb_func
	.type	drawChar3, %function
drawChar3:
	push	{r7, lr}
	sub	sp, sp, #40
	add	r7, sp, #0
	str	r0, [r7, #12]
	str	r1, [r7, #8]
	mov	r1, r2
	mov	r2, r3
	add	r3, r7, #7
	strb	r1, [r3]
	add	r3, r7, #4
	strh	r2, [r3]
	add	r3, r7, #7
	ldrb	r3, [r3]
	cmp	r3, #32
	bne	.LCB137
	b	.L27	@long jump
.LCB137:
	mov	r3, #0
	str	r3, [r7, #16]
	b	.L17
.L21:
	add	r3, r7, #7
	ldrb	r3, [r3]
	sub	r3, r3, #32
	lsl	r2, r3, #1
	ldr	r3, .L28
	lsl	r2, r2, #2
	ldr	r2, [r2, r3]
	ldr	r3, [r7, #16]
	lsl	r3, r3, #3
	lsr	r2, r2, r3
	mov	r3, r7
	add	r3, r3, #23
	strb	r2, [r3]
	mov	r3, #0
	str	r3, [r7, #24]
	b	.L18
.L20:
	mov	r3, r7
	add	r3, r3, #23
	ldrb	r2, [r3]
	ldr	r3, [r7, #24]
	asr	r2, r2, r3
	mov	r3, #1
	and	r3, r3, r2
	lsl	r3, r3, #24
	lsr	r3, r3, #24
	cmp	r3, #0
	beq	.L19
	ldr	r2, [r7, #12]
	ldr	r3, [r7, #24]
	add	r1, r2, r3
	ldr	r2, [r7, #8]
	ldr	r3, [r7, #16]
	add	r2, r2, r3
	add	r3, r7, #4
	ldrh	r3, [r3]
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	bl	setPixel3
.L19:
	ldr	r3, [r7, #24]
	add	r3, r3, #1
	str	r3, [r7, #24]
.L18:
	ldr	r3, [r7, #24]
	cmp	r3, #7
	ble	.L20
	ldr	r3, [r7, #16]
	add	r3, r3, #1
	str	r3, [r7, #16]
.L17:
	ldr	r3, [r7, #16]
	cmp	r3, #3
	ble	.L21
	mov	r3, #0
	str	r3, [r7, #28]
	b	.L22
.L26:
	add	r3, r7, #7
	ldrb	r3, [r3]
	sub	r3, r3, #32
	lsl	r3, r3, #1
	add	r2, r3, #1
	ldr	r3, .L28
	lsl	r2, r2, #2
	ldr	r2, [r2, r3]
	ldr	r3, [r7, #28]
	lsl	r3, r3, #3
	lsr	r2, r2, r3
	mov	r3, r7
	add	r3, r3, #35
	strb	r2, [r3]
	mov	r3, #0
	str	r3, [r7, #36]
	b	.L23
.L25:
	mov	r3, r7
	add	r3, r3, #35
	ldrb	r2, [r3]
	ldr	r3, [r7, #36]
	asr	r2, r2, r3
	mov	r3, #1
	and	r3, r3, r2
	lsl	r3, r3, #24
	lsr	r3, r3, #24
	cmp	r3, #0
	beq	.L24
	ldr	r2, [r7, #12]
	ldr	r3, [r7, #36]
	add	r1, r2, r3
	ldr	r2, [r7, #8]
	ldr	r3, [r7, #28]
	add	r3, r2, r3
	add	r2, r3, #4
	add	r3, r7, #4
	ldrh	r3, [r3]
	mov	r0, r1
	mov	r1, r2
	mov	r2, r3
	bl	setPixel3
.L24:
	ldr	r3, [r7, #36]
	add	r3, r3, #1
	str	r3, [r7, #36]
.L23:
	ldr	r3, [r7, #36]
	cmp	r3, #7
	ble	.L25
	ldr	r3, [r7, #28]
	add	r3, r3, #1
	str	r3, [r7, #28]
.L22:
	ldr	r3, [r7, #28]
	cmp	r3, #3
	ble	.L26
.L27:
	mov	sp, r7
	add	sp, sp, #40
	@ sp needed for prologue
	pop	{r7}
	pop	{r0}
	bx	r0
.L29:
	.align	2
.L28:
	.word	font
	.size	drawChar3, .-drawChar3
	.align	2
	.global	drawString3
	.code	16
	.thumb_func
	.type	drawString3, %function
drawString3:
	push	{r7, lr}
	sub	sp, sp, #24
	add	r7, sp, #0
	str	r0, [r7, #12]
	str	r1, [r7, #8]
	str	r2, [r7, #4]
	mov	r2, r3
	add	r3, r7, #2
	strh	r2, [r3]
	ldr	r3, [r7, #12]
	str	r3, [r7, #20]
	b	.L31
.L33:
	ldr	r3, [r7, #4]
	ldrb	r3, [r3]
	cmp	r3, #10
	bne	.L32
	ldr	r3, [r7, #12]
	str	r3, [r7, #20]
	ldr	r3, [r7, #8]
	add	r3, r3, #8
	str	r3, [r7, #8]
	ldr	r3, [r7, #4]
	add	r3, r3, #1
	str	r3, [r7, #4]
	b	.L31
.L32:
	ldr	r3, [r7, #4]
	ldrb	r2, [r3]
	ldr	r3, [r7, #4]
	add	r3, r3, #1
	str	r3, [r7, #4]
	ldr	r0, [r7, #20]
	ldr	r1, [r7, #8]
	add	r3, r7, #2
	ldrh	r3, [r3]
	bl	drawChar3
	ldr	r3, [r7, #20]
	add	r3, r3, #8
	str	r3, [r7, #20]
.L31:
	ldr	r3, [r7, #4]
	ldrb	r3, [r3]
	cmp	r3, #0
	bne	.L33
	mov	sp, r7
	add	sp, sp, #24
	@ sp needed for prologue
	pop	{r7}
	pop	{r0}
	bx	r0
	.size	drawString3, .-drawString3
	.ident	"GCC: (GNU) 4.4.1"
