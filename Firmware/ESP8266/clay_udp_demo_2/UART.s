	.file	"UART.c"
	.text
.Ltext0:
	.literal_position
	.literal .LC0, 1610612764
	.literal .LC2, 1610612736
	.align	4
	.type	uart_tx_one_char, @function
uart_tx_one_char:
.LFB0:
	.file 1 "user/UART.c"
	.loc 1 55 0
.LVL0:
.LBB6:
	.loc 1 58 0
	slli	a4, a2, 4
	sub	a2, a4, a2
.LVL1:
	l32r	a5, .LC0
	slli	a2, a2, 8
	add.n	a5, a2, a5
	.loc 1 60 0
	movi	a6, 0x7d
.L2:
	.loc 1 58 0
	l32i.n	a4, a5, 0
.LVL2:
	.loc 1 60 0
	extui	a4, a4, 16, 8
.LVL3:
	bltu	a6, a4, .L2
.LBE6:
	.loc 1 66 0
	l32r	a4, .LC2
	add.n	a2, a2, a4
	s32i.n	a3, a2, 0
	.loc 1 68 0
	movi.n	a2, 0
	ret.n
.LFE0:
	.size	uart_tx_one_char, .-uart_tx_one_char
	.literal_position
	.literal .LC3, fifo_tmp
	.literal .LC6, uart_no
	.literal .LC7, 1610612744
	.literal .LC8, fifo_len
	.literal .LC9, buf_idx
	.literal .LC10, 1610612752
	.literal .LC11, 1610612764
	.literal .LC12, 1610612736
	.literal .LC13, 1610612748
	.align	4
	.type	uart0_rx_intr_handler, @function
uart0_rx_intr_handler:
.LFB19:
	.loc 1 380 0
.LVL4:
	addi	sp, sp, -16
.LCFI0:
	.loc 1 385 0
	l32r	a2, .LC6
.LVL5:
	.loc 1 380 0
	s32i.n	a12, sp, 12
	s32i.n	a13, sp, 8
	s32i.n	a14, sp, 4
	s32i.n	a15, sp, 0
.LCFI1:
	.loc 1 385 0
	l8ui	a8, a2, 0
	l32r	a7, .LC7
	slli	a2, a8, 4
	sub	a8, a2, a8
	slli	a4, a8, 8
	l32r	a8, .LC8
	l32r	a5, .LC9
	l8ui	a9, a8, 0
	.loc 1 427 0
	l32r	a8, .LC10
	.loc 1 385 0
	add.n	a7, a4, a7
	.loc 1 387 0
	movi.n	a3, 0
	.loc 1 427 0
	add.n	a8, a4, a8
	.loc 1 385 0
	l32i.n	a6, a7, 0
.LVL6:
	l8ui	a2, a5, 0
	.loc 1 387 0
	mov.n	a10, a3
	.loc 1 389 0
	movi.n	a11, 8
	.loc 1 409 0
	movi	a12, 0x100
	.loc 1 424 0
	movi.n	a13, 2
	.loc 1 428 0
	movi.n	a14, -3
	.loc 1 392 0
	mov.n	a15, a8
	.loc 1 387 0
	j	.L5
.L14:
	.loc 1 389 0
	and	a5, a6, a11
	beqz.n	a5, .L6
	.loc 1 392 0
	s32i.n	a11, a15, 0
	j	.L7
.L6:
	.loc 1 394 0
	extui	a4, a6, 0, 1
	beqz.n	a4, .L8
	.loc 1 397 0
	l32r	a2, .LC11
	.loc 1 402 0
	l32r	a9, .LC12
	.loc 1 397 0
	l32i.n	a2, a2, 0
	.loc 1 402 0
	l32r	a6, .LC3
.LVL7:
	.loc 1 397 0
	extui	a2, a2, 0, 8
	.loc 1 400 0
	j	.L9
.L10:
	.loc 1 402 0
	l32i.n	a4, a9, 0
	add.n	a3, a5, a6
	s8i	a4, a3, 0
	addi.n	a5, a5, 1
.L9:
	.loc 1 400 0
	extui	a3, a5, 0, 8
	bltu	a3, a2, .L10
	.loc 1 407 0
	l32r	a4, .LC10
	movi.n	a3, 1
	s32i.n	a3, a4, 0
	mov.n	a9, a2
	j	.L26
.LVL8:
.L8:
	.loc 1 409 0
	bnone	a6, a12, .L11
	.loc 1 412 0
	l32r	a2, .LC11
	.loc 1 417 0
	l32r	a9, .LC12
	.loc 1 412 0
	l32i.n	a2, a2, 0
	.loc 1 417 0
	l32r	a6, .LC3
.LVL9:
	.loc 1 412 0
	extui	a2, a2, 0, 8
	.loc 1 415 0
	j	.L12
.L13:
	.loc 1 417 0
	l32i.n	a5, a9, 0
	add.n	a3, a4, a6
	s8i	a5, a3, 0
	addi.n	a4, a4, 1
.L12:
	.loc 1 415 0
	extui	a3, a4, 0, 8
	bltu	a3, a2, .L13
	.loc 1 422 0
	l32r	a3, .LC10
	mov.n	a9, a2
	s32i.n	a12, a3, 0
	movi.n	a3, 1
.L26:
	mov.n	a10, a3
	j	.L7
.LVL10:
.L11:
	.loc 1 424 0
	bnone	a6, a13, .L7
	.loc 1 428 0
	l32r	a5, .LC13
	.loc 1 427 0
	s32i.n	a13, a8, 0
	.loc 1 428 0
	l32i.n	a4, a5, 0
	and	a4, a4, a14
	s32i.n	a4, a5, 0
.LVL11:
.L7:
	.loc 1 435 0
	l32i.n	a6, a7, 0
.LVL12:
.L5:
	.loc 1 387 0
	bnez.n	a6, .L14
	beqz.n	a10, .L15
	l32r	a4, .LC9
	s8i	a2, a4, 0
.L15:
	beqz.n	a3, .L4
	l32r	a5, .LC8
	s8i	a9, a5, 0
.L4:
	.loc 1 437 0
	l32i.n	a12, sp, 12
	l32i.n	a13, sp, 8
	l32i.n	a14, sp, 4
	l32i.n	a15, sp, 0
	addi	sp, sp, 16
	ret.n
.LFE19:
	.size	uart0_rx_intr_handler, .-uart0_rx_intr_handler
	.literal_position
	.align	4
	.type	uart1_write_char, @function
uart1_write_char:
.LFB1:
	.loc 1 71 0
.LVL13:
	addi	sp, sp, -16
.LCFI2:
	s32i.n	a12, sp, 8
	s32i.n	a0, sp, 12
.LCFI3:
	.loc 1 71 0
	extui	a12, a2, 0, 8
	.loc 1 72 0
	bnei	a12, 10, .L28
.LVL14:
.LBB9:
.LBB10:
	.loc 1 74 0
	movi.n	a3, 0xd
	movi.n	a2, 1
.LVL15:
	call0	uart_tx_one_char
.LVL16:
	j	.L30
.LVL17:
.L28:
.LBE10:
.LBE9:
	.loc 1 77 0
	movi.n	a2, 0xd
.LVL18:
	beq	a12, a2, .L27
.L30:
	.loc 1 82 0
	mov.n	a3, a12
	movi.n	a2, 1
	call0	uart_tx_one_char
.LVL19:
.L27:
	.loc 1 84 0
	l32i.n	a0, sp, 12
	l32i.n	a12, sp, 8
.LVL20:
	addi	sp, sp, 16
	ret.n
.LFE1:
	.size	uart1_write_char, .-uart1_write_char
	.literal_position
	.align	4
	.type	uart0_write_char, @function
uart0_write_char:
.LFB2:
	.loc 1 87 0
.LVL21:
	addi	sp, sp, -16
.LCFI4:
	s32i.n	a12, sp, 8
	s32i.n	a0, sp, 12
.LCFI5:
	.loc 1 87 0
	extui	a12, a2, 0, 8
	.loc 1 88 0
	bnei	a12, 10, .L32
.LVL22:
.LBB13:
.LBB14:
	.loc 1 90 0
	movi.n	a3, 0xd
	movi.n	a2, 0
.LVL23:
	call0	uart_tx_one_char
.LVL24:
	j	.L34
.LVL25:
.L32:
.LBE14:
.LBE13:
	.loc 1 93 0
	movi.n	a2, 0xd
.LVL26:
	beq	a12, a2, .L31
.L34:
	.loc 1 98 0
	mov.n	a3, a12
	movi.n	a2, 0
	call0	uart_tx_one_char
.LVL27:
.L31:
	.loc 1 100 0
	l32i.n	a0, sp, 12
	l32i.n	a12, sp, 8
.LVL28:
	addi	sp, sp, 16
	ret.n
.LFE2:
	.size	uart0_write_char, .-uart0_write_char
	.literal_position
	.literal .LC14, 1610612768
	.align	4
	.global	UART_SetWordLength
	.type	UART_SetWordLength, @function
UART_SetWordLength:
.LFB5:
	.loc 1 229 0
.LVL29:
	.loc 1 230 0
	slli	a4, a2, 4
	sub	a2, a4, a2
.LVL30:
	l32r	a4, .LC14
	slli	a2, a2, 8
	add.n	a2, a2, a4
	l32i.n	a5, a2, 0
	movi.n	a4, -0xd
	and	a4, a5, a4
	slli	a3, a3, 2
.LVL31:
	or	a3, a4, a3
	s32i.n	a3, a2, 0
	ret.n
.LFE5:
	.size	UART_SetWordLength, .-UART_SetWordLength
	.literal_position
	.literal .LC15, 1610612768
	.align	4
	.global	UART_SetStopBits
	.type	UART_SetStopBits, @function
