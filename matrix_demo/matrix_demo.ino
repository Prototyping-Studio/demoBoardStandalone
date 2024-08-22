#include <Adafruit_DotStar.h>
#include <busyboard.h>

#define NUM_PIXELS 64 // Number of LEDs in strip
#define OFF 0
#define HAPPY_FACE 1
#define SAD_FACE 2

int faceID = 0;
int prevFaceID = 0;
bool newColor = false;
uint8_t red,green,blue = 0;
uint8_t topic;
char rxBytes[32];

// Here's how to control the LEDs from any two pins:
#define DATAPIN    11 //4
#define CLOCKPIN   13 //5
//Adafruit_DotStar strip(NUM_PIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
Adafruit_DotStar strip(NUM_PIXELS, DOTSTAR_BRG);

uint8_t happy_face[NUM_PIXELS][3] = {
{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{0,0,0},{0,0,0},{255,242,0},{255,242,0},{0,0,0},{0,0,0},{255,242,0},{255,242,0},{0,0,0},{0,0,0},{255,242,0},{255,242,0},{0,0,0},{0,0,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{0,0,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{0,0,0},{255,242,0},{255,242,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{255,242,0},{255,242,0},{255,242,0},{0,0,0},{163,73,164},{163,73,164},{0,0,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0}};

uint8_t sad_face[NUM_PIXELS][3] = {
{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,0,0},{0,0,0},{0,162,232},{0,162,232},{0,0,0},{0,0,0},{0,162,232},{0,162,232},{0,0,0},{0,0,0},{0,162,232},{0,162,232},{0,0,0},{0,0,0},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,162,232},{0,162,232},{0,162,232},{0,0,0},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,0,0},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232}};

void setFace( uint8_t (&localFace)[NUM_PIXELS][3],bool flip = true)
{
  int r,g,b = 0;
  int i = 0;
  for(int j = 0; j < NUM_PIXELS; j++)
  {
    if(flip)
        i = NUM_PIXELS-j-1;
    else
        i = j;
 
    r = localFace[i][0];
    g = localFace[i][1];
    b = localFace[i][2];

    strip.setPixelColor(j,g,r,b);
  }
   strip.show();
}

uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b)
{
  uint32_t RGB888 = (r << 8) & (g << 4) & b;
  uint16_t RGB565 = (((RGB888&0xf80000)>>8) + ((RGB888&0xfc00)>>5) + ((RGB888&0xf8)>>3));
  return RGB565;
}

void rgb888(uint16_t color,uint8_t &r, uint8_t &g, uint8_t &b)
{
  r = ((((color >> 11) & 0x1F) * 527) + 23) >> 6;
  g = ((((color >> 5) & 0x3F) * 259) + 33) >> 6;
  b = (((color & 0x1F) * 527) + 23) >> 6;
}

void setRGB(uint8_t r,uint8_t g, uint8_t b)
{
  for(int j = 0; j < NUM_PIXELS; j++)
  {
    strip.setPixelColor(j,g,r,b);
  }
  strip.show();
}

void commSetup()
{
  const char * nodeType = "${SERIAL,I:0:INT:face,I:1:UINT:rgb}";
  Serial.println(nodeType);
}

void setFaceNum(int face_id)
{
  if(face_id == SAD_FACE)
    setFace(sad_face);
  else if (face_id == HAPPY_FACE)
    setFace(happy_face);
  else if(face_id == OFF)
    setRGB(0,0,0);
}

void processMessage(uint8_t topicNum)
{
  if(topicNum == 0)
  {
    long faceNum = String(rxBytes).toInt();
    setFaceNum(faceNum);
  }
  else if(topicNum == 1)
  {
    long rgb = String(rxBytes).toInt();
    uint8_t r,g,b;
    rgb888(rgb,r,g,b);
    setRGB(r,g,b);
  }
}

void setup() {
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
  strip.setBrightness(2);

  Serial.begin(57600);
  commSetup();

  Serial.println("LCD Matrix Initialized!");
  setFaceNum(1);
}

void loop() 
{
  if(bb::receiveMessage(topic,rxBytes))
    processMessage(topic);
  delay(1);
}

