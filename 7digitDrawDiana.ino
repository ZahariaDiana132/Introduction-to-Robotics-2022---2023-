#include <ezButton.h> //biblioteca ce ajuta la debounce si long short press
ezButton button(12);  // create ezButton object that attach to pin 12;
const int SHORT_PRESS_TIME = 450; 
const int LONG_PRESS_TIME  = 500; 
const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;
const int segSize = 8;
const int joyXPin = A2;
const int joyYPin = A1;
const int joySWPin = 12;
const int joyLeftThreshold = 350;
const int joyRightThreshold = 650;
const int joyDownThreshold = 350;
const int joyUpThreshold = 650;
const int up = 0;
const int down = 1;
const int left = 2;
const int right = 3;
const int blinkTime = 400;
const int move = 4;
const int neutralVerify = -1;
const int stateOne = 1;
const int stateTwo = 2;
const int indexA = 0;
const int indexB = 1;
const int indexC = 2;
const int indexD = 3;
const int indexE = 4;
const int indexF = 5;
const int indexG = 6;
const int indexDP = 7;
bool joyIsNeutral = true;
bool dpState = false;
bool commonAnode = false; 
unsigned long pressedTime  = 500;
unsigned long releasedTime = 1000;
unsigned long currentMillis = 0;
unsigned long previousMillis = 0;
long pressDuration;
int copySegmentState = LOW;
int currentPin = 0;
int state = 1 ;
int i;
byte segmentOn = HIGH;

int segments[segSize] = { 
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte segmentStates[segSize] = {
 LOW,LOW,LOW,LOW,LOW,LOW,LOW,LOW
};

//matrice pentru mutari 
int digitMatrix[segSize][move]={
//up, down ,left, right ->move 
  {indexA, indexG, indexF, indexB},  //a
  {indexA, indexG, indexF, indexB},  //b
  {indexG, indexD, indexE, indexDP}, //c
  {indexG, indexD, indexE, indexC},  //d
  {indexG, indexD, indexE, indexC},  //e
  {indexA, indexG, indexF, indexB},  //f
  {indexA, indexD, indexG, indexG},  //g
  {indexDP,indexDP, indexC, indexDP} //dp

};

void setup() {

  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  pinMode(joySWPin, INPUT_PULLUP);
  if (commonAnode == true) {
    segmentOn = !segmentOn;
  }
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  Serial.begin(9600);

}

void loop() {

  if(state == stateOne){
  int joyY = analogRead(joyYPin);
  int joyX = analogRead(joyXPin);
  currentPin=currentPinChange(joyY,joyX,currentPin);
  currentMillis = millis();
  if (currentMillis - previousMillis >= blinkTime){                  //blinking
      previousMillis = currentMillis;                            
      copySegmentState = !copySegmentState;
      digitalWrite(segments[currentPin],copySegmentState);
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
        state = stateTwo; 
         else 
        state = stateOne;       
    }

    if( pressDuration > LONG_PRESS_TIME && state == 1){ 
      for(i=0;i<segSize-1;i++){
        segmentStates[i]=LOW;
        digitalWrite(segments[i],segmentStates[i]);
      }
        currentPin = indexDP;
    }
  }

  if(state == stateTwo){
    int joy2X = analogRead(joyXPin);
    int notNeutru = currentPinStateChange(joy2X,currentPin,segmentStates[currentPin]);
    if(notNeutru != neutralVerify){ 
      segmentStates[currentPin]=notNeutru; 
      digitalWrite(segments[currentPin],segmentStates[currentPin]);
      }
    else 
      digitalWrite(segments[currentPin],segmentStates[currentPin]);
    } 
  
  for(i=0;i<segSize;i++)
   if(i != currentPin);
    digitalWrite(segments[i],segmentStates[i]);
}


int currentPinStateChange(int joyX, int currentPin, byte segmentStates[]){
  if(joyX < joyDownThreshold && joyIsNeutral){ //up
     joyIsNeutral = false;
     return HIGH;
  }

  if(joyX > joyUpThreshold && joyIsNeutral){ //down
     joyIsNeutral = false;
     return LOW;
    }

  if(joyDownThreshold <= joyX && joyX <= joyUpThreshold) {
    joyIsNeutral = true; 
    return neutralVerify;
  }
}

int currentPinChange(int joyY,int joyX,int currentPin)
{
   
   if(joyX < joyDownThreshold && joyIsNeutral) { 
     joyIsNeutral = false;
     digitalWrite(segments[currentPin],segmentStates[currentPin]);
     return digitMatrix[currentPin][up];
   }
    if(joyX > joyUpThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      digitalWrite(segments[currentPin],segmentStates[currentPin]);
      return digitMatrix[currentPin][down];
    }
   if(joyY > joyRightThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      digitalWrite(segments[currentPin],segmentStates[currentPin]);
      return digitMatrix[currentPin][left];
    }
    if(joyY < joyLeftThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      digitalWrite(segments[currentPin],segmentStates[currentPin]);
      return digitMatrix[currentPin][right];
    }
    
     if(joyLeftThreshold <= joyY && joyY <= joyRightThreshold && joyDownThreshold <= joyX && joyX <= joyUpThreshold) {
       joyIsNeutral = true; 
       return currentPin;
  }
  
}