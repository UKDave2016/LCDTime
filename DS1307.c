#include "settings.h"


int DS1307_Init() 
{ 
    unsigned char s = 0 ;
    
    I2C_Start(); // Start I2C communication   
    DS1307_Write(0xd0); // Connect to DS1307 by sending its ID on I2c Bus 
    DS1307_Write(0x00); // register zero
    I2C_Start();
    DS1307_Write(0xd1); // Select the Ds1307 ControlRegister to configure Ds1307   
    s = DS1307_Read(); 
    I2C_NoAck();
    
    if (s & 0x80)
    { // clock on halt
        s = s & 0x7f ;
        I2C_Start();
        DS1307_Write(DS1307_ID); // connect to DS1307 by sending its ID on I2c Bus 
        DS1307_Write(SEC_ADDRESS); // Select the SEC RAM address   
        DS1307_Write(s); // Write sec on RAM address 00H 
        I2C_Stop(); // Stop I2C communication after initialising DS1307
        return 1 ;
    }
    else
        I2C_Stop();

    return 0 ;
} 

void DS1307_Write(unsigned char dat) 
{ 
I2C_Write(dat); // Connect to DS1307 by sending its ID on I2c Bus 
I2C_Clock(); 
} 

unsigned char DS1307_Read() 
{ 
return I2C_Read(); 
}

void DS1307_SetTime(unsigned char hh, unsigned char mm, unsigned char ss) 
{ 
I2C_Start(); // Start I2C communication   
DS1307_Write(DS1307_ID); // connect to DS1307 by sending its ID on I2c Bus 
DS1307_Write(SEC_ADDRESS); // Select the SEC RAM address   
DS1307_Write(ss); // Write sec on RAM address 00H 
DS1307_Write(mm); // Write min on RAM address 01H 
DS1307_Write(hh); // Write hour on RAM address 02H   
I2C_Stop(); // Stop I2C communication after Setting the Time 
}

void DS1307_SetDate(unsigned char nn,unsigned char dd, unsigned char mm, unsigned char yy) 
{ 
I2C_Start(); // Start I2C communication   
DS1307_Write(DS1307_ID); // connect to DS1307 by sending its ID on I2c Bus 
DS1307_Write(DATE_ADDRESS); // Request DAY RAM address at 03H   
DS1307_Write(nn); // Write day of week on RAM address 03H 
DS1307_Write(dd); // Write date on RAM address 04H 
DS1307_Write(mm); // Write month on RAM address 05H 
DS1307_Write(yy); // Write year on RAM address 06h   
I2C_Stop(); // Stop I2C communication after Setting the Date 
}

void DS1307_GetTime(unsigned char *h_ptr,unsigned char *m_ptr,unsigned char *s_ptr) 
{ 
I2C_Start(); // Start I2C communication   
DS1307_Write(DS1307_ID); // connect to DS1307 by sending its ID on I2c Bus 
DS1307_Write(SEC_ADDRESS); // Request Sec RAM address at 00H   
I2C_Stop(); // Stop I2C communication after selecting Sec Register   
I2C_Start(); // Start I2C communication 
DS1307_Write(0xD1); // connect to DS1307( under Read mode) //by sending its ID on I2c Bus   
*s_ptr = DS1307_Read(); I2C_Ack(); // read second and return Positive ACK 
*m_ptr = DS1307_Read(); I2C_Ack(); // read minute and return Positive ACK 
*h_ptr = DS1307_Read(); I2C_NoAck(); // read hour and return Negative/No ACK   
I2C_Stop(); // Stop I2C communication after reading the Time 
} 

void DS1307_GetDate(unsigned char *n_ptr,unsigned char *d_ptr,unsigned char *m_ptr,unsigned char *y_ptr) 
{ 
I2C_Start(); // Start I2C communication   
DS1307_Write(DS1307_ID); // connect to DS1307 by sending its ID on I2c Bus 
DS1307_Write(DATE_ADDRESS); // Request DAY RAM address at 04H   
I2C_Stop(); // Stop I2C communication after selecting DAY Register     
I2C_Start(); // Start I2C communication 
DS1307_Write(0xD1); // connect to DS1307( under Read mode) // by sending its ID on I2c Bus   
*n_ptr = DS1307_Read(); I2C_Ack(); // read Day of week and return Positive ACK 
*d_ptr = DS1307_Read(); I2C_Ack(); // read Day and return Positive ACK 
*m_ptr = DS1307_Read(); I2C_Ack(); // read Month and return Positive ACK 
*y_ptr = DS1307_Read(); I2C_NoAck(); // read Year and return Negative/No ACK   
I2C_Stop(); // Stop I2C communication after reading the Time 
} 

void DS1307_readRam(unsigned char *ptr, int offset, int length)
{
    I2C_Start(); // Start I2C communication   
    DS1307_Write(DS1307_ID); // connect to DS1307 by sending its ID on I2c Bus 
    DS1307_Write(DS_RAM + offset); // Request DAY RAM address at 04H   
    I2C_Stop(); // Stop I2C communication after selecting Sec Register   
    I2C_Start(); // Start I2C communication 
    DS1307_Write(0xD1); // connect to DS1307( under Read mode) //by sending its ID on I2c Bus   
    while(length-- > 1)
        *ptr++ = DS1307_Read(); I2C_Ack(); // read second and return Positive ACK 
    *ptr = DS1307_Read(); I2C_NoAck();
    I2C_Stop();
}

void DS1307_writeRam(unsigned char *ptr, int offset, int length)
{
    I2C_Start(); // Start I2C communication   
    DS1307_Write(DS1307_ID); // connect to DS1307 by sending its ID on I2c Bus 
    DS1307_Write(DS_RAM + offset); // Request DAY RAM address at 04H   
    
    while(length-- > 0)
        DS1307_Write(*ptr++);

    I2C_Stop();    
}

