	.file	"Clay_Message.c"
	.text
.Ltext0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC2:
	.string	"%d,%d,%d,%d"
.LC4:
	.string	",%d"
	.text
	.literal_position
	.literal .LC3, .LC2
	.literal .LC5, .LC4
	.align	4
	.global	FillBufferWithMessage
	.type	FillBufferWithMessage, @function
FillBufferWithMessage:
.LFB0:
	.file 1 "user/Clay_Message.c"
	.loc 1 28 0
.LVL0:
	addi	sp, sp, -64
.LCFI0:
	mov.n	a8, a4
	s32i.n	a13, sp, 52
	.loc 1 39 0
	l32i	a4, a2, 512
.LVL1:
.LCFI1:
	.loc 1 28 0
	mov.n	a13, a3
	s32i.n	a14, sp, 48
	.loc 1 39 0
	mov.n	a3, a2
.LVL2:
.LCFI2:
	.loc 1 28 0
	mov.n	a14, a2
	.loc 1 39 0
	mov.n	a2, a13
.LVL3:
	.loc 1 28 0
	s32i.n	a0, sp, 60
	s32i.n	a12, sp, 56
	.loc 1 39 0
	s32i.n	a8, sp, 16
	.loc 1 28 0
	s32i.n	a15, sp, 44
.LCFI3:
	.loc 1 39 0
	call0	strncpy
.LVL4:
	.loc 1 48 0
	addmi	a2, a14, 0x200
	.loc 1 43 0
	l8ui	a7, a2, 4
	l8ui	a6, a2, 5
	l16ui	a2, a2, 6
	.loc 1 40 0
	l32i	a12, a14, 512
.LVL5:
	.loc 1 43 0
	l32i.n	a8, sp, 16
	s32i.n	a2, sp, 0
	l32i	a5, a14, 520
	l32r	a4, .LC3
	sub	a3, a8, a12
	add.n	a2, a13, a12
	call0	snprintf
.LVL6:
	.loc 1 51 0
	l32i.n	a8, sp, 16
	.loc 1 43 0
	add.n	a12, a2, a12
.LVL7:
	.loc 1 51 0
	addi.n	a2, a8, 8
	bltu	a2, a12, .L2
	movi	a15, 0x20c
	movi	a2, 0x214
	add.n	a15, a14, a15
	add.n	a14, a14, a2
.LVL8:
.L4:
.LBB2:
	.loc 1 56 0
	l8ui	a5, a15, 0
	l32r	a4, .LC5
	sub	a3, a8, a12
	add.n	a2, a13, a12
	s32i.n	a8, sp, 16
	call0	snprintf
.LVL9:
	.loc 1 57 0
	l32i.n	a8, sp, 16
	.loc 1 56 0
	add.n	a12, a12, a2
.LVL10:
	.loc 1 57 0
	bltu	a12, a8, .L3
	.loc 1 59 0
	add.n	a13, a13, a8
.LVL11:
	addi.n	a13, a13, -1
	movi.n	a2, 0xa
	s8i	a2, a13, 0
.LVL12:
	.loc 1 61 0
	mov.n	a12, a8
	j	.L2
.LVL13:
.L3:
	addi.n	a15, a15, 1
.LVL14:
	.loc 1 54 0 discriminator 2
	bne	a14, a15, .L4
.LVL15:
.L2:
.LBE2:
	.loc 1 67 0
	l32i.n	a0, sp, 60
	mov.n	a2, a12
	l32i.n	a13, sp, 52
	l32i.n	a12, sp, 56
.LVL16:
	l32i.n	a14, sp, 48
	l32i.n	a15, sp, 44
	addi	sp, sp, 64
	ret.n
.LFE0:
	.size	FillBufferWithMessage, .-FillBufferWithMessage
	.section	.rodata.str1.1
.LC6:
	.string	"s_addr"
.LC8:
	.string	"%d"
.LC10:
	.string	"family"
.LC12:
	.string	"len"
.LC14:
	.string	"port"
.LC16:
	.string	"%d zero"
	.text
	.literal_position
	.literal .LC7, .LC6
	.literal .LC9, .LC8
	.literal .LC11, .LC10
	.literal .LC13, .LC12
	.literal .LC15, .LC14
	.literal .LC17, .LC16
	.align	4
	.global	CreateMessageFromBuffer
	.type	CreateMessageFromBuffer, @function
CreateMessageFromBuffer:
.LFB1:
	.loc 1 70 0
.LVL17:
	addi	sp, sp, -64
.LCFI4:
	s32i.n	a13, sp, 52
.LCFI5:
	mov.n	a13, a2
	.loc 1 72 0
	movi.n	a2, 0x2c
.LVL18:
	s8i	a2, sp, 4
	.loc 1 75 0
	movi.n	a3, 0xa
.LVL19:
	mov.n	a2, a13
	.loc 1 70 0
	s32i.n	a0, sp, 60
	s32i.n	a12, sp, 56
	s32i.n	a14, sp, 48
.LCFI6:
	mov.n	a12, a4
	s32i.n	a15, sp, 44
.LCFI7:
	.loc 1 75 0
	call0	strchr
.LVL20:
	addi.n	a14, a2, 1
.LVL21:
	.loc 1 76 0
	sub	a4, a14, a13
	s32i	a4, a12, 512
	.loc 1 77 0
	mov.n	a3, a13
	mov.n	a2, a12
	call0	memcpy
.LVL22:
	.loc 1 79 0
	addi.n	a3, sp, 4
	mov.n	a2, a14
	call0	strtok
.LVL23:
	mov.n	a14, a2
