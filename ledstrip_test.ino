#include <FastLED.h>

#define NUM_LEDS 37             // Number of LED lights
#define DATA_PIN 9              // Arduino output control signal serial port
#define LED_TYPE SK6812         // LED light belt type
#define COLOR_ORDER GRB         // The division order of red, green and blue LED in RGB lamp beads
int analogPin = A0;
int pm = 0;
int color;
uint8_t max_bright = 20;       // LED brightness control variable. The value is in the range from 0 to 255, the greater the value, the higher the light band brightness

const int buttonPin = 4;    // the number of the pushbutton pin
int ledState = LOW;
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

CRGB leds[NUM_LEDS];            // Build light band leds


void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  // Initialize the light band

}

void loop() {

  int reading = digitalRead(buttonPin);

  pm = analogRead(analogPin);
  // Serial.println(pm);
  color = pm / 3.93;
  Serial.println(color);
 // Serial.println(reading); 

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  if (ledState == HIGH) {
    FastLED.setBrightness(5);
    fill_palette (leds, 37, color, 0, RainbowColors_p, 255, LINEARBLEND );
    FastLED.show();
  }
  else if (ledState == LOW) {
    FastLED.setBrightness(0);
    fill_palette (leds, 37, color, 0, RainbowColors_p, 255, LINEARBLEND );
    FastLED.show();
  }

Serial.println(ledState);
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;


 /* FastLED.setBrightness(max_bright);                            // Set the light band brightness
  fill_palette (leds, 37, color, 0, RainbowColors_p, 255, LINEARBLEND );
  FastLED.show();
  delay(10);*/


}
