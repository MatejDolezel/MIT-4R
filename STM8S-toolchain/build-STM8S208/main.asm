;--------------------------------------------------------
; File Created by SDCC : free open source ISO C Compiler 
; Version 4.4.0 #14620 (Linux)
;--------------------------------------------------------
	.module main
	.optsdcc -mstm8
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _GPIO_WriteLow
	.globl _GPIO_WriteHigh
	.globl _GPIO_Init
	.globl _max7219_init
	.globl _max7219_posli
	.globl _delay
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area DATA
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area INITIALIZED
;--------------------------------------------------------
; Stack segment in internal ram
;--------------------------------------------------------
	.area SSEG
__start__stack:
	.ds	1

;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area DABS (ABS)

; default segment ordering for linker
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area CONST
	.area INITIALIZER
	.area CODE

;--------------------------------------------------------
; interrupt vector
;--------------------------------------------------------
	.area HOME
__interrupt_vect:
	int s_GSINIT ; reset
	int _TRAP_IRQHandler ; trap
	int _TLI_IRQHandler ; int0
	int _AWU_IRQHandler ; int1
	int _CLK_IRQHandler ; int2
	int _EXTI_PORTA_IRQHandler ; int3
	int _EXTI_PORTB_IRQHandler ; int4
	int _EXTI_PORTC_IRQHandler ; int5
	int _EXTI_PORTD_IRQHandler ; int6
	int _EXTI_PORTE_IRQHandler ; int7
	int _CAN_RX_IRQHandler ; int8
	int _CAN_TX_IRQHandler ; int9
	int _SPI_IRQHandler ; int10
	int _TIM1_UPD_OVF_TRG_BRK_IRQHandler ; int11
	int _TIM1_CAP_COM_IRQHandler ; int12
	int _TIM2_UPD_OVF_BRK_IRQHandler ; int13
	int _TIM2_CAP_COM_IRQHandler ; int14
	int _TIM3_UPD_OVF_BRK_IRQHandler ; int15
	int _TIM3_CAP_COM_IRQHandler ; int16
	int _UART1_TX_IRQHandler ; int17
	int _UART1_RX_IRQHandler ; int18
	int _I2C_IRQHandler ; int19
	int _UART3_TX_IRQHandler ; int20
	int _UART3_RX_IRQHandler ; int21
	int _ADC2_IRQHandler ; int22
	int _TIM4_UPD_OVF_IRQHandler ; int23
	int _EEPROM_EEC_IRQHandler ; int24
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME
	.area GSINIT
	.area GSFINAL
	.area GSINIT
	call	___sdcc_external_startup
	tnz	a
	jreq	__sdcc_init_data
	jp	__sdcc_program_startup
__sdcc_init_data:
; stm8_genXINIT() start
	ldw x, #l_DATA
	jreq	00002$
00001$:
	clr (s_DATA - 1, x)
	decw x
	jrne	00001$
00002$:
	ldw	x, #l_INITIALIZER
	jreq	00004$
00003$:
	ld	a, (s_INITIALIZER - 1, x)
	ld	(s_INITIALIZED - 1, x), a
	decw	x
	jrne	00003$
00004$:
; stm8_genXINIT() end
	.area GSFINAL
	jp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME
	.area HOME
__sdcc_program_startup:
	jp	_main