UART_SetStopBits:
.LFB6:
	.loc 1 234 0
.LVL32:
	.loc 1 235 0
	slli	a4, a2, 4
	sub	a2, a4, a2
.LVL33:
	l32r	a4, .LC15
	slli	a2, a2, 8
	add.n	a2, a2, a4
	l32i.n	a5, a2, 0
	movi	a4, -0x31
	and	a4, a5, a4
	slli	a3, a3, 4
.LVL34:
	or	a3, a4, a3
	s32i.n	a3, a2, 0
	ret.n
.LFE6:
	.size	UART_SetStopBits, .-UART_SetStopBits
	.literal_position
	.literal .LC16, 1610612768
	.literal .LC17, -33030145
	.align	4
	.global	UART_SetLineInverse
	.type	UART_SetLineInverse, @function
UART_SetLineInverse:
.LFB7:
	.loc 1 239 0
.LVL35:
	.loc 1 240 0
	slli	a4, a2, 4
	sub	a2, a4, a2
.LVL36:
	l32r	a4, .LC16
	slli	a2, a2, 8
	add.n	a2, a2, a4
	l32i.n	a5, a2, 0
	l32r	a4, .LC17
	and	a4, a5, a4
	s32i.n	a4, a2, 0
	.loc 1 241 0
	l32i.n	a4, a2, 0
	or	a3, a4, a3
.LVL37:
	s32i.n	a3, a2, 0
	ret.n
.LFE7:
	.size	UART_SetLineInverse, .-UART_SetLineInverse
	.literal_position
	.literal .LC18, 1610612768
	.align	4
	.global	UART_SetParity
	.type	UART_SetParity, @function
UART_SetParity:
.LFB8:
	.loc 1 245 0
.LVL38:
	.loc 1 246 0
	slli	a4, a2, 4
	sub	a2, a4, a2
.LVL39:
	l32r	a4, .LC18
	slli	a2, a2, 8
	add.n	a2, a2, a4
	l32i.n	a5, a2, 0
	movi.n	a4, -4
	and	a4, a5, a4
	s32i.n	a4, a2, 0
	.loc 1 248 0
	beqi	a3, 2, .L38
	.loc 1 253 0
	l32i.n	a4, a2, 0
	movi.n	a5, 2
	or	a3, a3, a5
.LVL40:
	or	a3, a3, a4
	s32i.n	a3, a2, 0
.L38:
	ret.n
.LFE8:
	.size	UART_SetParity, .-UART_SetParity
	.global	__udivsi3
	.literal_position
	.literal .LC19, 80000000
	.align	4
	.global	UART_SetBaudrate
	.type	UART_SetBaudrate, @function
UART_SetBaudrate:
.LFB9:
	.loc 1 258 0
.LVL41:
	addi	sp, sp, -16
.LCFI6:
	s32i.n	a12, sp, 8
.LCFI7:
	mov.n	a12, a2
	.loc 1 259 0
	l32r	a2, .LC19
.LVL42:
	.loc 1 258 0
	s32i.n	a0, sp, 12
.LCFI8:
	.loc 1 259 0
	call0	__udivsi3
.LVL43:
	mov.n	a3, a2
	mov.n	a2, a12
	call0	uart_div_modify
.LVL44:
	.loc 1 260 0
	l32i.n	a0, sp, 12
	l32i.n	a12, sp, 8
.LVL45:
	addi	sp, sp, 16
	ret.n
.LFE9:
	.size	UART_SetBaudrate, .-UART_SetBaudrate
	.literal_position
	.literal .LC20, 1610614800
	.literal .LC21, 1610612772
	.literal .LC22, -8323073
	.literal .LC23, 8388608
	.literal .LC24, -8388609
	.literal .LC25, 1610614792
	.literal .LC26, 1610612768
	.literal .LC27, 32768
	.literal .LC28, -32769
	.align	4
	.global	UART_SetFlowCtrl
	.type	UART_SetFlowCtrl, @function
UART_SetFlowCtrl:
.LFB10:
	.loc 1 264 0
.LVL46:
	.loc 1 264 0
	extui	a4, a4, 0, 8
	slli	a5, a2, 4
	.loc 1 265 0
	bbci	a3, 0, .L45
	.loc 1 267 0
	l32r	a6, .LC20
	movi	a7, -0x131
	l32i.n	a8, a6, 0
	.loc 1 268 0
	slli	a4, a4, 16
.LVL47:
	.loc 1 267 0
	and	a7, a8, a7
	s32i.n	a7, a6, 0
	l32i.n	a8, a6, 0
	movi	a7, 0x100
	or	a7, a8, a7
	s32i.n	a7, a6, 0
	.loc 1 268 0
	sub	a6, a5, a2
	slli	a7, a6, 8
	l32r	a6, .LC21
	add.n	a6, a7, a6
	l32i.n	a8, a6, 0
	l32r	a7, .LC22
	and	a7, a8, a7
	or	a4, a7, a4
	s32i.n	a4, a6, 0
	.loc 1 269 0
	l32i.n	a7, a6, 0
	l32r	a4, .LC23
	or	a4, a7, a4
	s32i.n	a4, a6, 0
	j	.L46
.L45:
	.loc 1 273 0
	sub	a4, a5, a2
	slli	a6, a4, 8
	l32r	a4, .LC21
	add.n	a4, a6, a4
	l32i.n	a7, a4, 0
	l32r	a6, .LC24
	and	a6, a7, a6
	s32i.n	a6, a4, 0
.L46:
	.loc 1 276 0
	bbci	a3, 1, .L47
.LVL48:
.LBB17:
.LBB18:
	.loc 1 278 0
	l32r	a3, .LC25
.LVL49:
	movi	a4, -0x131
	l32i.n	a6, a3, 0
	.loc 1 279 0
	sub	a5, a5, a2
	.loc 1 278 0
	and	a4, a6, a4
	s32i.n	a4, a3, 0
	l32i.n	a6, a3, 0
	movi	a4, 0x100
	or	a4, a6, a4
	s32i.n	a4, a3, 0
	.loc 1 279 0
	l32r	a3, .LC26
	slli	a5, a5, 8
	add.n	a5, a5, a3
	l32i.n	a3, a5, 0
	l32r	a2, .LC27
.LVL50:
	or	a2, a3, a2
	j	.L49
.LVL51:
.L47:
.LBE18:
.LBE17:
	.loc 1 283 0
	sub	a5, a5, a2
	l32r	a2, .LC26
.LVL52:
	slli	a5, a5, 8
	add.n	a5, a5, a2
	l32i.n	a3, a5, 0
.LVL53:
	l32r	a2, .LC28
	and	a2, a3, a2
.L49:
	s32i.n	a2, a5, 0
	ret.n
.LFE10:
	.size	UART_SetFlowCtrl, .-UART_SetFlowCtrl
	.literal_position
	.literal .LC29, 1610612764
	.literal .LC30, 16711680
	.align	4
	.global	UART_WaitTxFifoEmpty
	.type	UART_WaitTxFifoEmpty, @function
UART_WaitTxFifoEmpty:
.LFB11:
	.loc 1 288 0
.LVL54:
	.loc 1 289 0
	slli	a3, a2, 4
	sub	a2, a3, a2
.LVL55:
	l32r	a3, .LC29
	slli	a2, a2, 8
	add.n	a2, a2, a3
	l32r	a3, .LC30
.L51:
	.loc 1 289 0 is_stmt 0 discriminator 1
	l32i.n	a4, a2, 0
	bany	a4, a3, .L51
	.loc 1 291 0 is_stmt 1
	ret.n
.LFE11:
	.size	UART_WaitTxFifoEmpty, .-UART_WaitTxFifoEmpty
	.literal_position
	.literal .LC31, 1610612768
	.literal .LC32, 393216
	.literal .LC33, -393217
	.align	4
	.global	UART_ResetFifo
	.type	UART_ResetFifo, @function
UART_ResetFifo:
.LFB12:
	.loc 1 294 0
.LVL56:
	.loc 1 295 0
	slli	a3, a2, 4
	sub	a2, a3, a2
.LVL57:
	l32r	a3, .LC31
	slli	a2, a2, 8
	add.n	a2, a2, a3
	l32i.n	a4, a2, 0
	l32r	a3, .LC32
	or	a3, a4, a3
	s32i.n	a3, a2, 0
	.loc 1 296 0
	l32i.n	a4, a2, 0
	l32r	a3, .LC33
	and	a3, a4, a3
	s32i.n	a3, a2, 0
	ret.n
.LFE12:
	.size	UART_ResetFifo, .-UART_ResetFifo
	.literal_position
	.literal .LC34, 1610612752
	.align	4
	.global	UART_ClearIntrStatus
	.type	UART_ClearIntrStatus, @function
UART_ClearIntrStatus:
.LFB13:
	.loc 1 300 0
.LVL58:
	.loc 1 301 0
	slli	a4, a2, 4
	sub	a2, a4, a2
.LVL59:
	l32r	a4, .LC34
	slli	a2, a2, 8
	add.n	a2, a2, a4
	s32i.n	a3, a2, 0
	ret.n
.LFE13:
	.size	UART_ClearIntrStatus, .-UART_ClearIntrStatus
	.literal_position
	.literal .LC35, 1610612748
	.align	4
	.global	UART_SetIntrEna
	.type	UART_SetIntrEna, @function
UART_SetIntrEna:
.LFB14:
	.loc 1 305 0
.LVL60:
	.loc 1 306 0
	slli	a4, a2, 4
	sub	a2, a4, a2
.LVL61:
	l32r	a4, .LC35
	slli	a2, a2, 8
	add.n	a2, a2, a4
	l32i.n	a4, a2, 0
	or	a3, a4, a3
