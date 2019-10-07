/*
  Control LED on an "ESP8266 Lua Lolin" compatible board  
  Set IDE to NodeMCU 1.0
*/


void setup() {
  // The Lua Lolin has a LED connected to D4
  pinMode(D4, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // The internal (blue) LED has opposite behavior
  // HIGH means "off", LOW means "on",
  // but an external LED connected to D4 works as expected
  digitalWrite(D4, HIGH);
  delay(10000);
  digitalWrite(D4, LOW);
  delay(2000);
}