.LVL24:
	.loc 1 80 0
	l32r	a2, .LC7
.LVL25:
	.loc 1 88 0
	addmi	a15, a12, 0x200
	.loc 1 80 0
	call0	printf
.LVL26:
	.loc 1 81 0
	mov.n	a2, a14
	call0	printf
.LVL27:
	.loc 1 82 0
	l32r	a13, .LC9
.LVL28:
	movi	a4, 0x208
	add.n	a4, a12, a4
	mov.n	a3, a13
	mov.n	a2, a14
	call0	sscanf
.LVL29:
	.loc 1 84 0
	addi.n	a3, sp, 4
	mov.n	a2, a14
	call0	strtok
.LVL30:
	.loc 1 85 0
	mov.n	a4, sp
	mov.n	a3, a13
	.loc 1 84 0
	mov.n	a14, a2
.LVL31:
	.loc 1 85 0
	call0	sscanf
.LVL32:
	.loc 1 86 0
	l32r	a2, .LC11
	call0	printf
.LVL33:
	.loc 1 87 0
	mov.n	a2, a14
	call0	printf
.LVL34:
	.loc 1 88 0
	l32i.n	a2, sp, 0
	.loc 1 90 0
	addi.n	a3, sp, 4
	.loc 1 88 0
	s8i	a2, a15, 5
	.loc 1 90 0
	mov.n	a2, a14
	call0	strtok
.LVL35:
	.loc 1 91 0
	mov.n	a4, sp
	mov.n	a3, a13
	.loc 1 90 0
	mov.n	a14, a2
.LVL36:
	.loc 1 91 0
	call0	sscanf
.LVL37:
	.loc 1 92 0
	l32r	a2, .LC13
	call0	printf
.LVL38:
	.loc 1 93 0
	mov.n	a2, a14
	call0	printf
.LVL39:
	.loc 1 94 0
	l32i.n	a2, sp, 0
	.loc 1 96 0
	addi.n	a3, sp, 4
	.loc 1 94 0
	s8i	a2, a15, 4
	.loc 1 96 0
	mov.n	a2, a14
	call0	strtok
.LVL40:
	.loc 1 97 0
	mov.n	a4, sp
	mov.n	a3, a13
	.loc 1 96 0
	mov.n	a14, a2
.LVL41:
	.loc 1 97 0
	call0	sscanf
.LVL42:
	.loc 1 98 0
	l32r	a2, .LC15
	call0	printf
.LVL43:
	.loc 1 99 0
	mov.n	a2, a14
	call0	printf
.LVL44:
	.loc 1 100 0
	l32i.n	a2, sp, 0
	.loc 1 103 0
	movi.n	a5, 0
	.loc 1 100 0
	s16i	a2, a15, 6
.LVL45:
	movi	a15, 0x20c
	add.n	a15, a12, a15
.LVL46:
.L7:
	.loc 1 105 0 discriminator 3
	addi.n	a3, sp, 4
	mov.n	a2, a14
	s32i.n	a5, sp, 16
	call0	strtok
.LVL47:
	.loc 1 106 0 discriminator 3
	l32i.n	a5, sp, 16
	.loc 1 105 0 discriminator 3
	mov.n	a14, a2
.LVL48:
	.loc 1 106 0 discriminator 3
	l32r	a2, .LC17
.LVL49:
	mov.n	a3, a5
	call0	printf
.LVL50:
	.loc 1 107 0 discriminator 3
	mov.n	a2, a14
	call0	printf
.LVL51:
	.loc 1 108 0 discriminator 3
	movi.n	a2, 0xa
	call0	putchar
.LVL52:
	.loc 1 109 0 discriminator 3
	mov.n	a4, sp
	mov.n	a3, a13
	mov.n	a2, a14
	call0	sscanf
.LVL53:
	.loc 1 110 0 discriminator 3
	l32i.n	a2, sp, 0
	s8i	a2, a15, 0
	.loc 1 103 0 discriminator 3
	l32i.n	a5, sp, 16
	addi.n	a15, a15, 1
	addi.n	a5, a5, 1
.LVL54:
	.loc 1 103 0 discriminator 3
	bnei	a5, 8, .L7
	.loc 1 113 0
	l32i	a2, a12, 512
	movi	a3, 0x1ff
	bgeu	a3, a2, .L8
	.loc 1 115 0
	addmi	a12, a12, 0x100
.LVL55:
	movi.n	a2, 0xa
	s8i	a2, a12, 255
.LVL56:
.L8:
	.loc 1 119 0
	l32i.n	a0, sp, 60
	movi.n	a2, 0
	l32i.n	a12, sp, 56
	l32i.n	a13, sp, 52
	l32i.n	a14, sp, 48
.LVL57:
	l32i.n	a15, sp, 44
	addi	sp, sp, 64
	ret.n
.LFE1:
	.size	CreateMessageFromBuffer, .-CreateMessageFromBuffer
	.section	.rodata.str1.1
.LC18:
	.string	""
.LC20:
	.string	","
.LC22:
	.string	"%s%d"
.LC24:
	.string	"bfl: %d,len: %d msg: %s, addr: %d, fam: %d, len: %d, port: %d, zero: %s\n"
.LC26:
	.string	"len: %d, buf: %s]\n\n"
	.text
	.literal_position
	.literal .LC19, .LC18
	.literal .LC21, .LC20
	.literal .LC23, .LC22
	.literal .LC25, .LC24
	.literal .LC27, .LC26
	.align	4
	.global	Message_Conversion_Test
	.type	Message_Conversion_Test, @function
Message_Conversion_Test:
.LFB2:
	.loc 1 122 0
	addi	sp, sp, -32
