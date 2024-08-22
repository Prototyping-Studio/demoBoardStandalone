#include <busyboard.h>

int pirState = LOW;
int ledPin = 13;
int inputPin = 2;               // choose the input pin (for PIR sensor)
publishedVar<int> pirValue(0,"motion_detected");

void commSetup()
{
  Serial.print("${SERIAL");
  Serial.print(pirValue.getIdString());
  Serial.println("}");  
}

void setup() {
  Serial.begin(57600);
  while(!Serial);
  commSetup();

  Serial.println("PIR begin");

  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input 
}

void loop(){
  pirValue = digitalRead(inputPin);  // read input value
  if (pirValue == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
  delay(100);
}