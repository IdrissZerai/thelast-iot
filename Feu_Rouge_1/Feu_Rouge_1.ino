#define LED_RED 17
#define LED_GREEN 14
#define LED_ORANGE 18
#define Button_Pieton 25
#define Button_RED_LED 26
#define Button_1 
#define Button_2 
#define Button_3 
#define Button_4 
#define Button_5 

#define Delay_Red 3000
#define Delay_Green 5000
#define Orange_Wink 1000

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
int Compt = 0;
int Button_Red_State;
int Button_Pieton_State;

void Green_LED();
void Red_LED();
void Orange_LED();
void IRAM_ATTR ISR();
void setup() 
{
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_ORANGE, OUTPUT);
  pinMode(Button_Pieton, INPUT_PULLUP);
  pinMode(Button_RED_LED, INPUT);
  digitalWrite(LED_GREEN, HIGH);


  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() 
{
  int myButtons[] = {Button_1, Button_2, Button_3, Button_4, Button_5};
  for(int i = 0; i <= 4; i++){
  if(ReadingButton(myButtons[i]) == HIGH){
    counter++;
  }
  if((ReadingButton() == LOW) && counter > 0){
    counter--;
  }
  }
  if(counter > 2){
    Orange_LED();
    Red_LED();
    Green_LED();
   }
}
void Red_LED()
{
  Compt = 0;
  digitalWrite(LED_RED, HIGH);
  delay(Delay_Red);
  digitalWrite(LED_RED, LOW);
  Green_LED();
  
}
void Orange_LED()
{
  digitalWrite(LED_GREEN, LOW);
  for (int i=0; i<5; i++)
  {
  delay (10);
  digitalWrite(LED_ORANGE, HIGH);
  delay (Orange_Wink);
  digitalWrite(LED_ORANGE, LOW);
  delay (Orange_Wink);
  }
}
void Green_LED()
{
  digitalWrite(LED_GREEN, HIGH);
  delay(Delay_Green);
}

String ReadingButton(int Button){
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