.LCFI8:
	movi	a9, 0x690
	s32i.n	a0, sp, 28
	s32i.n	a12, sp, 24
	s32i.n	a13, sp, 20
	s32i.n	a14, sp, 16
	s32i.n	a15, sp, 12
	sub	sp, sp, a9
.LCFI9:
	.loc 1 124 0
	addi	a3, sp, 16
	addmi	a2, a3, 0x400
	movi.n	a3, 0xa
	s32i	a3, a2, 552
.LVL58:
	.loc 1 128 0
	movi	a5, 0x68
	.loc 1 126 0
	movi.n	a2, 0
	movi.n	a3, 9
.LVL59:
.L11:
	.loc 1 128 0 discriminator 3
	movi	a6, 0x438
	add.n	a6, a6, sp
	add.n	a4, a6, a2
	s8i	a5, a4, 0
	.loc 1 126 0 discriminator 3
	addi.n	a2, a2, 1
.LVL60:
	bne	a2, a3, .L11
	.loc 1 131 0
	addi	a9, sp, 16
	addmi	a2, a9, 0x400
.LVL61:
	movi.n	a3, 0xa
	s8i	a3, a2, 49
	.loc 1 134 0
	movi.n	a4, 0x55
	.loc 1 132 0
	movi.n	a3, 0
	s8i	a3, a2, 50
	.loc 1 134 0
	s32i	a4, a2, 560
	.loc 1 135 0
	addmi	a2, a9, 0x600
	s8i	a3, a2, 44
	movi	a12, 0x428
	.loc 1 136 0
	movi.n	a3, 0
	s16i	a3, a2, 46
	add.n	a12, a9, a12
	.loc 1 150 0
	movi	a13, 0x63c
.L14:
.LVL62:
	movi	a6, 0x20c
	.loc 1 147 0
	movi.n	a7, 0
	.loc 1 150 0
	addi	a10, sp, 16
	add.n	a6, a12, a6
	.loc 1 148 0
	mov.n	a8, a7
	.loc 1 150 0
	add.n	a9, a10, a13
.LVL63:
.L13:
	movi	a10, 0x680
	add.n	a10, a10, sp
	l8ui	a5, a6, 0
	s32i.n	a6, a10, 0
	movi	a10, 0x684
	add.n	a10, a10, sp
	s32i.n	a7, a10, 0
	movi	a10, 0x68c
	add.n	a10, a10, sp
	s32i.n	a8, a10, 0
	l32r	a2, .LC19
	l32r	a4, .LC21
	movi	a10, 0x688
	add.n	a10, a10, sp
	l32r	a3, .LC23
	moveqz	a4, a2, a8
	s32i.n	a9, a10, 0
	add.n	a2, a9, a7
	call0	sprintf
.LVL64:
	movi	a3, 0x684
	add.n	a3, a3, sp
	l32i.n	a7, a3, 0
	.loc 1 151 0
	addi	a4, sp, 16
	movi	a5, 0x68c
	.loc 1 150 0
	add.n	a2, a7, a2
	.loc 1 151 0
	addmi	a15, a4, 0x400
	add.n	a5, a5, sp
	movi	a10, 0x680
	l32i.n	a8, a5, 0
	.loc 1 150 0
	extui	a7, a2, 0, 8
.LVL65:
	.loc 1 151 0
	add.n	a10, a10, sp
	l32i	a2, a15, 560
.LVL66:
	l32i.n	a6, a10, 0
	add.n	a2, a2, a8
	s8i	a2, a6, 0
	.loc 1 148 0
	movi	a2, 0x688
	add.n	a2, a2, sp
	addi.n	a8, a8, 1
.LVL67:
	addi.n	a6, a6, 1
	l32i.n	a9, a2, 0
	bnei	a8, 8, .L13
	.loc 1 154 0
	movi	a4, 0x428
	addi	a3, sp, 16
	mov.n	a2, a12
	call0	FillBufferWithMessage
.LVL68:
	.loc 1 156 0
	l32i	a4, a15, 552
	.loc 1 154 0
	mov.n	a8, a2
.LVL69:
	.loc 1 156 0
	movi.n	a3, 0
	add.n	a2, a15, a4
.LVL70:
	s8i	a3, a2, 41
	.loc 1 162 0
	addi	a3, sp, 16
	addmi	a2, a3, 0x600
	.loc 1 157 0
	add.n	a3, a3, a13
	l8ui	a7, a2, 45
	s32i.n	a3, sp, 8
	l16ui	a3, a2, 46
	movi	a9, 0x68c
	s32i.n	a3, sp, 4
	l8ui	a2, a2, 44
	add.n	a9, a9, sp
	s32i.n	a2, sp, 0
	l32i	a6, a15, 560
	l32r	a2, .LC25
	s32i.n	a8, a9, 0
	mov.n	a5, a12
	mov.n	a3, a14
	call0	printf
.LVL71:
	.loc 1 167 0
	movi	a10, 0x68c
	add.n	a10, a10, sp
	l32i.n	a8, a10, 0
	l32r	a2, .LC27
	mov.n	a3, a8
	addi	a4, sp, 16
	call0	printf
.LVL72:
	.loc 1 169 0
	l32i	a2, a15, 560
	.loc 1 172 0
	mov.n	a4, a12
	.loc 1 169 0
	addi.n	a2, a2, 1
	s32i	a2, a15, 560
	.loc 1 170 0
	movi.n	a2, 0x4e
	s8i	a2, a15, 40
	.loc 1 172 0
	movi	a3, 0x428
	addi	a2, sp, 16
	call0	CreateMessageFromBuffer
