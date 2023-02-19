#include "Wire.h"

#define NuvoA (0xB4 >> 1)   // root address, second unit is at 0xB6.  Note that the Wire library has a 0-7F range, not a skipped 0-FF range.
#define NuvoB (0xB6 >> 1)

typedef union {
	struct {
		unsigned char P1 :1;
		unsigned char P2 :1;
		unsigned char P3 :1;
		unsigned char P4 :1;
		unsigned char P5 :1;
		unsigned char P6 :1;
		unsigned char Px :2;
	};
	struct {
		unsigned char All;
	};
} chBitflags;

unsigned int ADCVals_A[15], ADCVals_B[15];			// ADC readings
unsigned char Breakers_A[6];			// maximum current limits (high 8 bits only)
unsigned char bTripLevel_A[6];		// time delay setting for breaker channels
chBitflags ssrOutputs_A, ssrOutputs_B;						// user-set output states
chBitflags ssrTrips_A, ssrTrips_B;						// if SSR values exceeded the configured maximum current and were shut off by software.  (Overrules Output)
chBitflags hatOutputs_A;						// sets all HAT I/O output values if set (ignored if pins are inputs)
chBitflags hatInputs_A;						// raw-read values of all HAT I/Os
chBitflags hatDigitalDir_A;					// sets pins between digital push-pull and digital input
chBitflags hatAnalogInput_A;					// sets pins between analog inputs and digital-capable

unsigned char I2CWriteByte(unsigned char SlaveID, unsigned char Address, unsigned char Data);


void setup() {
  // T.M.L 2023-02-11: manually specify GPIO3 and GPIO20 for serial comm.  Something of this sort
  //is required, in order to release the I2C ("Wire") GPIOs for use there.
//  Serial.begin(115200); //DEBUG
  Serial.begin(115200, SERIAL_8N1, 3, 20);
  //NOTE: GPIO3 + GPIO20 interfere with the USB interface, which uses GPIO3, GPIO19, and GPIO20.
  Serial.setDebugOutput(true);

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

unsigned char serChar = 0;
bool pollA = false, pollB = false;
int error, timer;
void loop() {
  // Wait for a keypress on the serial...
  if (Serial.available()) {
    // one character commands for very basic data/control
    switch (serChar = Serial.read()) {    // assigning and checking at the same time
      case 'A' ... 'F': ssrOutputs_A.All ^= (1 << (serChar - 'A')); I2CWriteByte(NuvoA, 0x20, ssrOutputs_A.All); break;
      case 'a' ... 'f': ssrOutputs_B.All ^= (1 << (serChar - 'a')); I2CWriteByte(NuvoB, 0x20, ssrOutputs_B.All); break;
      case 'S': pollA = !pollA; break;
      case 's': pollB = !pollB; break;
      case 'T':
      case 't': Serial.println("ESP32-S3 serial comm is alive."); break;
    }
  }

  if ((millis() - timer) > 1000) {
    if (pollA) {
      Wire.beginTransmission(NuvoA);
      Wire.write(0x40);
      Wire.endTransmission();   // address set.
      error = Wire.requestFrom(NuvoA, 26);
      Serial.printf("requestNuvoA: %u = ", error);
      if(error){
        uint8_t temp[error];
        Wire.readBytes(temp, error);
        for (unsigned char x = 0; x < 26; x++) {
          Serial.print((temp[x++] << 8) | temp[x]); Serial.print(", ");   // stack the bytes, MSB first.
        }
  //          log_print_buf((unsigned short)temp, error);
      }
      Serial.println();
    }

    if (pollB) {
      Wire.beginTransmission(NuvoB);
      Wire.write(0x40);
      Wire.endTransmission();   // address set.
      error = Wire.requestFrom(NuvoB, 26);
      Serial.printf("requestNuvoB: %u = ", error);
      if(error){
        uint8_t temp[error];
        Wire.readBytes(temp, error);
        for (unsigned char x = 0; x < 26; x++) {
          Serial.print((temp[x++] << 8) | temp[x]); Serial.print(", ");   // stack the bytes, MSB first.
        }
  //          log_print_buf((unsigned short)temp, error);
      }
      Serial.println();
    }

    timer = millis();   //reset timeout
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