.LVL62:
	s32i.n	a3, a2, 0
	ret.n
.LFE14:
	.size	UART_SetIntrEna, .-UART_SetIntrEna
	.literal_position
	.align	4
	.global	UART_intr_handler_register
	.type	UART_intr_handler_register, @function
UART_intr_handler_register:
.LFB15:
	.loc 1 310 0
.LVL63:
	addi	sp, sp, -16
.LCFI9:
	.loc 1 311 0
	mov.n	a4, a3
	mov.n	a3, a2
.LVL64:
	movi.n	a2, 5
.LVL65:
	.loc 1 310 0
	s32i.n	a0, sp, 12
.LCFI10:
	.loc 1 311 0
	call0	_xt_isr_attach
.LVL66:
	.loc 1 312 0
	l32i.n	a0, sp, 12
	addi	sp, sp, 16
	ret.n
.LFE15:
	.size	UART_intr_handler_register, .-UART_intr_handler_register
	.literal_position
	.literal .LC36, uart1_write_char
	.literal .LC37, uart0_write_char
	.align	4
	.global	UART_SetPrintPort
	.type	UART_SetPrintPort, @function
UART_SetPrintPort:
.LFB16:
	.loc 1 315 0
.LVL67:
	addi	sp, sp, -16
.LCFI11:
	s32i.n	a0, sp, 12
.LCFI12:
	.loc 1 316 0
	bnei	a2, 1, .L58
	.loc 1 318 0
	l32r	a2, .LC36
.LVL68:
	j	.L60
.LVL69:
.L58:
	.loc 1 322 0
	l32r	a2, .LC37
.LVL70:
.L60:
	call0	os_install_putc1
.LVL71:
	.loc 1 324 0
	l32i.n	a0, sp, 12
	addi	sp, sp, 16
	ret.n
.LFE16:
	.size	UART_SetPrintPort, .-UART_SetPrintPort
	.literal_position
	.literal .LC38, 32768
	.literal .LC39, 1610614840
	.literal .LC40, 1610614808
	.literal .LC41, 1610614804
	.literal .LC42, 1610612768
	.align	4
	.global	UART_ParamConfig
	.type	UART_ParamConfig, @function
UART_ParamConfig:
.LFB17:
	.loc 1 327 0
.LVL72:
	addi	sp, sp, -16
.LCFI13:
	s32i.n	a12, sp, 8
	s32i.n	a13, sp, 4
	s32i.n	a0, sp, 12
.LCFI14:
	.loc 1 327 0
	mov.n	a13, a2
	mov.n	a12, a3
	.loc 1 328 0
	bnei	a2, 1, .L62
	.loc 1 330 0
	l32r	a2, .LC39
.LVL73:
	movi	a3, -0x131
.LVL74:
	l32i.n	a4, a2, 0
	and	a3, a4, a3
	s32i.n	a3, a2, 0
	l32i.n	a4, a2, 0
	movi.n	a3, 0x20
	or	a3, a4, a3
	j	.L69
.LVL75:
.L62:
	.loc 1 334 0
	l32r	a2, .LC40
.LVL76:
	movi	a3, -0x81
.LVL77:
	l32i.n	a4, a2, 0
	and	a3, a4, a3
	.loc 1 335 0
	l32r	a4, .LC41
	.loc 1 334 0
	s32i.n	a3, a2, 0
	.loc 1 335 0
	l32i.n	a5, a4, 0
	movi	a3, -0x131
	and	a5, a5, a3
	s32i.n	a5, a4, 0
	l32i.n	a5, a4, 0
	s32i.n	a5, a4, 0
	.loc 1 336 0
	l32i.n	a4, a2, 0
	and	a3, a4, a3
	s32i.n	a3, a2, 0
	l32i.n	a3, a2, 0
.L69:
	s32i.n	a3, a2, 0
	.loc 1 339 0
	l8ui	a4, a12, 20
	l32i.n	a3, a12, 16
	mov.n	a2, a13
	call0	UART_SetFlowCtrl
.LVL78:
	.loc 1 340 0
	l32i.n	a3, a12, 0
	mov.n	a2, a13
	call0	UART_SetBaudrate
.LVL79:
	.loc 1 342 0
	slli	a2, a13, 4
	sub	a2, a2, a13
	l32r	a7, .LC42
	l32i.n	a3, a12, 8
	slli	a2, a2, 8
	add.n	a7, a2, a7
	movi.n	a5, 0
	beqi	a3, 2, .L64
	.loc 1 342 0 is_stmt 0 discriminator 1
	movi.n	a5, 2
	or	a5, a3, a5
.L64:
	.loc 1 342 0 discriminator 4
	l32i.n	a3, a12, 16
	l32i.n	a6, a12, 12
	l32i.n	a2, a12, 4
	movi.n	a4, 2
	and	a4, a4, a3
	slli	a2, a2, 2
	l32r	a3, .LC38
	slli	a6, a6, 4
	or	a6, a6, a2
	movi.n	a2, 0
	moveqz	a3, a2, a4
	l32i.n	a2, a12, 24
	or	a2, a6, a2
	or	a5, a2, a5
	or	a2, a5, a3
	s32i.n	a2, a7, 0
	.loc 1 345 0 is_stmt 1 discriminator 4
	mov.n	a2, a13
	call0	UART_ResetFifo
.LVL80:
	.loc 1 346 0 discriminator 4
	l32i.n	a0, sp, 12
	l32i.n	a12, sp, 8
.LVL81:
	l32i.n	a13, sp, 4
.LVL82:
	addi	sp, sp, 16
	ret.n
.LFE17:
	.size	UART_ParamConfig, .-UART_ParamConfig
	.literal_position
	.literal .LC43, 1610612752
	.literal .LC44, 1610612772
	.literal .LC45, -16711681
	.literal .LC46, -2147483648
	.literal .LC47, 1610612748
	.align	4
	.global	UART_IntrConfig
	.type	UART_IntrConfig, @function
UART_IntrConfig:
.LFB18:
	.loc 1 349 0
.LVL83:
.LBB19:
.LBB20:
	.loc 1 301 0
	slli	a4, a2, 4
	sub	a2, a4, a2
.LVL84:
	l32r	a4, .LC43
	slli	a2, a2, 8
	add.n	a4, a2, a4
	movi	a5, 0x1ff
.LBE20:
.LBE19:
	.loc 1 353 0
	l32r	a8, .LC44
.LBB22:
.LBB21:
	.loc 1 301 0
	s32i.n	a5, a4, 0
.LBE21:
.LBE22:
	.loc 1 353 0
	add.n	a8, a2, a8
	.loc 1 356 0
	l32i.n	a9, a3, 0
	.loc 1 353 0
	l32i.n	a6, a8, 0
	l32r	a4, .LC45
	.loc 1 356 0
	movi	a5, 0x100
	and	a5, a9, a5
	.loc 1 353 0
	and	a7, a6, a4
.LVL85:
	.loc 1 359 0
	beqz.n	a5, .L71
	.loc 1 359 0 is_stmt 0 discriminator 1
	l8ui	a5, a3, 4
	l32r	a4, .LC46
	extui	a5, a5, 0, 7
	slli	a5, a5, 24
	or	a5, a5, a4
.L71:
	.loc 1 362 0 is_stmt 1
	movi.n	a4, 0
	.loc 1 355 0
	or	a6, a5, a7
.LVL86:
	.loc 1 362 0
	bbc	a9, a4, .L72
	.loc 1 362 0 is_stmt 0 discriminator 1
	l8ui	a4, a3, 6
	extui	a4, a4, 0, 7
.L72:
	.loc 1 362 0 discriminator 4
	or	a5, a4, a6
.LVL87:
	.loc 1 368 0 is_stmt 1 discriminator 4
	movi.n	a4, 0
	bbci	a9, 1, .L73
	.loc 1 368 0 is_stmt 0 discriminator 1
	l8ui	a4, a3, 5
	extui	a4, a4, 0, 7
	slli	a4, a4, 8
.L73:
	.loc 1 368 0 discriminator 4
	or	a4, a4, a5
.LVL88:
	.loc 1 374 0 is_stmt 1 discriminator 4
	s32i.n	a4, a8, 0
	.loc 1 375 0 discriminator 4
	l32r	a4, .LC47
.LVL89:
	add.n	a2, a2, a4
	l32i.n	a5, a2, 0
	movi	a4, -0x200
	and	a4, a5, a4
	s32i.n	a4, a2, 0
.LVL90:
	.loc 1 376 0 discriminator 4
	l32i.n	a4, a2, 0
	l32i.n	a3, a3, 0
.LVL91:
	or	a3, a4, a3
	s32i.n	a3, a2, 0
	ret.n
.LFE18:
	.size	UART_IntrConfig, .-UART_IntrConfig
	.literal_position
	.literal .LC48, 74880
	.literal .LC49, uart0_write_char
	.literal .LC50, uart0_rx_intr_handler
	.align	4
	.global	uart_init_new
	.type	uart_init_new, @function
uart_init_new:
.LFB20:
	.loc 1 440 0
	addi	sp, sp, -64
.LCFI15:
	.loc 1 441 0
	movi.n	a2, 0
	.loc 1 440 0
	s32i.n	a0, sp, 60
	s32i.n	a12, sp, 56
	s32i.n	a13, sp, 52
.LCFI16:
	.loc 1 441 0
	call0	UART_WaitTxFifoEmpty
.LVL92:
	.loc 1 442 0
	movi.n	a2, 1
	call0	UART_WaitTxFifoEmpty
