////////////////////////////////////////////////////////////////////
//
// Fake TV Security Light
//
// Built for DigiSpark
//
//
////////////////////////////////////////////////////////////////////
#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL_OUT  0
#define ADC_LDR           1 // Pin marked P2 === digital pin 2

#define NUM_LEDS  4

#define LED_BRIGHT  120

#define DAY_THRESHOLD 245
#define NIGHT_THRESHOLD 240

typedef struct
{
  int period;
  int r;
  int g;
  int b;
} FAKE_PICTURE;

FAKE_PICTURE pictures[] = 
{
  {1000, LED_BRIGHT, LED_BRIGHT, LED_BRIGHT / 2}, 
  {2000, LED_BRIGHT, LED_BRIGHT/2, LED_BRIGHT}, 
  {4000, LED_BRIGHT, LED_BRIGHT, LED_BRIGHT},
  {2000, LED_BRIGHT/2, LED_BRIGHT, LED_BRIGHT},
  {2000, LED_BRIGHT, LED_BRIGHT, LED_BRIGHT/2}
};

// Global variables :-/
Adafruit_NeoPixel strip =
  Adafruit_NeoPixel(NUM_LEDS, PIN_NEOPIXEL_OUT, NEO_GRB + NEO_KHZ800);

void setup() 
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
  static boolean isNight = false;
  static int pictureIndex = 0;

  int ldrValue = analogRead(ADC_LDR);

  if(isNight)
  {
    if(ldrValue >= DAY_THRESHOLD)
    {
      isNight = false;
    }
  }
  else
  {
    if(ldrValue <= NIGHT_THRESHOLD)
    {
      isNight = true;
    }
  }

  delay(pictures[pictureIndex].period);
  if(isNight)
  {
    setLEDs(pictures[pictureIndex].r, pictures[pictureIndex].g, 
      pictures[pictureIndex].b);
  }
  else
  {
    setLEDs(0, 0, 0);
  }

  pictureIndex ++;
  if(pictureIndex >= sizeof(pictures)/sizeof(pictures[0]))
  {
    pictureIndex = 0;
  }
}

void setLEDs(int r, int g, int b)
{
  uint32_t colour = strip.Color(r, g, b);
  
  for(int i = 0; i < NUM_LEDS; i++)
  {
    strip.setPixelColor(i, colour);    
  }
  
  strip.show();  
}
