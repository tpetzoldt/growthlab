/*
  Arduino analog light sensor example

  Output can be shown via the Arduino serial monitor or serial plotter

  The example is rather trivial, but works.

  License: public domain
 */

int sensorPin = A0;    // select the input pin for the potentiometer

void setup() {
  Serial.begin(115200);
}

void loop() {
  float sensorValue = analogRead(sensorPin);
  Serial.print("Light: ");
  Serial.println(sensorValue);
  // outcomment delay(100);
  // then and watch flickering of fluorescent and (some) LED lamps 
  // and some computer screens with Arduino serial plotter
  delay(100);
}
