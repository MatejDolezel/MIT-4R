#include "main.h"
#include "max7219.h"
#include "milis.h"
#include "swspi.h"
#include <stdbool.h>
#include <stm8s.h>

#define NCCLK_PORT GPIOB
#define NCCLK_PIN GPIO_PIN_0
#define NCDATA_PORT GPIOB
#define NCDATA_PIN GPIO_PIN_1
#define NCSW_PORT GPIOB
#define NCSW_PIN GPIO_PIN_2

void init(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovani MCU na 16MHz

    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(BTN_PORT, BTN_PIN, GPIO_MODE_IN_FL_NO_IT);
    /*GPIO_Init(DIN_PORT, DIN_PIN, GPIO_MODE_OUT_PP_LOW_FAST);*/
    /*GPIO_Init(CS_PORT,  CS_PIN,  GPIO_MODE_OUT_PP_LOW_FAST);*/
    /*GPIO_Init(CLK_PORT, CLK_PIN, GPIO_MODE_OUT_PP_LOW_FAST);*/
    swspi_init();

    GPIO_Init(NCCLK_PORT, NCCLK_PIN, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(NCDATA_PORT, NCDATA_PIN, GPIO_MODE_IN_FL_NO_IT);
    GPIO_Init(NCSW_PORT, NCSW_PIN, GPIO_MODE_IN_PU_NO_IT);

    init_milis();
}

uint8_t minuty1 = 0;

uint8_t sekundy1 = 0;

uint8_t minuty2 = 0;

uint8_t sekundy2 = 0;

int check_ncoder(void)
{
    static bool last = 0;
    
    int8_t r = 0;

    bool now = (bool)PUSH(NCCLK);
    
    if (last && !now) {
        
        if ((bool)PUSH(NCDATA))
            r = 1;
        else
            r = -1;
    }
    
    if (!last && now) {
        
        if ((bool)PUSH(NCDATA))
            r = -1;
        else
            r = 1;
    }
    last = now;
    return r;
}

void show_dispaly(void)
{
    swspi_tx2x8(DIGIT7, minuty2 / 10);
    swspi_tx2x8(DIGIT6, (minuty2 % 10) | 0xF0);
    swspi_tx2x8(DIGIT5, sekundy2 / 10);
    swspi_tx2x8(DIGIT4, sekundy2 % 10);

    swspi_tx2x8(DIGIT3, minuty1 / 10);
    swspi_tx2x8(DIGIT2, (minuty1 % 10) | 0xF0);
    swspi_tx2x8(DIGIT1, sekundy1 / 10);
    swspi_tx2x8(DIGIT0, sekundy1 % 10);
}

int main(void)
{

    uint32_t time = 0;
    
    uint32_t time_check = 0;

    init();

    swspi_tx2x8(SHUTDOWN, SHUTDOWN_ON);
    swspi_tx2x8(INTENSITY, 1);
    swspi_tx2x8(SCAN_LIMIT, 7);
    swspi_tx2x8(DECODE_MODE, DECODE_ALL);
    swspi_tx2x8(DISPLAY_TEST, DISPLAY_TEST_OFF);


    while (1) {
        
        if (milis() - time > 111) {
            time = milis();

            REVERSE(LED);

            show_dispaly();
            minuty1++;

        }
        
        if (milis() - time_check > 3) {
            time_check = milis();

            minuty2 += check_ncoder();
        }
    }
}