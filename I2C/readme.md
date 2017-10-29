I2C is a complex peripheral, this example implements the very basics needed to act as a I2C master. A single byte write and read.
This is enough to read a simple sensor like a TC74 temperature sensor.

For this example, a TC74 temperature sensor is required and must be connected as follows:
TC75 TO-220:
Pin 1	-	not connected
Pin 2	-	SDA, connect to PB5
Pin 3	-	GND, connect to GND
Pin 4	-	SCLK, connect to PB4
Pin 5	-	VCC, connect to 3.3 or 5V

I2C needs pullup resistors, so connect a resistor from SDA to VCC and from SCLK to VCC. 
These resistors can be any value between 1K and 10Kohm.