.LVL93:
	.loc 1 445 0
	l32r	a2, .LC48
	.loc 1 449 0
	movi.n	a12, 0
	.loc 1 445 0
	s32i.n	a2, sp, 0
	.loc 1 446 0
	movi.n	a2, 3
	s32i.n	a2, sp, 4
	.loc 1 448 0
	movi.n	a2, 1
	s32i.n	a2, sp, 12
	.loc 1 450 0
	movi	a2, 0x78
	.loc 1 447 0
	movi.n	a13, 2
	.loc 1 450 0
	s8i	a2, sp, 20
	.loc 1 452 0
	mov.n	a3, sp
	mov.n	a2, a12
	.loc 1 447 0
	s32i.n	a13, sp, 8
	.loc 1 449 0
	s32i.n	a12, sp, 16
	.loc 1 451 0
	s32i.n	a12, sp, 24
	.loc 1 452 0
	call0	UART_ParamConfig
.LVL94:
	.loc 1 455 0
	movi	a2, 0x10b
	s32i.n	a2, sp, 28
	.loc 1 459 0
	movi.n	a2, 0xa
	s8i	a2, sp, 34
	.loc 1 461 0
	movi.n	a2, 0x14
	.loc 1 462 0
	addi	a3, sp, 28
	.loc 1 461 0
	s8i	a2, sp, 33
	.loc 1 462 0
	mov.n	a2, a12
	.loc 1 460 0
	s8i	a13, sp, 32
	.loc 1 462 0
	call0	UART_IntrConfig
.LVL95:
.LBB23:
.LBB24:
	.loc 1 322 0
	l32r	a2, .LC49
	call0	os_install_putc1
.LVL96:
.LBE24:
.LBE23:
	.loc 1 465 0
	l32r	a2, .LC50
	mov.n	a3, a12
	call0	UART_intr_handler_register
.LVL97:
	.loc 1 466 0
	movi.n	a2, 0x20
	call0	_xt_isr_unmask
.LVL98:
	.loc 1 476 0
	l32i.n	a0, sp, 60
	l32i.n	a12, sp, 56
	l32i.n	a13, sp, 52
	addi	sp, sp, 64
	ret.n
.LFE20:
	.size	uart_init_new, .-uart_init_new
	.comm	xQueueUart,4,4
	.comm	xUartTaskHandle,4,4
	.global	fifo_tmp
	.section	.bss
	.type	fifo_tmp, @object
	.size	fifo_tmp, 128
fifo_tmp:
	.zero	128
	.global	buf_idx
	.type	buf_idx, @object
	.size	buf_idx, 1
buf_idx:
	.zero	1
	.global	fifo_len
	.type	fifo_len, @object
	.size	fifo_len, 1
fifo_len:
	.zero	1
	.global	uart_no
	.type	uart_no, @object
	.size	uart_no, 1
uart_no:
	.zero	1
	.comm	RcvChar,1,1
	.section	.debug_frame,"",@progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x3
	.string	""
	.uleb128 0x1
	.sleb128 -4
	.uleb128 0
	.byte	0xc
	.uleb128 0x1
	.uleb128 0
	.align	4
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.align	4
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.byte	0x4
	.4byte	.LCFI0-.LFB19
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0x8c
	.uleb128 0x1
	.byte	0x8d
	.uleb128 0x2
	.byte	0x8e
	.uleb128 0x3
	.byte	0x8f
	.uleb128 0x4
	.align	4
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.byte	0x4
	.4byte	.LCFI2-.LFB1
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI3-.LCFI2
	.byte	0x8c
	.uleb128 0x2
	.byte	0x80
	.uleb128 0x1
	.align	4
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.byte	0x4
	.4byte	.LCFI4-.LFB2
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI5-.LCFI4
	.byte	0x8c
	.uleb128 0x2
	.byte	0x80
	.uleb128 0x1
	.align	4
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.align	4
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.align	4
.LEFDE10:
.LSFDE12:
	.4byte	.LEFDE12-.LASFDE12
.LASFDE12:
	.4byte	.Lframe0
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.align	4
.LEFDE12:
.LSFDE14:
	.4byte	.LEFDE14-.LASFDE14
.LASFDE14:
	.4byte	.Lframe0
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.align	4
.LEFDE14:
.LSFDE16:
	.4byte	.LEFDE16-.LASFDE16
.LASFDE16:
	.4byte	.Lframe0
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.byte	0x4
	.4byte	.LCFI6-.LFB9
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI7-.LCFI6
	.byte	0x8c
	.uleb128 0x2
	.byte	0x4
	.4byte	.LCFI8-.LCFI7
	.byte	0x80
	.uleb128 0x1
	.align	4
.LEFDE16:
.LSFDE18:
	.4byte	.LEFDE18-.LASFDE18
.LASFDE18:
	.4byte	.Lframe0
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.align	4
.LEFDE18:
.LSFDE20:
	.4byte	.LEFDE20-.LASFDE20
.LASFDE20:
	.4byte	.Lframe0
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.align	4
.LEFDE20:
.LSFDE22:
	.4byte	.LEFDE22-.LASFDE22
.LASFDE22:
	.4byte	.Lframe0
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.align	4
.LEFDE22:
.LSFDE24:
	.4byte	.LEFDE24-.LASFDE24
.LASFDE24:
	.4byte	.Lframe0
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.align	4
.LEFDE24:
.LSFDE26:
	.4byte	.LEFDE26-.LASFDE26
.LASFDE26:
	.4byte	.Lframe0
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.align	4
.LEFDE26:
.LSFDE28:
	.4byte	.LEFDE28-.LASFDE28
.LASFDE28:
	.4byte	.Lframe0
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.byte	0x4
	.4byte	.LCFI9-.LFB15
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI10-.LCFI9
	.byte	0x80
	.uleb128 0x1
	.align	4
.LEFDE28:
.LSFDE30:
	.4byte	.LEFDE30-.LASFDE30
.LASFDE30:
	.4byte	.Lframe0
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.byte	0x4
	.4byte	.LCFI11-.LFB16
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI12-.LCFI11
	.byte	0x80
	.uleb128 0x1
	.align	4
.LEFDE30:
.LSFDE32:
	.4byte	.LEFDE32-.LASFDE32
.LASFDE32:
	.4byte	.Lframe0
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.byte	0x4
	.4byte	.LCFI13-.LFB17
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI14-.LCFI13
	.byte	0x8c
	.uleb128 0x2
	.byte	0x8d
	.uleb128 0x3
	.byte	0x80
	.uleb128 0x1
	.align	4
.LEFDE32:
.LSFDE34:
	.4byte	.LEFDE34-.LASFDE34
.LASFDE34:
	.4byte	.Lframe0
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.align	4
.LEFDE34:
.LSFDE36:
	.4byte	.LEFDE36-.LASFDE36
.LASFDE36:
	.4byte	.Lframe0
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.byte	0x4
	.4byte	.LCFI15-.LFB20
	.byte	0xe
	.uleb128 0x40
	.byte	0x4
	.4byte	.LCFI16-.LCFI15
	.byte	0x80
	.uleb128 0x1
	.byte	0x8c
	.uleb128 0x2
	.byte	0x8d
	.uleb128 0x3
	.align	4
.LEFDE36:
	.text
