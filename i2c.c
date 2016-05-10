#include "settings.h"

void I2C_Init()
{
    SCL_TRI = 0 ; // set clock port to output
    SDA_TRI = 0 ; // set data port to output
}

void I2C_Clock(void) 
{ 
    __delay_us(1); 
    SCL = 1;
    __delay_us(1);
    SCL = 0;
}

void I2C_Start() 
{ 
    SCL = 0; // Pull SCL low   
    SDA = 1; // Pull SDA High 
    __delay_us(1);   
    SCL = 1; //Pull SCL high 
    __delay_us(1);   
    SDA = 0; //Now Pull SDA LOW, to generate the Start Condition 
    __delay_us(1);   
    SCL = 0; //Finally Clear the SCL to complete the cycle 
}

void I2C_Stop(void) 
{ 
    SCL = 0; // Pull SCL low 
    __delay_us(1);   
    SDA = 0; // Pull SDA low 
    __delay_us(1);   
    SCL = 1; // Pull SCL High 
    __delay_us(1);   
    SDA = 1; // Now Pull SDA High, to generate the Stop Condition 
}

void I2C_Write(unsigned char dat) 
{ 
    unsigned char i ;   
    for(i=0;i<8;i++) // loop 8 times to send 1-byte of data 
    { 
        SDA = (dat & 0x80) ? 1 : 0 ;
   
        I2C_Clock(); // Generate Clock at SCL 

        dat = dat << 1; 
    } 
    SDA = 1; // Set SDA at last 
}

unsigned char I2C_Read(void) 
{
	unsigned char i, dat=0x00;   
    
    SDA_TRI = 1 ; // set pin for input
	
	for(i=0;i<8;i++) // loop 8times to read 1-byte of data 
	{ 
        __delay_us(1); 
        
        SCL = 1; // Pull SCL High 
        
        dat = dat << 1; //dat is Shifted each time and 
        
        if (SDA == 1)
            dat++;
        
        __delay_us(1);
          
        SCL = 0; // Clear SCL to complete the Clock        
	}
    
    SDA_TRI = 0 ; // set it back to output
    
return dat; // Finally return the received Byte* 
}

void I2C_Ack()
{ 
    SDA = 0; //Pull SDA low to indicate Positive ACK 
    I2C_Clock(); //Generate the Clock 
    SDA = 1; // Pull SDA back to High(IDLE state) 
}
 
 void I2C_NoAck() 
 { 
    SDA = 1; //Pull SDA high to indicate Negative/NO ACK 
    I2C_Clock(); // Generate the Clock 
    SCL = 1; // Set SCL */ 
 }
 
 