#include "stm8s.h"
#include "stdio.h"

#define ADDRESS     0x96

void Delay (uint16_t nCount);
void I2C_WriteByte(uint8_t address, uint8_t byte);
uint8_t I2C_ReadByte(uint8_t address);

void main(void)
{
  uint8_t temperature;
    
  UART1_DeInit();

  CLK_PeripheralClockConfig(CLK_PERIPHERAL_I2C, ENABLE);
  I2C_Cmd( ENABLE);
  I2C_Init(I2C_MAX_STANDARD_FREQ, ADDRESS, I2C_DUTYCYCLE_2, I2C_ACK_CURR, 
           I2C_ADDMODE_7BIT, 16);

  /* UART1 needs some settings:
  115200 as BAUD, 8 bit wordlength, 1 stopbit and no parity.
  Syncmode clock disabled, and let's enable both RX and TX so printf and getchar works
  */
  UART1_Init((uint32_t)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
              UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

  while (1)
  {

    // to read a register, first the register address has to be selected by writing it to I2C.
    I2C_WriteByte(ADDRESS, 0x00);     
    // then the register can be read by reading a byte.
    temperature =  I2C_ReadByte(ADDRESS);

    printf("temperature is: %u\n", temperature);
    Delay(0xFFFF);
  }

}

void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

void I2C_WriteByte(uint8_t address, uint8_t byte)
{
  I2C_GenerateSTART(ENABLE);
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));              //wait till the start event has happened
  I2C_Send7bitAddress( (uint8_t)address, I2C_DIRECTION_TX);           //send the address, transmit bit 
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));   //wait till the address is send
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTING));        //wait till there is no data in the send qeueu
  I2C_SendData(byte);                                                 //send a data byte
  I2C_GenerateSTOP( ENABLE);                                          //all done, stop event
}

uint8_t I2C_ReadByte(uint8_t address)
{
  uint8_t data = 0;
  I2C_GenerateSTART(ENABLE);
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress((uint8_t)address, I2C_DIRECTION_RX);          //send the addres with receive byte now
  while (!I2C_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));  
  while(I2C_GetFlagStatus( I2C_FLAG_RXNOTEMPTY) == RESET);          //wait till a byte is received
  data = I2C_ReceiveData();                                         //read it in
  I2C_GenerateSTOP( ENABLE);
  return data;
}

int putchar(int c) 
{
  //Write a character and wait till it's done
  UART1_SendData8(c);
  while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET);
  return 0;
}

int getchar(void)
{

  int c = 0;
  //Loop until a character can be read
  while (UART1_GetFlagStatus(UART1_FLAG_RXNE) == RESET);
    c = UART1_ReceiveData8();
  return (c);
}

