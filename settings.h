/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SETTINGS_H
#define	SETTINGS_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

#include "LCDTime.h"
#include "lcd_hd44780_pic16.h"
#include "myutils.h"
#include "custom_char.h"
#include "i2c.h"
#include "DS1307.h"

/************************************************
	LCD CONNECTIONS
*************************************************/

//LCD Data Port
#define LCD_DATA        D   //Port PB1-PB4 are connected to D4-D7
#define LCD_DATA_POS    4

//Register Select (RS)
#define LCD_RS_PORT     B
#define LCD_RS_POS      7

//Read/Write (RW)
#define LCD_RW_PORT     B
#define LCD_RW_POS      6

//Enable signal (E)
#define LCD_E_PORT      B
#define LCD_E_POS       5

// i2c clock pin
#define I2C_CLK_PORT    D
#define I2C_CLK_POS     1

// i2c data pin
#define I2C_DAT_PORT    D
#define I2C_DAT_POS     0


#define LCD_DATA_PORT 	PORT(LCD_DATA)
#define LCD_DATA_TRIS 	TRIS(LCD_DATA)

#define LCD_E           PORTBIT(LCD_E_PORT,LCD_E_POS)
#define LCD_E_TRIS      TRISBIT(LCD_E_PORT,LCD_E_POS)

#define LCD_RS          PORTBIT(LCD_RS_PORT,LCD_RS_POS)
#define LCD_RS_TRIS     TRISBIT(LCD_RS_PORT,LCD_RS_POS)

#define LCD_RW          PORTBIT(LCD_RW_PORT,LCD_RW_POS)
#define LCD_RW_TRIS     TRISBIT(LCD_RW_PORT,LCD_RW_POS)

#define SET_E() (LCD_E=1)
#define SET_RS() (LCD_RS=1)
#define SET_RW() (LCD_RW=1)

#define CLEAR_E() (LCD_E=0)
#define CLEAR_RS() (LCD_RS=0)
#define CLEAR_RW() (LCD_RW=0)

#define SCL              RD1
#define SCL_TRI          TRISD1
#define SDA              RD0
#define SDA_TRI          TRISD0

#define BUTTON           RB4
#define ENC_A            RB2
#define ENC_B            RB1
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Anti-clockwise step.
#define DIR_CCW 0x20

#define R_START 0x0
#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6

#define DS1307_ID 0xD0 // DS1307 ID   
#define SEC_ADDRESS 0x00 // Address to access Ds1307 SECONDS register 
#define DATE_ADDRESS 0x03 // Address to access Ds1307 DATE register 
#define CONTROL 0x07 // Address to access Ds1307 CONTROL register

#define MENU_NONE   0
#define MENU_TIME   1
#define MENU_DATE   2

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