.Letext0:
	.file 2 "c:\\espressif\\xtensa-lx106-elf\\xtensa-lx106-elf\\include\\stdint.h"
	.file 3 "c:/Espressif/ESP8266_RTOS_SDK/include/espressif/c_types.h"
	.file 4 "c:/Espressif/ESP8266_RTOS_SDK/include/freertos/portmacro.h"
	.file 5 "c:/Espressif/ESP8266_RTOS_SDK/include/freertos/task.h"
	.file 6 "c:/Espressif/ESP8266_RTOS_SDK/include/freertos/queue.h"
	.file 7 "user/../include/UART.h"
	.file 8 "c:/Espressif/ESP8266_RTOS_SDK/include/espressif/esp_misc.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xaa9
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF126
	.byte	0x1
	.4byte	.LASF127
	.4byte	.LASF128
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x3
	.4byte	.LASF4
	.byte	0x2
	.byte	0x2a
	.4byte	0x37
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF3
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.4byte	.LASF5
	.byte	0x2
	.byte	0x51
	.4byte	0x5e
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x3
	.4byte	.LASF9
	.byte	0x3
	.byte	0x2b
	.4byte	0x2c
	.uleb128 0x3
	.4byte	.LASF10
	.byte	0x3
	.byte	0x34
	.4byte	0x53
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.4byte	.LASF11
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF12
	.uleb128 0x5
	.byte	0x4
	.4byte	0x5e
	.byte	0x3
	.byte	0x49
	.4byte	0xc1
	.uleb128 0x6
	.string	"OK"
	.byte	0
	.uleb128 0x7
	.4byte	.LASF13
	.byte	0x1
	.uleb128 0x7
	.4byte	.LASF14
	.byte	0x2
	.uleb128 0x7
	.4byte	.LASF15
	.byte	0x3
	.uleb128 0x7
	.4byte	.LASF16
	.byte	0x4
	.byte	0
	.uleb128 0x3
	.4byte	.LASF17
	.byte	0x3
	.byte	0x4f
	.4byte	0x97
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF18
	.uleb128 0x8
	.byte	0x4
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF19
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF20
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF21
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF22
	.uleb128 0x9
	.4byte	0xfc
	.uleb128 0xa
	.4byte	0xd3
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0xf1
	.uleb128 0x3
	.4byte	.LASF23
	.byte	0x4
	.byte	0xb8
	.4byte	0xfc
	.uleb128 0x3
	.4byte	.LASF24
	.byte	0x5
	.byte	0x5f
	.4byte	0xd3
	.uleb128 0x3
	.4byte	.LASF25
	.byte	0x6
	.byte	0x53
	.4byte	0xd3
	.uleb128 0x5
	.byte	0x4
	.4byte	0x5e
	.byte	0x7
	.byte	0x27
	.4byte	0x148
	.uleb128 0x7
	.4byte	.LASF26
	.byte	0
	.uleb128 0x7
	.4byte	.LASF27
	.byte	0x1
	.uleb128 0x7
	.4byte	.LASF28
	.byte	0x2
	.uleb128 0x7
	.4byte	.LASF29
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF30
	.byte	0x7
	.byte	0x2c
	.4byte	0x123
	.uleb128 0x5
	.byte	0x4
	.4byte	0x5e
	.byte	0x7
	.byte	0x2f
	.4byte	0x172
	.uleb128 0x7
	.4byte	.LASF31
	.byte	0x1
	.uleb128 0x7
	.4byte	.LASF32
	.byte	0x2
	.uleb128 0x7
	.4byte	.LASF33
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF34
	.byte	0x7
	.byte	0x33
	.4byte	0x153
	.uleb128 0x5
	.byte	0x4
	.4byte	0x5e
	.byte	0x7
	.byte	0x36
	.4byte	0x196
	.uleb128 0x7
	.4byte	.LASF35
	.byte	0
	.uleb128 0x7
	.4byte	.LASF36
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF37
	.byte	0x7
	.byte	0x39
	.4byte	0x17d
	.uleb128 0x5
	.byte	0x4
	.4byte	0x5e
	.byte	0x7
	.byte	0x3c
	.4byte	0x1c0
	.uleb128 0x7
	.4byte	.LASF38
	.byte	0x2
	.uleb128 0x7
	.4byte	.LASF39
	.byte	0
	.uleb128 0x7
	.4byte	.LASF40
	.byte	0x1
	.byte	0
	.uleb128 0x3
	.4byte	.LASF41
	.byte	0x7
	.byte	0x40
	.4byte	0x1a1
	.uleb128 0x5
	.byte	0x4
	.4byte	0x5e
	.byte	0x7
	.byte	0x49
	.4byte	0x256
	.uleb128 0xc
	.4byte	.LASF42
	.2byte	0x12c
	.uleb128 0xc
	.4byte	.LASF43
	.2byte	0x258
	.uleb128 0xc
	.4byte	.LASF44
	.2byte	0x4b0
	.uleb128 0xc
	.4byte	.LASF45
	.2byte	0x960
	.uleb128 0xc
	.4byte	.LASF46
	.2byte	0x12c0
	.uleb128 0xc
	.4byte	.LASF47
	.2byte	0x2580
	.uleb128 0xc
	.4byte	.LASF48
	.2byte	0x4b00
	.uleb128 0xc
	.4byte	.LASF49
	.2byte	0x9600
	.uleb128 0xc
	.4byte	.LASF50
	.2byte	0xe100
	.uleb128 0xd
	.4byte	.LASF51
	.4byte	0x12480
	.uleb128 0xd
	.4byte	.LASF52
	.4byte	0x1c200
	.uleb128 0xd
	.4byte	.LASF53
	.4byte	0x38400
	.uleb128 0xd
	.4byte	.LASF54
	.4byte	0x70800
	.uleb128 0xd
	.4byte	.LASF55
	.4byte	0xe1000
	.uleb128 0xd
	.4byte	.LASF56
	.4byte	0x1c2000
	.uleb128 0xd
	.4byte	.LASF57
	.4byte	0x384000
	.byte	0
	.uleb128 0x3
	.4byte	.LASF58
	.byte	0x7
	.byte	0x5a
	.4byte	0x1cb
	.uleb128 0x5
	.byte	0x4
	.4byte	0x5e
	.byte	0x7
	.byte	0x5d
	.4byte	0x286
	.uleb128 0x7
	.4byte	.LASF59
	.byte	0
	.uleb128 0x7
	.4byte	.LASF60
	.byte	0x1
	.uleb128 0x7
	.4byte	.LASF61
	.byte	0x2
	.uleb128 0x7
	.4byte	.LASF62
	.byte	0x3
	.byte	0
	.uleb128 0x3
	.4byte	.LASF63
	.byte	0x7
	.byte	0x62
	.4byte	0x261
	.uleb128 0x5
	.byte	0x4
	.4byte	0x5e
	.byte	0x7
	.byte	0x65
	.4byte	0x2c8
	.uleb128 0x7
	.4byte	.LASF64
	.byte	0
	.uleb128 0xd
	.4byte	.LASF65
	.4byte	0x80000
	.uleb128 0xd
	.4byte	.LASF66
	.4byte	0x100000
	.uleb128 0xd
	.4byte	.LASF67
	.4byte	0x400000
	.uleb128 0xd
	.4byte	.LASF68
	.4byte	0x800000
	.byte	0
	.uleb128 0x3
	.4byte	.LASF69
	.byte	0x7
	.byte	0x6b
	.4byte	0x291
	.uleb128 0xe
	.byte	0x1c
	.byte	0x7
	.byte	0x6d
	.4byte	0x330
	.uleb128 0xf
	.4byte	.LASF70
	.byte	0x7
	.byte	0x6f
	.4byte	0x256
	.byte	0
	.uleb128 0xf
	.4byte	.LASF71
	.byte	0x7
	.byte	0x70
	.4byte	0x148
	.byte	0x4
	.uleb128 0xf
	.4byte	.LASF72
	.byte	0x7
	.byte	0x71
	.4byte	0x1c0
	.byte	0x8
	.uleb128 0xf
	.4byte	.LASF73
	.byte	0x7
	.byte	0x72
	.4byte	0x172
	.byte	0xc
	.uleb128 0xf
	.4byte	.LASF74
	.byte	0x7
	.byte	0x73
	.4byte	0x286
	.byte	0x10
	.uleb128 0xf
	.4byte	.LASF75
	.byte	0x7
	.byte	0x74
	.4byte	0x73
	.byte	0x14
	.uleb128 0xf
	.4byte	.LASF76
	.byte	0x7
	.byte	0x75
	.4byte	0x7e
	.byte	0x18
	.byte	0
	.uleb128 0x3
	.4byte	.LASF77
	.byte	0x7
	.byte	0x76
	.4byte	0x2d3
	.uleb128 0xe
	.byte	0x8
	.byte	0x7
	.byte	0x78
	.4byte	0x374
	.uleb128 0xf
	.4byte	.LASF78
	.byte	0x7
	.byte	0x7a
	.4byte	0x7e
	.byte	0
	.uleb128 0xf
	.4byte	.LASF79
	.byte	0x7
	.byte	0x7b
	.4byte	0x73
	.byte	0x4
	.uleb128 0xf
	.4byte	.LASF80
	.byte	0x7
	.byte	0x7c
	.4byte	0x73
	.byte	0x5
	.uleb128 0xf
	.4byte	.LASF81
	.byte	0x7
	.byte	0x7d
	.4byte	0x73
	.byte	0x6
	.byte	0
	.uleb128 0x3
	.4byte	.LASF82
	.byte	0x7
	.byte	0x7e
	.4byte	0x33b
	.uleb128 0x10
	.4byte	.LASF83
	.byte	0x1
	.byte	0x46
	.byte	0x1
	.4byte	0x395
	.uleb128 0x11
	.string	"c"
	.byte	0x1
	.byte	0x46
	.4byte	0xe3
	.byte	0
	.uleb128 0x10
	.4byte	.LASF84
	.byte	0x1
	.byte	0x56
	.byte	0x1
	.4byte	0x3ab
	.uleb128 0x11
	.string	"c"
	.byte	0x1
	.byte	0x56
	.4byte	0xe3
	.byte	0
	.uleb128 0x12
	.4byte	.LASF87
	.byte	0x1
	.2byte	0x107
	.byte	0x1
	.4byte	0x3dd
	.uleb128 0x13
	.4byte	.LASF85
	.byte	0x1
	.2byte	0x107
	.4byte	0x196
	.uleb128 0x13
	.4byte	.LASF74
	.byte	0x1
	.2byte	0x107
	.4byte	0x286
	.uleb128 0x13
	.4byte	.LASF86
	.byte	0x1
	.2byte	0x107
	.4byte	0x73
	.byte	0
	.uleb128 0x12
	.4byte	.LASF88
	.byte	0x1
	.2byte	0x12b
	.byte	0x1
	.4byte	0x403
	.uleb128 0x13
	.4byte	.LASF85
	.byte	0x1
	.2byte	0x12b
	.4byte	0x196
	.uleb128 0x13
	.4byte	.LASF89
	.byte	0x1
	.2byte	0x12b
	.4byte	0x7e
	.byte	0
	.uleb128 0x12
	.4byte	.LASF90
	.byte	0x1
	.2byte	0x13a
	.byte	0x1
	.4byte	0x41d
	.uleb128 0x13
	.4byte	.LASF85
	.byte	0x1
	.2byte	0x13a
	.4byte	0x196
	.byte	0
	.uleb128 0x14
	.4byte	.LASF129
	.byte	0x1
	.byte	0x36
	.4byte	0xc1
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x46c
	.uleb128 0x15
	.4byte	.LASF91
	.byte	0x1
	.byte	0x36
	.4byte	0x73
	.4byte	.LLST0
	.uleb128 0x16
	.4byte	.LASF92
	.byte	0x1
	.byte	0x36
	.4byte	0x73
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x17
	.4byte	.LBB6
	.4byte	.LBE6-.LBB6
	.uleb128 0x18
	.4byte	.LASF94
	.byte	0x1
	.byte	0x3a
	.4byte	0x7e
	.4byte	.LLST1
	.byte	0
	.byte	0
	.uleb128 0x19
	.4byte	.LASF130
	.byte	0x1
	.2byte	0x17b
	.4byte	.LFB19
	.4byte	.LFE19-.LFB19
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x4a3
	.uleb128 0x1a
	.4byte	.LASF93
	.byte	0x1
	.2byte	0x17b
	.4byte	0xd3
	.4byte	.LLST2
	.uleb128 0x1b
	.4byte	.LASF95
	.byte	0x1
	.2byte	0x181
	.4byte	0x7e
	.4byte	.LLST3
	.byte	0
	.uleb128 0x1c
	.4byte	0x37f
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x500
	.uleb128 0x1d
	.4byte	0x38b
	.4byte	.LLST4
	.uleb128 0x1e
	.4byte	.LBB9
	.4byte	.LBE9-.LBB9
	.4byte	0x4ea
	.uleb128 0x1d
	.4byte	0x38b
	.4byte	.LLST5
	.uleb128 0x1f
	.4byte	.LVL16
	.4byte	0x41d
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3d
	.byte	0
	.byte	0
	.uleb128 0x1f
	.4byte	.LVL19
	.4byte	0x41d
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x1c
	.4byte	0x395
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x55d
	.uleb128 0x1d
	.4byte	0x3a1
	.4byte	.LLST6
	.uleb128 0x1e
	.4byte	.LBB13
	.4byte	.LBE13-.LBB13
	.4byte	0x547
	.uleb128 0x1d
	.4byte	0x3a1
	.4byte	.LLST7
	.uleb128 0x1f
	.4byte	.LVL24
	.4byte	0x41d
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3d
	.byte	0
	.byte	0
	.uleb128 0x1f
	.4byte	.LVL27
	.4byte	0x41d
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x21
	.4byte	.LASF96
	.byte	0x1
	.byte	0xe4
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x591
	.uleb128 0x15
	.4byte	.LASF85
	.byte	0x1
	.byte	0xe4
	.4byte	0x196
	.4byte	.LLST8
	.uleb128 0x22
	.string	"len"
	.byte	0x1
	.byte	0xe4
	.4byte	0x148
	.4byte	.LLST9
	.byte	0
	.uleb128 0x21
	.4byte	.LASF97
	.byte	0x1
	.byte	0xe9
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x5c5
	.uleb128 0x15
	.4byte	.LASF85
	.byte	0x1
	.byte	0xe9
	.4byte	0x196
	.4byte	.LLST10
	.uleb128 0x15
	.4byte	.LASF98
	.byte	0x1
	.byte	0xe9
	.4byte	0x172
	.4byte	.LLST11
	.byte	0
	.uleb128 0x21
	.4byte	.LASF99
	.byte	0x1
	.byte	0xee
	.4byte	.LFB7
	.4byte	.LFE7-.LFB7
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x5f9
	.uleb128 0x15
	.4byte	.LASF85
	.byte	0x1
	.byte	0xee
	.4byte	0x196
	.4byte	.LLST12
	.uleb128 0x15
	.4byte	.LASF100
	.byte	0x1
	.byte	0xee
	.4byte	0x2c8
	.4byte	.LLST13
	.byte	0
	.uleb128 0x21
	.4byte	.LASF101
	.byte	0x1
	.byte	0xf4
	.4byte	.LFB8
	.4byte	.LFE8-.LFB8
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x62d
	.uleb128 0x15
	.4byte	.LASF85
	.byte	0x1
	.byte	0xf4
	.4byte	0x196
	.4byte	.LLST14
	.uleb128 0x15
	.4byte	.LASF102
	.byte	0x1
	.byte	0xf4
	.4byte	0x1c0
	.4byte	.LLST15
	.byte	0
	.uleb128 0x23
	.4byte	.LASF103
	.byte	0x1
	.2byte	0x101
	.4byte	.LFB9
	.4byte	.LFE9-.LFB9
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x686
	.uleb128 0x1a
	.4byte	.LASF85
	.byte	0x1
	.2byte	0x101
	.4byte	0x196
	.4byte	.LLST16
	.uleb128 0x1a
	.4byte	.LASF70
	.byte	0x1
	.2byte	0x101
	.4byte	0x7e
	.4byte	.LLST17
	.uleb128 0x24
	.4byte	.LASF104
	.byte	0x1
	.2byte	0x103
	.4byte	0x4c
	.4byte	0x675
	.uleb128 0x25
	.byte	0
	.uleb128 0x1f
	.4byte	.LVL44
	.4byte	0xa50
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x1c
	.4byte	0x3ab
	.4byte	.LFB10
	.4byte	.LFE10-.LFB10
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x6da
	.uleb128 0x1d
	.4byte	0x3b8
	.4byte	.LLST18
	.uleb128 0x1d
	.4byte	0x3c4
	.4byte	.LLST19
	.uleb128 0x1d
	.4byte	0x3d0
	.4byte	.LLST20
	.uleb128 0x17
	.4byte	.LBB17
	.4byte	.LBE17-.LBB17
	.uleb128 0x1d
	.4byte	0x3c4
	.4byte	.LLST21
	.uleb128 0x1d
	.4byte	0x3d0
	.4byte	.LLST22
	.uleb128 0x1d
	.4byte	0x3b8
	.4byte	.LLST23
	.byte	0
	.byte	0
	.uleb128 0x26
	.4byte	.LASF105
	.byte	0x1
	.2byte	0x11f
	.4byte	.LFB11
	.4byte	.LFE11-.LFB11
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x701
	.uleb128 0x1a
	.4byte	.LASF85
	.byte	0x1
	.2byte	0x11f
	.4byte	0x196
	.4byte	.LLST24
	.byte	0
	.uleb128 0x26
	.4byte	.LASF106
	.byte	0x1
	.2byte	0x125
	.4byte	.LFB12
	.4byte	.LFE12-.LFB12
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x728
	.uleb128 0x1a
	.4byte	.LASF85
	.byte	0x1
	.2byte	0x125
	.4byte	0x196
	.4byte	.LLST25
	.byte	0
	.uleb128 0x1c
	.4byte	0x3dd
	.4byte	.LFB13
	.4byte	.LFE13-.LFB13
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x74c
	.uleb128 0x1d
	.4byte	0x3ea
	.4byte	.LLST26
	.uleb128 0x27
	.4byte	0x3f6
	.uleb128 0x1
	.byte	0x53
	.byte	0
	.uleb128 0x26
	.4byte	.LASF107
	.byte	0x1
	.2byte	0x130
	.4byte	.LFB14
	.4byte	.LFE14-.LFB14
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x783
	.uleb128 0x1a
	.4byte	.LASF85
	.byte	0x1
	.2byte	0x130
	.4byte	0x196
	.4byte	.LLST27
	.uleb128 0x1a
	.4byte	.LASF108
	.byte	0x1
	.2byte	0x130
	.4byte	0x7e
	.4byte	.LLST28
	.byte	0
	.uleb128 0x26
	.4byte	.LASF109
	.byte	0x1
	.2byte	0x135
	.4byte	.LFB15
	.4byte	.LFE15-.LFB15
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x7d6
	.uleb128 0x28
	.string	"fn"
	.byte	0x1
	.2byte	0x135
	.4byte	0xd3
	.4byte	.LLST29
	.uleb128 0x28
	.string	"arg"
	.byte	0x1
	.2byte	0x135
	.4byte	0xd3
	.4byte	.LLST30
	.uleb128 0x1f
	.4byte	.LVL66
	.4byte	0xa62
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x35
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0
	.byte	0
	.uleb128 0x1c
	.4byte	0x403
	.4byte	.LFB16
	.4byte	.LFE16-.LFB16
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x7fc
	.uleb128 0x1d
	.4byte	0x410
	.4byte	.LLST31
	.uleb128 0x29
	.4byte	.LVL71
	.4byte	0xa7d
	.byte	0
	.uleb128 0x26
	.4byte	.LASF110
	.byte	0x1
	.2byte	0x146
	.4byte	.LFB17
	.4byte	.LFE17-.LFB17
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x86b
	.uleb128 0x1a
	.4byte	.LASF85
	.byte	0x1
	.2byte	0x146
	.4byte	0x196
	.4byte	.LLST32
	.uleb128 0x1a
	.4byte	.LASF111
	.byte	0x1
	.2byte	0x146
	.4byte	0x86b
	.4byte	.LLST33
	.uleb128 0x2a
	.4byte	.LVL78
	.4byte	0x3ab
	.4byte	0x846
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.byte	0
	.uleb128 0x2a
	.4byte	.LVL79
	.4byte	0x62d
	.4byte	0x85a
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.byte	0
	.uleb128 0x1f
	.4byte	.LVL80
	.4byte	0x701
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x330
	.uleb128 0x26
	.4byte	.LASF112
	.byte	0x1
	.2byte	0x15c
	.4byte	.LFB18
	.4byte	.LFE18-.LFB18
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x8d9
	.uleb128 0x1a
	.4byte	.LASF85
	.byte	0x1
	.2byte	0x15c
	.4byte	0x196
	.4byte	.LLST34
	.uleb128 0x1a
	.4byte	.LASF113
	.byte	0x1
	.2byte	0x15c
	.4byte	0x8d9
	.4byte	.LLST35
	.uleb128 0x1b
	.4byte	.LASF114
	.byte	0x1
	.2byte	0x15f
	.4byte	0x7e
	.4byte	.LLST36
	.uleb128 0x2b
	.4byte	0x3dd
	.4byte	.LBB19
	.4byte	.Ldebug_ranges0+0
	.byte	0x1
	.2byte	0x160
	.uleb128 0x2c
	.4byte	0x3f6
	.2byte	0x1ff
	.uleb128 0x1d
	.4byte	0x3ea
	.4byte	.LLST37
	.byte	0
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0x374
	.uleb128 0x26
	.4byte	.LASF115
	.byte	0x1
	.2byte	0x1b7
	.4byte	.LFB20
	.4byte	.LFE20-.LFB20
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x9c9
	.uleb128 0x2d
	.4byte	.LASF116
	.byte	0x1
	.2byte	0x1bc
	.4byte	0x330
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x2d
	.4byte	.LASF117
	.byte	0x1
	.2byte	0x1c6
	.4byte	0x374
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x2e
	.4byte	0x403
	.4byte	.LBB23
	.4byte	.LBE23-.LBB23
	.byte	0x1
	.2byte	0x1d0
	.4byte	0x941
	.uleb128 0x2f
	.4byte	0x410
	.byte	0
	.uleb128 0x1f
	.4byte	.LVL96
	.4byte	0xa7d
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	uart0_write_char
	.byte	0
	.byte	0
	.uleb128 0x2a
	.4byte	.LVL92
	.4byte	0x6da
	.4byte	0x954
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.uleb128 0x2a
	.4byte	.LVL93
	.4byte	0x6da
	.4byte	0x967
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x31
	.byte	0
	.uleb128 0x2a
	.4byte	.LVL94
	.4byte	0x7fc
	.4byte	0x981
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.byte	0
	.uleb128 0x2a
	.4byte	.LVL95
	.4byte	0x871
	.4byte	0x99b
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x91
	.sleb128 -36
	.byte	0
	.uleb128 0x2a
	.4byte	.LVL97
	.4byte	0x783
	.4byte	0x9b8
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	uart0_rx_intr_handler
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.byte	0
	.uleb128 0x1f
	.4byte	.LVL98
	.4byte	0xa9f
	.uleb128 0x20
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x8
	.byte	0x20
	.byte	0
	.byte	0
	.uleb128 0x30
	.4byte	.LASF118
	.byte	0x1
	.byte	0x2d
	.4byte	0x73
	.uleb128 0x5
	.byte	0x3
	.4byte	RcvChar
	.uleb128 0x30
	.4byte	.LASF85
	.byte	0x1
	.byte	0x2e
	.4byte	0x73
	.uleb128 0x5
	.byte	0x3
	.4byte	uart_no
	.uleb128 0x30
	.4byte	.LASF119
	.byte	0x1
	.byte	0x2f
	.4byte	0x73
	.uleb128 0x5
	.byte	0x3
	.4byte	fifo_len
	.uleb128 0x30
	.4byte	.LASF120
	.byte	0x1
	.byte	0x30
	.4byte	0x73
	.uleb128 0x5
	.byte	0x3
	.4byte	buf_idx
	.uleb128 0x31
	.4byte	0x73
	.4byte	0xa1d
	.uleb128 0x32
	.4byte	0xdc
	.byte	0x7f
	.byte	0
	.uleb128 0x30
	.4byte	.LASF121
	.byte	0x1
	.byte	0x31
	.4byte	0xa0d
	.uleb128 0x5
	.byte	0x3
	.4byte	fifo_tmp
	.uleb128 0x30
	.4byte	.LASF122
	.byte	0x1
	.byte	0x33
	.4byte	0x10d
	.uleb128 0x5
	.byte	0x3
	.4byte	xUartTaskHandle
	.uleb128 0x30
	.4byte	.LASF123
	.byte	0x1
	.byte	0x34
	.4byte	0x118
	.uleb128 0x5
	.byte	0x3
	.4byte	xQueueUart
	.uleb128 0x24
	.4byte	.LASF104
	.byte	0x1
	.2byte	0x103
	.4byte	0x4c
	.4byte	0xa62
	.uleb128 0x25
	.byte	0
	.uleb128 0x33
	.4byte	.LASF124
	.byte	0x4
	.byte	0xba
	.4byte	0xa7d
	.uleb128 0xa
	.4byte	0x73
	.uleb128 0xa
	.4byte	0x102
	.uleb128 0xa
	.4byte	0xd3
	.byte	0
	.uleb128 0x33
	.4byte	.LASF125
	.byte	0x8
	.byte	0x48
	.4byte	0xa8e
	.uleb128 0xa
	.4byte	0xa8e
	.byte	0
	.uleb128 0xb
	.byte	0x4
	.4byte	0xa94
	.uleb128 0x9
	.4byte	0xa9f
	.uleb128 0xa
	.4byte	0xe3
	.byte	0
	.uleb128 0x34
	.4byte	.LASF131
	.byte	0x4
	.byte	0xb2
	.uleb128 0xa
	.4byte	0x7e
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LVL0-.Ltext0
	.4byte	.LVL1-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL1-.Ltext0
	.4byte	.LFE0-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL2-.Ltext0
	.4byte	.LVL3-.Ltext0
	.2byte	0x8
	.byte	0x74
	.sleb128 0
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL4-.Ltext0
	.4byte	.LVL5-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL5-.Ltext0
	.4byte	.LFE19-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LVL6-.Ltext0
	.4byte	.LVL7-.Ltext0
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL8-.Ltext0
	.4byte	.LVL9-.Ltext0
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL10-.Ltext0
	.4byte	.LVL11-.Ltext0
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL12-.Ltext0
	.4byte	.LFE19-.Ltext0
	.2byte	0x1
	.byte	0x56
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LVL13-.Ltext0
	.4byte	.LVL15-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL15-.Ltext0
	.4byte	.LVL17-.Ltext0
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL17-.Ltext0
	.4byte	.LVL18-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL18-.Ltext0
	.4byte	.LVL20-.Ltext0
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL20-.Ltext0
	.4byte	.LFE1-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST5:
	.4byte	.LVL14-.Ltext0
	.4byte	.LVL17-.Ltext0
	.2byte	0x2
	.byte	0x3a
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST6:
	.4byte	.LVL21-.Ltext0
	.4byte	.LVL23-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL23-.Ltext0
	.4byte	.LVL25-.Ltext0
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL25-.Ltext0
	.4byte	.LVL26-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL26-.Ltext0
	.4byte	.LVL28-.Ltext0
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL28-.Ltext0
	.4byte	.LFE2-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST7:
	.4byte	.LVL22-.Ltext0
	.4byte	.LVL25-.Ltext0
	.2byte	0x2
	.byte	0x3a
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST8:
	.4byte	.LVL29-.Ltext0
	.4byte	.LVL30-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL30-.Ltext0
	.4byte	.LFE5-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST9:
	.4byte	.LVL29-.Ltext0
	.4byte	.LVL31-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL31-.Ltext0
	.4byte	.LFE5-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST10:
	.4byte	.LVL32-.Ltext0
	.4byte	.LVL33-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL33-.Ltext0
	.4byte	.LFE6-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST11:
	.4byte	.LVL32-.Ltext0
	.4byte	.LVL34-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL34-.Ltext0
	.4byte	.LFE6-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST12:
	.4byte	.LVL35-.Ltext0
	.4byte	.LVL36-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL36-.Ltext0
	.4byte	.LFE7-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST13:
	.4byte	.LVL35-.Ltext0
	.4byte	.LVL37-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL37-.Ltext0
	.4byte	.LFE7-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST14:
	.4byte	.LVL38-.Ltext0
	.4byte	.LVL39-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL39-.Ltext0
	.4byte	.LFE8-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST15:
	.4byte	.LVL38-.Ltext0
	.4byte	.LVL40-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL40-.Ltext0
	.4byte	.LFE8-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST16:
	.4byte	.LVL41-.Ltext0
	.4byte	.LVL42-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL42-.Ltext0
	.4byte	.LVL45-.Ltext0
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL45-.Ltext0
	.4byte	.LFE9-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST17:
	.4byte	.LVL41-.Ltext0
	.4byte	.LVL43-1-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL43-1-.Ltext0
	.4byte	.LFE9-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST18:
	.4byte	.LVL46-.Ltext0
	.4byte	.LVL50-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL50-.Ltext0
	.4byte	.LVL51-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	.LVL51-.Ltext0
	.4byte	.LVL52-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL52-.Ltext0
	.4byte	.LFE10-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST19:
	.4byte	.LVL46-.Ltext0
	.4byte	.LVL49-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL49-.Ltext0
	.4byte	.LVL51-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	.LVL51-.Ltext0
	.4byte	.LVL53-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL53-.Ltext0
	.4byte	.LFE10-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST20:
	.4byte	.LVL46-.Ltext0
	.4byte	.LVL47-.Ltext0
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL47-.Ltext0
	.4byte	.LFE10-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x54
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST21:
	.4byte	.LVL48-.Ltext0
	.4byte	.LVL49-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL49-.Ltext0
	.4byte	.LVL51-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST22:
	.4byte	.LVL48-.Ltext0
	.4byte	.LVL51-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x54
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST23:
	.4byte	.LVL48-.Ltext0
	.4byte	.LVL50-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL50-.Ltext0
	.4byte	.LVL51-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST24:
	.4byte	.LVL54-.Ltext0
	.4byte	.LVL55-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL55-.Ltext0
	.4byte	.LFE11-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST25:
	.4byte	.LVL56-.Ltext0
	.4byte	.LVL57-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL57-.Ltext0
	.4byte	.LFE12-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST26:
	.4byte	.LVL58-.Ltext0
	.4byte	.LVL59-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL59-.Ltext0
	.4byte	.LFE13-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST27:
	.4byte	.LVL60-.Ltext0
	.4byte	.LVL61-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL61-.Ltext0
	.4byte	.LFE14-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST28:
	.4byte	.LVL60-.Ltext0
	.4byte	.LVL62-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL62-.Ltext0
	.4byte	.LFE14-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST29:
	.4byte	.LVL63-.Ltext0
	.4byte	.LVL65-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL65-.Ltext0
	.4byte	.LVL66-1-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL66-1-.Ltext0
	.4byte	.LFE15-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST30:
	.4byte	.LVL63-.Ltext0
	.4byte	.LVL64-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL64-.Ltext0
	.4byte	.LVL66-1-.Ltext0
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL66-1-.Ltext0
	.4byte	.LFE15-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST31:
	.4byte	.LVL67-.Ltext0
	.4byte	.LVL68-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL68-.Ltext0
	.4byte	.LVL69-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	.LVL69-.Ltext0
	.4byte	.LVL70-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL70-.Ltext0
	.4byte	.LFE16-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST32:
	.4byte	.LVL72-.Ltext0
	.4byte	.LVL73-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL73-.Ltext0
	.4byte	.LVL75-.Ltext0
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL75-.Ltext0
	.4byte	.LVL76-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL76-.Ltext0
	.4byte	.LVL82-.Ltext0
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL82-.Ltext0
	.4byte	.LFE17-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST33:
	.4byte	.LVL72-.Ltext0
	.4byte	.LVL74-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL74-.Ltext0
	.4byte	.LVL75-.Ltext0
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL75-.Ltext0
	.4byte	.LVL77-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL77-.Ltext0
	.4byte	.LVL81-.Ltext0
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL81-.Ltext0
	.4byte	.LFE17-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST34:
	.4byte	.LVL83-.Ltext0
	.4byte	.LVL84-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL84-.Ltext0
	.4byte	.LFE18-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST35:
	.4byte	.LVL83-.Ltext0
	.4byte	.LVL91-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL91-.Ltext0
	.4byte	.LFE18-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST36:
	.4byte	.LVL83-.Ltext0
	.4byte	.LVL85-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL85-.Ltext0
	.4byte	.LVL86-.Ltext0
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL86-.Ltext0
	.4byte	.LVL87-.Ltext0
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL87-.Ltext0
	.4byte	.LVL88-.Ltext0
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL88-.Ltext0
	.4byte	.LVL89-.Ltext0
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL89-.Ltext0
	.4byte	.LVL90-.Ltext0
	.2byte	0x2
	.byte	0x78
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST37:
	.4byte	.LVL83-.Ltext0
	.4byte	.LVL84-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL84-.Ltext0
	.4byte	.LFE18-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x1c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.4byte	.LBB19-.Ltext0
	.4byte	.LBE19-.Ltext0
	.4byte	.LBB22-.Ltext0
	.4byte	.LBE22-.Ltext0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF78:
	.string	"UART_IntrEnMask"
