#include <busyboard.h>

publishedVar<int> irValue(0,"ir_value");
int inputPin = A0;

void commSetup()
{
  Serial.print("${SERIAL");
  Serial.print(irValue.getIdString());
  Serial.println("}");  
}

void setup() 
{
  Serial.begin(57600);
  while(!Serial){ delay(10); };
  commSetup();
}

void loop(){
  irValue = analogRead(inputPin);  // read input value
  delay(100);
}
