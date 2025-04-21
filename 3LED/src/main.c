#include <stdbool.h>
#include <stm8s.h>
//#include <stdio.h>
#include "main.h"
#include "milis.h"
#include "delay.h"
#include "uart1.h"
#include "daughterboard.h"
#include <stdint.h>

#define LED1_PIN GPIO_PIN_2
#define LED2_PIN GPIO_PIN_3
#define LED3_PIN GPIO_PIN_4
#define BUTTON_PIN GPIO_PIN_4

uint8_t ledState = 0;

void main(void) {
 
    GPIO_Init(GPIOB, LED1_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(GPIOB, LED2_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
    GPIO_Init(GPIOB, LED3_PIN, GPIO_MODE_OUT_PP_LOW_FAST);

    GPIO_Init(GPIOE, BUTTON_PIN, GPIO_MODE_IN_PU_NO_IT); 

    while (1) {
    
        if (GPIO_ReadInputPin(GPIOE, BUTTON_PIN) == RESET) {
        
            uint16_t i = 0;
            while (i != 200) {
                __asm__("nop");
                i++;
            }

            GPIO_WriteLow(GPIOB, LED1_PIN);
            GPIO_WriteLow(GPIOB, LED2_PIN);
            GPIO_WriteLow(GPIOB, LED3_PIN);

            if (ledState == 0) {
                GPIO_WriteHigh(GPIOB, LED1_PIN);
            } else if (ledState == 1) {
                GPIO_WriteHigh(GPIOB, LED2_PIN);
            } else if (ledState == 2) {
                GPIO_WriteHigh(GPIOB, LED3_PIN);
            }

            ledState = (ledState + 1) % 3;

            while (GPIO_ReadInputPin(GPIOE, BUTTON_PIN) == RESET);
        }
    }
}