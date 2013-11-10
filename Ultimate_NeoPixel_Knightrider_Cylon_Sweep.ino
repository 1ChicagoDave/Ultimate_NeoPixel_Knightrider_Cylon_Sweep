#include <Adafruit_NeoPixel.h>

// David R Ratliff
// Oct 27, 2013
// Modified from "neo_nightrider" found on GitHub - unknown Author
// Reduced compiled sketch size by almost 1,000 bytes
// Simplified code a bit, easier to change values now 
//    --   (only need to change a few values up top & the rest reference them)

#define PIN 0    // Pin that NeoPixel Strip is connected to. I use pin 0 on Adafruit Trinket

Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800); //first number controls the amount of pixels you have (add a few to help the "turnaround")
const int bright = 10;    //select 1 thru 10 ( this is multiplied by 25 to get brightest pixel value (from 0-255)
const int wait = 45;    //speed of leds - length of delay() in milliseconds
const int tailSize = 7;    // length of light "tail" including lead light
const int arraySize = tailSize + 1;

// Array to hold 'r' (RED) color values - Add more values array to lengthen 'tail' of lights
// Last value should be "0" to ensure pixels are turned off appropriately
int r[arraySize] = {
  25*bright, 20*bright, 10*bright, 4*bright, 2*bright, bright, bright, 0};    
// Due to logarithmic nature of the human eye, each aditional brightness level should be slightly less than half the previous value for best effect.

// Not (really) used green & blue color values  
int g0 = 0; 
int b0 = 0;


void setup() 
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}
void loop() 
{
  colorWipe(r[0], g0, b0, wait);
}    // end void loop()  

void colorWipe(int R, int G, int B, int wait) 
{
  //    Run lights starting from pixel 0
  for(int i=0; i<strip.numPixels(); i++) 
  {
    for (int q = 0; q <= tailSize; q++)
    {
      strip.setPixelColor(i-q, r[q], g0, b0);
    }    // end for (int q...
    strip.show();
    delay(wait); 
  }    // end for (int i...

  // Now, shrink the tail....
  for(int p = 1; p <= tailSize; p++)
  {
    for(int t = (strip.numPixels()-tailSize); t < (strip.numPixels()-2); t++)
    {
      int v = ((strip.numPixels()-t)+p);
      if (v > tailSize) v = tailSize;

      strip.setPixelColor(t, r[v], g0, b0);
    }

    strip.show();
    // No delay() here. It causes too long of a pause at ends of strip.
  }



  //      Run lights back to pixel 0
  for(int i=(strip.numPixels()-1); i >= 0; i--) 
  {
    for (int q = 0; q <= tailSize; q++)
    {
      strip.setPixelColor(i+q, r[q], g0, b0);
      // strip.setPixelColor(i+4, r[4], g0, b0);
    }    // end for (int q...  
    strip.show();
    delay(wait); 
  }    // end for (int i...  

  // Now, shrink the tail....
  for(int p = 1; p <= tailSize; p++)
  {
    for(int t = tailSize; t >= 2; t--)
    {
      int v = (t+p);
      if (v > tailSize) v = tailSize;

      strip.setPixelColor(t, r[v], g0, b0);
    }

    strip.show();
  }

}    // end void colorWipe()










