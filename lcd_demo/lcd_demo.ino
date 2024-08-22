#include "Adafruit_LiquidCrystal.h"
#include "busyboard.h"

#define ROWS 2
#define COLS 16

// Connect via i2c, default address #0 (A0-A2 not jumpered)
Adafruit_LiquidCrystal lcd(0);
uint8_t topic;
char rxBytes[32];

void clearRow(int rowNum)
{
  String emptyStr;
  for(int i = 0; i < COLS; i++)
  {
    emptyStr += " ";
  }
  lcd.setCursor(0,rowNum);
  lcd.print(emptyStr);
}

void commSetup()
{
  const char * nodeType = "${SERIAL,I:0:STR:text_out_0,I:1:STR:text_out_1}";
  Serial.println(nodeType);
}

void setup() {
  Serial.begin(57600);
  while(!Serial);
  commSetup();

  Serial.println("LCD Character Backpack I2C Test.");

  // set up the LCD's number of rows and columns:
  if (!lcd.begin(COLS, ROWS)) {
    Serial.println("Could not init backpack. Check wiring.");
    while (1);
  }
  // Print a message to the LCD.
  Serial.println("Backpack init'd.");

  lcd.print("Waiting for msg...");
  lcd.setBacklight(HIGH);
}

void processMessage(uint8_t topic)
{
  if(topic == 0)
  {
    clearRow(0);
    lcd.setCursor(0,0);
    lcd.print(rxBytes);
  }
  else if(topic == 1)
  {
    clearRow(1);
    lcd.setCursor(0,1);
    lcd.print(rxBytes);
  }
}

void loop() 
{
 if(bb::receiveMessage(topic,rxBytes))
    processMessage(topic);
  delay(1);
}
