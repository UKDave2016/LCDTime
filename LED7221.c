#include "settings.h"

unsigned char led_digits[10] = { 0x00,0xBF,0xF9,0xDF,0xB6,0xA2,0x8E,0x3e,0x0F,0xE6 } ;




// digit 0-3
// value 0-9
void setLED(int digit, int value)
{
    unsigned char d = 0x80 >> (3-digit) ;
    unsigned char v = led_digits[value] ;
    
    sendLED((v << 8) | d);
}

void sendLED(unsigned int c)
{
    int i ;
    
    LED_LOAD = 0 ;
    __delay_ms(4);
    
    for (i=0;i<16;i++)
    {
        __delay_ms(1);
        
        if (c & 0x8000)
            LED_DIN = 1 ;
        else
            LED_DIN = 0 ;

        c = c << 1 ;
        
        __delay_ms(1) ;
        LED_CLK = 1 ;
        __delay_ms(1) ;
        LED_CLK = 0 ;
    }   
    
    __delay_ms(4);
    LED_LOAD = 1 ;
}

void initLED()
{
    TRISC0 = 0 ;
    TRISC1 = 0 ;
    TRISC2 = 0 ;
    
    LED_LOAD = 1 ; // !CS
    
    sendLED(0x0900) ; // no decoding
    sendLED(0x0A00) ; // 0/16 intensity
    sendLED(0x0B07) ; // use all 7 digit lines
    sendLED(0x0C01) ; // enable

    sendLED(0x0F01) ; // test
    __delay_ms(750);
    __delay_ms(750);
    __delay_ms(750);
    __delay_ms(750);
    sendLED(0x0F00) ; // test off
}

