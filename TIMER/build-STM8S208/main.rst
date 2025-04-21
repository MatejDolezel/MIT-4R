                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ISO C Compiler
                                      3 ; Version 4.4.4 #14992 (MINGW64)
                                      4 ;--------------------------------------------------------
                                      5 	.module main
                                      6 	
                                      7 ;--------------------------------------------------------
                                      8 ; Public variables in this module
                                      9 ;--------------------------------------------------------
                                     10 	.globl _main
                                     11 	.globl _GPIO_WriteLow
                                     12 	.globl _GPIO_WriteHigh
                                     13 	.globl _GPIO_Init
                                     14 	.globl _max7219_init
                                     15 	.globl _max7219_posli
                                     16 	.globl _delay
                                     17 ;--------------------------------------------------------
                                     18 ; ram data
                                     19 ;--------------------------------------------------------
                                     20 	.area DATA
                                     21 ;--------------------------------------------------------
                                     22 ; ram data
                                     23 ;--------------------------------------------------------
                                     24 	.area INITIALIZED
                                     25 ;--------------------------------------------------------
                                     26 ; Stack segment in internal ram
                                     27 ;--------------------------------------------------------
                                     28 	.area SSEG
      0085C7                         29 __start__stack:
      0085C7                         30 	.ds	1
                                     31 
                                     32 ;--------------------------------------------------------
                                     33 ; absolute external ram data
                                     34 ;--------------------------------------------------------
                                     35 	.area DABS (ABS)
                                     36 
                                     37 ; default segment ordering for linker
                                     38 	.area HOME
                                     39 	.area GSINIT
                                     40 	.area GSFINAL
                                     41 	.area CONST
                                     42 	.area INITIALIZER
                                     43 	.area CODE
                                     44 
                                     45 ;--------------------------------------------------------
                                     46 ; interrupt vector
                                     47 ;--------------------------------------------------------
                                     48 	.area HOME
      008000                         49 __interrupt_vect:
      008000 82 00 80 6F             50 	int s_GSINIT ; reset
      008004 82 00 82 CD             51 	int _TRAP_IRQHandler ; trap
      008008 82 00 82 CE             52 	int _TLI_IRQHandler ; int0
      00800C 82 00 82 CF             53 	int _AWU_IRQHandler ; int1
      008010 82 00 82 D0             54 	int _CLK_IRQHandler ; int2
      008014 82 00 82 D1             55 	int _EXTI_PORTA_IRQHandler ; int3
      008018 82 00 82 D2             56 	int _EXTI_PORTB_IRQHandler ; int4
      00801C 82 00 82 D3             57 	int _EXTI_PORTC_IRQHandler ; int5
      008020 82 00 82 D4             58 	int _EXTI_PORTD_IRQHandler ; int6
      008024 82 00 82 D5             59 	int _EXTI_PORTE_IRQHandler ; int7
      008028 82 00 82 D6             60 	int _CAN_RX_IRQHandler ; int8
      00802C 82 00 82 D7             61 	int _CAN_TX_IRQHandler ; int9
      008030 82 00 82 D8             62 	int _SPI_IRQHandler ; int10
      008034 82 00 82 D9             63 	int _TIM1_UPD_OVF_TRG_BRK_IRQHandler ; int11
      008038 82 00 82 DA             64 	int _TIM1_CAP_COM_IRQHandler ; int12
      00803C 82 00 82 DB             65 	int _TIM2_UPD_OVF_BRK_IRQHandler ; int13
      008040 82 00 82 DC             66 	int _TIM2_CAP_COM_IRQHandler ; int14
      008044 82 00 82 DD             67 	int _TIM3_UPD_OVF_BRK_IRQHandler ; int15
      008048 82 00 82 DE             68 	int _TIM3_CAP_COM_IRQHandler ; int16
      00804C 82 00 82 DF             69 	int _UART1_TX_IRQHandler ; int17
      008050 82 00 82 E0             70 	int _UART1_RX_IRQHandler ; int18
      008054 82 00 82 E1             71 	int _I2C_IRQHandler ; int19
      008058 82 00 82 E2             72 	int _UART3_TX_IRQHandler ; int20
      00805C 82 00 82 E3             73 	int _UART3_RX_IRQHandler ; int21
      008060 82 00 82 E4             74 	int _ADC2_IRQHandler ; int22
      008064 82 00 82 E5             75 	int _TIM4_UPD_OVF_IRQHandler ; int23
      008068 82 00 82 FF             76 	int _EEPROM_EEC_IRQHandler ; int24
                                     77 ;--------------------------------------------------------
                                     78 ; global & static initialisations
                                     79 ;--------------------------------------------------------
                                     80 	.area HOME
                                     81 	.area GSINIT
                                     82 	.area GSFINAL
                                     83 	.area GSINIT
      00806F CD 84 23         [ 4]   84 	call	___sdcc_external_startup
      008072 4D               [ 1]   85 	tnz	a
      008073 27 03            [ 1]   86 	jreq	__sdcc_init_data
      008075 CC 80 6C         [ 2]   87 	jp	__sdcc_program_startup
      008078                         88 __sdcc_init_data:
                                     89 ; stm8_genXINIT() start
      008078 AE 00 00         [ 2]   90 	ldw x, #l_DATA
      00807B 27 07            [ 1]   91 	jreq	00002$
      00807D                         92 00001$:
      00807D 72 4F 00 00      [ 1]   93 	clr (s_DATA - 1, x)
      008081 5A               [ 2]   94 	decw x
      008082 26 F9            [ 1]   95 	jrne	00001$
      008084                         96 00002$:
      008084 AE 00 04         [ 2]   97 	ldw	x, #l_INITIALIZER
      008087 27 09            [ 1]   98 	jreq	00004$
      008089                         99 00003$:
      008089 D6 80 94         [ 1]  100 	ld	a, (s_INITIALIZER - 1, x)
      00808C D7 00 00         [ 1]  101 	ld	(s_INITIALIZED - 1, x), a
      00808F 5A               [ 2]  102 	decw	x
      008090 26 F7            [ 1]  103 	jrne	00003$
      008092                        104 00004$:
                                    105 ; stm8_genXINIT() end
                                    106 	.area GSFINAL
      008092 CC 80 6C         [ 2]  107 	jp	__sdcc_program_startup
                                    108 ;--------------------------------------------------------
                                    109 ; Home
                                    110 ;--------------------------------------------------------
                                    111 	.area HOME
                                    112 	.area HOME
      00806C                        113 __sdcc_program_startup:
      00806C CC 81 60         [ 2]  114 	jp	_main
                                    115 ;	return from main will return to caller
                                    116 ;--------------------------------------------------------
                                    117 ; code
                                    118 ;--------------------------------------------------------
                                    119 	.area CODE
                                    120 ;	./src/main.c: 36: void main(void) {
                                    121 ; genLabel
                                    122 ;	-----------------------------------------
                                    123 ;	 function main
                                    124 ;	-----------------------------------------
                                    125 ;	Register assignment is optimal.
                                    126 ;	Stack space usage: 0 bytes.
      008160                        127 _main:
                                    128 ;	./src/main.c: 37: uint8_t cislo = 0;
                                    129 ; genAssign
      008160 4F               [ 1]  130 	clr	a
                                    131 ;	./src/main.c: 39: max7219_init();
                                    132 ; genCall
      008161 88               [ 1]  133 	push	a
      008162 CD 81 83         [ 4]  134 	call	_max7219_init
      008165 84               [ 1]  135 	pop	a
                                    136 ;	./src/main.c: 41: while (1) {
                                    137 ; genLabel
      008166                        138 00102$:
                                    139 ;	./src/main.c: 42: max7219_posli(DIGIT0, cislo);
                                    140 ; genIPush
      008166 88               [ 1]  141 	push	a
      008167 88               [ 1]  142 	push	a
                                    143 ; genSend
      008168 A6 01            [ 1]  144 	ld	a, #0x01
                                    145 ; genCall
      00816A CD 81 C5         [ 4]  146 	call	_max7219_posli
      00816D 84               [ 1]  147 	pop	a
                                    148 ;	./src/main.c: 44: cislo = (cislo + 1) % 10;
                                    149 ; genAssign
                                    150 ; genCast
                                    151 ; genAssign
                                    152 ; genPlus
      00816E 4C               [ 1]  153 	inc	a
                                    154 ; genDivMod
      00816F 5F               [ 1]  155 	clrw	x
      008170 97               [ 1]  156 	ld	xl, a
      008171 A6 0A            [ 1]  157 	ld	a, #0x0a
      008173 62               [ 2]  158 	div	x, a
                                    159 ; genCast
                                    160 ; genAssign
                                    161 ;	./src/main.c: 46: delay(500);
                                    162 ; genIPush
      008174 88               [ 1]  163 	push	a
      008175 4B F4            [ 1]  164 	push	#0xf4
      008177 4B 01            [ 1]  165 	push	#0x01
      008179 5F               [ 1]  166 	clrw	x
      00817A 89               [ 2]  167 	pushw	x
                                    168 ; genCall
      00817B CD 82 56         [ 4]  169 	call	_delay
      00817E 84               [ 1]  170 	pop	a
                                    171 ; genGoto
      00817F CC 81 66         [ 2]  172 	jp	00102$
                                    173 ; genLabel
      008182                        174 00104$:
                                    175 ;	./src/main.c: 48: }
                                    176 ; genEndFunction
      008182 81               [ 4]  177 	ret
                                    178 ;	Total main function size at codegen: 35 bytes.
                                    179 ;	./src/main.c: 50: void max7219_init(void) {
                                    180 ; genLabel
                                    181 ;	-----------------------------------------
                                    182 ;	 function max7219_init
                                    183 ;	-----------------------------------------
                                    184 ;	Register assignment is optimal.
                                    185 ;	Stack space usage: 0 bytes.
      008183                        186 _max7219_init:
                                    187 ;	./src/main.c: 52: GPIO_Init(CS_GPIO, CS_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
                                    188 ; genIPush
      008183 4B C0            [ 1]  189 	push	#0xc0
                                    190 ; genSend
      008185 A6 04            [ 1]  191 	ld	a, #0x04
                                    192 ; genSend
      008187 AE 50 0F         [ 2]  193 	ldw	x, #0x500f
                                    194 ; genCall
      00818A CD 83 00         [ 4]  195 	call	_GPIO_Init
                                    196 ;	./src/main.c: 53: GPIO_Init(CLK_GPIO, CLK_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
                                    197 ; genIPush
      00818D 4B C0            [ 1]  198 	push	#0xc0
                                    199 ; genSend
      00818F A6 10            [ 1]  200 	ld	a, #0x10
                                    201 ; genSend
      008191 AE 50 0F         [ 2]  202 	ldw	x, #0x500f
                                    203 ; genCall
      008194 CD 83 00         [ 4]  204 	call	_GPIO_Init
                                    205 ;	./src/main.c: 54: GPIO_Init(DATA_GPIO, DATA_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
                                    206 ; genIPush
      008197 4B C0            [ 1]  207 	push	#0xc0
                                    208 ; genSend
      008199 A6 08            [ 1]  209 	ld	a, #0x08
                                    210 ; genSend
      00819B AE 50 0F         [ 2]  211 	ldw	x, #0x500f
                                    212 ; genCall
      00819E CD 83 00         [ 4]  213 	call	_GPIO_Init
                                    214 ;	./src/main.c: 57: max7219_posli(DECODE_MODE, DECODE_ALL);  // zapnutí znakového režimu
                                    215 ; genIPush
      0081A1 4B FF            [ 1]  216 	push	#0xff
                                    217 ; genSend
      0081A3 A6 09            [ 1]  218 	ld	a, #0x09
                                    219 ; genCall
      0081A5 CD 81 C5         [ 4]  220 	call	_max7219_posli
                                    221 ;	./src/main.c: 58: max7219_posli(SCAN_LIMIT, 0);           // Používám jen jednu cifru
                                    222 ; genIPush
      0081A8 4B 00            [ 1]  223 	push	#0x00
                                    224 ; genSend
      0081AA A6 0B            [ 1]  225 	ld	a, #0x0b
                                    226 ; genCall
      0081AC CD 81 C5         [ 4]  227 	call	_max7219_posli
                                    228 ;	./src/main.c: 59: max7219_posli(INTENSITY, 1);            // Nízký jas
                                    229 ; genIPush
      0081AF 4B 01            [ 1]  230 	push	#0x01
                                    231 ; genSend
      0081B1 A6 0A            [ 1]  232 	ld	a, #0x0a
                                    233 ; genCall
      0081B3 CD 81 C5         [ 4]  234 	call	_max7219_posli
                                    235 ;	./src/main.c: 60: max7219_posli(DISPLAY_TEST, DISPLAY_TEST_OFF); // Vypnutí testu
                                    236 ; genIPush
      0081B6 4B 00            [ 1]  237 	push	#0x00
                                    238 ; genSend
      0081B8 A6 0F            [ 1]  239 	ld	a, #0x0f
                                    240 ; genCall
      0081BA CD 81 C5         [ 4]  241 	call	_max7219_posli
                                    242 ;	./src/main.c: 61: max7219_posli(SHUTDOWN, DISPLAY_ON);    // Zapnutí displeje
                                    243 ; genIPush
      0081BD 4B 01            [ 1]  244 	push	#0x01
                                    245 ; genSend
      0081BF A6 0C            [ 1]  246 	ld	a, #0x0c
                                    247 ; genCall
      0081C1 CD 81 C5         [ 4]  248 	call	_max7219_posli
                                    249 ; genLabel
      0081C4                        250 00101$:
                                    251 ;	./src/main.c: 62: }
                                    252 ; genEndFunction
      0081C4 81               [ 4]  253 	ret
                                    254 ;	Total max7219_init function size at codegen: 66 bytes.
                                    255 ;	./src/main.c: 64: void max7219_posli(uint8_t adresa, uint8_t data) {
                                    256 ; genLabel
                                    257 ;	-----------------------------------------
                                    258 ;	 function max7219_posli
                                    259 ;	-----------------------------------------
                                    260 ;	Register assignment is optimal.
                                    261 ;	Stack space usage: 2 bytes.
      0081C5                        262 _max7219_posli:
      0081C5 89               [ 2]  263 	pushw	x
                                    264 ; genReceive
      0081C6 6B 01            [ 1]  265 	ld	(0x01, sp), a
                                    266 ;	./src/main.c: 67: CS_LOW; // Aktivace komunikace (LOAD/CS do Low)
                                    267 ; genSend
      0081C8 A6 04            [ 1]  268 	ld	a, #0x04
                                    269 ; genSend
      0081CA AE 50 0F         [ 2]  270 	ldw	x, #0x500f
                                    271 ; genCall
      0081CD CD 84 14         [ 4]  272 	call	_GPIO_WriteLow
                                    273 ;	./src/main.c: 70: maska = 0x80;
                                    274 ; genAssign
      0081D0 A6 80            [ 1]  275 	ld	a, #0x80
      0081D2 6B 02            [ 1]  276 	ld	(0x02, sp), a
                                    277 ;	./src/main.c: 71: while (maska) {
                                    278 ; genLabel
      0081D4                        279 00104$:
                                    280 ; genIfx
      0081D4 0D 02            [ 1]  281 	tnz	(0x02, sp)
      0081D6 26 03            [ 1]  282 	jrne	00157$
      0081D8 CC 82 0D         [ 2]  283 	jp	00106$
      0081DB                        284 00157$:
                                    285 ;	./src/main.c: 72: if (maska & adresa) {
                                    286 ; genAnd
      0081DB 7B 02            [ 1]  287 	ld	a, (0x02, sp)
      0081DD 14 01            [ 1]  288 	and	a, (0x01, sp)
                                    289 ; genIfx
      0081DF 4D               [ 1]  290 	tnz	a
      0081E0 26 03            [ 1]  291 	jrne	00158$
      0081E2 CC 81 F0         [ 2]  292 	jp	00102$
      0081E5                        293 00158$:
                                    294 ;	./src/main.c: 73: DATA_HIGH;
                                    295 ; genSend
      0081E5 A6 08            [ 1]  296 	ld	a, #0x08
                                    297 ; genSend
      0081E7 AE 50 0F         [ 2]  298 	ldw	x, #0x500f
                                    299 ; genCall
      0081EA CD 85 2E         [ 4]  300 	call	_GPIO_WriteHigh
                                    301 ; genGoto
      0081ED CC 81 F8         [ 2]  302 	jp	00103$
                                    303 ; genLabel
      0081F0                        304 00102$:
                                    305 ;	./src/main.c: 75: DATA_LOW;
                                    306 ; genSend
      0081F0 A6 08            [ 1]  307 	ld	a, #0x08
                                    308 ; genSend
      0081F2 AE 50 0F         [ 2]  309 	ldw	x, #0x500f
                                    310 ; genCall
      0081F5 CD 84 14         [ 4]  311 	call	_GPIO_WriteLow
                                    312 ; genLabel
      0081F8                        313 00103$:
                                    314 ;	./src/main.c: 77: CLK_HIGH;
                                    315 ; genSend
      0081F8 A6 10            [ 1]  316 	ld	a, #0x10
                                    317 ; genSend
      0081FA AE 50 0F         [ 2]  318 	ldw	x, #0x500f
                                    319 ; genCall
      0081FD CD 85 2E         [ 4]  320 	call	_GPIO_WriteHigh
                                    321 ;	./src/main.c: 78: CLK_LOW;
                                    322 ; genSend
      008200 A6 10            [ 1]  323 	ld	a, #0x10
                                    324 ; genSend
      008202 AE 50 0F         [ 2]  325 	ldw	x, #0x500f
                                    326 ; genCall
      008205 CD 84 14         [ 4]  327 	call	_GPIO_WriteLow
                                    328 ;	./src/main.c: 79: maska >>= 1;
                                    329 ; genRightShiftLiteral
      008208 04 02            [ 1]  330 	srl	(0x02, sp)
                                    331 ; genGoto
      00820A CC 81 D4         [ 2]  332 	jp	00104$
                                    333 ; genLabel
      00820D                        334 00106$:
                                    335 ;	./src/main.c: 83: maska = 0x80;
                                    336 ; genAssign
      00820D A6 80            [ 1]  337 	ld	a, #0x80
      00820F 6B 02            [ 1]  338 	ld	(0x02, sp), a
                                    339 ;	./src/main.c: 84: while (maska) {
                                    340 ; genLabel
      008211                        341 00110$:
                                    342 ; genIfx
      008211 0D 02            [ 1]  343 	tnz	(0x02, sp)
      008213 26 03            [ 1]  344 	jrne	00159$
      008215 CC 82 4A         [ 2]  345 	jp	00112$
      008218                        346 00159$:
                                    347 ;	./src/main.c: 85: if (maska & data) {
                                    348 ; genAnd
      008218 7B 02            [ 1]  349 	ld	a, (0x02, sp)
      00821A 14 05            [ 1]  350 	and	a, (0x05, sp)
                                    351 ; genIfx
      00821C 4D               [ 1]  352 	tnz	a
      00821D 26 03            [ 1]  353 	jrne	00160$
      00821F CC 82 2D         [ 2]  354 	jp	00108$
      008222                        355 00160$:
                                    356 ;	./src/main.c: 86: DATA_HIGH;
                                    357 ; genSend
      008222 A6 08            [ 1]  358 	ld	a, #0x08
                                    359 ; genSend
      008224 AE 50 0F         [ 2]  360 	ldw	x, #0x500f
                                    361 ; genCall
      008227 CD 85 2E         [ 4]  362 	call	_GPIO_WriteHigh
                                    363 ; genGoto
      00822A CC 82 35         [ 2]  364 	jp	00109$
                                    365 ; genLabel
      00822D                        366 00108$:
                                    367 ;	./src/main.c: 88: DATA_LOW;
                                    368 ; genSend
      00822D A6 08            [ 1]  369 	ld	a, #0x08
                                    370 ; genSend
      00822F AE 50 0F         [ 2]  371 	ldw	x, #0x500f
                                    372 ; genCall
      008232 CD 84 14         [ 4]  373 	call	_GPIO_WriteLow
                                    374 ; genLabel
      008235                        375 00109$:
                                    376 ;	./src/main.c: 90: CLK_HIGH; 
                                    377 ; genSend
      008235 A6 10            [ 1]  378 	ld	a, #0x10
                                    379 ; genSend
      008237 AE 50 0F         [ 2]  380 	ldw	x, #0x500f
                                    381 ; genCall
      00823A CD 85 2E         [ 4]  382 	call	_GPIO_WriteHigh
                                    383 ;	./src/main.c: 91: CLK_LOW;
                                    384 ; genSend
      00823D A6 10            [ 1]  385 	ld	a, #0x10
                                    386 ; genSend
      00823F AE 50 0F         [ 2]  387 	ldw	x, #0x500f
                                    388 ; genCall
      008242 CD 84 14         [ 4]  389 	call	_GPIO_WriteLow
                                    390 ;	./src/main.c: 92: maska >>= 1;
                                    391 ; genRightShiftLiteral
      008245 04 02            [ 1]  392 	srl	(0x02, sp)
                                    393 ; genGoto
      008247 CC 82 11         [ 2]  394 	jp	00110$
                                    395 ; genLabel
      00824A                        396 00112$:
                                    397 ;	./src/main.c: 95: CS_HIGH; // Deaktivace komunikace (LOAD/CS do High)
                                    398 ; genSend
      00824A A6 04            [ 1]  399 	ld	a, #0x04
                                    400 ; genSend
      00824C AE 50 0F         [ 2]  401 	ldw	x, #0x500f
                                    402 ; genCall
      00824F CD 85 2E         [ 4]  403 	call	_GPIO_WriteHigh
                                    404 ; genLabel
      008252                        405 00113$:
                                    406 ;	./src/main.c: 96: }
                                    407 ; genEndFunction
      008252 85               [ 2]  408 	popw	x
      008253 85               [ 2]  409 	popw	x
      008254 84               [ 1]  410 	pop	a
      008255 FC               [ 2]  411 	jp	(x)
                                    412 ;	Total max7219_posli function size at codegen: 145 bytes.
                                    413 ;	./src/main.c: 98: void delay(uint32_t ms) {
                                    414 ; genLabel
                                    415 ;	-----------------------------------------
                                    416 ;	 function delay
                                    417 ;	-----------------------------------------
                                    418 ;	Register assignment might be sub-optimal.
                                    419 ;	Stack space usage: 4 bytes.
      008256                        420 _delay:
      008256 52 04            [ 2]  421 	sub	sp, #4
                                    422 ;	./src/main.c: 99: while (ms--) {
                                    423 ; genAssign
      008258 16 09            [ 2]  424 	ldw	y, (0x09, sp)
                                    425 ; genLabel
      00825A                        426 00102$:
                                    427 ; genAssign
      00825A 17 03            [ 2]  428 	ldw	(0x03, sp), y
      00825C 1E 07            [ 2]  429 	ldw	x, (0x07, sp)
      00825E 1F 01            [ 2]  430 	ldw	(0x01, sp), x
                                    431 ; genMinus
      008260 72 A2 00 01      [ 2]  432 	subw	y, #0x0001
      008264 1E 07            [ 2]  433 	ldw	x, (0x07, sp)
      008266 24 01            [ 1]  434 	jrnc	00139$
      008268 5A               [ 2]  435 	decw	x
      008269                        436 00139$:
      008269 1F 07            [ 2]  437 	ldw	(0x07, sp), x
                                    438 ; genIfx
      00826B 1E 03            [ 2]  439 	ldw	x, (0x03, sp)
      00826D 26 07            [ 1]  440 	jrne	00140$
      00826F 1E 01            [ 2]  441 	ldw	x, (0x01, sp)
      008271 26 03            [ 1]  442 	jrne	00140$
      008273 CC 82 87         [ 2]  443 	jp	00108$
      008276                        444 00140$:
                                    445 ;	./src/main.c: 100: for (uint32_t i = 0; i < 200; i++) {
                                    446 ; genAssign
      008276 0F 04            [ 1]  447 	clr	(0x04, sp)
                                    448 ; genLabel
      008278                        449 00106$:
                                    450 ; genCmp
                                    451 ; genCmpTnz
      008278 7B 04            [ 1]  452 	ld	a, (0x04, sp)
      00827A A1 C8            [ 1]  453 	cp	a, #0xc8
      00827C 25 03            [ 1]  454 	jrc	00141$
      00827E CC 82 5A         [ 2]  455 	jp	00102$
      008281                        456 00141$:
                                    457 ; skipping generated iCode
                                    458 ;	./src/main.c: 101: __asm__("nop");
                                    459 ;	genInline
      008281 9D               [ 1]  460 	nop
                                    461 ;	./src/main.c: 100: for (uint32_t i = 0; i < 200; i++) {
                                    462 ; genPlus
      008282 0C 04            [ 1]  463 	inc	(0x04, sp)
                                    464 ; genGoto
      008284 CC 82 78         [ 2]  465 	jp	00106$
                                    466 ; genLabel
      008287                        467 00108$:
                                    468 ;	./src/main.c: 104: }
                                    469 ; genEndFunction
      008287 1E 05            [ 2]  470 	ldw	x, (5, sp)
      008289 5B 0A            [ 2]  471 	addw	sp, #10
      00828B FC               [ 2]  472 	jp	(x)
                                    473 ;	Total delay function size at codegen: 53 bytes.
                                    474 	.area CODE
                                    475 	.area CONST
                                    476 	.area INITIALIZER
                                    477 	.area CABS (ABS)