;	return from main will return to caller
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CODE
;	./src/main.c: 36: void main(void) {
; genLabel
;	-----------------------------------------
;	 function main
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 0 bytes.
_main:
;	./src/main.c: 37: uint8_t cislo = 0;
; genAssign
	clr	a
;	./src/main.c: 39: max7219_init();
; genCall
	push	a
	call	_max7219_init
	pop	a
;	./src/main.c: 41: while (1) {
; genLabel
00102$:
;	./src/main.c: 42: max7219_posli(DIGIT0, cislo);
; genIPush
	push	a
	push	a
; genSend
	ld	a, #0x01
; genCall
	call	_max7219_posli
	pop	a
;	./src/main.c: 44: cislo = (cislo + 1) % 10;
; genCast
; genAssign
	clrw	x
; genPlus
	ld	xl, a
	incw	x
; genIPush
	push	#0x0a
	push	#0x00
; genSend
; genCall
	call	__modsint
	ld	a, xl
; genCast
; genAssign
;	./src/main.c: 46: delay(500);
; genIPush
	push	a
	push	#0xf4
	push	#0x01
	clrw	x
	pushw	x
; genCall
	call	_delay
	pop	a
; genGoto
	jp	00102$
; genLabel
00104$:
;	./src/main.c: 48: }
; genEndFunction
	ret
;	./src/main.c: 50: void max7219_init(void) {
; genLabel
;	-----------------------------------------
;	 function max7219_init
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 0 bytes.
_max7219_init:
;	./src/main.c: 52: GPIO_Init(CS_GPIO, CS_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
; genIPush
	push	#0xc0
; genSend
	ld	a, #0x04
; genSend
	ldw	x, #0x500f
; genCall
	call	_GPIO_Init
;	./src/main.c: 53: GPIO_Init(CLK_GPIO, CLK_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
; genIPush
	push	#0xc0
; genSend
	ld	a, #0x10
; genSend
	ldw	x, #0x500f
; genCall
	call	_GPIO_Init
;	./src/main.c: 54: GPIO_Init(DATA_GPIO, DATA_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
; genIPush
	push	#0xc0
; genSend
	ld	a, #0x08
; genSend
	ldw	x, #0x500f
; genCall
	call	_GPIO_Init
;	./src/main.c: 57: max7219_posli(DECODE_MODE, DECODE_ALL);  // zapnutí znakového režimu
; genIPush
	push	#0xff
; genSend
	ld	a, #0x09
; genCall
	call	_max7219_posli
;	./src/main.c: 58: max7219_posli(SCAN_LIMIT, 0);           // Používám jen jednu cifru
; genIPush
	push	#0x00
; genSend
	ld	a, #0x0b
; genCall
	call	_max7219_posli
;	./src/main.c: 59: max7219_posli(INTENSITY, 1);            // Nízký jas
; genIPush
	push	#0x01
; genSend
	ld	a, #0x0a
; genCall
	call	_max7219_posli
;	./src/main.c: 60: max7219_posli(DISPLAY_TEST, DISPLAY_TEST_OFF); // Vypnutí testu
; genIPush
	push	#0x00
; genSend
	ld	a, #0x0f
; genCall
	call	_max7219_posli
;	./src/main.c: 61: max7219_posli(SHUTDOWN, DISPLAY_ON);    // Zapnutí displeje
; genIPush
	push	#0x01
; genSend
	ld	a, #0x0c
; genCall
	call	_max7219_posli
; genLabel
00101$:
;	./src/main.c: 62: }
; genEndFunction
	ret
;	./src/main.c: 64: void max7219_posli(uint8_t adresa, uint8_t data) {
; genLabel
;	-----------------------------------------
;	 function max7219_posli
;	-----------------------------------------
;	Register assignment is optimal.
;	Stack space usage: 2 bytes.
_max7219_posli:
	pushw	x
; genReceive
	ld	(0x01, sp), a
;	./src/main.c: 67: CS_LOW; // Aktivace komunikace (LOAD/CS do Low)
; genSend
	ld	a, #0x04
; genSend
	ldw	x, #0x500f
; genCall
	call	_GPIO_WriteLow
;	./src/main.c: 70: maska = 0x80;
; genAssign
	ld	a, #0x80
	ld	(0x02, sp), a
;	./src/main.c: 71: while (maska) {
; genLabel
00104$:
; genIfx
	tnz	(0x02, sp)
	jrne	00157$
	jp	00106$
00157$:
;	./src/main.c: 72: if (maska & adresa) {
; genAnd
	ld	a, (0x02, sp)
	and	a, (0x01, sp)
; genIfx
	tnz	a
	jrne	00158$
	jp	00102$
00158$:
;	./src/main.c: 73: DATA_HIGH;
; genSend
	ld	a, #0x08
; genSend
	ldw	x, #0x500f
; genCall
	call	_GPIO_WriteHigh
; genGoto
	jp	00103$
; genLabel
00102$:
;	./src/main.c: 75: DATA_LOW;
; genSend
	ld	a, #0x08
; genSend
	ldw	x, #0x500f
; genCall
	call	_GPIO_WriteLow
; genLabel
00103$:
;	./src/main.c: 77: CLK_HIGH;
; genSend
	ld	a, #0x10
; genSend
	ldw	x, #0x500f
; genCall
	call	_GPIO_WriteHigh
;	./src/main.c: 78: CLK_LOW;
; genSend
	ld	a, #0x10
; genSend
	ldw	x, #0x500f
; genCall
	call	_GPIO_WriteLow
;	./src/main.c: 79: maska >>= 1;
; genRightShiftLiteral
	srl	(0x02, sp)
; genGoto
	jp	00104$
; genLabel
00106$:
;	./src/main.c: 83: maska = 0x80;
; genAssign
	ld	a, #0x80
	ld	(0x02, sp), a
;	./src/main.c: 84: while (maska) {
; genLabel
00110$:
; genIfx
	tnz	(0x02, sp)
	jrne	00159$
	jp	00112$
00159$:
;	./src/main.c: 85: if (maska & data) {
; genAnd
	ld	a, (0x02, sp)
	and	a, (0x05, sp)
; genIfx
	tnz	a
	jrne	00160$
	jp	00108$
00160$:
;	./src/main.c: 86: DATA_HIGH;
; genSend
	ld	a, #0x08
; genSend
	ldw	x, #0x500f
; genCall
	call	_GPIO_WriteHigh
; genGoto
	jp	00109$
; genLabel
00108$:
;	./src/main.c: 88: DATA_LOW;
; genSend
	ld	a, #0x08
; genSend
	ldw	x, #0x500f
; genCall
	call	_GPIO_WriteLow
; genLabel
00109$:
;	./src/main.c: 90: CLK_HIGH; 
; genSend
	ld	a, #0x10
; genSend
	ldw	x, #0x500f
; genCall
	call	_GPIO_WriteHigh
;	./src/main.c: 91: CLK_LOW;
; genSend
	ld	a, #0x10
; genSend
	ldw	x, #0x500f
; genCall
	call	_GPIO_WriteLow
;	./src/main.c: 92: maska >>= 1;
; genRightShiftLiteral
	srl	(0x02, sp)
; genGoto
	jp	00110$
; genLabel
00112$:
;	./src/main.c: 95: CS_HIGH; // Deaktivace komunikace (LOAD/CS do High)
; genSend
	ld	a, #0x04
; genSend
	ldw	x, #0x500f
; genCall
	call	_GPIO_WriteHigh
; genLabel
00113$:
;	./src/main.c: 96: }
; genEndFunction
	popw	x
	popw	x
	pop	a
	jp	(x)
;	./src/main.c: 98: void delay(uint32_t ms) {
; genLabel
;	-----------------------------------------
;	 function delay
;	-----------------------------------------
;	Register assignment might be sub-optimal.
;	Stack space usage: 8 bytes.
_delay:
	sub	sp, #8
;	./src/main.c: 99: while (ms--) {
; genAssign
	ldw	y, (0x0b, sp)
	ldw	(0x01, sp), y
	ldw	y, (0x0d, sp)
; genLabel
00102$:
; genAssign
	ldw	(0x07, sp), y
	ldw	x, (0x01, sp)
	ldw	(0x05, sp), x
; genMinus
	subw	y, #0x0001
	ldw	x, (0x01, sp)
	jrnc	00139$
	decw	x
00139$:
	ldw	(0x01, sp), x
; genIfx
	ldw	x, (0x07, sp)
	jrne	00140$
	ldw	x, (0x05, sp)
	jrne	00140$
	jp	00108$
00140$:
;	./src/main.c: 100: for (uint32_t i = 0; i < 200; i++) {
; genAssign
	clrw	x
	ldw	(0x07, sp), x
	ldw	(0x05, sp), x
; genLabel
00106$:
; genCmp
; genCmpTnz
	ldw	x, (0x07, sp)
	cpw	x, #0x00c8
	ld	a, (0x06, sp)
	sbc	a, #0x00
	ld	a, (0x05, sp)
	sbc	a, #0x00
	jrc	00141$
	jp	00102$
00141$:
; skipping generated iCode
;	./src/main.c: 101: __asm__("nop");
;	genInline
	nop
;	./src/main.c: 100: for (uint32_t i = 0; i < 200; i++) {
; genPlus
	ldw	x, (0x07, sp)
	incw	x
	ldw	(0x07, sp), x
	jrne	00142$
	ldw	x, (0x05, sp)
	incw	x
	ldw	(0x05, sp), x
00142$:
; genGoto
	jp	00106$
; genLabel
00108$:
;	./src/main.c: 104: }
; genEndFunction
	ldw	x, (9, sp)
	addw	sp, #14
	jp	(x)
	.area CODE
	.area CONST
	.area INITIALIZER
	.area CABS (ABS)
