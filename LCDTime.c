/*
 * File:   LCDTime.c
 * Author: Dave
 *
 * Created on 08 May 2016, 09:57
 */

#include "settings.h"

#pragma config FOSC = XT        // Oscillator Selection bits
#pragma config WDTE = OFF       // Watchdog Timer Enable bit
#pragma config PWRTE = ON      // Power-up Timer Enable bit
#pragma config BOREN = ON       // Brown-out Reset Enable bit
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

int hour=6, minute=5, seconds=4, year=16, month=5, date=8, day = 1 ;
char last_hour = 0xee ;

unsigned char bButton = 0 ;
unsigned char state = R_START;

const unsigned char ttable[7][4] = {
  // R_START
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},
  // R_CW_FINAL
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},
  // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},
  // R_CW_NEXT
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},
  // R_CCW_BEGIN
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},
  // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW},
  // R_CCW_NEXT
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START},
};


const unsigned char monthDays[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 } ;
unsigned char menuFunction = MENU_NONE ;

void main(void) 
{
    I2C_Init() ;
    LCDInit(LS_NONE);
    DS1307_Init() ;

    LCDClear();
    
   // initLED() ;
    
   while(1)
  {
      readClock();
      
      showClock() ;           
      
      readInputs() ;
      
      if (bButton)
      {
        doMenu();
     }
  }
}

void doMenu()
{   
    while(bButton)
        readInputs();
    
    // set the new time
    if (menuFunction == MENU_NONE | menuFunction == MENU_TIME)
    {
        int h,m,s ;
        
        h = hour ;
        m = minute ;
        s = seconds ;
        
        LCDClear();
        LCDWriteString("Set Hours");
        
        LCDGotoXY(0,1) ;
        showTime();

        while(!bButton)
        {
            readInputs();
            
            if (state & DIR_CW)
            {
                hour++;
                if (hour > 23)
                    hour = 0 ;
            }
            else if (state & DIR_CCW)
            {
                hour--;
                if (hour < 0)
                    hour = 0 ;
            }
            
            if (state)
            {
                LCDGotoXY(0,1) ;
                showTime();
            }
        }
        
        while(bButton)
            readInputs();
    
        LCDGotoXY(0,0) ;
        LCDWriteString("Set Minutes");

        while(!bButton)
        {
            readInputs();
            
            if (state & DIR_CW)
            {
                minute++;
                if (minute > 59)
                    minute = 0 ;
            }
            else if (state & DIR_CCW)
            {
                minute--;
                if (minute < 0)
                    minute = 0 ;
            }
            
            if (state)
            {
                LCDGotoXY(0,1) ;
                showTime();
            }
        }
        
        while(bButton)
            readInputs();

        LCDGotoXY(0,0) ;
        LCDWriteString("Set Seconds");

        while(!bButton)
        {
            readInputs();
            
            if (state & DIR_CW)
            {
                seconds++;
                if (seconds > 59)
                    seconds = 0 ;
            }
            else if (state & DIR_CCW)
            {
                seconds--;
                if (seconds < 0)
                    seconds = 0 ;
            }
            
            if (state)
            {
                LCDGotoXY(0,1) ;
                showTime();
            }
        }
        
        // save changes
        if (h != hour || m != minute || s != seconds)
        {
            h = ((hour / 10) << 4) + hour % 10 ;
            m = ((minute / 10) << 4) + minute % 10 ;
            s = ((seconds / 10) << 4) + seconds % 10 ;

            DS1307_SetTime(h,m,s) ;
        }
        
        while(bButton)
            readInputs();
    }
    
    // set the new date
    if (menuFunction == MENU_NONE | menuFunction == MENU_DATE)
    {
        int n,d,m,y ;
        
        n = day ;
        d = date ;
        m = month ;
        y = year ;
        
        LCDClear();
        LCDWriteString("Set Year");
        
        LCDGotoXY(0,1) ;
        showDate();

        while(!bButton)
        {
            readInputs();
            
            if (state & DIR_CW)
            {
                year++;
                if (year > 99)
                    year = 0 ;
            }
            else if (state & DIR_CCW)
            {
                year--;
                if (year < 0)
                    date = 99 ;
            }
            
            if (state)
            {
                LCDGotoXY(0,1) ;
                showDate();
            }
        }
        
        while(bButton)
            readInputs();
    
        LCDGotoXY(0,0) ;
        LCDWriteString("Set Month");

        while(!bButton)
        {
            readInputs();
            
            if (state & DIR_CW)
            {
                month++;
                if (month > 12)
                    month = 1 ;
            }
            else if (state & DIR_CCW)
            {
                month--;
                if (!month)
                    month = 12 ;
            }
            
            if (state)
            {
                LCDGotoXY(0,1) ;
                showDate();
            }
        }
        
        while(bButton)
            readInputs();

        LCDGotoXY(0,0) ;
        LCDWriteString("Set Date ");

        while(!bButton)
        {
            readInputs();
            
            if (state & DIR_CW)
            {
                date++;
                if (date > monthDays[month-1])
                    date = 1 ;
            }
            else if (state & DIR_CCW)
            {
                date--;
                if (date < 0)
                    date = monthDays[month-1] ;
            }
            
            if (state)
            {
                LCDGotoXY(0,1) ;
                showDate();
            }
        }
        
        while(bButton)
            readInputs();

        LCDGotoXY(0,0) ;
        LCDWriteString("Set Day  ");

        while(!bButton)
        {
            readInputs();
            
            if (state & DIR_CW)
            {
                day++;
                if (day > 7)
                    day = 1 ;
            }
            else if (state & DIR_CCW)
            {
                day--;
                if (day < 0)
                    day = 7 ;
            }
            
            if (state)
            {
                LCDGotoXY(0,1) ;
                showDate();
            }
        }

        if (n != day || d != date || m != month || y != year)
        {
            n = ((day / 10) << 4) + day % 10 ;
            d = ((date / 10) << 4) + date % 10 ;
            m = ((month / 10) << 4) + month % 10 ;
            y = ((year / 10) << 4) + year % 10 ;

            DS1307_SetDate(n,d,m,y) ;
        }

        
        while(bButton)
            readInputs();
    }
}

