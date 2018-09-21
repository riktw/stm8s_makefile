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
  printf("Now with the added bonus of GDB debugging :D\n");
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

