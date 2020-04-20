#include "stm8s.h"
#include "LedMatrix.h"
#include "stdio.h"

#define PWM_VAL    ((uint16_t)0)    //75%

#define TIM4_PERIOD       255
#define LED_PWM 60

static void TIM1_Config(void);
static void TIM2_Config(void);
static void TIM4_Config(void);
static void UART_Config(void);

static uint8_t test_O[7][5] =
		   {{0, LED_PWM, LED_PWM, LED_PWM, 0},
			{LED_PWM, 0, 0, 0, LED_PWM},
			{LED_PWM, 0, 0, 0, LED_PWM},
			{LED_PWM, 0, 0, 0, LED_PWM},
			{LED_PWM, 0, 0, 0, LED_PWM},
			{LED_PWM, 0, 0, 0, LED_PWM},
			{0, LED_PWM, LED_PWM, LED_PWM, 0}};

void main(void)
{
	CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
	TIM1_Config();
	TIM2_Config();
	TIM4_Config();
	UART_Config();

	SetupLedMatrix();
	uint8_t dataCounter = 0;
	int dataReceived[4] = {0};
	uint8_t rowReceived = 0;
	uint8_t row = 0;
	uint8_t values[5] = {0};

	while (1)
	{
		if(dataCounter != 4)
		{
			dataReceived[dataCounter] = getchar();
			dataCounter++;
		}
		else
		{
			dataCounter = 0;
			if(dataReceived[3] == '\n')
			{
				if(rowReceived ==  1)
				{
					rowReceived = 0;
					values[2] = (dataReceived[0]);
					values[3] = (dataReceived[1]);
					values[4] = (dataReceived[2]);
					ChangeRow(row, values);
					putchar('Y');
				}
				else
				{
					row = dataReceived[0];
					uint8_t col = dataReceived[1];
					values[0] = (dataReceived[2]);

					if((row < 10) && (col < 10) && (values[0] < 65))
					{
						ChangeLED(row, col, values[0]);
						putchar('Y');
					}
					else
					{
						putchar('N');
					}
				}
			}
			else if(dataReceived[1] == 10)
			{
				rowReceived = 1;
				row = dataReceived[0];
				values[0] = (dataReceived[2]);
				values[1] = (dataReceived[3]);
			}
			else
			{
				putchar('N');
			}
		}
	}
}

static void TIM4_Config(void)
{
  /* TIM4 configuration:
   * 16Mhz clock, 128 prescaler, count to 124 for 1ms interrupts
   */

  /* Time base configuration */
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD);
  /* Clear TIM4 update flag */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  /* Enable update interrupt */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);

  /* enable interrupts */
  enableInterrupts();

  /* Enable TIM4 */
  TIM4_Cmd(ENABLE);
}

static void TIM1_Config(void)
{
  TIM1_DeInit();

  //Timer 1 counts to 4095, prescaler not needed (0), count up, repitition counter 0 as well.
  TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, 4095, 0);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */

  //Pin PC_3
  TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
		  PWM_VAL, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
               TIM1_OCNIDLESTATE_RESET);
  TIM1_OC3PreloadConfig(ENABLE);

  //Pin PC_4
  TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, PWM_VAL, TIM1_OCPOLARITY_LOW,
               TIM1_OCIDLESTATE_SET);
  TIM1_OC4PreloadConfig(ENABLE);

  // TIM1 counter enable
  TIM1_Cmd(ENABLE);

  // TIM1 enable outputs
  TIM1_CtrlPWMOutputs(ENABLE);
}


static void TIM2_Config(void)
{
  TIM2_TimeBaseInit(TIM2_PRESCALER_1, 4095);

  // A lot easier, enable PWM, enable the output on the GPIO, add the value and it's a go.
  //Pin PD_4
  TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,PWM_VAL, TIM2_OCPOLARITY_HIGH);
  TIM2_OC1PreloadConfig(ENABLE);

  //Pin PD_3
  TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,PWM_VAL, TIM2_OCPOLARITY_HIGH);
  TIM2_OC2PreloadConfig(ENABLE);

  //Pin PA_3
  TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,PWM_VAL, TIM2_OCPOLARITY_HIGH);
  TIM2_OC3PreloadConfig(ENABLE);

  TIM2_ARRPreloadConfig(ENABLE);

  // TIM2 enable counter
  TIM2_Cmd(ENABLE);
}

static void UART_Config(void)
{
	UART1_DeInit();

	/* UART1 needs some settings:
	115200 as BAUD, 8 bit wordlength, 1 stopbit and no parity.
	Syncmode clock disabled, and let's enable both RX and TX so printf and getchar works
	*/
	UART1_Init((uint32_t)19200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
			  UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
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

void TimingDelay_Decrement(void)
{
	UpdateLedMatrix();
}

