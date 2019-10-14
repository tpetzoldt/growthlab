const int ledA = 12;
const int ledB = 13;

int ledStateA = LOW;
int ledStateB = LOW;

unsigned long previousMillis = 0;
const long onA=5000,  onB=1000, 
           offA=1000, offB=500;

void setup() {
  // set the digital pin as output:
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {
  
  unsigned long currentMillis = millis();
 
  if (currentMillis % (onA + offA) < onA)  {
    ledStateA = HIGH;
  } else {
    ledStateA = LOW;
  }
 
  if (currentMillis % (onB + offB) < onB)  {
    ledStateB = HIGH;
  } else {
    ledStateB = LOW;
  }
 
  digitalWrite(ledA, ledStateA);
  digitalWrite(ledB, ledStateB);
  
  delay(100);
}
