const int interruptPin = 2;
const int buzzerPin = 3;
const int carLedRedPin = 6;
const int carLedYellowPin = 8;
const int carLedGreenPin = 10;
const int pedLedRedPin = 13;
const int pedLedGreenPin = 12;
const int debounceInterval = 50;

//intervals
const unsigned long timer4 = 200; // blink 4
const unsigned long timer3 = 500; // blink 3
const unsigned long state2Delay = 8000; //8 second delay after pressing
const unsigned long state2Timer = 3000; //state 2
const unsigned long state3Timer = 8000; //time spent in state3
const unsigned long state4Timer = 4000; //state 4

//InterruptPin
bool interruptPinState = LOW;
bool lastInterruptPinState = LOW;
bool read = LOW;
bool lastRead = LOW;

//led state
bool carLedStateRed = LOW;
bool carLedStateYellow = LOW;
bool carLedStateGreen = LOW;
bool pedLedStateRed = HIGH;
bool pedLedStateGreen = HIGH;

//sounds 
int buzzerTone = 10;
int buzzerDuration = 300;
int lastDebounceTimer = 0;
int currentState = 1;
unsigned long previousMillis = 0;
unsigned long startMillis = 0;
unsigned long currentMillis = 0;


void setup() {
  pinMode(pedLedRedPin, OUTPUT);
  pinMode(pedLedGreenPin, OUTPUT);
  pinMode(carLedRedPin, OUTPUT);
  pinMode(carLedYellowPin, OUTPUT);
  pinMode(carLedGreenPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  Serial.begin(9600);

}

void loop() {

  state1();
  read= digitalRead(interruptPin);
  
  if (millis() - lastDebounceTimer > debounceInterval)
  {
    if (read != interruptPinState)
    {
      interruptPinState = read;
      if (interruptPinState == LOW)
      {
          state2();
          state3();
          state4();
      }
    }
  }
  lastRead = read;
  

}

void state1() {
  //green light for cars and red light for pedestrians
  carLedStateRed = LOW;
  carLedStateYellow = LOW;
  carLedStateGreen = HIGH;
  pedLedStateRed = HIGH;
  pedLedStateGreen = LOW;

  digitalWrite(carLedRedPin,carLedStateRed );
  digitalWrite(carLedGreenPin, carLedStateGreen);
  digitalWrite(carLedYellowPin, carLedStateYellow);
  digitalWrite(pedLedGreenPin,pedLedStateGreen);
  digitalWrite(pedLedRedPin,pedLedStateRed);

}

void state2() {

  // When we reach state 2 the car traffic lights gets yellow, it happens 8 sec after presing it, and stays in state 2 for 3 second
   //if the cars light is not yellow, change it from green to yellow

    startMillis = millis();
    currentMillis = millis();

    while(currentMillis - startMillis <= state2Delay){ //delay 8 seconds
      currentMillis = millis(); 
    }

      startMillis=millis();

    while(currentMillis - startMillis <= state2Timer ) {
         
     
      if (carLedStateYellow == LOW){
         carLedStateYellow = HIGH;
       digitalWrite(carLedYellowPin, carLedStateYellow);
       }
      if (carLedStateGreen = !LOW){
      carLedStateGreen = !carLedStateGreen;
      digitalWrite(carLedGreenPin, carLedStateGreen);
       }
     currentMillis =millis();
  }

}



void state4(){

  // When in state 4 the pedestrian traffic light is green and blinks faster while the car's stays red
  // This lasts for 4 seconds

  startMillis = millis();
  currentMillis = millis();
  while (currentMillis - startMillis <= state4Timer)                     //duration
  {
    if (currentMillis - previousMillis >= timer4)                  //blink
    {
      previousMillis = currentMillis;                            
     //faster buzzer sound
      pedLedStateGreen = !pedLedStateGreen;
      tone(buzzerPin, buzzerTone, buzzerDuration);
      digitalWrite(pedLedGreenPin, pedLedStateGreen);
    }
    currentMillis = millis();
  }
}

void state3(){

  // When in state 3 cars get red, pedestrians get green and a beeping starts this state lasts 8 seconds

  startMillis = millis();
  currentMillis = millis();
  while (currentMillis - startMillis <= state3Timer)             //makes it last 8 seconds
  {
   //cars get red, pedestrians get green
  if (carLedStateYellow != LOW){
      carLedStateYellow = !carLedStateYellow;
      digitalWrite(carLedYellowPin, carLedStateYellow);
    }

    if (carLedStateRed != HIGH){                          
      carLedStateRed = !carLedStateRed;                       
      digitalWrite(carLedRedPin, carLedStateRed);           
    }

    if (pedLedStateRed != LOW){
      pedLedStateRed = !pedLedStateRed;
      digitalWrite(pedLedRedPin, pedLedStateRed);
    }

    if (pedLedStateGreen != HIGH){
      pedLedStateGreen = !pedLedStateGreen;
      digitalWrite(pedLedGreenPin, pedLedStateGreen);
    }

    if (currentMillis - previousMillis >= timer3){    //buzzer         
      previousMillis = currentMillis;
      tone(buzzerPin, buzzerTone, buzzerDuration);
    }
    
    currentMillis = millis();
  }
  
}