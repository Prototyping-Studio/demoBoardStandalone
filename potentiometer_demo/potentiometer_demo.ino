#include <busyboard.h>

int ledPin = 13;     // select the pin for the LED
int sensorPin0 = A0; // select the input pin for the potentiometer
int sensorPin1 = A1;

publishedVar<int> potValue0(0,"pot0"); // default value, name
publishedVar<int> potValue1(0,"pot1"); 

void commSetup()
{
  Serial.print("${SERIAL");
  Serial.print(potValue0.getIdString());
  Serial.print(potValue1.getIdString());
  Serial.println("}");  
}

void setup()
{
  Serial.begin(57600);
  while(!Serial){};
  commSetup();
}

void loop() {
  // read the value from the sensor:
  potValue0 = analogRead(sensorPin0);
  potValue1 = analogRead(sensorPin1);
  Serial.println("-");
  delay(100);
}
