/*
  Combines the BH1750 digital Light sensor with an OLED display

  Purpose:
  - simple lux meter 
    (the values are of course not precise, but surprisingly close 
     to a commercial hobby lux meter)
  - in combination with a (laser) LED: digital light sensor for growth experiments
  
  Controller  : Arduino Uno (works also with ESP8266 boards)
  Light sensor: BH1750
  Display     : SH1106  (1.3" I2C)

  Connection of light sensor and display to the controller
  The I2C interface allows to connect both in parallel.
  
  Sensor    Arduino Uno    NodeMCU ESP8266:
  VCC        3V3            3V3
  GND        GND            GND
  SDA        A4/SDA         D2
  SCL        A5/SCL         D1

  Note: available OLED displays have different pinout.
        Be very careful, NEVER CONFUSE 3.3V and GND!


  Created from online examples by https://github.com/tpetzoldt
  License: GPL 2.0
*/


//https://github.com/olikraus/u8g2/wiki/u8x8reference
#include <U8x8lib.h>   // OLED display library

// Create the Lightsensor instance
#include <BH1750FVI.h> // light sensor library

// enable one of the following lines to set resolution
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
//BH1750FVI LightSensor(BH1750FVI::k_DevModeContHighRes);

// change the following line if you own a different display
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(9600);
  LightSensor.begin();  

  /* Initialize OLED display */
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_7x14_1x2_r);
  u8x8.drawString(0,0,"Start ...");
  delay(100);
  u8x8.clearDisplay();
}

void loop() {
  uint16_t lux = LightSensor.GetLightIntensity();

  // Output to Serial monitor or plotter of the Arduino IDE
  Serial.print("Light: ");
  Serial.println(lux);

  // Output to the OLED display
  //u8x8.clearDisplay();
  //u8x8.clearLine(0, 2); // announced for future versions v2.14 of the u8x8 lib
  u8x8.drawString(0, 2,"Light          "); //overwrite leftover chars from lux
  u8x8.drawString(7, 2, String(lux).c_str());
  delay(1000);
}
