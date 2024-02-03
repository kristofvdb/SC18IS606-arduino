#include "Arduino.h"
#include "SC18IS606.h"

SC18IS602B spiBridge(1,0,0,0);


void setup() {

  Serial.begin(115200);

  Serial.setDebugOutput(true);  
    Serial.println("Starting\n"); // will be shown in the terminal
  printf("start\n");
	//Startup I2C interface on D1 (SDA) and D2 (SCL)
	//for the ESP8266
#if 1
#ifdef ARDUINO_ARCH_ESP8266
	spiBridge.begin(D1, D2);
#else
	spiBridge.begin();
#endif
  spiBridge.reset();
  delay(500);

	//Setup SS0 / GPIO0 to be a GPIO pin, set to push-pull output
	spiBridge.enableGPIO(0, true);
	spiBridge.setupGPIO(0, SC18IS601B_GPIO_MODE_PUSH_PULL);
  delay(100);
  spiBridge.writeGPIO(0, HIGH);
  spiBridge.readGPIO(0);
#endif
}

void loop() {
  bool b = spiBridge.readGPIO(0);
  printf("GPIO %d", b);
  spiBridge.writeGPIO(0, !b);
	//spiBridge.writeGPIO(0, HIGH);
	//delay(5000);
	//spiBridge.writeGPIO(0, LOW);
	delay(500);
  //delay(500);
  //spiBridge.reset();
  //delay(10);
  printf("check version:\n");
  if(spiBridge.checkVersion())
    printf("version ok\n");
  else
    printf("version nok\n");
}
