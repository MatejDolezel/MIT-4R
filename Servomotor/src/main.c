#include <stdbool.h>
#include <stm8s.h>
//#include <stdio.h>
#include "main.h"
#include "milis.h"
//#include "delay.h"
//#include "uart1.h"

#define PWM_PORT GPIOD
#define PWM_PIN GPIO_PIN_4

uint16_t compare = 500;   

void init(void) {
    
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovani MCU na 16MHz

    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);

    init_milis();
    // init_uart1();

    TIM2_TimeBaseInit(     // inicializace časovače TIM2 T=20ms
        TIM2_PRESCALER_16, // předdělička
        20000 - 1          // strop čítače
    );

    TIM2_OC1Init(                // inicializace kanálu OC1; Nucleo => PD4
        TIM2_OCMODE_PWM1,        // funkce kanálu PWM1
        TIM2_OUTPUTSTATE_ENABLE, // povolit HW výstup
        compare,                 // překlápěcí práh
        TIM2_OCPOLARITY_HIGH     // polarita výsledného signálu
    );

    GPIO_Init(PWM_PORT, PWM_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);

    TIM2_Cmd(ENABLE); // spuštění čítače
    TIM2_OC1PreloadConfig(ENABLE); // povolení preload prahového registru

}

int main(void) {

    uint32_t time = 0;

    init();

    while (1) {
        if (milis() - time > 333) {
            
            REVERSE(LED);
            time = milis();

            compare += 100;
            if (compare > 2500) {     
                compare = 500;
            }
            TIM2_SetCompare1(compare);

        }
        // delay_ms(333);
    }
}