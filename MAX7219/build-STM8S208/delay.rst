                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ISO C Compiler
                                      3 ; Version 4.4.4 #14992 (MINGW64)
                                      4 ;--------------------------------------------------------
                                      5 	.module delay
                                      6 	
                                      7 ;--------------------------------------------------------
                                      8 ; Public variables in this module
                                      9 ;--------------------------------------------------------
                                     10 	.globl _delay_us
                                     11 	.globl _delay_ms
                                     12 ;--------------------------------------------------------
                                     13 ; ram data
                                     14 ;--------------------------------------------------------
                                     15 	.area DATA
                                     16 ;--------------------------------------------------------
                                     17 ; ram data
                                     18 ;--------------------------------------------------------
                                     19 	.area INITIALIZED
                                     20 ;--------------------------------------------------------
                                     21 ; absolute external ram data
                                     22 ;--------------------------------------------------------
                                     23 	.area DABS (ABS)
                                     24 
                                     25 ; default segment ordering for linker
                                     26 	.area HOME
                                     27 	.area GSINIT
                                     28 	.area GSFINAL
                                     29 	.area CONST
                                     30 	.area INITIALIZER
                                     31 	.area CODE
                                     32 
                                     33 ;--------------------------------------------------------
                                     34 ; global & static initialisations
                                     35 ;--------------------------------------------------------
                                     36 	.area HOME
                                     37 	.area GSINIT
                                     38 	.area GSFINAL
                                     39 	.area GSINIT
                                     40 ;--------------------------------------------------------
                                     41 ; Home
                                     42 ;--------------------------------------------------------
                                     43 	.area HOME
                                     44 	.area HOME
                                     45 ;--------------------------------------------------------
                                     46 ; code
                                     47 ;--------------------------------------------------------
                                     48 	.area CODE
                                     49 ;	inc/delay.h: 18: static @inline void _delay_cycl( unsigned short __ticks )
                                     50 ; genLabel
                                     51 ;	-----------------------------------------
                                     52 ;	 function _delay_cycl
                                     53 ;	-----------------------------------------
                                     54 ;	Register assignment is optimal.
                                     55 ;	Stack space usage: 0 bytes.
      008099                         56 __delay_cycl:
                                     57 ; genReceive
                                     58 ;	inc/delay.h: 29: __asm__("nop\n nop\n"); 
                                     59 ;	genInline
      008099 9D               [ 1]   60 	nop
      00809A 9D               [ 1]   61 	nop
                                     62 ;	inc/delay.h: 30: do { 		// ASM: ldw X, #tick; lab$: decw X; tnzw X; jrne lab$
                                     63 ; genAssign
                                     64 ; genLabel
      00809B                         65 00101$:
                                     66 ;	inc/delay.h: 31: __ticks--;//      2c;                 1c;     2c    ; 1/2c   
                                     67 ; genMinus
      00809B 5A               [ 2]   68 	decw	x
                                     69 ;	inc/delay.h: 32: } while ( __ticks );
                                     70 ; genIfx
      00809C 5D               [ 2]   71 	tnzw	x
      00809D 27 03            [ 1]   72 	jreq	00121$
      00809F CC 80 9B         [ 2]   73 	jp	00101$
      0080A2                         74 00121$:
                                     75 ;	inc/delay.h: 33: __asm__("nop\n");
                                     76 ;	genInline
      0080A2 9D               [ 1]   77 	nop
                                     78 ; genLabel
      0080A3                         79 00104$:
                                     80 ;	inc/delay.h: 43: }
                                     81 ; genEndFunction
      0080A3 81               [ 4]   82 	ret
                                     83 ;	Total _delay_cycl function size at codegen: 9 bytes.
                                     84 ;	inc/delay.h: 45: static @inline void _delay_us( const unsigned short __us ){
                                     85 ; genLabel
                                     86 ;	-----------------------------------------
                                     87 ;	 function _delay_us
                                     88 ;	-----------------------------------------
                                     89 ;	Register assignment might be sub-optimal.
                                     90 ;	Stack space usage: 0 bytes.
      0080A4                         91 __delay_us:
                                     92 ; genReceive
                                     93 ;	inc/delay.h: 46: _delay_cycl( (unsigned short)( T_COUNT(__us) ));
                                     94 ; genCast
                                     95 ; genAssign
      0080A4 90 5F            [ 1]   96 	clrw	y
                                     97 ; genIPush
      0080A6 89               [ 2]   98 	pushw	x
      0080A7 90 89            [ 2]   99 	pushw	y
                                    100 ; genIPush
      0080A9 4B 00            [ 1]  101 	push	#0x00
      0080AB 4B 24            [ 1]  102 	push	#0x24
      0080AD 4B F4            [ 1]  103 	push	#0xf4
      0080AF 4B 00            [ 1]  104 	push	#0x00
                                    105 ; genCall
      0080B1 CD 85 46         [ 4]  106 	call	__mullong
      0080B4 5B 08            [ 2]  107 	addw	sp, #8
                                    108 ; genCast
                                    109 ; genAssign
                                    110 ; genIPush
      0080B6 4B 40            [ 1]  111 	push	#0x40
      0080B8 4B 42            [ 1]  112 	push	#0x42
      0080BA 4B 0F            [ 1]  113 	push	#0x0f
      0080BC 4B 00            [ 1]  114 	push	#0x00
                                    115 ; genIPush
      0080BE 89               [ 2]  116 	pushw	x
      0080BF 90 89            [ 2]  117 	pushw	y
                                    118 ; genCall
      0080C1 CD 83 B9         [ 4]  119 	call	__divulong
      0080C4 5B 08            [ 2]  120 	addw	sp, #8
                                    121 ; genRightShiftLiteral
      0080C6 90 54            [ 2]  122 	srlw	y
      0080C8 56               [ 2]  123 	rrcw	x
      0080C9 90 54            [ 2]  124 	srlw	y
      0080CB 56               [ 2]  125 	rrcw	x
      0080CC 90 54            [ 2]  126 	srlw	y
      0080CE 56               [ 2]  127 	rrcw	x
                                    128 ; genCast
                                    129 ; genAssign
                                    130 ; genPlus
      0080CF 5C               [ 1]  131 	incw	x
                                    132 ;	inc/delay.h: 29: __asm__("nop\n nop\n"); 
                                    133 ;	genInline
      0080D0 9D               [ 1]  134 	nop
      0080D1 9D               [ 1]  135 	nop
                                    136 ;	inc/delay.h: 30: do { 		// ASM: ldw X, #tick; lab$: decw X; tnzw X; jrne lab$
                                    137 ; genAssign
                                    138 ; genLabel
      0080D2                        139 00101$:
                                    140 ;	inc/delay.h: 31: __ticks--;//      2c;                 1c;     2c    ; 1/2c   
                                    141 ; genMinus
      0080D2 5A               [ 2]  142 	decw	x
                                    143 ;	inc/delay.h: 32: } while ( __ticks );
                                    144 ; genIfx
      0080D3 5D               [ 2]  145 	tnzw	x
      0080D4 27 03            [ 1]  146 	jreq	00122$
      0080D6 CC 80 D2         [ 2]  147 	jp	00101$
      0080D9                        148 00122$:
                                    149 ;	inc/delay.h: 33: __asm__("nop\n");
                                    150 ;	genInline
      0080D9 9D               [ 1]  151 	nop
                                    152 ;	inc/delay.h: 46: _delay_cycl( (unsigned short)( T_COUNT(__us) ));
                                    153 ; genLabel
      0080DA                        154 00105$:
                                    155 ;	inc/delay.h: 47: }
                                    156 ; genEndFunction
      0080DA 81               [ 4]  157 	ret
                                    158 ;	Total _delay_us function size at codegen: 54 bytes.
                                    159 ;	./src/delay.c: 4: void delay_us(uint8_t us)
                                    160 ; genLabel
                                    161 ;	-----------------------------------------
                                    162 ;	 function delay_us
                                    163 ;	-----------------------------------------
                                    164 ;	Register assignment might be sub-optimal.
                                    165 ;	Stack space usage: 4 bytes.
      0080DB                        166 _delay_us:
      0080DB 52 04            [ 2]  167 	sub	sp, #4
                                    168 ; genReceive
                                    169 ;	./src/delay.c: 6: _delay_us(us);
                                    170 ; genCast
                                    171 ; genAssign
                                    172 ;	inc/delay.h: 46: _delay_cycl( (unsigned short)( T_COUNT(__us) ));
                                    173 ; genCast
                                    174 ; genAssign
      0080DD 5F               [ 1]  175 	clrw	x
      0080DE 0F 01            [ 1]  176 	clr	(0x01, sp)
                                    177 ; genIPush
      0080E0 88               [ 1]  178 	push	a
      0080E1 89               [ 2]  179 	pushw	x
      0080E2 4F               [ 1]  180 	clr	a
      0080E3 88               [ 1]  181 	push	a
                                    182 ; genIPush
      0080E4 4B 00            [ 1]  183 	push	#0x00
      0080E6 4B 24            [ 1]  184 	push	#0x24
      0080E8 4B F4            [ 1]  185 	push	#0xf4
      0080EA 4B 00            [ 1]  186 	push	#0x00
                                    187 ; genCall
      0080EC CD 85 46         [ 4]  188 	call	__mullong
      0080EF 5B 08            [ 2]  189 	addw	sp, #8
                                    190 ; genCast
                                    191 ; genAssign
                                    192 ; genIPush
      0080F1 4B 40            [ 1]  193 	push	#0x40
      0080F3 4B 42            [ 1]  194 	push	#0x42
      0080F5 4B 0F            [ 1]  195 	push	#0x0f
      0080F7 4B 00            [ 1]  196 	push	#0x00
                                    197 ; genIPush
      0080F9 89               [ 2]  198 	pushw	x
      0080FA 90 89            [ 2]  199 	pushw	y
                                    200 ; genCall
      0080FC CD 83 B9         [ 4]  201 	call	__divulong
      0080FF 5B 08            [ 2]  202 	addw	sp, #8
                                    203 ; genRightShiftLiteral
      008101 90 54            [ 2]  204 	srlw	y
      008103 56               [ 2]  205 	rrcw	x
      008104 90 54            [ 2]  206 	srlw	y
      008106 56               [ 2]  207 	rrcw	x
      008107 90 54            [ 2]  208 	srlw	y
      008109 56               [ 2]  209 	rrcw	x
                                    210 ; genCast
                                    211 ; genAssign
                                    212 ; genPlus
      00810A 5C               [ 1]  213 	incw	x
                                    214 ;	inc/delay.h: 29: __asm__("nop\n nop\n"); 
                                    215 ;	genInline
      00810B 9D               [ 1]  216 	nop
      00810C 9D               [ 1]  217 	nop
                                    218 ;	inc/delay.h: 30: do { 		// ASM: ldw X, #tick; lab$: decw X; tnzw X; jrne lab$
                                    219 ; genAssign
                                    220 ; genLabel
      00810D                        221 00101$:
                                    222 ;	inc/delay.h: 31: __ticks--;//      2c;                 1c;     2c    ; 1/2c   
                                    223 ; genMinus
      00810D 5A               [ 2]  224 	decw	x
                                    225 ;	inc/delay.h: 32: } while ( __ticks );
                                    226 ; genIfx
      00810E 5D               [ 2]  227 	tnzw	x
      00810F 27 03            [ 1]  228 	jreq	00123$
      008111 CC 81 0D         [ 2]  229 	jp	00101$
      008114                        230 00123$:
                                    231 ;	inc/delay.h: 33: __asm__("nop\n");
                                    232 ;	genInline
      008114 9D               [ 1]  233 	nop
                                    234 ;	./src/delay.c: 6: _delay_us(us);
                                    235 ; genLabel
      008115                        236 00106$:
                                    237 ;	./src/delay.c: 7: }
                                    238 ; genEndFunction
      008115 5B 04            [ 2]  239 	addw	sp, #4
      008117 81               [ 4]  240 	ret
                                    241 ;	Total delay_us function size at codegen: 60 bytes.
                                    242 ;	./src/delay.c: 9: void delay_ms(uint16_t ms)
                                    243 ; genLabel
                                    244 ;	-----------------------------------------
                                    245 ;	 function delay_ms
                                    246 ;	-----------------------------------------
                                    247 ;	Register assignment might be sub-optimal.
                                    248 ;	Stack space usage: 2 bytes.
      008118                        249 _delay_ms:
      008118 89               [ 2]  250 	pushw	x
                                    251 ; genReceive
      008119 1F 01            [ 2]  252 	ldw	(0x01, sp), x
                                    253 ;	./src/delay.c: 11: for (int16_t i = 0; i < ms; i++) {
                                    254 ; genAssign
      00811B 90 5F            [ 1]  255 	clrw	y
                                    256 ; genLabel
      00811D                        257 00123$:
                                    258 ; genCast
                                    259 ; genAssign
      00811D 93               [ 1]  260 	ldw	x, y
                                    261 ; genCmp
                                    262 ; genCmpTnz
      00811E 13 01            [ 2]  263 	cpw	x, (0x01, sp)
      008120 25 03            [ 1]  264 	jrc	00202$
      008122 CC 81 5E         [ 2]  265 	jp	00125$
      008125                        266 00202$:
                                    267 ; skipping generated iCode
                                    268 ;	inc/delay.h: 29: __asm__("nop\n nop\n"); 
                                    269 ;	genInline
      008125 9D               [ 1]  270 	nop
      008126 9D               [ 1]  271 	nop
                                    272 ;	inc/delay.h: 30: do { 		// ASM: ldw X, #tick; lab$: decw X; tnzw X; jrne lab$
                                    273 ; genAssign
      008127 AE 01 F5         [ 2]  274 	ldw	x, #0x01f5
                                    275 ; genLabel
      00812A                        276 00102$:
                                    277 ;	inc/delay.h: 31: __ticks--;//      2c;                 1c;     2c    ; 1/2c   
                                    278 ; genMinus
      00812A 5A               [ 2]  279 	decw	x
                                    280 ;	inc/delay.h: 32: } while ( __ticks );
                                    281 ; genIfx
      00812B 5D               [ 2]  282 	tnzw	x
      00812C 27 03            [ 1]  283 	jreq	00203$
      00812E CC 81 2A         [ 2]  284 	jp	00102$
      008131                        285 00203$:
                                    286 ;	inc/delay.h: 33: __asm__("nop\n");
                                    287 ;	genInline
      008131 9D               [ 1]  288 	nop
                                    289 ;	inc/delay.h: 29: __asm__("nop\n nop\n"); 
                                    290 ;	genInline
      008132 9D               [ 1]  291 	nop
      008133 9D               [ 1]  292 	nop
                                    293 ;	inc/delay.h: 30: do { 		// ASM: ldw X, #tick; lab$: decw X; tnzw X; jrne lab$
                                    294 ; genAssign
      008134 AE 01 F5         [ 2]  295 	ldw	x, #0x01f5
                                    296 ; genLabel
      008137                        297 00107$:
                                    298 ;	inc/delay.h: 31: __ticks--;//      2c;                 1c;     2c    ; 1/2c   
                                    299 ; genMinus
      008137 5A               [ 2]  300 	decw	x
                                    301 ;	inc/delay.h: 32: } while ( __ticks );
                                    302 ; genIfx
      008138 5D               [ 2]  303 	tnzw	x
      008139 27 03            [ 1]  304 	jreq	00204$
      00813B CC 81 37         [ 2]  305 	jp	00107$
      00813E                        306 00204$:
                                    307 ;	inc/delay.h: 33: __asm__("nop\n");
                                    308 ;	genInline
      00813E 9D               [ 1]  309 	nop
                                    310 ;	inc/delay.h: 29: __asm__("nop\n nop\n"); 
                                    311 ;	genInline
      00813F 9D               [ 1]  312 	nop
      008140 9D               [ 1]  313 	nop
                                    314 ;	inc/delay.h: 30: do { 		// ASM: ldw X, #tick; lab$: decw X; tnzw X; jrne lab$
                                    315 ; genAssign
      008141 AE 01 F5         [ 2]  316 	ldw	x, #0x01f5
                                    317 ; genLabel
      008144                        318 00112$:
                                    319 ;	inc/delay.h: 31: __ticks--;//      2c;                 1c;     2c    ; 1/2c   
                                    320 ; genMinus
      008144 5A               [ 2]  321 	decw	x
                                    322 ;	inc/delay.h: 32: } while ( __ticks );
                                    323 ; genIfx
      008145 5D               [ 2]  324 	tnzw	x
      008146 27 03            [ 1]  325 	jreq	00205$
      008148 CC 81 44         [ 2]  326 	jp	00112$
      00814B                        327 00205$:
                                    328 ;	inc/delay.h: 33: __asm__("nop\n");
                                    329 ;	genInline
      00814B 9D               [ 1]  330 	nop
                                    331 ;	inc/delay.h: 29: __asm__("nop\n nop\n"); 
                                    332 ;	genInline
      00814C 9D               [ 1]  333 	nop
      00814D 9D               [ 1]  334 	nop
                                    335 ;	inc/delay.h: 30: do { 		// ASM: ldw X, #tick; lab$: decw X; tnzw X; jrne lab$
                                    336 ; genAssign
      00814E AE 01 E7         [ 2]  337 	ldw	x, #0x01e7
                                    338 ; genLabel
      008151                        339 00117$:
                                    340 ;	inc/delay.h: 31: __ticks--;//      2c;                 1c;     2c    ; 1/2c   
                                    341 ; genMinus
      008151 5A               [ 2]  342 	decw	x
                                    343 ;	inc/delay.h: 32: } while ( __ticks );
                                    344 ; genIfx
      008152 5D               [ 2]  345 	tnzw	x
      008153 27 03            [ 1]  346 	jreq	00206$
      008155 CC 81 51         [ 2]  347 	jp	00117$
      008158                        348 00206$:
                                    349 ;	inc/delay.h: 33: __asm__("nop\n");
                                    350 ;	genInline
      008158 9D               [ 1]  351 	nop
                                    352 ;	./src/delay.c: 11: for (int16_t i = 0; i < ms; i++) {
                                    353 ; genPlus
      008159 90 5C            [ 1]  354 	incw	y
                                    355 ; genGoto
      00815B CC 81 1D         [ 2]  356 	jp	00123$
                                    357 ; genLabel
      00815E                        358 00125$:
                                    359 ;	./src/delay.c: 17: }
                                    360 ; genEndFunction
      00815E 85               [ 2]  361 	popw	x
      00815F 81               [ 4]  362 	ret
                                    363 ;	Total delay_ms function size at codegen: 67 bytes.
                                    364 	.area CODE
                                    365 	.area CONST
                                    366 	.area INITIALIZER
                                    367 	.area CABS (ABS)
