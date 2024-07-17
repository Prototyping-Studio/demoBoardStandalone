// Simple strand test for Adafruit Dot Star RGB LED strip.
// This is a basic diagnostic tool, NOT a graphics demo...helps confirm
// correct wiring and tests each pixel's ability to display red, green
// and blue and to forward data down the line.  By limiting the number
// and color of LEDs, it's reasonably safe to power a couple meters off
// the Arduino's 5V pin.  DON'T try that with other code!

#include <Adafruit_DotStar.h>
// Because conditional #includes don't work w/Arduino sketches...
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#include <avr/power.h> // ENABLE THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 64 // Number of LEDs in strip

// Here's how to control the LEDs from any two pins:
#define DATAPIN    4
#define CLOCKPIN   5
Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);
// The last parameter is optional -- this is the color data order of the
// DotStar strip, which has changed over time in different production runs.
// Your code just uses R,G,B colors, the library then reassigns as needed.
// Default is DOTSTAR_BRG, so change this if you have an earlier strip.

// Hardware SPI is a little faster, but must be wired to specific pins
// (Arduino Uno = pin 11 for data, 13 for clock, other boards are different).
//Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_BRG);

#define NUM_PIXELS 64
#define VERTICAL_FLIP
int reduction = 7;


int face_scary[NUM_PIXELS][3] = {
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,255,0},{0,0,0},{0,0,0},{0,0,255},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{255,0,0},{0,0,0},{0,0,0},{0,0,0},{255,0,0},{255,0,0},{0,0,0},{0,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{255,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{255,0,0},{255,0,0},{255,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

int happy_face[NUM_PIXELS][3] = {
{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{0,0,0},{0,0,0},{255,242,0},{255,242,0},{0,0,0},{0,0,0},{255,242,0},{255,242,0},{0,0,0},{0,0,0},{255,242,0},{255,242,0},{0,0,0},{0,0,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{0,0,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{0,0,0},{255,242,0},{255,242,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{255,242,0},{255,242,0},{255,242,0},{0,0,0},{163,73,164},{163,73,164},{0,0,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0},{255,242,0}};

int sad_face[NUM_PIXELS][3] = {
{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,0,0},{0,0,0},{0,162,232},{0,162,232},{0,0,0},{0,0,0},{0,162,232},{0,162,232},{0,0,0},{0,0,0},{0,162,232},{0,162,232},{0,0,0},{0,0,0},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,162,232},{0,162,232},{0,162,232},{0,0,0},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,0,0},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232},{0,162,232}};

int fire[NUM_PIXELS][3] = {
{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{255,127,39},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{255,127,39},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{255,127,39},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{255,127,39},{255,127,39},{255,127,39},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{255,127,39},{255,127,39},{255,242,0},{255,127,39},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{255,127,39},{255,242,0},{255,201,14},{255,127,39},{0,0,0},{0,0,0},{0,0,0},{255,127,39},{255,127,39},{255,201,14},{255,242,0},{255,127,39},{0,0,0},{0,0,0},{0,0,0},{255,127,39},{255,201,14},{255,242,0},{255,201,14},{255,127,39},{255,127,39},{0,0,0}};
void setFire()
{
  int color = 0;
  int i = 0;
  for(int j = 0; j < NUM_PIXELS; j++)
  {
    #ifdef VERTICAL_FLIP
    i = NUM_PIXELS-j-1;
    #else
    i = j;
    strip.setPixelColor(j, fire[i][1] >> reduction,fire[i][0] >> reduction,fire[i][2] >> reduction);
  }
   strip.show();
}

void setSadFace()
{
  int color = 0;
  int i = 0;
  for(int j = 0; j < NUM_PIXELS; j++)
  {
    #ifdef VERTICAL_FLIP
    i = NUM_PIXELS-j-1;
    #else
    i = j;
    strip.setPixelColor(j, sad_face[i][1] >> reduction,sad_face[i][0] >> reduction,sad_face[i][2] >> reduction);
  }
   strip.show();
}
void setHappyFace()
{
  int color = 0;
  int i = 0;
  for(int j = 0; j < NUM_PIXELS; j++)
  {
    #ifdef VERTICAL_FLIP
    i = NUM_PIXELS-j-1;
    #else
    i = j;
    strip.setPixelColor(j, happy_face[i][1] >> reduction,happy_face[i][0] >> reduction,happy_face[i][2] >> reduction);
  }
   strip.show();
}

void setup() {

#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000L)
  clock_prescale_set(clock_div_1); // Enable 16 MHz on Trinket

  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}

void loop() {

  setHappyFace();
  delay(3000);
  setSadFace();
  delay(3000);
}

