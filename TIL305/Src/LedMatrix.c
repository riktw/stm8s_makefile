#include "LedMatrix.h"
#include "stm8s.h"
#include "string.h"

#define PWM1_VAL    ((uint16_t)0)     //12.5%
#define PWM2_VAL    ((uint16_t)500)     //12.5%

void Delay(uint16_t nCount)
{
	/* Decrement nCount value */
	while (nCount != 0)
	{
		nCount--;
	}
}

static uint8_t LEDArray[7][5] =
		   {{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0},
			{0, 0, 0, 0, 0}};

void SetupLedMatrix(void)
{
	/* Initialize I/Os in Output Mode */
	GPIO_Init(ROW0_PORT, (GPIO_Pin_TypeDef)ROW0_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(ROW1_PORT, (GPIO_Pin_TypeDef)ROW1_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(ROW2_PORT, (GPIO_Pin_TypeDef)ROW2_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(ROW3_PORT, (GPIO_Pin_TypeDef)ROW3_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(ROW4_PORT, (GPIO_Pin_TypeDef)ROW4_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(ROW5_PORT, (GPIO_Pin_TypeDef)ROW5_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(ROW6_PORT, (GPIO_Pin_TypeDef)ROW6_PIN, GPIO_MODE_OUT_PP_LOW_FAST);

	GPIO_Init(COL0_PORT, (GPIO_Pin_TypeDef)COL0_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(COL1_PORT, (GPIO_Pin_TypeDef)COL1_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(COL2_PORT, (GPIO_Pin_TypeDef)COL2_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(COL3_PORT, (GPIO_Pin_TypeDef)COL3_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
	GPIO_Init(COL4_PORT, (GPIO_Pin_TypeDef)COL4_PIN, GPIO_MODE_OUT_PP_LOW_FAST);

	GPIO_WriteHigh(COL0_PORT, (GPIO_Pin_TypeDef)COL0_PIN);
	GPIO_WriteHigh(COL1_PORT, (GPIO_Pin_TypeDef)COL1_PIN);
	GPIO_WriteHigh(COL2_PORT, (GPIO_Pin_TypeDef)COL2_PIN);
	GPIO_WriteHigh(COL3_PORT, (GPIO_Pin_TypeDef)COL3_PIN);
	GPIO_WriteHigh(COL4_PORT, (GPIO_Pin_TypeDef)COL4_PIN);

	GPIO_WriteHigh(ROW0_PORT, (GPIO_Pin_TypeDef)ROW0_PIN);
	GPIO_WriteHigh(ROW1_PORT, (GPIO_Pin_TypeDef)ROW1_PIN);
	GPIO_WriteHigh(ROW2_PORT, (GPIO_Pin_TypeDef)ROW2_PIN);
	GPIO_WriteHigh(ROW3_PORT, (GPIO_Pin_TypeDef)ROW3_PIN);
	GPIO_WriteHigh(ROW4_PORT, (GPIO_Pin_TypeDef)ROW4_PIN);
	GPIO_WriteHigh(ROW5_PORT, (GPIO_Pin_TypeDef)ROW5_PIN);
	GPIO_WriteHigh(ROW6_PORT, (GPIO_Pin_TypeDef)ROW6_PIN);
}

void ChangeLED(unsigned char  row, unsigned char  column, unsigned char  status)
{
	LEDArray[row][column] = status;
}

void ChangeRow(unsigned char  row, unsigned char  *status)
{
	memcpy(LEDArray[row], status, 5);
}

void ChangeArray(unsigned char  *array)
{
	memcpy(LEDArray, array, 35);
}

void UpdateLedMatrix(void)
{
	static uint8_t rowCounter = 0;
	if(rowCounter == 6)
	{
		rowCounter = 0;
	}
	else
	{
		rowCounter++;
	}


	TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,PWM1_VAL, TIM2_OCPOLARITY_HIGH);
	TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,PWM1_VAL, TIM2_OCPOLARITY_HIGH);
	TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,PWM1_VAL, TIM2_OCPOLARITY_HIGH);
	TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, PWM1_VAL, TIM1_OCPOLARITY_LOW,
			               TIM1_OCIDLESTATE_SET);
	TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
					PWM1_VAL, TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET, TIM1_OCNIDLESTATE_RESET);

	Delay(500); //wait for PWM to be fully off.

	switch (rowCounter)
	{
		case 0:
			GPIO_WriteHigh(ROW6_PORT, (GPIO_Pin_TypeDef)ROW6_PIN);
			GPIO_WriteLow(ROW0_PORT, (GPIO_Pin_TypeDef)ROW0_PIN);

		break;
		case 1:
			GPIO_WriteHigh(ROW0_PORT, (GPIO_Pin_TypeDef)ROW0_PIN);
			GPIO_WriteLow(ROW1_PORT, (GPIO_Pin_TypeDef)ROW1_PIN);
		break;
		case 2:
			GPIO_WriteHigh(ROW1_PORT, (GPIO_Pin_TypeDef)ROW1_PIN);
			GPIO_WriteLow(ROW2_PORT, (GPIO_Pin_TypeDef)ROW2_PIN);
		break;
		case 3:
			GPIO_WriteHigh(ROW2_PORT, (GPIO_Pin_TypeDef)ROW2_PIN);
			GPIO_WriteLow(ROW3_PORT, (GPIO_Pin_TypeDef)ROW3_PIN);
		break;
		case 4:
			GPIO_WriteHigh(ROW3_PORT, (GPIO_Pin_TypeDef)ROW3_PIN);
			GPIO_WriteLow(ROW4_PORT, (GPIO_Pin_TypeDef)ROW4_PIN);
		break;
		case 5:
			GPIO_WriteHigh(ROW4_PORT, (GPIO_Pin_TypeDef)ROW4_PIN);
			GPIO_WriteLow(ROW5_PORT, (GPIO_Pin_TypeDef)ROW5_PIN);
		break;
		case 6:
			GPIO_WriteHigh(ROW5_PORT, (GPIO_Pin_TypeDef)ROW5_PIN);
			GPIO_WriteLow(ROW6_PORT, (GPIO_Pin_TypeDef)ROW6_PIN);
		break;

		default:
		break;
	}



	TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,LEDArray[rowCounter][0]*LEDArray[rowCounter][0], TIM2_OCPOLARITY_HIGH);
	TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,LEDArray[rowCounter][1]*LEDArray[rowCounter][1], TIM2_OCPOLARITY_HIGH);
	TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,LEDArray[rowCounter][2]*LEDArray[rowCounter][2], TIM2_OCPOLARITY_HIGH);
	TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, LEDArray[rowCounter][3]*LEDArray[rowCounter][3], TIM1_OCPOLARITY_LOW,
				   TIM1_OCIDLESTATE_SET);
	TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,
			LEDArray[rowCounter][4]*LEDArray[rowCounter][4], TIM1_OCPOLARITY_LOW, TIM1_OCNPOLARITY_HIGH, TIM1_OCIDLESTATE_SET,
			TIM1_OCNIDLESTATE_RESET);


}
