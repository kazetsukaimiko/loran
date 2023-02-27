#include <Arduino.h>
#include "Wire.h"
#include "esp32-hal-gpio.h"

void setupNuvosForCommunication() {

	//NOTE: Weak pull-ups required on the Wire leads!  This should be programmatically possible from the GPIO matrix
	//and potentially even the Arduino functions, assuming they do not ruin peripheral pin assignments
	pinMode(43, INPUT_PULLUP);  // These MUST be before the "Wire.begin"
	pinMode(44, INPUT_PULLUP);  // otherwise they disconnect Wire from the pins.
	Wire.begin(44, 43);     // manually specify the TX0/RX0 pins, which are the default programming leads

	//esp_err_t gpio_pullup_en(gpio_num_t gpio_num)

	byte error, address;
	int nDevices = 0;

	while (nDevices == 0)
	{
		delay(2000);

		Serial.println("Scanning for I2C devices ...");
		for(address = 0x01; address < 0x7f; address++){
			Wire.beginTransmission(address);
			error = Wire.endTransmission();
			if (error == 0){
				Serial.printf("I2C device found at address 0x%02X\n", address);
				nDevices++;
			} else if(error != 2){
                
				Serial.printf("Error %d at address 0x%02X\n", error, address);
			}
		}
		if (nDevices == 0){
			Serial.println("No I2C devices found, continue scanning...");
		}
	}
}


unsigned char I2CWriteByte(unsigned char SlaveID, unsigned char Address, unsigned char Data)
{
	Wire.beginTransmission(SlaveID);
	Wire.write(Address);
	Wire.write(Data);
	Wire.endTransmission();
	return 0;
}