.LVL73:
	mov.n	a14, a2
.LVL74:
	.loc 1 173 0
	j	.L14
.LFE2:
	.size	Message_Conversion_Test, .-Message_Conversion_Test
	.global	Terminator
	.data
	.type	Terminator, @object
	.size	Terminator, 1
Terminator:
	.byte	10
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
	.byte	0x4
	.4byte	.LCFI0-.LFB0
	.byte	0xe
	.uleb128 0x40
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0x8d
	.uleb128 0x3
	.byte	0x4
	.4byte	.LCFI2-.LCFI1
	.byte	0x8e
	.uleb128 0x4
	.byte	0x4
	.4byte	.LCFI3-.LCFI2
	.byte	0x80
	.uleb128 0x1
	.byte	0x8c
	.uleb128 0x2
	.byte	0x8f
	.uleb128 0x5
	.align	4
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.byte	0x4
	.4byte	.LCFI4-.LFB1
	.byte	0xe
	.uleb128 0x40
	.byte	0x4
	.4byte	.LCFI5-.LCFI4
	.byte	0x8d
	.uleb128 0x3
	.byte	0x4
	.4byte	.LCFI6-.LCFI5
	.byte	0x80
	.uleb128 0x1
	.byte	0x8c
	.uleb128 0x2
	.byte	0x8e
	.uleb128 0x4
	.byte	0x4
	.4byte	.LCFI7-.LCFI6
	.byte	0x8f
	.uleb128 0x5
	.align	4
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.byte	0x4
	.4byte	.LCFI8-.LFB2
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI9-.LCFI8
	.byte	0xe
	.uleb128 0x6b0
	.byte	0x80
	.uleb128 0x1
	.byte	0x8c
	.uleb128 0x2
	.byte	0x8d
	.uleb128 0x3
	.byte	0x8e
	.uleb128 0x4
	.byte	0x8f
	.uleb128 0x5
	.align	4
.LEFDE4:
	.text