void readInputs()
{
 
    bButton = 0 ;
    
    if (BUTTON == 1)
    {
        __delay_us(15) ;
        if (BUTTON == 1)
        {
            bButton = 1 ;
            return ;
        }
    }
    
   unsigned char pinstate = (ENC_B << 1) | ENC_A ;
  // Determine new state from the pins and state table.
   state = ttable[state & 0xf][pinstate];
}

void readClock()
{
    unsigned char a,b,c,n ;
    
    DS1307_GetTime(&a,&b,&c);
    
    hour = (a % 16) + ((a / 16 ) * 10) ;
    minute = (b % 16) + ((b / 16 ) * 10) ;
    seconds = (c % 16) + ((c / 16 ) * 10) ;
    
    if (hour != last_hour)
    {
        last_hour = hour ;
        
        DS1307_GetDate(&n,&a,&b,&c) ;
        
        day = (n % 16) ; // 1-7
        date = (a % 16) + ((a / 16 ) * 10) ;
        month = (b % 16) + ((b / 16 ) * 10) ;
        year = (c % 16) + ((c / 16 ) * 10) ;
    }
}

void showClock()
{
    LCDGotoXY(0,0) ;
    showTime() ;
    
    LCDGotoXY(0,1) ;
    showDate() ;
}


void showTime()
{
    LCDWriteInt(hour,2);
    LCDData(':') ;
    LCDWriteInt(minute,2);
    LCDData(':') ;
    LCDWriteInt(seconds,2);
    
//    setLED(0,minute / 10) ;
//    setLED(1,minute % 10) ;
//    setLED(2,seconds / 10) ;
//    setLED(3,seconds % 10) ;
}

void showDate()
{
    LCDWriteInt(date,2);
    LCDData('/') ;
    LCDWriteInt(month,2);
    LCDData('/') ;
    LCDData('2') ;
    LCDData('0') ;
    LCDWriteInt(year,2);
    LCDData(32) ;
    LCDData(32) ;
    switch(day)
    {
        case    1   :   LCDWriteString("Mon") ; break ;
        case    2   :   LCDWriteString("Tue") ; break ;
        case    3   :   LCDWriteString("Wed") ; break ;
        case    4   :   LCDWriteString("Thu") ; break ;
        case    5   :   LCDWriteString("Fri") ; break ;
        case    6   :   LCDWriteString("Sat") ; break ;
        case    7   :   LCDWriteString("Sun") ; break ;
    } ;
}