.LASF59:
	.string	"USART_HardwareFlowControl_None"
.LASF98:
	.string	"bit_num"
.LASF35:
	.string	"UART0"
.LASF64:
	.string	"UART_None_Inverse"
.LASF69:
	.string	"UART_LineLevelInverse"
.LASF30:
	.string	"UART_WordLength"
.LASF87:
	.string	"UART_SetFlowCtrl"
.LASF116:
	.string	"uart_config"
.LASF26:
	.string	"UART_WordLength_5b"
.LASF8:
	.string	"long long unsigned int"
.LASF96:
	.string	"UART_SetWordLength"
.LASF119:
	.string	"fifo_len"
.LASF70:
	.string	"baud_rate"
.LASF121:
	.string	"fifo_tmp"
.LASF73:
	.string	"stop_bits"
.LASF41:
	.string	"UART_ParityMode"
.LASF103:
	.string	"UART_SetBaudrate"
.LASF7:
	.string	"long long int"
.LASF0:
	.string	"signed char"
.LASF38:
	.string	"USART_Parity_None"
.LASF24:
	.string	"xTaskHandle"
.LASF106:
	.string	"UART_ResetFifo"
.LASF32:
	.string	"USART_StopBits_1_5"
.LASF75:
	.string	"UART_RxFlowThresh"