.Letext0:
	.file 2 "c:\\espressif\\xtensa-lx106-elf\\xtensa-lx106-elf\\include\\stdint.h"
	.file 3 "c:\\espressif\\xtensa-lx106-elf\\lib\\gcc\\xtensa-lx106-elf\\5.1.0\\include\\stddef.h"
	.file 4 "c:/Espressif/ESP8266_RTOS_SDK/include/espressif/c_types.h"
	.file 5 "c:/Espressif/ESP8266_RTOS_SDK/include/lwip/ipv4/lwip/inet.h"
	.file 6 "c:/Espressif/ESP8266_RTOS_SDK/include/lwip/lwip/sockets.h"
	.file 7 "include/Clay_Message.h"
	.file 8 "c:\\espressif\\xtensa-lx106-elf\\xtensa-lx106-elf\\include\\stdio.h"
	.file 9 "c:\\espressif\\xtensa-lx106-elf\\xtensa-lx106-elf\\include\\string.h"
	.file 10 "<built-in>"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x7bd
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF60
	.byte	0x1
	.4byte	.LASF61
	.4byte	.LASF62
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF0
	.uleb128 0x3
	.4byte	.LASF3
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
	.uleb128 0x3
	.4byte	.LASF4
	.byte	0x2
	.byte	0x36
	.4byte	0x50
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.4byte	.LASF6
	.byte	0x2
	.byte	0x51
	.4byte	0x69
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x3
	.4byte	.LASF10
	.byte	0x3
	.byte	0xd8
	.4byte	0x69
	.uleb128 0x3
	.4byte	.LASF11
	.byte	0x4
	.byte	0x24
	.4byte	0x2c
	.uleb128 0x3
	.4byte	.LASF12
	.byte	0x4
	.byte	0x26
	.4byte	0x45
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x4
	.byte	0x28
	.4byte	0x5e
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x4
	.byte	0x2b
	.4byte	0x2c
	.uleb128 0x3
	.4byte	.LASF15
	.byte	0x4
	.byte	0x34
	.4byte	0x5e
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.4byte	.LASF16
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF17
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF18
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF19
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF20
	.uleb128 0x6
	.byte	0x4
	.4byte	0xeb
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF21
	.uleb128 0x6
	.byte	0x4
	.4byte	0xf8
	.uleb128 0x7
	.4byte	0xeb
	.uleb128 0x8
	.4byte	0xeb
	.4byte	0x10d
	.uleb128 0x9
	.4byte	0xde
	.byte	0x7
	.byte	0
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF22
	.uleb128 0x6
	.byte	0x4
	.4byte	0xaa
	.uleb128 0x3
	.4byte	.LASF23
	.byte	0x5
	.byte	0x2e
	.4byte	0x9f
	.uleb128 0xa
	.4byte	.LASF26
	.byte	0x4
	.byte	0x5
	.byte	0x31
	.4byte	0x13e
	.uleb128 0xb
	.4byte	.LASF28
	.byte	0x5
	.byte	0x32
	.4byte	0x11a
	.byte	0
	.byte	0
	.uleb128 0x3
	.4byte	.LASF24
	.byte	0x6
	.byte	0x36
	.4byte	0x89
	.uleb128 0x3
	.4byte	.LASF25
	.byte	0x6
	.byte	0x3b
	.4byte	0x94
	.uleb128 0xa
	.4byte	.LASF27
	.byte	0x10
	.byte	0x6
	.byte	0x3f
	.4byte	0x19d
	.uleb128 0xb
	.4byte	.LASF29
	.byte	0x6
	.byte	0x40
	.4byte	0x89
	.byte	0
	.uleb128 0xb
	.4byte	.LASF30
	.byte	0x6
	.byte	0x41
	.4byte	0x13e
	.byte	0x1
	.uleb128 0xb
	.4byte	.LASF31
	.byte	0x6
	.byte	0x42
	.4byte	0x149
	.byte	0x2
	.uleb128 0xb
	.4byte	.LASF32
	.byte	0x6
	.byte	0x43
	.4byte	0x125
	.byte	0x4
	.uleb128 0xb
	.4byte	.LASF33
	.byte	0x6
	.byte	0x45
	.4byte	0xfd
	.byte	0x8
	.byte	0
	.uleb128 0xc
	.2byte	0x214
	.byte	0x7
	.byte	0x14
	.4byte	0x1cd
	.uleb128 0xb
	.4byte	.LASF34
	.byte	0x7
	.byte	0x16
	.4byte	0x1cd
	.byte	0
	.uleb128 0xd
	.4byte	.LASF35
	.byte	0x7
	.byte	0x17
	.4byte	0xb5
	.2byte	0x200
	.uleb128 0xd
	.4byte	.LASF36
	.byte	0x7
	.byte	0x18
	.4byte	0x154
	.2byte	0x204
	.byte	0
	.uleb128 0x8
	.4byte	0xaa
	.4byte	0x1de
	.uleb128 0xe
	.4byte	0xde
	.2byte	0x1ff
	.byte	0
	.uleb128 0x3
	.4byte	.LASF37
	.byte	0x7
	.byte	0x1b
	.4byte	0x19d
	.uleb128 0xf
	.4byte	.LASF42
	.byte	0x1
	.byte	0x1b
	.4byte	0xb5
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x2ac
	.uleb128 0x10
	.4byte	.LASF38
	.byte	0x1
	.byte	0x1b
	.4byte	0x2ac
	.4byte	.LLST0
	.uleb128 0x10
	.4byte	.LASF39
	.byte	0x1
	.byte	0x1b
	.4byte	0x114
	.4byte	.LLST1
	.uleb128 0x10
	.4byte	.LASF40
	.byte	0x1
	.byte	0x1b
	.4byte	0xb5
	.4byte	.LLST2
	.uleb128 0x11
	.4byte	.LASF41
	.byte	0x1
	.byte	0x1d
	.4byte	0xb5
	.4byte	.LLST3
	.uleb128 0x12
	.4byte	.LBB2
	.4byte	.LBE2-.LBB2
	.4byte	0x275
	.uleb128 0x13
	.string	"i"
	.byte	0x1
	.byte	0x35
	.4byte	0x57
	.4byte	.LLST4
	.uleb128 0x14
	.4byte	.LVL9
	.4byte	0x6c7
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x7d
	.sleb128 0
	.byte	0x7c
	.sleb128 0
	.byte	0x22
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC4
	.byte	0
	.byte	0
	.uleb128 0x16
	.4byte	.LVL4
	.4byte	0x6e8
	.4byte	0x28f
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.uleb128 0x14
	.4byte	.LVL6
	.4byte	0x6c7
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x7d
	.sleb128 0
	.byte	0x7c
	.sleb128 0
	.byte	0x22
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC2
	.byte	0
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x1de
	.uleb128 0xf
	.4byte	.LASF43
	.byte	0x1
	.byte	0x45
	.4byte	0xb5
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x582
	.uleb128 0x10
	.4byte	.LASF38
	.byte	0x1
	.byte	0x45
	.4byte	0x114
	.4byte	.LLST5
	.uleb128 0x10
	.4byte	.LASF44
	.byte	0x1
	.byte	0x45
	.4byte	0xb5
	.4byte	.LLST6
	.uleb128 0x10
	.4byte	.LASF39
	.byte	0x1
	.byte	0x45
	.4byte	0x2ac
	.4byte	.LLST7
	.uleb128 0x17
	.4byte	.LASF41
	.byte	0x1
	.byte	0x47
	.4byte	0xb5
	.byte	0
	.uleb128 0x18
	.4byte	.LASF45
	.byte	0x1
	.byte	0x48
	.4byte	0xeb
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x18
	.4byte	.LASF46
	.byte	0x1
	.byte	0x49
	.4byte	0xb5
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x11
	.4byte	.LASF47
	.byte	0x1
	.byte	0x4b
	.4byte	0x114
	.4byte	.LLST8
	.uleb128 0x13
	.string	"i"
	.byte	0x1
	.byte	0x66
	.4byte	0x57
	.4byte	.LLST9
	.uleb128 0x16
	.4byte	.LVL20
	.4byte	0x707
	.4byte	0x355
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3a
	.byte	0
	.uleb128 0x16
	.4byte	.LVL22
	.4byte	0x721
	.4byte	0x378
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x5
	.byte	0x7e
	.sleb128 0
	.byte	0x7d
	.sleb128 0
	.byte	0x1c
	.byte	0
	.uleb128 0x16
	.4byte	.LVL23
	.4byte	0x745
	.4byte	0x392
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.byte	0
	.uleb128 0x16
	.4byte	.LVL26
	.4byte	0x75f
	.4byte	0x3a9
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC6
	.byte	0
	.uleb128 0x16
	.4byte	.LVL27
	.4byte	0x75f
	.4byte	0x3bd
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.uleb128 0x16
	.4byte	.LVL29
	.4byte	0x775
	.4byte	0x3de
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x3
	.byte	0x7c
	.sleb128 520
	.byte	0
	.uleb128 0x16
	.4byte	.LVL30
	.4byte	0x745
	.4byte	0x3f8
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.byte	0
	.uleb128 0x16
	.4byte	.LVL32
	.4byte	0x775
	.4byte	0x418
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.byte	0
	.uleb128 0x16
	.4byte	.LVL33
	.4byte	0x75f
	.4byte	0x42f
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC10
	.byte	0
	.uleb128 0x16
	.4byte	.LVL34
	.4byte	0x75f
	.4byte	0x443
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.uleb128 0x16
	.4byte	.LVL35
	.4byte	0x745
	.4byte	0x45d
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.byte	0
	.uleb128 0x16
	.4byte	.LVL37
	.4byte	0x775
	.4byte	0x47d
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.byte	0
	.uleb128 0x16
	.4byte	.LVL38
	.4byte	0x75f
	.4byte	0x494
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC12
	.byte	0
	.uleb128 0x16
	.4byte	.LVL39
	.4byte	0x75f
	.4byte	0x4a8
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.uleb128 0x16
	.4byte	.LVL40
	.4byte	0x745
	.4byte	0x4c2
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.byte	0
	.uleb128 0x16
	.4byte	.LVL42
	.4byte	0x775
	.4byte	0x4e2
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.byte	0
	.uleb128 0x16
	.4byte	.LVL43
	.4byte	0x75f
	.4byte	0x4f9
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC14
	.byte	0
	.uleb128 0x16
	.4byte	.LVL44
	.4byte	0x75f
	.4byte	0x50d
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.uleb128 0x16
	.4byte	.LVL47
	.4byte	0x745
	.4byte	0x527
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.byte	0
	.uleb128 0x16
	.4byte	.LVL50
	.4byte	0x75f
	.4byte	0x53e
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC16
	.byte	0
	.uleb128 0x16
	.4byte	.LVL51
	.4byte	0x75f
	.4byte	0x552
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.uleb128 0x16
	.4byte	.LVL52
	.4byte	0x790
	.4byte	0x565
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x3a
	.byte	0
	.uleb128 0x14
	.4byte	.LVL53
	.4byte	0x775
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x19
	.4byte	.LASF63
	.byte	0x1
	.byte	0x79
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x695
	.uleb128 0x1a
	.string	"m"
	.byte	0x1
	.byte	0x7b
	.4byte	0x1de
	.uleb128 0x3
	.byte	0x91
	.sleb128 -632
	.uleb128 0x13
	.string	"i"
	.byte	0x1
	.byte	0x7d
	.4byte	0x57
	.4byte	.LLST10
	.uleb128 0x11
	.4byte	.LASF48
	.byte	0x1
	.byte	0x8a
	.4byte	0xb5
	.4byte	.LLST11
	.uleb128 0x11
	.4byte	.LASF49
	.byte	0x1
	.byte	0x8b
	.4byte	0xb5
	.4byte	.LLST12
	.uleb128 0x18
	.4byte	.LASF50
	.byte	0x1
	.byte	0x8c
	.4byte	0x695
	.uleb128 0x3
	.byte	0x91
	.sleb128 -100
	.uleb128 0x11
	.4byte	.LASF51
	.byte	0x1
	.byte	0x8d
	.4byte	0xeb
	.4byte	.LLST13
	.uleb128 0x1a
	.string	"buf"
	.byte	0x1
	.byte	0x8f
	.4byte	0x6a5
	.uleb128 0x3
	.byte	0x91
	.sleb128 -1696
	.uleb128 0x16
	.4byte	.LVL64
	.4byte	0x7a9
	.4byte	0x613
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC22
	.byte	0
	.uleb128 0x16
	.4byte	.LVL68
	.4byte	0x1e9
	.4byte	0x635
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x3
	.byte	0x7c
	.sleb128 -1064
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x3
	.byte	0xa
	.2byte	0x428
	.byte	0
	.uleb128 0x16
	.4byte	.LVL71
	.4byte	0x75f
	.4byte	0x658
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC24
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.byte	0
	.uleb128 0x16
	.4byte	.LVL72
	.4byte	0x75f
	.4byte	0x676
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC26
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x3
	.byte	0x7c
	.sleb128 -1064
	.byte	0
	.uleb128 0x14
	.4byte	.LVL73
	.4byte	0x2b2
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0x7c
	.sleb128 -1064
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x3
	.byte	0xa
	.2byte	0x428
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x8
	.4byte	0xeb
	.4byte	0x6a5
	.uleb128 0x9
	.4byte	0xde
	.byte	0x31
	.byte	0
	.uleb128 0x8
	.4byte	0xaa
	.4byte	0x6b6
	.uleb128 0xe
	.4byte	0xde
	.2byte	0x427
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF64
	.byte	0x1
	.byte	0x16
	.4byte	0xeb
	.uleb128 0x5
	.byte	0x3
	.4byte	Terminator
	.uleb128 0x1c
	.4byte	.LASF52
	.byte	0x8
	.2byte	0x10b
	.4byte	0x57
	.4byte	0x6e8
	.uleb128 0x1d
	.4byte	0xe5
	.uleb128 0x1d
	.4byte	0x7e
	.uleb128 0x1d
	.4byte	0xf2
	.uleb128 0x1e
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF53
	.byte	0x9
	.byte	0x24
	.4byte	0xe5
	.4byte	0x707
	.uleb128 0x1d
	.4byte	0xe5
	.uleb128 0x1d
	.4byte	0xf2
	.uleb128 0x1d
	.4byte	0x7e
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF54
	.byte	0x9
	.byte	0x1b
	.4byte	0xe5
	.4byte	0x721
	.uleb128 0x1d
	.4byte	0xf2
	.uleb128 0x1d
	.4byte	0x57
	.byte	0
	.uleb128 0x20
	.4byte	.LASF58
	.4byte	0xd5
	.4byte	0x73e
	.uleb128 0x1d
	.4byte	0xd5
	.uleb128 0x1d
	.4byte	0x73e
	.uleb128 0x1d
	.4byte	0xde
	.byte	0
	.uleb128 0x6
	.byte	0x4
	.4byte	0x744
	.uleb128 0x21
	.uleb128 0x1f
	.4byte	.LASF55
	.byte	0x9
	.byte	0x2b
	.4byte	0xe5
	.4byte	0x75f
	.uleb128 0x1d
	.4byte	0xe5
	.uleb128 0x1d
	.4byte	0xf2
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF56
	.byte	0x8
	.byte	0xb3
	.4byte	0x57
	.4byte	0x775
	.uleb128 0x1d
	.4byte	0xf2
	.uleb128 0x1e
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF57
	.byte	0x8
	.byte	0xb7
	.4byte	0x57
	.4byte	0x790
	.uleb128 0x1d
	.4byte	0xf2
	.uleb128 0x1d
	.4byte	0xf2
	.uleb128 0x1e
	.byte	0
	.uleb128 0x22
	.4byte	.LASF65
	.byte	0xa
	.byte	0
	.4byte	.LASF66
	.4byte	0x57
	.4byte	0x7a9
	.uleb128 0x1d
	.4byte	0x57
	.byte	0
	.uleb128 0x23
	.4byte	.LASF59
	.byte	0x8
	.byte	0xdf
	.4byte	0x57
	.uleb128 0x1d
	.4byte	0xe5
	.uleb128 0x1d
	.4byte	0xf2
	.uleb128 0x1e
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
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
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
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0x5
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
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
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0xf
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
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x12
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
	.uleb128 0x13
	.uleb128 0x34
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
	.uleb128 0x14
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x1c
	.uleb128 0xb
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x87
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
	.uleb128 0x34
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
	.uleb128 0x18
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1c
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1f
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x22
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
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
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
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LVL0-.Ltext0
	.4byte	.LVL3-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL3-.Ltext0
	.4byte	.LVL4-1-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL4-1-.Ltext0
	.4byte	.LVL8-.Ltext0
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL8-.Ltext0
	.4byte	.LVL15-.Ltext0
	.2byte	0x4
	.byte	0x7e
	.sleb128 -532
	.byte	0x9f
	.4byte	.LVL15-.Ltext0
	.4byte	.LFE0-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL0-.Ltext0
	.4byte	.LVL2-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL2-.Ltext0
	.4byte	.LVL11-.Ltext0
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL11-.Ltext0
	.4byte	.LVL13-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	.LVL13-.Ltext0
	.4byte	.LVL15-.Ltext0
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL15-.Ltext0
	.4byte	.LFE0-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL0-.Ltext0
	.4byte	.LVL1-.Ltext0
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL1-.Ltext0
	.4byte	.LVL4-1-.Ltext0
	.2byte	0x1
	.byte	0x58
	.4byte	.LVL4-1-.Ltext0
	.4byte	.LFE0-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x54
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LVL0-.Ltext0
	.4byte	.LVL5-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL5-.Ltext0
	.4byte	.LVL12-.Ltext0
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL12-.Ltext0
	.4byte	.LVL13-.Ltext0
	.2byte	0x1
	.byte	0x58
	.4byte	.LVL13-.Ltext0
	.4byte	.LVL16-.Ltext0
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL16-.Ltext0
	.4byte	.LFE0-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LVL8-.Ltext0
	.4byte	.LVL13-.Ltext0
	.2byte	0x8
	.byte	0x7f
	.sleb128 0
	.byte	0x7e
	.sleb128 0
	.byte	0x1c
	.byte	0x23
	.uleb128 0x8
	.byte	0x9f
	.4byte	.LVL13-.Ltext0
	.4byte	.LVL14-.Ltext0
	.2byte	0x8
	.byte	0x7f
	.sleb128 0
	.byte	0x7e
	.sleb128 0
	.byte	0x1c
	.byte	0x23
	.uleb128 0x9
	.byte	0x9f
	.4byte	.LVL14-.Ltext0
	.4byte	.LVL15-.Ltext0
	.2byte	0x8
	.byte	0x7f
	.sleb128 0
	.byte	0x7e
	.sleb128 0
	.byte	0x1c
	.byte	0x23
	.uleb128 0x8
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST5:
	.4byte	.LVL17-.Ltext0
	.4byte	.LVL18-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL18-.Ltext0
	.4byte	.LVL28-.Ltext0
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL28-.Ltext0
	.4byte	.LFE1-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST6:
	.4byte	.LVL17-.Ltext0
	.4byte	.LVL19-.Ltext0
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL19-.Ltext0
	.4byte	.LFE1-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST7:
	.4byte	.LVL17-.Ltext0
	.4byte	.LVL20-1-.Ltext0
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL20-1-.Ltext0
	.4byte	.LVL55-.Ltext0
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL55-.Ltext0
	.4byte	.LVL56-.Ltext0
	.2byte	0x4
	.byte	0x7c
	.sleb128 -256
	.byte	0x9f
	.4byte	.LVL56-.Ltext0
	.4byte	.LFE1-.Ltext0
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x54
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST8:
	.4byte	.LVL21-.Ltext0
	.4byte	.LVL24-.Ltext0
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL24-.Ltext0
	.4byte	.LVL25-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL25-.Ltext0
	.4byte	.LVL31-.Ltext0
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL31-.Ltext0
	.4byte	.LVL32-1-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL32-1-.Ltext0
	.4byte	.LVL36-.Ltext0
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL36-.Ltext0
	.4byte	.LVL37-1-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL37-1-.Ltext0
	.4byte	.LVL41-.Ltext0
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL41-.Ltext0
	.4byte	.LVL42-1-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL42-1-.Ltext0
	.4byte	.LVL48-.Ltext0
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL48-.Ltext0
	.4byte	.LVL49-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL49-.Ltext0
	.4byte	.LVL57-.Ltext0
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST9:
	.4byte	.LVL45-.Ltext0
	.4byte	.LVL46-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL46-.Ltext0
	.4byte	.LVL47-1-.Ltext0
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL54-.Ltext0
	.4byte	.LFE1-.Ltext0
	.2byte	0x1
	.byte	0x55
	.4byte	0
	.4byte	0
