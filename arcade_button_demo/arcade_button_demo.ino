#include "Adafruit_seesaw.h"
#include <seesaw_neopixel.h>
#include "ButtonLED.h"
#include <busyboard.h>

#define  DEFAULT_I2C_ADDR 0x3A
#define  SWITCH0  18  // PA01
#define  SWITCH1  19 // PA02
#define  SWITCH2  20 // PA03
#define  SWITCH3  2 // PA06
#define  PWM0  12  // PC00
#define  PWM1  13 // PC01
#define  PWM2  0 // PA04
#define  PWM3  1 // PA05
#define NUM_BTNS 4

Adafruit_seesaw ss;

ButtonLED buttons[NUM_BTNS] = 
{
 ButtonLED(PWM0,SWITCH0,"button_0"),
 ButtonLED(PWM1,SWITCH1,"button_1"),
 ButtonLED(PWM2,SWITCH2,"button_2"),
 ButtonLED(PWM3,SWITCH3,"button_3")
};

void commSetup()
{
  Serial.print("${SERIAL");
  for(int i = 0; i < NUM_BTNS;i++)
  {
    Serial.print(buttons[i].value_.getIdString());
  }
  Serial.println("}");  
}

void setup() {
  Serial.begin(57600);
  while(!Serial){};
  commSetup();

  Serial.println(F("Adafruit PID 5296 I2C QT 4x LED Arcade Buttons test!"));
  
  if (!ss.begin(DEFAULT_I2C_ADDR)) {
    Serial.println(F("seesaw not found!"));
    while(1) delay(10);
  }

  uint16_t pid;
  uint8_t year, mon, day;
  
  ss.getProdDatecode(&pid, &year, &mon, &day);
  Serial.print("seesaw found PID: ");
  Serial.print(pid);
  Serial.print(" datecode: ");
  Serial.print(2000+year); Serial.print("/"); 
  Serial.print(mon); Serial.print("/"); 
  Serial.println(day);

  if (pid != 5296) {
    Serial.println(F("Wrong seesaw PID"));
    while (1) delay(10);
  }

  Serial.println(F("seesaw started OK!"));

  if (!ss.begin(DEFAULT_I2C_ADDR)) {
    while(1) delay(10);
  }

  for(int i = 0; i < NUM_BTNS; i++)
  {
    ss.pinMode(buttons[i].sw_, INPUT_PULLUP);
    ss.analogWrite(buttons[i].pwm_, 0);
  }

}

void loop() 
{
  for(int i = 0; i < NUM_BTNS; i++)
  {
    buttons[i].value_ = !ss.digitalRead(buttons[i].sw_);

    if(buttons[i].value_ == 1)
    {
      Serial.print("Switch ");
      Serial.print(i);
      Serial.println(" pressed!");
      ss.analogWrite(buttons[i].pwm_, 255);
    }
    else
    {
      ss.analogWrite(buttons[i].pwm_, 0);
    }
  }

  delay(100);
}

