#include "stm8s.h"
#include "stdio.h"

void main(void)
{

  char receivedByte;
    
  UART1_DeInit();

  /* UART1 needs some settings:
  115200 as BAUD, 8 bit wordlength, 1 stopbit and no parity.
  Syncmode clock disabled, and let's enable both RX and TX so printf and getchar works
  */
  UART1_Init((uint32_t)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
              UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

  printf("Printf with an STM8S is remarably easy :D\n");
  printf("Enter text now and it will be echoed with a newline added\n");

  while (1)
  {
    receivedByte = getchar();
    printf("%c\n", receivedByte);
  }

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


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
