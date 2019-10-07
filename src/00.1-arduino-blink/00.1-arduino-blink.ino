/*
  Control LED on an "Arduino Uno" compatible board
  Set IDE to Arduino/Genuino Uno
*/

#define LED_1 13

void setup() {
  // The Arduino Uno internal LED is connected to pin 13
  pinMode(LED_1, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_1, HIGH);
  delay(2000);
  digitalWrite(LED_1, LOW);
  delay(2000);
}
