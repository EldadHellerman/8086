	.file	"main.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.init_spi,"ax",@progbits
.global	init_spi
	.type	init_spi, @function
init_spi:
.LFB6:
	.file 1 ".././main.c"
	.loc 1 19 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 20 0
	sbi 0x8,0
	sbi 0x7,0
	.loc 1 21 0
	sbi 0x8,1
	sbi 0x7,1
	.loc 1 22 0
	cbi 0x5,2
	sbi 0x4,2
	.loc 1 23 0
	sbi 0x4,3
	sbi 0x4,5
	sbi 0x4,2
	.loc 1 24 0
	ldi r24,lo8(80)
	out 0x2c,r24
	ret
	.cfi_endproc
.LFE6:
	.size	init_spi, .-init_spi
	.section	.text.spi,"ax",@progbits
.global	spi
	.type	spi, @function
spi:
.LFB7:
	.loc 1 28 0
	.cfi_startproc
.LVL0:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 30 0
	out 0x2e,r25
.L3:
	.loc 1 31 0 discriminator 1
	in __tmp_reg__,0x2d
	sbrs __tmp_reg__,7
	rjmp .L3
	.loc 1 32 0
	in r18,0x2e
	ldi r19,0
.LVL1:
	.loc 1 33 0
	out 0x2e,r24
	.loc 1 34 0
	mov r25,r18
	clr r24
.LVL2:
.L4:
	.loc 1 35 0 discriminator 1
	in __tmp_reg__,0x2d
	sbrs __tmp_reg__,7
	rjmp .L4
	.loc 1 36 0
	in r18,0x2e
.LVL3:
	.loc 1 38 0
	or r24,r18
.LVL4:
	ret
	.cfi_endproc
.LFE7:
	.size	spi, .-spi
	.section	.text.spi_recieve,"ax",@progbits
.global	spi_recieve
	.type	spi_recieve, @function
spi_recieve:
.LFB8:
	.loc 1 40 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 42 0
	out 0x2e,__zero_reg__
.L8:
	.loc 1 43 0 discriminator 1
	in __tmp_reg__,0x2d
	sbrs __tmp_reg__,7
	rjmp .L8
	.loc 1 44 0
	in r24,0x2e
	ldi r25,0
.LVL5:
	.loc 1 45 0
	out 0x2e,__zero_reg__
	.loc 1 46 0
	mov r25,r24
	clr r24
.LVL6:
.L9:
	.loc 1 47 0 discriminator 1
	in __tmp_reg__,0x2d
	sbrs __tmp_reg__,7
	rjmp .L9
	.loc 1 48 0
	in r18,0x2e
.LVL7:
	.loc 1 50 0
	or r24,r18
.LVL8:
	ret
	.cfi_endproc
.LFE8:
	.size	spi_recieve, .-spi_recieve
	.section	.text.spi_send,"ax",@progbits
.global	spi_send
	.type	spi_send, @function
spi_send:
.LFB9:
	.loc 1 52 0
	.cfi_startproc
.LVL9:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 53 0
	out 0x2e,r25
.L13:
	.loc 1 54 0 discriminator 1
	in __tmp_reg__,0x2d
	sbrs __tmp_reg__,7
	rjmp .L13
	.loc 1 55 0
	out 0x2e,r24
.L14:
	.loc 1 56 0 discriminator 1
	in __tmp_reg__,0x2d
	sbrs __tmp_reg__,7
	rjmp .L14
/* epilogue start */
	.loc 1 57 0
	ret
	.cfi_endproc
.LFE9:
	.size	spi_send, .-spi_send
	.section	.text.ad_set,"ax",@progbits
.global	ad_set
	.type	ad_set, @function
ad_set:
.LFB10:
	.loc 1 59 0
	.cfi_startproc
.LVL10:
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 60 0
	movw r24,r22
	call spi_send
.LVL11:
	.loc 1 61 0
	sbi 0x5,2
	cbi 0x5,2
	ret
	.cfi_endproc
.LFE10:
	.size	ad_set, .-ad_set
	.section	.text.ad_get,"ax",@progbits
.global	ad_get
	.type	ad_get, @function
ad_get:
.LFB11:
	.loc 1 64 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 66 0
	in r24,0x2c
	ori r24,lo8(8)
	out 0x2c,r24
	.loc 1 67 0
	cbi 0x8,1
	sbi 0x8,1
	.loc 1 68 0
	call spi_recieve
