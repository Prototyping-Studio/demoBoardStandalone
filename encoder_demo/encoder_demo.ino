/*
 * This is a demo for a QT Py RP2040 connected to a quad rotary encoder breakout
 * using the onboard Stemma QT Port
 * https://www.adafruit.com/product/4900
 * https://www.adafruit.com/product/5752
 * 
 */
#include "Adafruit_seesaw.h"
#include <seesaw_neopixel.h>
#define MAX_ARR_LEN 24

#include <busyboard.h>

#define SS_NEO_PIN       18
#define SS_ENC0_SWITCH   12
#define SS_ENC1_SWITCH   14
#define SS_ENC2_SWITCH   17
#define SS_ENC3_SWITCH   9
#define SEESAW_ADDR      0x49
#define PUB_ON_CHANGE_ONLY true

publishedVar<int> enc_positions[4] = 
{
  publishedVar<int>(0,"enc0"), // default value, name
  publishedVar<int>(0,"enc1"), 
  publishedVar<int>(0,"enc2"),
  publishedVar<int>(0,"enc3") 
};

publishedVar<int> btn0(0,"btn0", PUB_ON_CHANGE_ONLY);
publishedVar<int> btn1(0,"btn1", PUB_ON_CHANGE_ONLY); 
publishedVar<int> btn2(0,"btn2", PUB_ON_CHANGE_ONLY);
publishedVar<int> btn3(0,"btn3", PUB_ON_CHANGE_ONLY);

int delta_tmp = 0;

void commSetup()
{
  Serial.print("${SERIAL");
  Serial.print(enc_positions[0].getIdString());
  Serial.print(enc_positions[1].getIdString());
  Serial.print(enc_positions[2].getIdString());
  Serial.print(enc_positions[3].getIdString());
  Serial.print(btn0.getIdString());
  Serial.print(btn1.getIdString());
  Serial.print(btn2.getIdString());
  Serial.print(btn3.getIdString());
  Serial.println("}");  
}

Adafruit_seesaw ss = Adafruit_seesaw(&Wire);
seesaw_NeoPixel pixels = seesaw_NeoPixel(4, SS_NEO_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(57600);
  while (!Serial) delay(10);
  commSetup();

  Serial.println("Looking for seesaw!");
  
  if (! ss.begin(SEESAW_ADDR) || !pixels.begin(SEESAW_ADDR)) {
    Serial.println("Couldn't find seesaw on default address");
    while(1) delay(10);
  }
  Serial.println("seesaw started");
  uint32_t version = ((ss.getVersion() >> 16) & 0xFFFF);
  if (version  != 5752){
    Serial.print("Wrong firmware loaded? ");
    Serial.println(version);
    while(1) delay(10);
  }
  Serial.println("Found I2C Quad Encoder");

  ss.pinMode(SS_ENC0_SWITCH, INPUT_PULLUP);
  ss.pinMode(SS_ENC1_SWITCH, INPUT_PULLUP);
  ss.pinMode(SS_ENC2_SWITCH, INPUT_PULLUP);
  ss.pinMode(SS_ENC3_SWITCH, INPUT_PULLUP);
  ss.setGPIOInterrupts(1UL << SS_ENC0_SWITCH | 1UL << SS_ENC1_SWITCH | 
                       1UL << SS_ENC2_SWITCH | 1UL << SS_ENC3_SWITCH, 1);

  // get starting positions
  for (int e=0; e<4; e++) {
    enc_positions[e] = ss.getEncoderPosition(e);
    ss.enableEncoderInterrupt(e);
  }
  
  Serial.println("Turning on interrupts");

  pixels.setBrightness(255);
  pixels.show(); // Initialize all pixels to 'off'
}

void loop() {

  btn0 = ss.digitalRead(SS_ENC0_SWITCH);
  btn1 = ss.digitalRead(SS_ENC1_SWITCH);
  btn2 = ss.digitalRead(SS_ENC2_SWITCH);
  btn3 = ss.digitalRead(SS_ENC3_SWITCH);

  for (int e=0; e<4; e++) 
  {
    delta_tmp = ss.getEncoderDelta(e);
    if(delta_tmp != 0)
    {
      enc_positions[e] = delta_tmp;
    }
  }
  delay(10);
}
