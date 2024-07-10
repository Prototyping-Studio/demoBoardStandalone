int irValue = 0;

int inputPin = A0;

void setup() {
  Serial.begin(9600);
  
}

void loop(){
  irValue = analogRead(inputPin);  // read input value

  Serial.println(irValue);

  delay(100);
}