.LVL12:
	.loc 1 69 0
	in r18,0x2c
	andi r18,lo8(-9)
	out 0x2c,r18
	.loc 1 71 0
	ret
	.cfi_endproc
.LFE11:
	.size	ad_get, .-ad_get
	.section	.text.hold_bus,"ax",@progbits
.global	hold_bus
	.type	hold_bus, @function
hold_bus:
.LFB12:
	.loc 1 73 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 79 0
	cbi 0xa,4
	cbi 0xb,4
	.loc 1 80 0
	cbi 0xa,2
	sbi 0xb,2
	.loc 1 81 0
	cbi 0xa,3
	sbi 0xb,3
	.loc 1 84 0
	sbi 0xa,4
	.loc 1 85 0
	sbi 0xa,2
	.loc 1 86 0
	sbi 0xa,3
	ret
	.cfi_endproc
.LFE12:
	.size	hold_bus, .-hold_bus
	.section	.text.release_bus,"ax",@progbits
.global	release_bus
	.type	release_bus, @function
release_bus:
.LFB13:
	.loc 1 89 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 90 0
	cbi 0xb,4
	cbi 0xa,4
	.loc 1 91 0
	sbi 0xb,2
	cbi 0xa,2
	.loc 1 92 0
	sbi 0xb,3
	cbi 0xa,3
	.loc 1 95 0
	cbi 0xb,2
	.loc 1 96 0
	cbi 0xb,3
	ret
	.cfi_endproc
.LFE13:
	.size	release_bus, .-release_bus
	.section	.text.read_word,"ax",@progbits
.global	read_word
	.type	read_word, @function
read_word:
.LFB14:
	.loc 1 99 0
	.cfi_startproc
.LVL13:
	push r28
.LCFI0:
	.cfi_def_cfa_offset 3
	.cfi_offset 28, -2
	push r29
.LCFI1:
	.cfi_def_cfa_offset 4
	.cfi_offset 29, -3
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	movw r28,r24
	.loc 1 101 0
	call hold_bus
.LVL14:
	.loc 1 102 0
	movw r22,r28
	ldi r24,0
	ldi r25,0
	call ad_set
.LVL15:
	.loc 1 104 0
	cbi 0x8,0
	.loc 1 105 0
	sbi 0xb,4
	cbi 0xb,4
	.loc 1 106 0
	sbi 0x8,0
	.loc 1 107 0
	cbi 0xb,2
	.loc 1 108 0
	call ad_get
.LVL16:
	.loc 1 109 0
	sbi 0xb,2
/* epilogue start */
	.loc 1 111 0
	pop r29
	pop r28
.LVL17:
	ret
	.cfi_endproc
.LFE14:
	.size	read_word, .-read_word
	.section	.text.write_word,"ax",@progbits
.global	write_word
	.type	write_word, @function
write_word:
.LFB15:
	.loc 1 113 0
	.cfi_startproc
.LVL18:
	push r16
.LCFI2:
	.cfi_def_cfa_offset 3
	.cfi_offset 16, -2
	push r17
.LCFI3:
	.cfi_def_cfa_offset 4
	.cfi_offset 17, -3
	push r28
.LCFI4:
	.cfi_def_cfa_offset 5
	.cfi_offset 28, -4
	push r29
.LCFI5:
	.cfi_def_cfa_offset 6
	.cfi_offset 29, -5
/* prologue: function */
/* frame size = 0 */
/* stack size = 4 */
.L__stack_usage = 4
	movw r16,r24
	movw r28,r22
	.loc 1 114 0
	call hold_bus
.LVL19:
	.loc 1 115 0
	movw r22,r16
	ldi r24,0
	ldi r25,0
	call ad_set
.LVL20:
	.loc 1 117 0
	cbi 0x8,0
	.loc 1 118 0
	sbi 0xb,4
	cbi 0xb,4
	.loc 1 119 0
	movw r22,r28
	ldi r24,0
	ldi r25,0
	call ad_set
.LVL21:
	.loc 1 120 0
	cbi 0xb,3
	.loc 1 121 0
	sbi 0xb,3
	.loc 1 122 0
	sbi 0x8,0
/* epilogue start */
	.loc 1 123 0
	pop r29
	pop r28
.LVL22:
	pop r17
	pop r16
