An example for the EEPROM.
It reads a value from EEPROM, writes it to another place in eeprom and increases it by one.
It compares the read value with the value now in eeprom address 2 to see if it matches.
By running this example and resetting the board several times, you can see the value printed out increase by one at each reset, showing the value is remembered when power is gone.
The EEPROM in the stm8s003 is 128 bytes big, if you need more, the stm8s103 has 640 bytes, though on my board, it seems like the stm8s003 also has 640 bytes of EEPROM :)