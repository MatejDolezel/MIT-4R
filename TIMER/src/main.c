#include "stm8s.h"

// makra, kterými volíme komunikační piny
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

volatile uint8_t cislo = 0; // Globální proměnná

void max7219_init(void);
void max7219_posli(uint8_t adresa, uint8_t data);
void tim2_init(void);

void main(void) {
    max7219_init(); 
    tim2_init();   

    enableInterrupts(); // Povolení globálních přerušení

    while (1) {
        max7219_posli(DIGIT0, cislo);

        // Hlavní smyčka neprovádí nic - veškerá logika je v přerušení
    }
}

void max7219_init(void) {
    GPIO_Init(CS_GPIO, CS_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CLK_GPIO, CLK_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(DATA_GPIO, DATA_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);

    max7219_posli(DECODE_MODE, DECODE_ALL);  
    max7219_posli(SCAN_LIMIT, 0);           
    max7219_posli(INTENSITY, 1);            
    max7219_posli(DISPLAY_TEST, DISPLAY_TEST_OFF); 
    max7219_posli(SHUTDOWN, DISPLAY_ON);    
}

void max7219_posli(uint8_t adresa, uint8_t data) {
    uint8_t maska;

    CS_LOW;

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

    CS_HIGH;
}

// Inicializace časovače TIM2
void tim2_init(void) {
    TIM2_TimeBaseInit(TIM2_PRESCALER_1024, 39062); // Nastavení předděličky a periody
    TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);        // Povolení přerušení při přetečení
    TIM2_Cmd(ENABLE);                             // Spuštění časovače
}

// ISR pro přerušení časovače TIM2
@far @interrupt void TIM2_UPD_OVF_IRQHandler(void) {
    TIM2_ClearITPendingBit(TIM2_IT_UPDATE); // Vymazání příznaku přerušení

    // Zvýšení číslice a resetování na 0 při dosažení 10
    cislo = (cislo + 1) % 10;
}