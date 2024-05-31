void ledOn()
{
    digitalWrite(LED_BUILTIN, HIGH); 
}

void ledOff()
{
    digitalWrite(LED_BUILTIN, LOW);  
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{

  delay(1);
}
