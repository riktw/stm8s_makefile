A makefile based example project for the stm8s003 discovery board, but it'll probably work for any stm8s0x and stm8s1x CPU by changing the device in the makefile. Running it on the cheap stm8s103 boards from ebay should just be changing the following lines in the makefile:
DEVICE=STM8S003
DEVICE_FLASH=stm8s003f3

To use:
Install SDCC for the compiler and stm8flash for flashing. In Debian and most debian based Linux distro's a simple apt install sdcc will do the trick for sdcc.
stm8flash can be found here: https://github.com/vdudouyt/stm8flash
For Debian 9, a git clone, make, make install, did the trick for me.
If you can only use stm8flash as root, you need the udev rules, which can be found here:
https://github.com/texane/stlink/tree/master/etc/udev/rules.d

After those are installed, make & make flash will build everything and program the microcontroller.
The output file (blinky.ihx) can be found in the build folder.
The example project blinks the on board LED on the stm8x003 discovery board (pin PD0 to be precise)

Everything is GPLv3 licensed unless stated otherwise in the file itself, the stm8s peripheral driver has it's own license for example.
Exeption, and credit where credit is due: The files in STM8S_StdPeriph_Driver are made by ST and the patches and scripts/makefiles are made by SDuino: https://github.com/tenbaht/sduino

20/09/2018:
I managed to get GDB up and running, I updated the makefile to support this.
By default, the makefile now generates a .elf file for the stm8 GDB tools (https://stm8-binutils-gdb.sourceforge.io/) 
It also only compiles the library once, which saves some time. To rebuild this, delete the .lib file from the /Inc folder. 
To build an ihx file to flash using stm8flash, use "make NODEBUG=1" and to build and directly program it, use "make NODEBUG=1 flash"

Eclipse .cproject and .project files are also included, so you "should" be able to import it into eclipse and have a working enviroment. Your mileage may vary.
