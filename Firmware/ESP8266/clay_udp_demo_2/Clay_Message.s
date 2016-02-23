	.file	"Clay_Message.c"
	.text
.Ltext0:
	.global	Terminator
	.data
	.type	Terminator, @object
	.size	Terminator, 1
Terminator:
	.byte	10
	.text
.Letext0:
	.file 1 "user/Clay_Message.c"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x32
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF0
	.byte	0x1
	.4byte	.LASF1
	.4byte	.LASF2
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	.LASF3
	.byte	0x1
	.byte	0x8
	.4byte	0x2e
	.uleb128 0x5
	.byte	0x3
	.4byte	Terminator
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF4
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
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
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
	.uleb128 0x3
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
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x14
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF0:
	.string	"GNU C89 5.1.0 -mlongcalls -mtext-section-literals -mno-serialize-volatile -g -Os -std=gnu90 -fno-inline-functions"
.LASF3:
	.string	"Terminator"
.LASF1:
	.string	"user/Clay_Message.c"
.LASF2:
	.string	"C:\\\\Users\\\\thebh\\\\Desktop\\\\dtf\\\\git\\\\clay\\\\Firmware\\\\ESP8266\\\\clay_udp_demo_2"
.LASF4:
	.string	"char"
	.ident	"GCC: (GNU) 5.1.0"
