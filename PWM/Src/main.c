#include "stm8s.h"

#define PWM1_VAL    ((uint16_t)2048)    //50%
#define PWM2_VAL    ((uint16_t)1536)    //37,5%
#define PWM3_VAL    ((uint16_t)1024)    //25%
#define PWM4_VAL    ((uint16_t)512)     //12.5%

#define PWM5_VAL    ((uint16_t)3072)    //75%
#define PWM6_VAL    ((uint16_t)2048)    //50%
#define PWM7_VAL    ((uint16_t)1024)    //25%

#define LED_GPIO_PORT  (GPIOD)
#define LED_GPIO_PINS  (GPIO_PIN_0)


static void TIM1_Config(void);
static void TIM2_Config(void);
void Delay(uint16_t nCount);


void main(void)
{

  /* Initialize I/Os in Output Mode */
  GPIO_Init(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS, GPIO_MODE_OUT_PP_LOW_FAST);

  TIM1_Config();
  TIM2_Config();



  while (1)
  {
    GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
    TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, PWM1_VAL, TIM1_OCPOLARITY_HIGH,
               TIM1_OCIDLESTATE_SET);
    TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,PWM5_VAL, TIM2_OCPOLARITY_HIGH);
    Delay(0xFFFF);

    GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);
    TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, PWM4_VAL, TIM1_OCPOLARITY_HIGH,
               TIM1_OCIDLESTATE_SET);
    TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,PWM7_VAL, TIM2_OCPOLARITY_HIGH);
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

static void TIM1_Config(void)
{

  TIM1_DeInit();

  //Timer 1 counts to 4095, prescaler not needed (0), count up, repitition counter 0 as well.
  TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, 4095, 0);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  
  /*
  In order: OCMODE_PWM2 for PWM output, OUTPUTSTATE_ENABLE to output to the pin.
  OUTPUTNSTATE_DISABLE to disable the inverted PWM output pin, PWM1_VAL is the output value.
  OCPOLARITY_LOW and OCPOLARITY_HIGH are used to generate the normal/inverted output, AFAIK, 
  but no inverted one is used here. At idle the normal output is low, inverted one high, again AFAIK.
  channel 4 doesn't have the inverted output so is a bit simpler.

  PreloadConfig enabled means that when writing a new value to a PWM channel it will be updated at the next PWM cycle
  and not directly, helping against glitches.

  Yes timer 1 has a load of options :)
  */

  //Pin PC_1
  TIM1_OC1Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
               PWM1_VAL, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
               TIM1_OCNIDLESTATE_RESET); 
  TIM1_OC1PreloadConfig(ENABLE);

  //Pin PC_2
  TIM1_OC2Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE, PWM2_VAL,
               TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET, 
               TIM1_OCNIDLESTATE_RESET);
  TIM1_OC2PreloadConfig(ENABLE);

  //Pin PC_3
  TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
               PWM3_VAL, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
               TIM1_OCNIDLESTATE_RESET);
  TIM1_OC3PreloadConfig(ENABLE);

  //Pin PC_4
  TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, PWM4_VAL, TIM1_OCPOLARITY_LOW,
               TIM1_OCIDLESTATE_SET);
  TIM1_OC4PreloadConfig(ENABLE);

  // TIM1 counter enable 
  TIM1_Cmd(ENABLE);

  // TIM1 enable outputs
  TIM1_CtrlPWMOutputs(ENABLE);
}


static void TIM2_Config(void)
{
  // But no worries, TIM2 is a bit simpler, and different.
  // It's a 16 bit timer with a prescaler that can be 1-32786, but only to the power of two. So 1, 2, 4, 8 etc.
  // TIM1 is a 16 bit timer with a 16 bit prescaler.
  // TIM2 can only count up, the datasheet lists all the differences
  TIM2_TimeBaseInit(TIM2_PRESCALER_1, 4095);

  // A lot easier, enable PWM, enable the output on the GPIO, add the value and it's a go.
  //Pin PD_4
  TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,PWM5_VAL, TIM2_OCPOLARITY_HIGH);
  TIM2_OC1PreloadConfig(ENABLE);

  //Pin PD_3
  TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,PWM6_VAL, TIM2_OCPOLARITY_HIGH);
  TIM2_OC2PreloadConfig(ENABLE);
      
  //Pin PA_3
  TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,PWM7_VAL, TIM2_OCPOLARITY_HIGH);
  TIM2_OC3PreloadConfig(ENABLE);

  TIM2_ARRPreloadConfig(ENABLE);

  // TIM2 enable counter 
  TIM2_Cmd(ENABLE);
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
