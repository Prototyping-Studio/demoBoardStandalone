#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>
#include "busyboard.h"

#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)
#define CARDCS 4     // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(-1, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

void commSetup()
{
  const char * nodeType = "${SERIAL,I:0:STR:track_name,I:1:INT:volume}";
  Serial.println(nodeType);
}

uint8_t topic;
char rxBytes[32];

void setup()
{
  Serial.begin(57600);
  while(!Serial){};
  commSetup();

 if (! musicPlayer.begin()) {
      Serial.println("Can't find music player!");
     while (1);
  }
  if (!SD.begin(CARDCS)) {
    Serial.println("Can't find SD!");
    while (1);  // don't do anything more
  }
  setVolume(50);
  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
}

void setVolume(uint8_t vol)
{
  uint8_t safeVol = constrain(vol,0,100);
  uint8_t newVol = map(safeVol,0,100,60,0);
  if(safeVol == 0)
    newVol = 255; // completely off

  Serial.print("Setting volume: ");
  Serial.print(safeVol);
  Serial.println("%");

  musicPlayer.setVolume(newVol,newVol);
}

void processMessage(uint8_t topicNum)
{
  if(topicNum == 0)
  {
    Serial.print("Playing ");
    Serial.println(rxBytes);
    musicPlayer.startPlayingFile(rxBytes);
  }
  else if(topicNum == 1)
  {
    long newVolume = String(rxBytes).toInt();
    setVolume(newVolume);
  }
}

void loop()
{
  if(bb::receiveMessage(topic,rxBytes))
    processMessage(topic);
  delay(1);
}

