//DS= [D]ata [S]torage - data
//STCP= [ST]orage [C]lock [P]in latch
//SHCP= [SH]ift register [C]lock [P]in clock
#include <ezButton.h> //biblioteca ce ajuta la debounce si long short press
ezButton button(2);  // create ezButton object that attach to pin 12;
const int SHORT_PRESS_TIME = 450; 
const int LONG_PRESS_TIME  = 500; 
const int joyXPin = A2;
const int joyYPin = A1;
const int joySWPin = 12;
const int joyLeftThreshold = 350;
const int joyRightThreshold = 650;
const int joyDownThreshold = 350;
const int joyUpThreshold = 650;
const int latchPin = 11; // STCP to 12 on Shift Register
const int clockPin = 10; // SHCP to 11 on Shift Register
const int dataPin = 12; // DS to 14 on Shift Register
const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;
const byte regSize = 8; // 1 byte aka 8 bits
const int blinkTime = 300;
const int displayCount = 4;
const int encodingsNumber = 16;
const int stateOne = 1;
const int stateTwo = 2;
int displayDigits[] = {
  segD1, segD2, segD3, segD4
};
int displayDigitsVal[displayCount]{ 
  0, 0, 0, 0 
};
byte byteEncodings[encodingsNumber] = {
//A B C D E F G DP
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110, //F

};
  
unsigned long lastIncrement = 0;
unsigned long delayCount = 0;
unsigned long number = 0;
unsigned long pressedTime  = 500;
unsigned long releasedTime = 1000;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
int currentDisplay = 0;
long pressDuration;
bool joyIsNeutral = true;
bool joyIsNeutrall = true;
int state = 1;
int lastDisplay = 3;
int firstDisplay = 0;
int i;
byte stateOfDp = true;
void setup() {
  // put your setup code here, to run once:
 // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
 for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }  
   button.setDebounceTime(50); // set debounce time to 50 milliseconds
  Serial.begin(9600);
}
void loop() {
 
  for(int i = 0; i <displayCount; i++){
    if (i == currentDisplay) byteEncodings[displayDigitsVal[i]] += stateOfDp;
    writeReg(byteEncodings[displayDigitsVal[i]]);
    if (i == currentDisplay) byteEncodings[displayDigitsVal[i]] -= stateOfDp;
    activateDisplay(i); delay(1);
  }



   if(state == stateOne){
    int joyY = analogRead(joyYPin);
    currentDisplay=currentDisplayChange(joyY,currentDisplay);

    currentMillis = millis();  
    if (currentMillis - previousMillis >= blinkTime){                  //blinking
      previousMillis = currentMillis; 
      stateOfDp = !stateOfDp;     
    }

  }
  
  button.loop(); // MUST call the loop() function first

  if(button.isPressed()){
    pressedTime = millis();
  }
  if(button.isReleased()){
    releasedTime = millis();

   pressDuration = releasedTime - pressedTime;

    if( pressDuration < SHORT_PRESS_TIME){ 
      if (state == stateOne) 
        {state = stateTwo; }
         else 
        {state = stateOne; } 
    }
    if( pressDuration > LONG_PRESS_TIME && state == 1){ 
      for(int i = 0; i < displayCount; i++)
       displayDigitsVal[i] = 0;
      currentDisplay = 0;
    }

  }

  if( state == stateTwo){
    int joyX = analogRead(joyXPin);
    currentNumberChange(joyX, currentDisplay);
    stateOfDp = true;

  }
}

void writeReg(byte digit) {
    // ST_CP LOW to keep LEDs from changing while reading serial data
    digitalWrite(latchPin, LOW);
    // Shift out the bits
    shiftOut(dataPin, clockPin, MSBFIRST, digit);
    /* ST_CP on Rising to move the data from shift register
     * to storage register, making the bits available for output.
     */
    digitalWrite(latchPin, HIGH);
}

void activateDisplay(int displayNumber) {
  // first, disable all the display digits
  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], HIGH);
  }
  // then enable only the digit you want to use now
  digitalWrite(displayDigits[displayNumber], LOW);
  
}

int currentDisplayChange(int joyY,int currentDisplay)
{
   
   if(joyY > joyRightThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      if(currentDisplay < lastDisplay )
        return currentDisplay+1;
      else 
        return firstDisplay;

    }
    if(joyY < joyLeftThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      if(currentDisplay > firstDisplay)
        return currentDisplay-1;
      else 
        return lastDisplay;
    }
    
     if(joyLeftThreshold <= joyY && joyY <= joyRightThreshold) {
       joyIsNeutral = true; 
       return currentDisplay;
      
  }
  
}

void currentNumberChange(int joyX,int currentDisplay)
{
   
   if(joyX < joyDownThreshold && joyIsNeutrall) { //up
     if(displayDigitsVal[currentDisplay] < 15)
      displayDigitsVal[currentDisplay] += 1;
      joyIsNeutrall = false;
   
   }
    if(joyX > joyUpThreshold && joyIsNeutrall) { //down
      if(displayDigitsVal[currentDisplay] > 0)
        displayDigitsVal[currentDisplay] -= 1;
        joyIsNeutrall = false;
    }
    
 if(joyDownThreshold <= joyX && joyX <= joyUpThreshold) 
       joyIsNeutrall = true; 


  
}



