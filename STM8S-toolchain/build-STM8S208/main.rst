                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ISO C Compiler 
                                      3 ; Version 4.4.0 #14620 (Linux)
                                      4 ;--------------------------------------------------------
                                      5 	.module main
                                      6 	.optsdcc -mstm8
                                      7 	
                                      8 ;--------------------------------------------------------
                                      9 ; Public variables in this module
                                     10 ;--------------------------------------------------------
                                     11 	.globl _main
                                     12 	.globl _GPIO_WriteLow
                                     13 	.globl _GPIO_WriteHigh
                                     14 	.globl _GPIO_Init
                                     15 	.globl _max7219_init
                                     16 	.globl _max7219_posli
                                     17 	.globl _delay
                                     18 ;--------------------------------------------------------
                                     19 ; ram data
                                     20 ;--------------------------------------------------------
                                     21 	.area DATA
                                     22 ;--------------------------------------------------------
                                     23 ; ram data
                                     24 ;--------------------------------------------------------
                                     25 	.area INITIALIZED
                                     26 ;--------------------------------------------------------
                                     27 ; Stack segment in internal ram
                                     28 ;--------------------------------------------------------
                                     29 	.area SSEG
      0085E9                         30 __start__stack:
      0085E9                         31 	.ds	1
                                     32 
                                     33 ;--------------------------------------------------------
                                     34 ; absolute external ram data
                                     35 ;--------------------------------------------------------
                                     36 	.area DABS (ABS)
                                     37 
                                     38 ; default segment ordering for linker
                                     39 	.area HOME
                                     40 	.area GSINIT
                                     41 	.area GSFINAL
                                     42 	.area CONST
                                     43 	.area INITIALIZER
                                     44 	.area CODE
                                     45 
                                     46 ;--------------------------------------------------------
                                     47 ; interrupt vector
                                     48 ;--------------------------------------------------------
                                     49 	.area HOME
      008000                         50 __interrupt_vect:
      008000 82 00 80 6F             51 	int s_GSINIT ; reset
      008004 82 00 82 EC             52 	int _TRAP_IRQHandler ; trap
      008008 82 00 82 ED             53 	int _TLI_IRQHandler ; int0
      00800C 82 00 82 EE             54 	int _AWU_IRQHandler ; int1
      008010 82 00 82 EF             55 	int _CLK_IRQHandler ; int2
      008014 82 00 82 F0             56 	int _EXTI_PORTA_IRQHandler ; int3
      008018 82 00 82 F1             57 	int _EXTI_PORTB_IRQHandler ; int4
      00801C 82 00 82 F2             58 	int _EXTI_PORTC_IRQHandler ; int5
      008020 82 00 82 F3             59 	int _EXTI_PORTD_IRQHandler ; int6
      008024 82 00 82 F4             60 	int _EXTI_PORTE_IRQHandler ; int7
      008028 82 00 82 F5             61 	int _CAN_RX_IRQHandler ; int8
      00802C 82 00 82 F6             62 	int _CAN_TX_IRQHandler ; int9
      008030 82 00 82 F7             63 	int _SPI_IRQHandler ; int10
      008034 82 00 82 F8             64 	int _TIM1_UPD_OVF_TRG_BRK_IRQHandler ; int11
      008038 82 00 82 F9             65 	int _TIM1_CAP_COM_IRQHandler ; int12
      00803C 82 00 82 FA             66 	int _TIM2_UPD_OVF_BRK_IRQHandler ; int13
      008040 82 00 82 FB             67 	int _TIM2_CAP_COM_IRQHandler ; int14
      008044 82 00 82 FC             68 	int _TIM3_UPD_OVF_BRK_IRQHandler ; int15
      008048 82 00 82 FD             69 	int _TIM3_CAP_COM_IRQHandler ; int16
      00804C 82 00 82 FE             70 	int _UART1_TX_IRQHandler ; int17
      008050 82 00 82 FF             71 	int _UART1_RX_IRQHandler ; int18
      008054 82 00 83 00             72 	int _I2C_IRQHandler ; int19
      008058 82 00 83 01             73 	int _UART3_TX_IRQHandler ; int20
      00805C 82 00 83 02             74 	int _UART3_RX_IRQHandler ; int21
      008060 82 00 83 03             75 	int _ADC2_IRQHandler ; int22
      008064 82 00 83 04             76 	int _TIM4_UPD_OVF_IRQHandler ; int23
      008068 82 00 83 1E             77 	int _EEPROM_EEC_IRQHandler ; int24
                                     78 ;--------------------------------------------------------
                                     79 ; global & static initialisations
                                     80 ;--------------------------------------------------------
                                     81 	.area HOME
                                     82 	.area GSINIT
                                     83 	.area GSFINAL
                                     84 	.area GSINIT
      00806F CD 84 30         [ 4]   85 	call	___sdcc_external_startup
      008072 4D               [ 1]   86 	tnz	a
      008073 27 03            [ 1]   87 	jreq	__sdcc_init_data
      008075 CC 80 6C         [ 2]   88 	jp	__sdcc_program_startup
      008078                         89 __sdcc_init_data:
                                     90 ; stm8_genXINIT() start
      008078 AE 00 00         [ 2]   91 	ldw x, #l_DATA
      00807B 27 07            [ 1]   92 	jreq	00002$
      00807D                         93 00001$:
      00807D 72 4F 00 00      [ 1]   94 	clr (s_DATA - 1, x)
      008081 5A               [ 2]   95 	decw x
      008082 26 F9            [ 1]   96 	jrne	00001$
      008084                         97 00002$:
      008084 AE 00 04         [ 2]   98 	ldw	x, #l_INITIALIZER
      008087 27 09            [ 1]   99 	jreq	00004$
      008089                        100 00003$:
      008089 D6 80 94         [ 1]  101 	ld	a, (s_INITIALIZER - 1, x)
      00808C D7 00 00         [ 1]  102 	ld	(s_INITIALIZED - 1, x), a
      00808F 5A               [ 2]  103 	decw	x
      008090 26 F7            [ 1]  104 	jrne	00003$
      008092                        105 00004$:
                                    106 ; stm8_genXINIT() end
                                    107 	.area GSFINAL
      008092 CC 80 6C         [ 2]  108 	jp	__sdcc_program_startup
                                    109 ;--------------------------------------------------------
                                    110 ; Home
                                    111 ;--------------------------------------------------------
                                    112 	.area HOME
                                    113 	.area HOME
      00806C                        114 __sdcc_program_startup:
      00806C CC 81 60         [ 2]  115 	jp	_main
                                    116 ;	return from main will return to caller
                                    117 ;--------------------------------------------------------
                                    118 ; code
                                    119 ;--------------------------------------------------------
                                    120 	.area CODE
                                    121 ;	./src/main.c: 36: void main(void) {
                                    122 ; genLabel
                                    123 ;	-----------------------------------------
                                    124 ;	 function main
                                    125 ;	-----------------------------------------
                                    126 ;	Register assignment might be sub-optimal.
                                    127 ;	Stack space usage: 0 bytes.
      008160                        128 _main:
                                    129 ;	./src/main.c: 37: uint8_t cislo = 0;
                                    130 ; genAssign
      008160 4F               [ 1]  131 	clr	a
                                    132 ;	./src/main.c: 39: max7219_init();
                                    133 ; genCall
      008161 88               [ 1]  134 	push	a
      008162 CD 81 88         [ 4]  135 	call	_max7219_init
      008165 84               [ 1]  136 	pop	a
                                    137 ;	./src/main.c: 41: while (1) {
                                    138 ; genLabel
      008166                        139 00102$:
                                    140 ;	./src/main.c: 42: max7219_posli(DIGIT0, cislo);
                                    141 ; genIPush
      008166 88               [ 1]  142 	push	a
      008167 88               [ 1]  143 	push	a
                                    144 ; genSend
      008168 A6 01            [ 1]  145 	ld	a, #0x01
                                    146 ; genCall
      00816A CD 81 CA         [ 4]  147 	call	_max7219_posli
      00816D 84               [ 1]  148 	pop	a
                                    149 ;	./src/main.c: 44: cislo = (cislo + 1) % 10;
                                    150 ; genCast
                                    151 ; genAssign
      00816E 5F               [ 1]  152 	clrw	x
                                    153 ; genPlus
      00816F 97               [ 1]  154 	ld	xl, a
      008170 5C               [ 1]  155 	incw	x
                                    156 ; genIPush
      008171 4B 0A            [ 1]  157 	push	#0x0a
      008173 4B 00            [ 1]  158 	push	#0x00
                                    159 ; genSend
                                    160 ; genCall
      008175 CD 85 50         [ 4]  161 	call	__modsint
      008178 9F               [ 1]  162 	ld	a, xl
                                    163 ; genCast
                                    164 ; genAssign
                                    165 ;	./src/main.c: 46: delay(500);
                                    166 ; genIPush
      008179 88               [ 1]  167 	push	a
      00817A 4B F4            [ 1]  168 	push	#0xf4
      00817C 4B 01            [ 1]  169 	push	#0x01
      00817E 5F               [ 1]  170 	clrw	x
      00817F 89               [ 2]  171 	pushw	x
                                    172 ; genCall
      008180 CD 82 5B         [ 4]  173 	call	_delay
      008183 84               [ 1]  174 	pop	a
                                    175 ; genGoto
      008184 CC 81 66         [ 2]  176 	jp	00102$
                                    177 ; genLabel
      008187                        178 00104$:
                                    179 ;	./src/main.c: 48: }
                                    180 ; genEndFunction
      008187 81               [ 4]  181 	ret
                                    182 ;	./src/main.c: 50: void max7219_init(void) {
                                    183 ; genLabel
                                    184 ;	-----------------------------------------
                                    185 ;	 function max7219_init
                                    186 ;	-----------------------------------------
                                    187 ;	Register assignment is optimal.
                                    188 ;	Stack space usage: 0 bytes.
      008188                        189 _max7219_init:
                                    190 ;	./src/main.c: 52: GPIO_Init(CS_GPIO, CS_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
                                    191 ; genIPush
      008188 4B C0            [ 1]  192 	push	#0xc0
                                    193 ; genSend
      00818A A6 04            [ 1]  194 	ld	a, #0x04
                                    195 ; genSend
      00818C AE 50 0F         [ 2]  196 	ldw	x, #0x500f
                                    197 ; genCall
      00818F CD 83 1F         [ 4]  198 	call	_GPIO_Init
                                    199 ;	./src/main.c: 53: GPIO_Init(CLK_GPIO, CLK_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
                                    200 ; genIPush
      008192 4B C0            [ 1]  201 	push	#0xc0
                                    202 ; genSend
      008194 A6 10            [ 1]  203 	ld	a, #0x10
                                    204 ; genSend
      008196 AE 50 0F         [ 2]  205 	ldw	x, #0x500f
                                    206 ; genCall
      008199 CD 83 1F         [ 4]  207 	call	_GPIO_Init
                                    208 ;	./src/main.c: 54: GPIO_Init(DATA_GPIO, DATA_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
                                    209 ; genIPush
      00819C 4B C0            [ 1]  210 	push	#0xc0
                                    211 ; genSend
      00819E A6 08            [ 1]  212 	ld	a, #0x08
                                    213 ; genSend
      0081A0 AE 50 0F         [ 2]  214 	ldw	x, #0x500f
                                    215 ; genCall
      0081A3 CD 83 1F         [ 4]  216 	call	_GPIO_Init
                                    217 ;	./src/main.c: 57: max7219_posli(DECODE_MODE, DECODE_ALL);  // zapnutí znakového režimu
                                    218 ; genIPush
      0081A6 4B FF            [ 1]  219 	push	#0xff
                                    220 ; genSend
      0081A8 A6 09            [ 1]  221 	ld	a, #0x09
                                    222 ; genCall
      0081AA CD 81 CA         [ 4]  223 	call	_max7219_posli
                                    224 ;	./src/main.c: 58: max7219_posli(SCAN_LIMIT, 0);           // Používám jen jednu cifru
                                    225 ; genIPush
      0081AD 4B 00            [ 1]  226 	push	#0x00
                                    227 ; genSend
      0081AF A6 0B            [ 1]  228 	ld	a, #0x0b
                                    229 ; genCall
      0081B1 CD 81 CA         [ 4]  230 	call	_max7219_posli
                                    231 ;	./src/main.c: 59: max7219_posli(INTENSITY, 1);            // Nízký jas
                                    232 ; genIPush
      0081B4 4B 01            [ 1]  233 	push	#0x01
                                    234 ; genSend
      0081B6 A6 0A            [ 1]  235 	ld	a, #0x0a
                                    236 ; genCall
      0081B8 CD 81 CA         [ 4]  237 	call	_max7219_posli
                                    238 ;	./src/main.c: 60: max7219_posli(DISPLAY_TEST, DISPLAY_TEST_OFF); // Vypnutí testu
                                    239 ; genIPush
      0081BB 4B 00            [ 1]  240 	push	#0x00
                                    241 ; genSend
      0081BD A6 0F            [ 1]  242 	ld	a, #0x0f
                                    243 ; genCall
      0081BF CD 81 CA         [ 4]  244 	call	_max7219_posli
                                    245 ;	./src/main.c: 61: max7219_posli(SHUTDOWN, DISPLAY_ON);    // Zapnutí displeje
                                    246 ; genIPush
      0081C2 4B 01            [ 1]  247 	push	#0x01
                                    248 ; genSend
      0081C4 A6 0C            [ 1]  249 	ld	a, #0x0c
                                    250 ; genCall
      0081C6 CD 81 CA         [ 4]  251 	call	_max7219_posli
                                    252 ; genLabel
      0081C9                        253 00101$:
                                    254 ;	./src/main.c: 62: }
                                    255 ; genEndFunction
      0081C9 81               [ 4]  256 	ret
                                    257 ;	./src/main.c: 64: void max7219_posli(uint8_t adresa, uint8_t data) {
                                    258 ; genLabel
                                    259 ;	-----------------------------------------
                                    260 ;	 function max7219_posli
                                    261 ;	-----------------------------------------
                                    262 ;	Register assignment is optimal.
                                    263 ;	Stack space usage: 2 bytes.
      0081CA                        264 _max7219_posli:
      0081CA 89               [ 2]  265 	pushw	x
                                    266 ; genReceive
      0081CB 6B 01            [ 1]  267 	ld	(0x01, sp), a
                                    268 ;	./src/main.c: 67: CS_LOW; // Aktivace komunikace (LOAD/CS do Low)
                                    269 ; genSend
      0081CD A6 04            [ 1]  270 	ld	a, #0x04
                                    271 ; genSend
      0081CF AE 50 0F         [ 2]  272 	ldw	x, #0x500f
                                    273 ; genCall
      0081D2 CD 84 24         [ 4]  274 	call	_GPIO_WriteLow
                                    275 ;	./src/main.c: 70: maska = 0x80;
                                    276 ; genAssign
      0081D5 A6 80            [ 1]  277 	ld	a, #0x80
      0081D7 6B 02            [ 1]  278 	ld	(0x02, sp), a
                                    279 ;	./src/main.c: 71: while (maska) {
                                    280 ; genLabel
      0081D9                        281 00104$:
                                    282 ; genIfx
      0081D9 0D 02            [ 1]  283 	tnz	(0x02, sp)
      0081DB 26 03            [ 1]  284 	jrne	00157$
      0081DD CC 82 12         [ 2]  285 	jp	00106$
      0081E0                        286 00157$:
                                    287 ;	./src/main.c: 72: if (maska & adresa) {
                                    288 ; genAnd
      0081E0 7B 02            [ 1]  289 	ld	a, (0x02, sp)
      0081E2 14 01            [ 1]  290 	and	a, (0x01, sp)
                                    291 ; genIfx
      0081E4 4D               [ 1]  292 	tnz	a
      0081E5 26 03            [ 1]  293 	jrne	00158$
      0081E7 CC 81 F5         [ 2]  294 	jp	00102$
      0081EA                        295 00158$:
                                    296 ;	./src/main.c: 73: DATA_HIGH;
                                    297 ; genSend
      0081EA A6 08            [ 1]  298 	ld	a, #0x08
                                    299 ; genSend
      0081EC AE 50 0F         [ 2]  300 	ldw	x, #0x500f
                                    301 ; genCall
      0081EF CD 85 3B         [ 4]  302 	call	_GPIO_WriteHigh
                                    303 ; genGoto
      0081F2 CC 81 FD         [ 2]  304 	jp	00103$
                                    305 ; genLabel
      0081F5                        306 00102$:
                                    307 ;	./src/main.c: 75: DATA_LOW;
                                    308 ; genSend
      0081F5 A6 08            [ 1]  309 	ld	a, #0x08
                                    310 ; genSend
      0081F7 AE 50 0F         [ 2]  311 	ldw	x, #0x500f
                                    312 ; genCall
      0081FA CD 84 24         [ 4]  313 	call	_GPIO_WriteLow
                                    314 ; genLabel
      0081FD                        315 00103$:
                                    316 ;	./src/main.c: 77: CLK_HIGH;
                                    317 ; genSend
      0081FD A6 10            [ 1]  318 	ld	a, #0x10
                                    319 ; genSend
      0081FF AE 50 0F         [ 2]  320 	ldw	x, #0x500f
                                    321 ; genCall
      008202 CD 85 3B         [ 4]  322 	call	_GPIO_WriteHigh
                                    323 ;	./src/main.c: 78: CLK_LOW;
                                    324 ; genSend
      008205 A6 10            [ 1]  325 	ld	a, #0x10
                                    326 ; genSend
      008207 AE 50 0F         [ 2]  327 	ldw	x, #0x500f
                                    328 ; genCall
      00820A CD 84 24         [ 4]  329 	call	_GPIO_WriteLow
                                    330 ;	./src/main.c: 79: maska >>= 1;
                                    331 ; genRightShiftLiteral
      00820D 04 02            [ 1]  332 	srl	(0x02, sp)
                                    333 ; genGoto
      00820F CC 81 D9         [ 2]  334 	jp	00104$
                                    335 ; genLabel
      008212                        336 00106$:
                                    337 ;	./src/main.c: 83: maska = 0x80;
                                    338 ; genAssign
      008212 A6 80            [ 1]  339 	ld	a, #0x80
      008214 6B 02            [ 1]  340 	ld	(0x02, sp), a
                                    341 ;	./src/main.c: 84: while (maska) {
                                    342 ; genLabel
      008216                        343 00110$:
                                    344 ; genIfx
      008216 0D 02            [ 1]  345 	tnz	(0x02, sp)
      008218 26 03            [ 1]  346 	jrne	00159$
      00821A CC 82 4F         [ 2]  347 	jp	00112$
      00821D                        348 00159$:
                                    349 ;	./src/main.c: 85: if (maska & data) {
                                    350 ; genAnd
      00821D 7B 02            [ 1]  351 	ld	a, (0x02, sp)
      00821F 14 05            [ 1]  352 	and	a, (0x05, sp)
                                    353 ; genIfx
      008221 4D               [ 1]  354 	tnz	a
      008222 26 03            [ 1]  355 	jrne	00160$
      008224 CC 82 32         [ 2]  356 	jp	00108$
      008227                        357 00160$:
                                    358 ;	./src/main.c: 86: DATA_HIGH;
                                    359 ; genSend
      008227 A6 08            [ 1]  360 	ld	a, #0x08
                                    361 ; genSend
      008229 AE 50 0F         [ 2]  362 	ldw	x, #0x500f
                                    363 ; genCall
      00822C CD 85 3B         [ 4]  364 	call	_GPIO_WriteHigh
                                    365 ; genGoto
      00822F CC 82 3A         [ 2]  366 	jp	00109$
                                    367 ; genLabel
      008232                        368 00108$:
                                    369 ;	./src/main.c: 88: DATA_LOW;
                                    370 ; genSend
      008232 A6 08            [ 1]  371 	ld	a, #0x08
                                    372 ; genSend
      008234 AE 50 0F         [ 2]  373 	ldw	x, #0x500f
                                    374 ; genCall
      008237 CD 84 24         [ 4]  375 	call	_GPIO_WriteLow
                                    376 ; genLabel
      00823A                        377 00109$:
                                    378 ;	./src/main.c: 90: CLK_HIGH; 
                                    379 ; genSend
      00823A A6 10            [ 1]  380 	ld	a, #0x10
                                    381 ; genSend
      00823C AE 50 0F         [ 2]  382 	ldw	x, #0x500f
                                    383 ; genCall
      00823F CD 85 3B         [ 4]  384 	call	_GPIO_WriteHigh
                                    385 ;	./src/main.c: 91: CLK_LOW;
                                    386 ; genSend
      008242 A6 10            [ 1]  387 	ld	a, #0x10
                                    388 ; genSend
      008244 AE 50 0F         [ 2]  389 	ldw	x, #0x500f
                                    390 ; genCall
      008247 CD 84 24         [ 4]  391 	call	_GPIO_WriteLow
                                    392 ;	./src/main.c: 92: maska >>= 1;
                                    393 ; genRightShiftLiteral
      00824A 04 02            [ 1]  394 	srl	(0x02, sp)
                                    395 ; genGoto
      00824C CC 82 16         [ 2]  396 	jp	00110$
                                    397 ; genLabel
      00824F                        398 00112$:
                                    399 ;	./src/main.c: 95: CS_HIGH; // Deaktivace komunikace (LOAD/CS do High)
                                    400 ; genSend
      00824F A6 04            [ 1]  401 	ld	a, #0x04
                                    402 ; genSend
      008251 AE 50 0F         [ 2]  403 	ldw	x, #0x500f
                                    404 ; genCall
      008254 CD 85 3B         [ 4]  405 	call	_GPIO_WriteHigh
                                    406 ; genLabel
      008257                        407 00113$:
                                    408 ;	./src/main.c: 96: }
                                    409 ; genEndFunction
      008257 85               [ 2]  410 	popw	x
      008258 85               [ 2]  411 	popw	x
      008259 84               [ 1]  412 	pop	a
      00825A FC               [ 2]  413 	jp	(x)
                                    414 ;	./src/main.c: 98: void delay(uint32_t ms) {
                                    415 ; genLabel
                                    416 ;	-----------------------------------------
                                    417 ;	 function delay
                                    418 ;	-----------------------------------------
                                    419 ;	Register assignment might be sub-optimal.
                                    420 ;	Stack space usage: 8 bytes.
      00825B                        421 _delay:
      00825B 52 08            [ 2]  422 	sub	sp, #8
                                    423 ;	./src/main.c: 99: while (ms--) {
                                    424 ; genAssign
      00825D 16 0B            [ 2]  425 	ldw	y, (0x0b, sp)
      00825F 17 01            [ 2]  426 	ldw	(0x01, sp), y
      008261 16 0D            [ 2]  427 	ldw	y, (0x0d, sp)
                                    428 ; genLabel
      008263                        429 00102$:
                                    430 ; genAssign
      008263 17 07            [ 2]  431 	ldw	(0x07, sp), y
      008265 1E 01            [ 2]  432 	ldw	x, (0x01, sp)
      008267 1F 05            [ 2]  433 	ldw	(0x05, sp), x
                                    434 ; genMinus
      008269 72 A2 00 01      [ 2]  435 	subw	y, #0x0001
      00826D 1E 01            [ 2]  436 	ldw	x, (0x01, sp)
      00826F 24 01            [ 1]  437 	jrnc	00139$
      008271 5A               [ 2]  438 	decw	x
      008272                        439 00139$:
      008272 1F 01            [ 2]  440 	ldw	(0x01, sp), x
                                    441 ; genIfx
      008274 1E 07            [ 2]  442 	ldw	x, (0x07, sp)
      008276 26 07            [ 1]  443 	jrne	00140$
      008278 1E 05            [ 2]  444 	ldw	x, (0x05, sp)
      00827A 26 03            [ 1]  445 	jrne	00140$
      00827C CC 82 A6         [ 2]  446 	jp	00108$
      00827F                        447 00140$:
                                    448 ;	./src/main.c: 100: for (uint32_t i = 0; i < 200; i++) {
                                    449 ; genAssign
      00827F 5F               [ 1]  450 	clrw	x
      008280 1F 07            [ 2]  451 	ldw	(0x07, sp), x
      008282 1F 05            [ 2]  452 	ldw	(0x05, sp), x
                                    453 ; genLabel
      008284                        454 00106$:
                                    455 ; genCmp
                                    456 ; genCmpTnz
      008284 1E 07            [ 2]  457 	ldw	x, (0x07, sp)
      008286 A3 00 C8         [ 2]  458 	cpw	x, #0x00c8
      008289 7B 06            [ 1]  459 	ld	a, (0x06, sp)
      00828B A2 00            [ 1]  460 	sbc	a, #0x00
      00828D 7B 05            [ 1]  461 	ld	a, (0x05, sp)
      00828F A2 00            [ 1]  462 	sbc	a, #0x00
      008291 25 03            [ 1]  463 	jrc	00141$
      008293 CC 82 63         [ 2]  464 	jp	00102$
      008296                        465 00141$:
                                    466 ; skipping generated iCode
                                    467 ;	./src/main.c: 101: __asm__("nop");
                                    468 ;	genInline
      008296 9D               [ 1]  469 	nop
                                    470 ;	./src/main.c: 100: for (uint32_t i = 0; i < 200; i++) {
                                    471 ; genPlus
      008297 1E 07            [ 2]  472 	ldw	x, (0x07, sp)
      008299 5C               [ 1]  473 	incw	x
      00829A 1F 07            [ 2]  474 	ldw	(0x07, sp), x
      00829C 26 05            [ 1]  475 	jrne	00142$
      00829E 1E 05            [ 2]  476 	ldw	x, (0x05, sp)
      0082A0 5C               [ 1]  477 	incw	x
      0082A1 1F 05            [ 2]  478 	ldw	(0x05, sp), x
      0082A3                        479 00142$:
                                    480 ; genGoto
      0082A3 CC 82 84         [ 2]  481 	jp	00106$
                                    482 ; genLabel
      0082A6                        483 00108$:
                                    484 ;	./src/main.c: 104: }
                                    485 ; genEndFunction
      0082A6 1E 09            [ 2]  486 	ldw	x, (9, sp)
      0082A8 5B 0E            [ 2]  487 	addw	sp, #14
      0082AA FC               [ 2]  488 	jp	(x)
                                    489 	.area CODE
                                    490 	.area CONST
                                    491 	.area INITIALIZER
                                    492 	.area CABS (ABS)
