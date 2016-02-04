#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define MAX_LEDS 12
#define ONE_WIRE_BUS 12
#define SLEEP_MINUTES 1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(MAX_LEDS, 13, NEO_GRB + NEO_KHZ800);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature dallsTemp(&oneWire);

uint16_t curRingLed = 0;

void setup() {
  pixels.begin();
  pixels.show();
  dallasTemp.begin();
}

void loop() {
  int temp_colour = 0;

  temp_colour = int(dallasTemp.getTempCByIndex(0));
  // scale range from [5..30] to [0..255]
  temp_colour = (temp_colour - 5) * 8.5;

  for(curRingLed=0; curRingLED < MAX_LEDS; curRingLed++) {
    pixels.setPixelColor(curRingLed, pixels.Color(temp_colour, 0, 255 - temp_colour));
  }

  pixels.show();

  ESP.deepSleep(SLEEP_MINUTES * 60 * 1000l * 1000l);  
}

