/*
  Combines the BH1750 digital Light sensor with an OLED display

  Purpose:
  - simple lux meter 
    (the values are of course not precise, but surprisingly close 
     to a commercial hobby lux meter)
  - in combination with a (laser) LED: digital light sensor for growth experiments
  - optional sensors: 
    - analog light sensor (photoresistor)
    - digital temperature sensor (DS18B20)
  
  
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

// ----- OLED display ----------------------------------------
//https://github.com/olikraus/u8g2/wiki/u8x8reference
#include <U8x8lib.h>   // OLED display library

// change the following line if you own a different display
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);


// ----- BH 1750 light sensor  --------------------------------
// Create the Lightsensor instance 
#include <BH1750FVI.h> // light sensor library

// ----- analog light sensor ----------------------------------
#define analog A0

// enable one of the following lines to set resolution
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
//BH1750FVI LightSensor(BH1750FVI::k_DevModeContHighRes);

// ----- DS18B20 temperature sensor  -------------------------
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2 // 2=GPIO4 D1 mini
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ----- LEDs ------------------------------------------------
#define red 12   // 6
#define white 13 // 7

void setup() {
  Serial.begin(9600);
  LightSensor.begin();  

  sensors.begin();
  sensors.setResolution(12); // 12 bit

  /* Initialize OLED display */
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_7x14_1x2_r);
  u8x8.drawString(0,0,"Start ...");
  delay(100);
  u8x8.clearDisplay();

  pinMode(red, OUTPUT);
  pinMode(white, OUTPUT);
}

int i=10;

void loop() {

  if (i < 2) {
    digitalWrite(red, HIGH);
    digitalWrite(white, LOW);
    u8x8.drawString(14, 5, "*");
  } else {
    digitalWrite(red, LOW);
    digitalWrite(white, HIGH);
  }
  
  uint16_t lux = LightSensor.GetLightIntensity();

  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();

  double temp = sensors.getTempCByIndex(0);
  double turb = 100.0 - 100.0*float(analogRead(analog)/1024.0);
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("\tLux: ");
  Serial.print(lux);
  Serial.print("\tOD: ");
  Serial.println(turb);
  
  // Output to the OLED display
  //u8x8.clearDisplay();
  //u8x8.clearLine(0, 2); // announced for future versions v2.14 of the u8x8 lib
  u8x8.drawString(0, 1,"Temp            "); //overwrite leftover chars
  u8x8.drawString(7, 1, String(temp).c_str());
  
  u8x8.drawString(0, 3,"Lux             "); //overwrite leftover chars
  u8x8.drawString(7, 3, String(lux).c_str());

  u8x8.drawString(0, 5,"OD              "); //overwrite leftover chars
  u8x8.drawString(7, 5, String(turb).c_str());

  i++;
  if (i > 14) i = 0;
  delay(1000);
}
