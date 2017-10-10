PWM is cool too, and not too hard on the SMT8S boards.
Timer 1 can output 4 different PWM signals, and 3 complementary PWM signals.
Channel 1, 2 and 3 can generate a PWM signal and the inverse on a second pin, which can be nice for motor control or a SMPS.
Channel 4 only has 1 output though.
Timer2 has 3 outputs, channel 1, 2 and 3, no complementaty outputs.

The following IO's are used:
Timer 1 channel 1: PC_1

Timer 1 channel 2: PC_2

Timer 1 channel 3: PC_3

Timer 1 channel 4: PC_4

Timer 2 channel 1: PD_4

Timer 2 channel 1: PD_3

Timer 2 channel 1: PA_3


For this example the 4 normal outputs of timer 1 are used to generate 4 PWM signals, 50, 37,5, 25 and 12,5% duty cycle.
The 3 channels of timer 2 are used for 75, 50 and 25% pwm outputs, giving you a grand total of 7 outputs.

The 4th output of TIM1 and the 3th output of TIM2 are changed on the fly between two values, to demonstrate that as well, when the LED turns on or off, the values change, making is easier to show on a logic analyzer:

![alt text](https://github.com/riktw/stm8s_makefile/blob/master/PWM/LA.png "7 PWM's at one!")
