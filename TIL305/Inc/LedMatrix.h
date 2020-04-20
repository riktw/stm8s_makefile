#ifndef _LEDMATRIX_H_
#define _LEDMATRIX_H_

#define COL0_PORT (GPIOD)
#define COL1_PORT (GPIOD)
#define COL2_PORT (GPIOA)
#define COL3_PORT (GPIOC)
#define COL4_PORT (GPIOC)

#define COL0_PIN (GPIO_PIN_4)
#define COL1_PIN (GPIO_PIN_3)
#define COL2_PIN (GPIO_PIN_3)
#define COL3_PIN (GPIO_PIN_4)
#define COL4_PIN (GPIO_PIN_3)

#define ROW0_PORT (GPIOA)
#define ROW1_PORT (GPIOA)
#define ROW2_PORT (GPIOC)
#define ROW3_PORT (GPIOB)
#define ROW4_PORT (GPIOB)
#define ROW5_PORT (GPIOC)
#define ROW6_PORT (GPIOC)

#define ROW0_PIN (GPIO_PIN_1)
#define ROW1_PIN (GPIO_PIN_2)
#define ROW2_PIN (GPIO_PIN_7)
#define ROW3_PIN (GPIO_PIN_5)
#define ROW4_PIN (GPIO_PIN_4)
#define ROW5_PIN (GPIO_PIN_6)
#define ROW6_PIN (GPIO_PIN_5)

void SetupLedMatrix(void);
void UpdateLedMatrix(void);
void ChangeLED(unsigned char  row, unsigned char  column, unsigned char  status);
void ChangeRow(unsigned char  row, unsigned char  *status);
void ChangeArray(unsigned char  *array);

#endif
