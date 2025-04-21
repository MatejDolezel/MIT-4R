                                      1 ;--------------------------------------------------------
                                      2 ; File Created by SDCC : free open source ISO C Compiler
                                      3 ; Version 4.4.4 #14992 (MINGW64)
                                      4 ;--------------------------------------------------------
                                      5 	.module milis
                                      6 	
                                      7 ;--------------------------------------------------------
                                      8 ; Public variables in this module
                                      9 ;--------------------------------------------------------
                                     10 	.globl _TIM4_ClearFlag
                                     11 	.globl _TIM4_ITConfig
                                     12 	.globl _TIM4_Cmd
                                     13 	.globl _TIM4_TimeBaseInit
                                     14 	.globl _ITC_SetSoftwarePriority
                                     15 	.globl _miliseconds
                                     16 	.globl _milis
                                     17 	.globl _init_milis
                                     18 ;--------------------------------------------------------
                                     19 ; ram data
                                     20 ;--------------------------------------------------------
                                     21 	.area DATA
                                     22 ;--------------------------------------------------------
                                     23 ; ram data
                                     24 ;--------------------------------------------------------
                                     25 	.area INITIALIZED
      000001                         26 _miliseconds::
      000001                         27 	.ds 4
                                     28 ;--------------------------------------------------------
                                     29 ; absolute external ram data
                                     30 ;--------------------------------------------------------
                                     31 	.area DABS (ABS)
                                     32 
                                     33 ; default segment ordering for linker
                                     34 	.area HOME
                                     35 	.area GSINIT
                                     36 	.area GSFINAL
                                     37 	.area CONST
                                     38 	.area INITIALIZER
                                     39 	.area CODE
                                     40 
                                     41 ;--------------------------------------------------------
                                     42 ; global & static initialisations
                                     43 ;--------------------------------------------------------
                                     44 	.area HOME
                                     45 	.area GSINIT
                                     46 	.area GSFINAL
                                     47 	.area GSINIT
                                     48 ;--------------------------------------------------------
                                     49 ; Home
                                     50 ;--------------------------------------------------------
                                     51 	.area HOME
                                     52 	.area HOME
                                     53 ;--------------------------------------------------------
                                     54 ; code
                                     55 ;--------------------------------------------------------
                                     56 	.area CODE
                                     57 ;	./src/milis.c: 13: MILIS_PROTOTYPE
                                     58 ; genLabel
                                     59 ;	-----------------------------------------
                                     60 ;	 function milis
                                     61 ;	-----------------------------------------
                                     62 ;	Register assignment is optimal.
                                     63 ;	Stack space usage: 4 bytes.
      00828C                         64 _milis:
      00828C 52 04            [ 2]   65 	sub	sp, #4
                                     66 ;	./src/milis.c: 20: TIM4_ITConfig(TIM4_IT_UPDATE, DISABLE);
                                     67 ; genIPush
      00828E 4B 00            [ 1]   68 	push	#0x00
                                     69 ; genSend
      008290 A6 01            [ 1]   70 	ld	a, #0x01
                                     71 ; genCall
      008292 CD 83 97         [ 4]   72 	call	_TIM4_ITConfig
                                     73 ;	./src/milis.c: 21: tmp = miliseconds;
                                     74 ; genAssign
      008295 CE 00 03         [ 2]   75 	ldw	x, _miliseconds+2
      008298 90 CE 00 01      [ 2]   76 	ldw	y, _miliseconds+0
      00829C 17 01            [ 2]   77 	ldw	(0x01, sp), y
                                     78 ;	./src/milis.c: 22: TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
                                     79 ; genIPush
      00829E 89               [ 2]   80 	pushw	x
      00829F 4B 01            [ 1]   81 	push	#0x01
                                     82 ; genSend
      0082A1 A6 01            [ 1]   83 	ld	a, #0x01
                                     84 ; genCall
      0082A3 CD 83 97         [ 4]   85 	call	_TIM4_ITConfig
      0082A6 85               [ 2]   86 	popw	x
                                     87 ;	./src/milis.c: 23: return tmp;
                                     88 ; genReturn
      0082A7 16 01            [ 2]   89 	ldw	y, (0x01, sp)
                                     90 ; genLabel
      0082A9                         91 00101$:
                                     92 ;	./src/milis.c: 24: }
                                     93 ; genEndFunction
      0082A9 5B 04            [ 2]   94 	addw	sp, #4
      0082AB 81               [ 4]   95 	ret
                                     96 ;	Total milis function size at codegen: 32 bytes.
                                     97 ;	./src/milis.c: 27: void init_milis(void)
                                     98 ; genLabel
                                     99 ;	-----------------------------------------
                                    100 ;	 function init_milis
                                    101 ;	-----------------------------------------
                                    102 ;	Register assignment is optimal.
                                    103 ;	Stack space usage: 0 bytes.
      0082AC                        104 _init_milis:
                                    105 ;	./src/milis.c: 29: TIM4_TimeBaseInit(PRESCALER, PERIOD);       // (16MHz / 128) / 125 = 1000Hz
                                    106 ; genIPush
      0082AC 4B 7C            [ 1]  107 	push	#0x7c
                                    108 ; genSend
      0082AE A6 07            [ 1]  109 	ld	a, #0x07
                                    110 ; genCall
      0082B0 CD 85 3A         [ 4]  111 	call	_TIM4_TimeBaseInit
                                    112 ;	./src/milis.c: 30: TIM4_ClearFlag(TIM4_FLAG_UPDATE);
                                    113 ; genSend
      0082B3 A6 01            [ 1]  114 	ld	a, #0x01
                                    115 ; genCall
      0082B5 CD 85 C2         [ 4]  116 	call	_TIM4_ClearFlag
                                    117 ;	./src/milis.c: 31: TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
                                    118 ; genIPush
      0082B8 4B 01            [ 1]  119 	push	#0x01
                                    120 ; genSend
      0082BA A6 01            [ 1]  121 	ld	a, #0x01
                                    122 ; genCall
      0082BC CD 83 97         [ 4]  123 	call	_TIM4_ITConfig
                                    124 ;	./src/milis.c: 32: ITC_SetSoftwarePriority(ITC_IRQ_TIM4_OVF, ITC_PRIORITYLEVEL_1);     // nízká priorita pøerušení
                                    125 ; genIPush
      0082BF 4B 01            [ 1]  126 	push	#0x01
                                    127 ; genSend
      0082C1 A6 17            [ 1]  128 	ld	a, #0x17
                                    129 ; genCall
      0082C3 CD 84 41         [ 4]  130 	call	_ITC_SetSoftwarePriority
                                    131 ;	./src/milis.c: 33: enableInterrupts();
                                    132 ;	genInline
      0082C6 9A               [ 1]  133 	rim
                                    134 ;	./src/milis.c: 34: TIM4_Cmd(ENABLE);
                                    135 ; genSend
      0082C7 A6 01            [ 1]  136 	ld	a, #0x01
                                    137 ; genCall
      0082C9 CC 84 25         [ 2]  138 	jp	_TIM4_Cmd
                                    139 ; genLabel
      0082CC                        140 00101$:
                                    141 ;	./src/milis.c: 35: }
                                    142 ; genEndFunction
      0082CC 81               [ 4]  143 	ret
                                    144 ;	Total init_milis function size at codegen: 32 bytes.
                                    145 	.area CODE
                                    146 	.area CONST
                                    147 	.area INITIALIZER
      008095                        148 __xinit__miliseconds:
      008095 00 00 00 00            149 	.byte #0x00, #0x00, #0x00, #0x00	; 0
                                    150 	.area CABS (ABS)
