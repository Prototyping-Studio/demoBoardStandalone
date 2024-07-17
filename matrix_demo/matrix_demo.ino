#include <Adafruit_DotStar.h>


#define NUM_PIXELS 64 // Number of LEDs in strip
#define BRIGHTNESS_REDUCTION 7
#define SAD_FACE 0
#define HAPPY_FACE 1

int faceID = 0;
int prevFaceID = 0;

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
 
    r = localFace[i][1];
    g = localFace[i][0];
    b = localFace[i][2];

    strip.setPixelColor(j, 
    r >> BRIGHTNESS_REDUCTION,
    g >> BRIGHTNESS_REDUCTION,
    b >> BRIGHTNESS_REDUCTION);
  }
   strip.show();
}


void setup() {
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP


  delay(500);
  setFace(happy_face);
}

void loop() {
  setFace(sad_face);
  delay(3000);
  setFace(happy_face);
  delay(3000);
}

