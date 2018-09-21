#include "stm8s.h"
#include "stdio.h"

void Delay(uint16_t nCount);

void main(void)
{

  uint16_t adcValue;
    
  ADC1_DeInit();
  UART1_DeInit();

  /* UART1 needs some settings:
  115200 as BAUD, 8 bit wordlength, 1 stopbit and no parity.
  Syncmode clock disabled, and let's enable both RX and TX so printf and getchar works
  */
  UART1_Init((uint32_t)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
              UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);

  /*
    lot of options, again: CONVERSIONMODE_SINGLE means, do a single conversion at a time. ADC1_CHANNEL_0 selects channel 0.
    ADC1_PRESSEL_FCPU_D8 is the sample speed, longer sample speed means less noise. 
    ADC1_EXTTRIG_GPIO and ADC1_SCHMITTTRIG_CHANNEL0 are both not used (DISABLE) 
    ADC1_ALIGN_RIGHT or ADC1_ALIGN_LEFT decides how to read in the sample, ADC1_ALIGN_RIGHT is the normal alignment.
  */
  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_0, ADC1_PRESSEL_FCPU_D8, ADC1_EXTTRIG_GPIO,
              DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL0, DISABLE);

  ADC1_Cmd(ENABLE);

  printf("ADC demo, reads the value on ADC pin x a few times per second and prints it.\n");

  while (1)
  {
    /*
      Set the ADC to a channel, start measuring, wait until the measurement is taken
      clear the measurement done flag and print the measurement out and repeat.
    */
    ADC1_ConversionConfig(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_0, ADC1_ALIGN_RIGHT);
    printf("Switched to ADC channel 0\n");
    adcValue = ADC1_GetConversionValue();
    while(!ADC1_GetFlagStatus(ADC1_FLAG_EOC));
    ADC1_GetFlagStatus(ADC1_FLAG_EOC);
    printf("ADC Channel 0 value is: %i\n", adcValue);
    Delay(0xFFFF);


    ADC1_ConversionConfig(ADC1_CONVERSIONMODE_SINGLE, ADC1_CHANNEL_1, ADC1_ALIGN_RIGHT);
    printf("Switched to ADC channel 1\n");
    adcValue = ADC1_GetConversionValue();
    while(!ADC1_GetFlagStatus(ADC1_FLAG_EOC));
    ADC1_GetFlagStatus(ADC1_FLAG_EOC);
    printf("ADC Channel 1 value is: %i\n", adcValue);
    Delay(0xFFFF);

    printf("\n");
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