.LASF19:
	.string	"long int"
.LASF95:
	.string	"uart_intr_status"
.LASF27:
	.string	"UART_WordLength_6b"
.LASF9:
	.string	"uint8"
.LASF44:
	.string	"BIT_RATE_1200"
.LASF112:
	.string	"UART_IntrConfig"
.LASF12:
	.string	"double"
.LASF99:
	.string	"UART_SetLineInverse"
.LASF10:
	.string	"uint32"
.LASF100:
	.string	"inverse_mask"
.LASF108:
	.string	"ena_mask"
.LASF56:
	.string	"BIT_RATE_1843200"
.LASF91:
	.string	"uart"
.LASF88:
	.string	"UART_ClearIntrStatus"
.LASF66:
	.string	"UART_CTS_Inverse"
.LASF127:
	.string	"user/UART.c"
.LASF65:
	.string	"UART_Rxd_Inverse"
.LASF6:
	.string	"unsigned int"
.LASF61:
	.string	"USART_HardwareFlowControl_CTS"
.LASF28:
	.string	"UART_WordLength_7b"
.LASF18:
	.string	"long unsigned int"
.LASF53:
	.string	"BIT_RATE_230400"
.LASF3:
	.string	"short unsigned int"
.LASF77:
	.string	"UART_ConfigTypeDef"