.LLST10:
	.4byte	.LVL58-.Ltext0
	.4byte	.LVL59-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL59-.Ltext0
	.4byte	.LVL61-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL62-.Ltext0
	.4byte	.LVL63-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL63-.Ltext0
	.4byte	.LVL64-1-.Ltext0
	.2byte	0x1
	.byte	0x58
	.4byte	.LVL67-.Ltext0
	.4byte	.LVL68-1-.Ltext0
	.2byte	0x1
	.byte	0x58
	.4byte	0
	.4byte	0
.LLST11:
	.4byte	.LVL69-.Ltext0
	.4byte	.LVL70-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL70-.Ltext0
	.4byte	.LVL71-1-.Ltext0
	.2byte	0x1
	.byte	0x58
	.4byte	0
	.4byte	0
.LLST12:
	.4byte	.LVL62-.Ltext0
	.4byte	.LVL74-.Ltext0
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL74-.Ltext0
	.4byte	.LFE2-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LLST13:
	.4byte	.LVL62-.Ltext0
	.4byte	.LVL63-.Ltext0
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL63-.Ltext0
	.4byte	.LVL64-1-.Ltext0
	.2byte	0x1
	.byte	0x57
	.4byte	.LVL65-.Ltext0
	.4byte	.LVL66-.Ltext0
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL66-.Ltext0
	.4byte	.LVL68-1-.Ltext0
	.2byte	0x1
	.byte	0x57
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
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF37:
	.string	"Clay_Message"
