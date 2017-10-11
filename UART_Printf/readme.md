Printf is very nice for debugging, luckily it's simple to make.
the SDCC compiler needs a function for putchar and getchar, which are fairly easy to create.
Putchar sends a single character to the UART peripheral and waits until it is done.
Getchar waits until a character has been received and returns it.

The IO pins used are:
RX = PD6
TX = PD5