.LVL23:
	ret
	.cfi_endproc
.LFE15:
	.size	write_word, .-write_word
	.section	.text.main,"ax",@progbits
.global	main
	.type	main, @function
main:
.LFB16:
	.loc 1 125 0
	.cfi_startproc
/* prologue: function */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	.loc 1 126 0
	call init_spi
.LVL24:
	.loc 1 127 0
	call hold_bus
.LVL25:
	.loc 1 129 0
	out 0xa,__zero_reg__
	ldi r28,0
	ldi r29,0
.LVL26:
.L24:
	.loc 1 138 0 discriminator 1
	movw r24,r28
	call read_word
.LVL27:
	adiw r28,1
	rjmp .L24
	.cfi_endproc
.LFE16:
	.size	main, .-main
	.text
.Letext0:
	.file 2 "c:\\program files (x86)\\atmel\\studio\\7.0\\toolchain\\avr8\\avr8-gnu-toolchain\\avr\\include\\stdint.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x2c3
	.word	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF23
	.byte	0x1
	.long	.LASF24
	.long	.LASF25
	.long	.Ldebug_ranges0+0
	.long	0
	.long	0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF0
	.uleb128 0x3
	.long	.LASF2
	.byte	0x2
	.byte	0x7e
	.long	0x3b
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x4
	.byte	0x2
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.long	.LASF3
	.byte	0x2
	.byte	0x80
	.long	0x54
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF4
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF5
	.uleb128 0x3
	.long	.LASF6
	.byte	0x2
	.byte	0x82
	.long	0x6d
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF9
	.uleb128 0x5
	.byte	0x1
	.long	.LASF17
	.byte	0x1
	.byte	0x13
	.byte	0x1
	.long	.LFB6
	.long	.LFE6
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0x6
	.byte	0x1
	.string	"spi"
	.byte	0x1
	.byte	0x1c
	.byte	0x1
	.long	0x49
	.long	.LFB7
	.long	.LFE7
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0xd5
	.uleb128 0x7
	.long	.LASF13
	.byte	0x1
	.byte	0x1c
	.long	0x49
	.long	.LLST0
	.uleb128 0x8
	.long	.LASF10
	.byte	0x1
	.byte	0x1d
	.long	0x49
	.long	.LLST1
	.byte	0
	.uleb128 0x9
	.byte	0x1
	.long	.LASF11
	.byte	0x1
	.byte	0x28
	.long	0x49
	.long	.LFB8
	.long	.LFE8
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x102
	.uleb128 0x8
	.long	.LASF10
	.byte	0x1
	.byte	0x29
	.long	0x49
	.long	.LLST2
	.byte	0
	.uleb128 0xa
	.byte	0x1
	.long	.LASF12
	.byte	0x1
	.byte	0x34
	.byte	0x1
	.long	.LFB9
	.long	.LFE9
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x12f
	.uleb128 0xb
	.long	.LASF13
	.byte	0x1
	.byte	0x34
	.long	0x49
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0
	.uleb128 0xa
	.byte	0x1
	.long	.LASF14
	.byte	0x1
	.byte	0x3b
	.byte	0x1
	.long	.LFB10
	.long	.LFE10
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x162
	.uleb128 0x7
	.long	.LASF15
	.byte	0x1
	.byte	0x3b
	.long	0x62
	.long	.LLST3
	.uleb128 0xc
	.long	.LVL11
	.long	0x102
	.byte	0
	.uleb128 0xd
	.byte	0x1
	.long	.LASF16
	.byte	0x1
	.byte	0x40
	.byte	0x1
	.long	0x49
	.long	.LFB11
	.long	.LFE11
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.long	0x19a
	.uleb128 0xe
	.string	"r"
	.byte	0x1
	.byte	0x44
	.long	0x49
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.uleb128 0xc
	.long	.LVL12
	.long	0xd5
	.byte	0
	.uleb128 0x5
	.byte	0x1
	.long	.LASF18
	.byte	0x1
	.byte	0x49
	.byte	0x1
	.long	.LFB12
	.long	.LFE12
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0x5
	.byte	0x1
	.long	.LASF19
	.byte	0x1
	.byte	0x59
	.byte	0x1
	.long	.LFB13
	.long	.LFE13
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0xf
	.byte	0x1
	.long	.LASF20
	.byte	0x1
	.byte	0x63
	.byte	0x1
	.long	0x49
	.long	.LFB14
	.long	.LFE14
	.long	.LLST4
	.byte	0x1
	.long	0x221
	.uleb128 0x7
	.long	.LASF15
	.byte	0x1
	.byte	0x63
	.long	0x49
	.long	.LLST5
	.uleb128 0x10
	.long	.LASF10
	.byte	0x1
	.byte	0x64
	.long	0x49
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.uleb128 0xc
	.long	.LVL14
	.long	0x19a
	.uleb128 0xc
	.long	.LVL15
	.long	0x12f
	.uleb128 0xc
	.long	.LVL16
	.long	0x162
	.byte	0
	.uleb128 0x11
	.byte	0x1
	.long	.LASF21
	.byte	0x1
	.byte	0x71
	.byte	0x1
	.long	.LFB15
	.long	.LFE15
	.long	.LLST6
	.byte	0x1
	.long	0x275
	.uleb128 0x7
	.long	.LASF15
	.byte	0x1
	.byte	0x71
	.long	0x49
	.long	.LLST7
	.uleb128 0x7
	.long	.LASF13
	.byte	0x1
	.byte	0x71
	.long	0x49
	.long	.LLST8
	.uleb128 0xc
	.long	.LVL19
	.long	0x19a
	.uleb128 0xc
	.long	.LVL20
	.long	0x12f
	.uleb128 0xc
	.long	.LVL21
	.long	0x12f
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF22
	.byte	0x1
	.byte	0x7d
	.byte	0x1
	.long	0x42
	.long	.LFB16
	.long	.LFE16
	.byte	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.byte	0x1
	.uleb128 0x8
	.long	.LASF15
	.byte	0x1
	.byte	0x80
	.long	0x62
	.long	.LLST9
	.uleb128 0xc
	.long	.LVL24
	.long	0x82
	.uleb128 0xc
	.long	.LVL25
	.long	0x19a
	.uleb128 0x13
	.long	.LVL27
	.long	0x1c6
	.uleb128 0x14
	.byte	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.byte	0x2
	.byte	0x8c
	.sleb128 0
	.byte	0
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
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
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
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
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
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
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
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
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
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
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
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x6
	.uleb128 0x2117
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x2117
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0xa
	.uleb128 0x2111
	.uleb128 0xa
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LVL0
	.long	.LVL2
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL2
	.long	.LFE7
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST1:
	.long	.LVL1
	.long	.LVL2
	.word	0x6
	.byte	0x62
	.byte	0x93
	.uleb128 0x1
	.byte	0x63
	.byte	0x93
	.uleb128 0x1
	.long	.LVL2
	.long	.LVL3
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL3
	.long	.LVL4
	.word	0x9
	.byte	0x82
	.sleb128 0
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x88
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.long	0
	.long	0
