#include "stm8s.h"
#include "stdio.h"

void Delay (uint16_t nCount);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{

  /* Initialize I/Os in Output Mode */
  FLASH_SetProgrammingTime(FLASH_PROGRAMMODE_STANDARD);
  FLASH_Unlock(FLASH_MEMTYPE_DATA);

  uint32_t AddressValone = FLASH_DATA_START_PHYSICAL_ADDRESS; //use the first EEPROM byte
  uint32_t AddressValtwo = FLASH_DATA_START_PHYSICAL_ADDRESS + 1; //use the second EEPROM byte

  /* UART1 needs some settings:
    115200 as BAUD, 8 bit wordlength, 1 stopbit and no parity.
    Syncmode clock disabled, and let's enable both RX and TX so printf and getchar works
    */
    UART1_Init((uint32_t)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
                UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);


    printf("EEPROM test\n");

    //Read back the value from address one, write it to address 2.
	uint8_t val = FLASH_ReadByte(AddressValone);
	FLASH_ProgramByte(AddressValtwo, val);
	//Write the value increased by 1 to address one.
	FLASH_ProgramByte(AddressValone, (val+1));

	//If the value matches whats's in address two, it all worked.
	if(val == FLASH_ReadByte(AddressValtwo))
	{
		printf("EEPROM works, val is: %i \n", val);
	}
	else
	{
		printf("EEPROM failed, val is: %i, read value is: %i \n", val, FLASH_ReadByte(AddressValtwo));
	}

	while(1);  //stop for now
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

