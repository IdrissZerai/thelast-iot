#define Button_RED_LED 4
#define Button_1 14
#define Button_2 02
#define Button_3 17

#define Delay_Red 5000
#define Delay_Green 5000
#define Orange_Wink 500



#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
    #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define RGBLEDPIN            25

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      10

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, RGBLEDPIN, NEO_GRB + NEO_KHZ800);


const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers


int Green_LED_State;
int Red_LED_State;
int Orange_LED_State;
int counter = 0;
int Button_Red_State;
int Button_Pieton_State;

void Green_LED();
void Red_LED();
void Orange_LED();
void IRAM_ATTR ISR();
int myButtons[] = {Button_1, Button_2, Button_3};
void setup() 
{
  Serial.begin(9600);
  pixels.setBrightness(255);
  pixels.begin();
  pixels.clear();
  pixels.setPixelColor(2, pixels.Color(0, 150, 0)); // Moderately bright green color.
  pixels.show();
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() 
{
  
  delay(1000);
 
  //Serial.print(ReadingButton(myButtons[0]));
  //Serial.print(ReadingButton(myButtons[1]));
  if(((ReadingButton(myButtons[0]) == HIGH) && (ReadingButton(myButtons[1]) == HIGH) && (ReadingButton(myButtons[2]) == HIGH)) || (ReadingButton(Button_RED_LED) == HIGH) ) {
   Orange_LED();
    Red_LED();
    Green_LED();
  }
  
  
 
   Serial.print(counter);
}
void Red_LED()
{
  counter = 0;
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  pixels.show();
  delay(Delay_Red);
  pixels.clear();
  Green_LED();
  
}
void Orange_LED()
{
  pixels.clear();
  for (int i=0; i<5; i++)
  {
  delay (10);
  pixels.setPixelColor(1, pixels.Color(255, 128, 0));
  pixels.show();
  delay (Orange_Wink);
  pixels.clear();
  delay (Orange_Wink);
  }
}
void Green_LED()
{
  pixels.clear();
  pixels.setPixelColor(2, pixels.Color(0, 150, 0)); // Moderately bright green color.
  pixels.show();
  delay(Delay_Green);
}

int ReadingButton(int Button){
  // read the state of the switch into a local variable:
  int reading = digitalRead(Button);

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
        // put counter here
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  return lastButtonState;
}