.LASF53:
	.string	"strncpy"
.LASF48:
	.string	"bufferFillLength"
.LASF35:
	.string	"Length"
.LASF57:
	.string	"sscanf"
.LASF46:
	.string	"temp"
.LASF2:
	.string	"short int"
.LASF10:
	.string	"size_t"
.LASF20:
	.string	"sizetype"
.LASF66:
	.string	"putchar"
.LASF58:
	.string	"memcpy"
.LASF36:
	.string	"Address"
.LASF45:
	.string	"Comma"
.LASF50:
	.string	"sinZeroStr"
.LASF44:
	.string	"SourceLength"
.LASF49:
	.string	"messageFillLength"
.LASF3:
	.string	"uint8_t"
.LASF14:
	.string	"uint8"
.LASF30:
	.string	"sin_family"
.LASF61:
	.string	"user/Clay_Message.c"
.LASF29:
	.string	"sin_len"
.LASF42:
	.string	"FillBufferWithMessage"
.LASF52:
	.string	"snprintf"
.LASF16:
	.string	"float"
.LASF8:
	.string	"long long int"
.LASF19:
	.string	"long int"
.LASF51:
	.string	"sinZeroSize"
.LASF56:
	.string	"printf"
.LASF55:
	.string	"strtok"
.LASF41:
	.string	"rval"