.LLST2:
	.long	.LVL5
	.long	.LVL7
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL7
	.long	.LVL8
	.word	0x9
	.byte	0x82
	.sleb128 0
	.byte	0x8
	.byte	0xff
	.byte	0x1a
	.byte	0x88
	.sleb128 0
	.byte	0x21
	.byte	0x9f
	.long	0
	.long	0
.LLST3:
	.long	.LVL10
	.long	.LVL11-1
	.word	0xc
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL11-1
	.long	.LFE10
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x66
	.byte	0x9f
	.long	0
	.long	0
.LLST4:
	.long	.LFB14
	.long	.LCFI0
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI0
	.long	.LCFI1
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI1
	.long	.LFE14
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	0
	.long	0
.LLST5:
	.long	.LVL13
	.long	.LVL14-1
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL14-1
	.long	.LVL17
	.word	0x6
	.byte	0x6c
	.byte	0x93
	.uleb128 0x1
	.byte	0x6d
	.byte	0x93
	.uleb128 0x1
	.long	.LVL17
	.long	.LFE14
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST6:
	.long	.LFB15
	.long	.LCFI2
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 2
	.long	.LCFI2
	.long	.LCFI3
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 3
	.long	.LCFI3
	.long	.LCFI4
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 4
	.long	.LCFI4
	.long	.LCFI5
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 5
	.long	.LCFI5
	.long	.LFE15
	.word	0x3
	.byte	0x92
	.uleb128 0x20
	.sleb128 6
	.long	0
	.long	0