.LASF43:
	.string	"BIT_RATE_600"
.LASF131:
	.string	"_xt_isr_unmask"
.LASF92:
	.string	"TxChar"
.LASF25:
	.string	"xQueueHandle"
.LASF89:
	.string	"clr_mask"
.LASF129:
	.string	"uart_tx_one_char"
.LASF36:
	.string	"UART1"
.LASF23:
	.string	"_xt_isr"
.LASF29:
	.string	"UART_WordLength_8b"
.LASF90:
	.string	"UART_SetPrintPort"
.LASF72:
	.string	"parity"
.LASF52:
	.string	"BIT_RATE_115200"
.LASF74:
	.string	"flow_ctrl"
.LASF20:
	.string	"sizetype"
.LASF114:
	.string	"reg_val"
.LASF117:
	.string	"uart_intr"
.LASF67:
	.string	"UART_Txd_Inverse"
.LASF37:
	.string	"UART_Port"
.LASF84:
	.string	"uart0_write_char"
.LASF68:
	.string	"UART_RTS_Inverse"
.LASF110:
	.string	"UART_ParamConfig"
.LASF71:
	.string	"data_bits"
.LASF102:
	.string	"Parity_mode"
.LASF120:
	.string	"buf_idx"
.LASF31:
	.string	"USART_StopBits_1"
.LASF33:
	.string	"USART_StopBits_2"
.LASF11:
	.string	"float"
.LASF57:
	.string	"BIT_RATE_3686400"
.LASF63:
	.string	"UART_HwFlowCtrl"
.LASF60:
	.string	"USART_HardwareFlowControl_RTS"
.LASF47:
	.string	"BIT_RATE_9600"
.LASF109:
	.string	"UART_intr_handler_register"
.LASF22:
	.string	"_Bool"
.LASF81:
	.string	"UART_RX_FifoFullIntrThresh"
.LASF1:
	.string	"unsigned char"
.LASF130:
	.string	"uart0_rx_intr_handler"
.LASF111:
	.string	"pUARTConfig"
.LASF48:
	.string	"BIT_RATE_19200"
.LASF49:
	.string	"BIT_RATE_38400"
.LASF50:
	.string	"BIT_RATE_57600"
.LASF107:
	.string	"UART_SetIntrEna"
.LASF128:
	.string	"C:\\\\Users\\\\thebh\\\\Desktop\\\\dtf\\\\git\\\\clay\\\\Firmware\\\\ESP8266\\\\clay_udp_demo_2"
.LASF39:
	.string	"USART_Parity_Even"
.LASF55:
	.string	"BIT_RATE_921600"
.LASF5:
	.string	"uint32_t"
.LASF97:
	.string	"UART_SetStopBits"
.LASF85:
	.string	"uart_no"
.LASF45:
	.string	"BIT_RATE_2400"
.LASF21:
	.string	"char"
.LASF13:
	.string	"FAIL"
.LASF54:
	.string	"BIT_RATE_460800"
.LASF82:
	.string	"UART_IntrConfTypeDef"
.LASF86:
	.string	"rx_thresh"
.LASF76:
	.string	"UART_InverseMask"
.LASF2:
	.string	"short int"
.LASF62:
	.string	"USART_HardwareFlowControl_CTS_RTS"
.LASF104:
	.string	"uart_div_modify"
.LASF40:
	.string	"USART_Parity_Odd"
.LASF113:
	.string	"pUARTIntrConf"
.LASF93:
	.string	"para"
.LASF46:
	.string	"BIT_RATE_4800"
.LASF105:
	.string	"UART_WaitTxFifoEmpty"
.LASF101:
	.string	"UART_SetParity"
.LASF122:
	.string	"xUartTaskHandle"
.LASF79:
	.string	"UART_RX_TimeOutIntrThresh"
.LASF17:
	.string	"STATUS"
.LASF83:
	.string	"uart1_write_char"
.LASF4:
	.string	"uint8_t"
.LASF125:
	.string	"os_install_putc1"
.LASF123:
	.string	"xQueueUart"
.LASF94:
	.string	"fifo_cnt"
.LASF15:
	.string	"BUSY"
.LASF124:
	.string	"_xt_isr_attach"
.LASF58:
	.string	"UART_BautRate"
.LASF80:
	.string	"UART_TX_FifoEmptyIntrThresh"
.LASF42:
	.string	"BIT_RATE_300"
.LASF118:
	.string	"RcvChar"
.LASF115:
	.string	"uart_init_new"
.LASF51:
	.string	"BIT_RATE_74880"
.LASF34:
	.string	"UART_StopBits"
.LASF126:
	.string	"GNU C89 5.1.0 -mlongcalls -mtext-section-literals -mno-serialize-volatile -g -Os -std=gnu90 -fno-inline-functions"
.LASF16:
	.string	"CANCEL"
.LASF14:
	.string	"PENDING"
	.ident	"GCC: (GNU) 5.1.0"