.LASF32:
	.string	"sin_addr"
.LASF59:
	.string	"sprintf"
.LASF62:
	.string	"C:\\\\Users\\\\thebh\\\\Desktop\\\\dtf\\\\git\\\\clay\\\\Firmware\\\\ESP8266\\\\clay_udp_demo_2"
.LASF24:
	.string	"sa_family_t"
.LASF1:
	.string	"unsigned char"
.LASF54:
	.string	"strchr"
.LASF0:
	.string	"signed char"
.LASF33:
	.string	"sin_zero"
.LASF9:
	.string	"long long unsigned int"
.LASF6:
	.string	"uint32_t"
.LASF7:
	.string	"unsigned int"
.LASF63:
	.string	"Message_Conversion_Test"
.LASF28:
	.string	"s_addr"
.LASF64:
	.string	"Terminator"
.LASF40:
	.string	"DestinationLength"
.LASF38:
	.string	"Source"
.LASF21:
	.string	"char"
.LASF4:
	.string	"uint16_t"
.LASF5:
	.string	"short unsigned int"
.LASF22:
	.string	"_Bool"
.LASF23:
	.string	"in_addr_t"
.LASF65:
	.string	"__builtin_putchar"
.LASF15:
	.string	"uint32"
.LASF18:
	.string	"long unsigned int"
.LASF26:
	.string	"in_addr"
.LASF17:
	.string	"double"
.LASF43:
	.string	"CreateMessageFromBuffer"
.LASF31:
	.string	"sin_port"
.LASF11:
	.string	"u8_t"
.LASF13:
	.string	"u32_t"
.LASF25:
	.string	"in_port_t"
.LASF39:
	.string	"Destination"
.LASF12:
	.string	"u16_t"
.LASF60:
	.string	"GNU C89 5.1.0 -mlongcalls -mtext-section-literals -mno-serialize-volatile -g -Os -std=gnu90 -fno-inline-functions"
.LASF34:
	.string	"Message"
.LASF47:
	.string	"NewlineIndex"
.LASF27:
	.string	"sockaddr_in"
	.ident	"GCC: (GNU) 5.1.0"