.LLST7:
	.long	.LVL18
	.long	.LVL19-1
	.word	0x6
	.byte	0x68
	.byte	0x93
	.uleb128 0x1
	.byte	0x69
	.byte	0x93
	.uleb128 0x1
	.long	.LVL19-1
	.long	.LVL23
	.word	0x6
	.byte	0x60
	.byte	0x93
	.uleb128 0x1
	.byte	0x61
	.byte	0x93
	.uleb128 0x1
	.long	.LVL23
	.long	.LFE15
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x68
	.byte	0x9f
	.long	0
	.long	0
.LLST8:
	.long	.LVL18
	.long	.LVL19-1
	.word	0x6
	.byte	0x66
	.byte	0x93
	.uleb128 0x1
	.byte	0x67
	.byte	0x93
	.uleb128 0x1
	.long	.LVL19-1
	.long	.LVL22
	.word	0x6
	.byte	0x6c
	.byte	0x93
	.uleb128 0x1
	.byte	0x6d
	.byte	0x93
	.uleb128 0x1
	.long	.LVL22
	.long	.LFE15
	.word	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x66
	.byte	0x9f
	.long	0
	.long	0
.LLST9:
	.long	.LVL25
	.long	.LVL26
	.word	0x2
	.byte	0x30
	.byte	0x9f
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x6c
	.word	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.word	0
	.word	0
	.long	.LFB6
	.long	.LFE6-.LFB6
	.long	.LFB7
	.long	.LFE7-.LFB7
	.long	.LFB8
	.long	.LFE8-.LFB8
	.long	.LFB9
	.long	.LFE9-.LFB9
	.long	.LFB10
	.long	.LFE10-.LFB10
	.long	.LFB11
	.long	.LFE11-.LFB11
	.long	.LFB12
	.long	.LFE12-.LFB12
	.long	.LFB13
	.long	.LFE13-.LFB13
	.long	.LFB14
	.long	.LFE14-.LFB14
	.long	.LFB15
	.long	.LFE15-.LFB15
	.long	.LFB16
	.long	.LFE16-.LFB16
	.long	0
	.long	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LFB6
	.long	.LFE6
	.long	.LFB7
	.long	.LFE7
	.long	.LFB8
	.long	.LFE8
	.long	.LFB9
	.long	.LFE9
	.long	.LFB10
	.long	.LFE10
	.long	.LFB11
	.long	.LFE11
	.long	.LFB12
	.long	.LFE12
	.long	.LFB13
	.long	.LFE13
	.long	.LFB14
	.long	.LFE14
	.long	.LFB15
	.long	.LFE15
	.long	.LFB16
	.long	.LFE16
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF24:
	.string	".././main.c"
.LASF25:
	.string	"C:\\\\Users\\\\Eldad\\\\Desktop\\\\folders\\\\hobbys\\\\Programing\\\\8086\\\\coprocessor\\\\AtMega328P Coprocessor V2\\\\AtMega328P Coprocessor V2\\\\Debug"
.LASF19:
	.string	"release_bus"
.LASF13:
	.string	"data"
.LASF12:
	.string	"spi_send"
.LASF1:
	.string	"unsigned char"
.LASF16:
	.string	"ad_get"
.LASF7:
	.string	"long unsigned int"
.LASF14:
	.string	"ad_set"
.LASF22:
	.string	"main"
.LASF11:
	.string	"spi_recieve"
.LASF4:
	.string	"unsigned int"
.LASF15:
	.string	"address"
.LASF9:
	.string	"long long unsigned int"
.LASF2:
	.string	"uint8_t"
.LASF10:
	.string	"result"
.LASF23:
	.string	"GNU C 4.9.2 -fpreprocessed -mn-flash=1 -mno-skip-bug -mmcu=avr5 -g2 -O1 -std=gnu99 -funsigned-char -funsigned-bitfields -ffunction-sections -fdata-sections -fpack-struct -fshort-enums"
.LASF8:
	.string	"long long int"
.LASF17:
	.string	"init_spi"
.LASF3:
	.string	"uint16_t"
.LASF20:
	.string	"read_word"
.LASF6:
	.string	"uint32_t"
.LASF5:
	.string	"long int"
.LASF18:
	.string	"hold_bus"
.LASF0:
	.string	"signed char"
.LASF21:
	.string	"write_word"
	.ident	"GCC: (AVR_8_bit_GNU_Toolchain_3.5.4_1709) 4.9.2"
