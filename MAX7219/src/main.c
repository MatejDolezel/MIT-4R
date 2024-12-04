#include "stm8s.h"


#define CLK_GPIO GPIOD              
#define CLK_PIN  GPIO_PIN_4         
#define DATA_GPIO GPIOD             
#define DATA_PIN  GPIO_PIN_3         
#define CS_GPIO GPIOD               
#define CS_PIN  GPIO_PIN_2          
#define CLK_HIGH         GPIO_WriteHigh(CLK_GPIO, CLK_PIN)
#define CLK_LOW          GPIO_WriteLow(CLK_GPIO, CLK_PIN)
#define DATA_HIGH        GPIO_WriteHigh(DATA_GPIO, DATA_PIN)
#define DATA_LOW         GPIO_WriteLow(DATA_GPIO, DATA_PIN)
#define CS_HIGH          GPIO_WriteHigh(CS_GPIO, CS_PIN)
#define CS_LOW           GPIO_WriteLow(CS_GPIO, CS_PIN)

// makra adres/příkazů pro ovládání displeje
#define DIGIT0           1
#define DECODE_MODE      9
#define INTENSITY        10
#define SCAN_LIMIT       11
#define SHUTDOWN         12
#define DISPLAY_TEST     15

// makra argumentů
#define DISPLAY_ON       1
#define DISPLAY_OFF      0
#define DISPLAY_TEST_OFF 0
#define DECODE_ALL       0xFF
#define DECODE_NONE      0

void max7219_init(void);
void max7219_posli(uint8_t adresa, uint8_t data);
void delay(uint32_t ms);

void main(void) {
    uint8_t cislo = 0;

    max7219_init();

    while (1) {
        max7219_posli(DIGIT0, cislo);

        cislo = (cislo + 1) % 10;

        delay(500);
    }
}

void max7219_init(void) {
    // Nastavení pinů jako výstup
    GPIO_Init(CS_GPIO, CS_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CLK_GPIO, CLK_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(DATA_GPIO, DATA_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);

    // Inicializace displeje
    max7219_posli(DECODE_MODE, DECODE_ALL);  // zapnutí znakového režimu
    max7219_posli(SCAN_LIMIT, 0);           // Používám jen jednu cifru
    max7219_posli(INTENSITY, 1);            // Nízký jas
    max7219_posli(DISPLAY_TEST, DISPLAY_TEST_OFF); // Vypnutí testu
    max7219_posli(SHUTDOWN, DISPLAY_ON);    // Zapnutí displeje
}

void max7219_posli(uint8_t adresa, uint8_t data) {
    uint8_t maska;

    CS_LOW; // Aktivace komunikace (LOAD/CS do Low)

    // Odeslání adresy
    maska = 0x80;
    while (maska) {
        if (maska & adresa) {
            DATA_HIGH;
        } else {
            DATA_LOW;
        }
        CLK_HIGH;
        CLK_LOW;
        maska >>= 1;
    }

    // Odeslání dat
    maska = 0x80;
    while (maska) {
        if (maska & data) {
            DATA_HIGH;
        } else {
            DATA_LOW;
        }
        CLK_HIGH; 
        CLK_LOW;
        maska >>= 1;
    }

    CS_HIGH; // Deaktivace komunikace (LOAD/CS do High)
}

void delay(uint32_t ms) {
    while (ms--) {
        for (uint32_t i = 0; i < 200; i++) {
            __asm__("nop");
        }
    }
}