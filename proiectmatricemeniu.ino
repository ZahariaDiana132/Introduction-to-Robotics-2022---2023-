#include "LedControl.h" 

#include <LiquidCrystal.h>

#include<EEPROM.h>

#include "pitches.h"

// notes in the melody for game:
int melody1[] = {
  NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5,
  NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_C5,
  NOTE_C6, NOTE_G6, NOTE_E6, NOTE_C6, NOTE_G6, NOTE_E6,
  
  NOTE_B4, NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_B5,
  NOTE_FS5, NOTE_DS5, NOTE_DS5, NOTE_E5, NOTE_F5,
  NOTE_F5, NOTE_FS5, NOTE_G5, NOTE_G5, NOTE_GS5, NOTE_A5, NOTE_B5
};


int noteDurations[] = {
  16, 16, 16, 16,
  32, 16, 8, 16,
  16, 16, 16, 32, 16, 8,
  
  16, 16, 16, 16, 32,
  16, 8, 32, 32, 32,
  32, 32, 32, 32, 32, 16, 8
};


int noteLength;

#define	NOTE_G3	196
#define NOTE_A2 110
#define DELAY_TIME 250



const int choice = 1;
const int menu = 2;//stare menu
const int game = 6; //stare joc
const int settings = 4;
const int setBright = 9;
const int setDifficulty = 10;
const int highScore = 5;
const int about = 7;
const int howPlay = 8;
const int exitt = 11;
const int soundOnOf = 12;
const int resetHighsc = 13;
const int exits = 14;
const int restart = 15;
int menugame[3] = {game, menu,restart}; // to switch from menu state to game state
int menuList[5] = {settings, highScore, howPlay, about, exitt}; // actual menu states
int settingslist[5] ={ setBright, setDifficulty, soundOnOf, resetHighsc, exits};// settings options

// lcd pins
const byte pinRs = 9;

const byte pinEn = 8;

const byte pinD4 = 7;

const byte pinD5 = 6;

const byte pinD6 = 5;

const byte pinD7 = 4;


//matrix pins
const byte dinPin = 12;

const byte clockPin = 11;

const byte loadPin = 10;

const byte matrixSize = 8;

// buttons pins
const int buttonLeft = A5;
const int buttonRight = A4;
const int debounceTime = 100;
bool buttonLeftState = LOW;
bool lastLeftButtonPinState = LOW;
bool buttonRightState = LOW;
bool lastRightButtonPinState = LOW;
bool readLeft = LOW;
bool lastReadLeft = LOW;
bool readRight = LOW;
bool lastReadRight = LOW;
int lastDebounceTime = 0;
bool readSW = LOW;
bool readSW2 = LOW;
bool readSW22 =LOW;
bool readSWS = LOW;
bool readSWSS = LOW;
bool readSWH = LOW;
bool readSWB = LOW;
bool readSWD = LOW;
bool readSWSD = LOW;
bool readSWRH = LOW;
bool readSWStr = LOW;
bool buttonSWState = LOW;
bool lastSWButtonPinState = LOW;
// joystick pins
const int joyXPin = A2;
const int joyYPin = A1;
const int pinSW = A3;

// variables for joystick
const int joyLeftThreshold = 350;//in the game
const int joyRightThreshold = 650;//in the game
const int joyDownThreshold = 350;//for menu
const int joyUpThreshold = 650;//for menu


//buzzer pin 
const int buzzerPin = A0;


// matrix and lcd initializations

LiquidCrystal lcd(pinRs, pinEn, pinD4, pinD5, pinD6, pinD7);
LedControl lc = LedControl(dinPin, clockPin, loadPin, 1); //DIN, CLK, LOAD, No. DRIVER



// images for 8x8 matrix used for menu
const byte images[][8] {
  {
  0b00111100,
  0b01000010,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b01000010,
  0b00111100
  },
  {
  0b00111100,
  0b01000010,
  0b10100101,
  0b10000001,
  0b10100101,
  0b10011001,
  0b01000010,
  0b00111100
  },
  {
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111
  },
  {
  0b00000000,
  0b01100110,
  0b11111111,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000
  },
  {
  0b00010000,
  0b00111000,
  0b10010000,
  0b01111100,
  0b00010010,
  0b00101000,
  0b00100100,
  0b00100010
  },
  {
  0b00010000,
  0b00111000,
  0b00010010,
  0b01111100,
  0b10010000,
  0b00101000,
  0b01001000,
  0b10001000
},
{ 0b00111100,
  0b01111110,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100
  },
  {
  0b10000001,
  0b01000010,
  0b00100100,
  0b00011000,
  0b00011000,
  0b00100100,
  0b01000010,
  0b10000001
  },
  {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b11011011
  },
  {
  0b00000011, //settings
  0b00000011,
  0b00001111,
  0b00001111,
  0b00111111,
  0b00111111,
  0b11111111,
  0b11111111
  },
  {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00011000,
  0b00011000,
  0b01111000,
  0b01111110
  },
  {
  0b00111100,
  0b01000010,
  0b00000010,
  0b00001100,
  0b00010000,
  0b00010000,
  0b00000000,
  0b00010000
  },
  {
  0b00011000,
  0b00011000,
  0b00000000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000
  },
  {
  0b00000000,
  0b00100000,
  0b00110000,
  0b00111000,
  0b00111100,
  0b00111000,
  0b00110000,
  0b00100000
  },
  {
  0b00111100,
  0b01000010,
  0b01000010,
  0b01000010,
  0b00100100,
  0b00011000,
  0b00011000,
  0b00011000
  },
  {
  0b00000000,
  0b01111110,
  0b10000001,
  0b10000001,
  0b10111001,
  0b10110001,
  0b10101001,
  0b10000101
  },
  {
  0b10000000,
  0b10100000,
  0b10101000,
  0b10101000,
  0b10101010,
  0b10101010,
  0b10101010,
  0b10101010
  },
  {
  0b10000010,
  0b11000110,
  0b10101010,
  0b10010010,
  0b10000010,
  0b10000010,
  0b10000010,
  0b10000010
  }


};

const int nameLenght = 3;
const int maxDifficulty = 3;
const int minDifficulty = 1;
const int ON = 1;
const int OFF = 0;

// custom lcd characters
byte arrow[] = {
  B00000,
  B00100,
  B00110,
  B00111,
  B00110,
  B00100,
  B00000,
  B00000
};
byte smile[] = {
	0b00000,
	0b00000,
	0b01001,
	0b00000,
	0b01001,
	0b00110,
	0b00000,
	0b00000
};
byte heart[] = {
  0b00000,
	0b00000,
	0b11011,
	0b11111,
	0b11111,
	0b01110,
	0b00100,
	0b00000
};

byte arrowUp[] = {
	0b00000,
	0b00000,
	0b00100,
	0b01110,
	0b11111,
	0b00000,
	0b00000,
	0b00000
};

byte arrowDown[] = {
	0b00000,
	0b00000,
	0b00000,
	0b11111,
	0b01110,
	0b00100,
	0b00000,
	0b00000
};

byte clearCell[] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};



//SUUS
 String strr;
 String stt;

int lenMsg = 168;
int lenMsg3 = 208;
int ii = 0;
int ok = 0;
int scadress = 1;
int adress = 11;
int nmm = adress;
int pozChr = 0;
int tempo = 210;
const long interval = 70;
unsigned long lastMiillis = 0;
int lastState = 0;
int lastPoz = 0;
int lastPoz2 = 0;
int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5,
  NOTE_D5, NOTE_G5, NOTE_E5,
  NOTE_D5, NOTE_G5
};


int durations[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4,
  8, 8 ,4, 4 ,4
};

 void displayImageSetup(const byte* image) {
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          lc.setLed(0, i, j, bitRead(image[i], 7 - j));
        }
      }
    }
    
const char  messagePadded[] PROGMEM = "  Project by Zaharia Diana Cristiana, link github : https://github.com/ZahariaDiana132/Introduction-to-Robotics-2022---2023- , Nume: Dance Dance Revolution             ";
const char  messagePadded3[] PROGMEM = "  For the left/right collumn press left/right buttons when an overlap occurs, For the middle collumn dependin on if a dot overlaps in the left/right side move the joystick to the left/right side           ";
int letter = 0;
int letter3 = 0;
int poz = 0;
int poz2 = 0;
int poz22 = 0;
int note1 = 0;
int intro = 0;
int nrlives = 4;
int score = 0;
int livesLeft = 3;
int laststart = -1;
int joyX = 0;
int joyY = 0;
int joy2X = 0;
int joy2Y = 0;
int joy22X = 0;
int joy22Y = 0;
int joyGX = 0;
int joyGY = 0;
int joyGY1 = 0;
int joyGY2 = 0;
int joyYB =  0;
int joyYD = 0;
int joyXH = 0;
int joyYSD = 0;
int joyYRH = 0;
int joyXSS = 0;
bool joyIsNeutral = true;
unsigned long lastExecutedMillis;
int state = 0; 
int repeatSound = 0 ;
int noteLength2;
int n1,n2,n3,n4,n5; //adrese nume highscore
int scoreStat = 0; // nu e highscore
int highS = 1;

// top 5 highscore names

char scoreNames[5][4];
 String st1;
 String st2;
 String st3;
 String st4;
 String st5;
// top 5 scores
int scores[5];

int s1 = 1, s2 = 2, s3 = 3, s4 =4, s5 = 5;

int currentPoz = 0;
int lastCurrentPoz = 0;
int matrixBrightness;
int activeDifficulty;
byte sound;
byte opt = OFF;
#define SOUND_ADDR 10
#define DIFFIC_ADDR 9
#define BRIGHT_ADDR 8



void setup() {

  pinMode(pinSW,INPUT_PULLUP);// activate pull-upresistor on the// push-button pin
  lcd.begin(16,2);
  lcd.clear();
  lcd.createChar(0, arrow);
  lcd.createChar(1, heart);
  lcd.createChar(2, smile);
  lcd.createChar(3, arrowUp);
  lcd.createChar(4, arrowDown);
  lcd.createChar(5, clearCell);
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.clearDisplay(0);// clear screen
  sound =  EEPROM.read(SOUND_ADDR);
  matrixBrightness = EEPROM.read(BRIGHT_ADDR);
  activeDifficulty = EEPROM.read(DIFFIC_ADDR);
/*
     for (int i = 0; i < 5; i++)
    EEPROM.update((scadress + i) , 0);
    */
      for (int i = 0; i < 5; i++)
    scores[i] = EEPROM.read((scadress + i));
/*
  String str1 = "AAA ";
  String str2 = "CCC ";
  int strnume1 = writeStringToEEPROM(adress, str1);
  int strnume2 = writeStringToEEPROM(strnume1, str2);
  int strnume3 = writeStringToEEPROM(strnume2, str2);
  int strnume4 = writeStringToEEPROM(strnume3, str1);
  writeStringToEEPROM(strnume4, str2);*/

  int nume1 = readStringFromEEPROM(adress, &st1);
  int nume2 = readStringFromEEPROM(nume1, &st2);
  int nume3 = readStringFromEEPROM(nume2, &st3);
  int nume4 = readStringFromEEPROM(nume3, &st4);  
  readStringFromEEPROM(nume4, &st5);

  st1.toCharArray(scoreNames[0],4);
  st2.toCharArray(scoreNames[1],4);
  st3.toCharArray(scoreNames[2],4);
  st4.toCharArray(scoreNames[3],4);
  st5.toCharArray(scoreNames[4],4);

  lc.setIntensity(0, matrixBrightness); // sets brightness (0~15 possible values)

  pinMode(buzzerPin, OUTPUT);
  //analogWrite(pinV0, contrast);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  // set up the LCD's number of columns and rows:
   Serial.begin(9600);
   lcd.setCursor(0, 0);
   lcd.print(" Press joystick ");
   lcd.setCursor(0, 1);
   lcd.print(" button to start");

   noteLength = sizeof(noteDurations) / sizeof(int);

}

void loop() {
 

  if(state == 0){
    readSW = digitalRead(pinSW);
  
  if (millis() - lastDebounceTime > debounceTime)
  {
    if (readSW != buttonSWState)
    {
      buttonSWState = readSW;
      if (buttonSWState == LOW)
      {
             
            lcd.begin(16,2);
            lcd.setCursor(2, 0);
            // Print a message to the LCD.
            lcd.write(byte(1));
            lcd.print(" LOADING: ");
            lcd.write(byte(1));
            lcd.setCursor(0, 1);
            lcd.write(byte(2));  
            lcd.print(" please wait... ");
   /*  
*/

  int size = sizeof(durations) / sizeof(int);

  for (int note = 0; note < size; note++) {
     if(repeatSound % 2 == 0)
      displayImageSetup(images[4]);
     else 
       displayImageSetup(images[5]);
    //to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int duration = 1000 / durations[note];
     if(sound == 1){
    tone(buzzerPin, melody[note], duration);}

    //to distinguish the notes, set a minimum time between them.
    //the note's duration + 30% seems to work well:
    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    
    //stop the tone playing:
    noTone(buzzerPin);
    repeatSound++;
  }
  
  displayImageSetup(images[1]);
  lcd.clear();
  lcd.setCursor(2, 0);
  // Print a message to the LCD.
  lcd.print("DANCE  DANCE");
  // set the cursor to column 0, line 1

  // (note: line 1 is the second row, since counting begins with 0):

  lcd.setCursor(3, 1);
  lcd.print("REVOLUTION!");
  delay(2000);
  state = choice;
  lcd.clear();
  repeatSound = 0;
      }
    }
  }
}


  if(state == choice){

   poz=joyStickMenu(menugame[3],3,poz);
  if( poz == 0){
   lcd.setCursor(0, 0);
   lcd.write(byte(0)); 
   lcd.print(" PLAY GAME");
   lcd.setCursor(15, 0);
   lcd.write(byte(5)); 
   lcd.setCursor(0, 1);
   lcd.print("  MENU     ");
   lcd.setCursor(15, 1);
   lcd.write(byte(4)); 
   displayImageSetup(images[13]);
   }
  else if(poz == 1)
  {
   lcd.setCursor(0, 0);
   lcd.write(byte(0)); 
   lcd.print(" MENU     ");
   lcd.setCursor(15, 0);
   lcd.write(byte(3)); 
   lcd.setCursor(0, 1);
   lcd.print("  RESTART    ");
   lcd.setCursor(15, 1);
   lcd.write(byte(4)); 
   displayImageSetup(images[17]);
 
  }
  else {
    
   lcd.setCursor(0, 0);
   lcd.print("  MENU     ");
   lcd.setCursor(15, 0);
   lcd.write(byte(3));
   lcd.setCursor(0, 1);
   lcd.write(byte(0)); 
   lcd.print(" RESTART     ");
   lcd.setCursor(15, 1);
   lcd.write(byte(5)); 
   displayImageSetup(images[7]); 

  }

   readSW = digitalRead(pinSW);
   if (readSW != lastState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastState = readSW;
  }
  if (millis() - lastDebounceTime > debounceTime)
  {
    if (readSW != buttonSWState)
    {
      buttonSWState = readSW;
      if (buttonSWState == LOW)
      {
        state = menugame[poz];
        lcd.clear();
        lastState = 0;
      }
    }
  }
   lastState = readSW;
}
 
 if(state == restart){

   lc.clearDisplay(0);
   lcd.setCursor(0, 0);
   lcd.print(" Press joystick ");
   lcd.setCursor(0, 1);
   lcd.print(" button to start");
   state = 0;
 }


  if(state == menu)
  {  
 
    poz2=joyStickMenuList(menuList[5],5,poz2);
     if(lastPoz != poz2)
     lcd.clear();
    lastPoz=poz2;
    if(poz2 == 0){
      displayImageSetup(images[9]);
      lcd.setCursor(0, 0);
      lcd.write(byte(0)); 
      lcd.print(" SETTINGS");
      lcd.setCursor(15, 0);
      lcd.write(byte(5)); 
      lcd.setCursor(0, 1);
      lcd.print("  HIGHSCORE");
      lcd.setCursor(15, 1);
      lcd.write(byte(4)); 
    }
    else if(poz2 == 1){
      displayImageSetup(images[10]);
      lcd.setCursor(0, 0);
      lcd.write(byte(0)); 
      lcd.print(" HIGHSCORE");
      lcd.setCursor(15, 0);
      lcd.write(byte(3)); 
      lcd.setCursor(0, 1);
      lcd.print("  HOW TO PLAY");
      lcd.setCursor(15, 1);
      lcd.write(byte(4)); 
    }
    else if(poz2 == 2){
      displayImageSetup(images[11]);
      lcd.setCursor(0, 0);
      lcd.write(byte(0)); 
      lcd.print(" HOW TO PLAY");
      lcd.setCursor(15, 0);
      lcd.write(byte(3)); 
      lcd.setCursor(0, 1);
      lcd.print("  ABOUT");
      lcd.setCursor(15, 1);
      lcd.write(byte(4)); 
    }
    else if(poz2 == 3) {
      displayImageSetup(images[12]);
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
      lcd.print(" ABOUT");
      lcd.setCursor(15, 0);
      lcd.write(byte(3));
      lcd.setCursor(0, 1); 
      lcd.print("  EXIT");
      lcd.setCursor(15, 1);
      lcd.write(byte(4));
    }
    else {
      displayImageSetup(images[7]);
      lcd.setCursor(0, 0);
      lcd.print("  ABOUT");
      lcd.setCursor(15, 0);
      lcd.write(byte(3));
      lcd.setCursor(0, 1);
      lcd.write(byte(0)); 
      lcd.print(" EXIT");
      lcd.setCursor(15, 1);
      lcd.write(byte(5));
    }
  readSW2 = digitalRead(pinSW);
   if (readSW2 != lastState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastState = readSW2;
  }
  if (millis() - lastDebounceTime > debounceTime)
  {
    if (readSW2 != buttonSWState)
    {
      buttonSWState = readSW2;
      if (buttonSWState == LOW)
      {
        state = menuList[poz2];
        lcd.clear();
        lastState = 0;
        letter = 0;
        letter3 = 0;
      }
    }
  }
  lastState = readSW2;


 }
 
 if(state == exitt){
   state = choice;
 }
  if(state == settings){
      
     poz22 =joyStickSettingsList(settingslist[5],5,poz22);
     if(lastPoz2 != poz22)
     lcd.clear();
    lastPoz2=poz22;
    if(poz22 == 0){
      displayImageSetup(images[14]);
      lcd.setCursor(0, 0);
      lcd.write(byte(0)); 
      lcd.print(" SET BRIGHTNESS");
      lcd.setCursor(15, 0);
      lcd.write(byte(5));
      lcd.setCursor(0, 1);
      lcd.print("  DIFFICULTY");
      lcd.setCursor(15, 1);
      lcd.write(byte(4));
    }
    else if(poz22 == 1){
      displayImageSetup(images[15]);
      lcd.setCursor(0, 0);
      lcd.write(byte(0)); 
      lcd.print(" DIFFICULTY");
      lcd.setCursor(15, 0);
      lcd.write(byte(3));
      lcd.setCursor(0, 1);
      lcd.print("  SOUND ON/OFF");
      lcd.setCursor(15, 1);
      lcd.write(byte(4));
    }
    else if( poz22 == 2 ){
      displayImageSetup(images[16]);
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
      lcd.print(" SOUND ON/OFF");
      lcd.setCursor(15, 0);
      lcd.write(byte(3));
      lcd.setCursor(0, 1); 
      lcd.print("  RESET HIGH");
      lcd.setCursor(15, 1);
      lcd.write(byte(4));

    }
    else if( poz22 == 3 ){
      displayImageSetup(images[10]);
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
      lcd.print(" RESET HIGH");
      lcd.setCursor(15, 0);
      lcd.write(byte(3));
      lcd.setCursor(0, 1); 
      lcd.print("  EXIT->MENU");
      lcd.setCursor(15, 1);
      lcd.write(byte(4));

    }
    else {
      displayImageSetup(images[7]);
      lcd.setCursor(0, 0);
      lcd.print("  RESET HIGH");
      lcd.setCursor(15, 0);
      lcd.write(byte(3));
      lcd.setCursor(0, 1); 
      lcd.write(byte(0));
      lcd.print(" EXIT->MENU");
      lcd.setCursor(15, 1);
      lcd.write(byte(5));

    }

  readSW22 = digitalRead(pinSW);
   if (readSW22 != lastState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastState = readSW22;
  }
  if (millis() - lastDebounceTime > debounceTime)
  {
    if (readSW22 != buttonSWState)
    {
      buttonSWState = readSW22;
      if (buttonSWState == LOW)
      {
        state = settingslist[poz22];
        lcd.clear();
        lastState = 0;
      }
    }
  }
  lastState = readSW22;

  }

 
  if(state == howPlay){
   displayImageSetup(images[1]);
    lcd.setCursor(0, 0);
    lcd.print("INSTRUCTIONS: ");
    letter3 = joyStickScroll2(letter3);
    if(letter3 <= lenMsg3 - 16)
  {
    showLetters3(0, letter3);
  }

   readSWS = digitalRead(pinSW);
   if (readSWS != lastState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastState = readSWS;
  }
  if (millis() - lastDebounceTime > debounceTime)
  {
    if (readSWS != buttonSWState)
    {
      buttonSWState = readSWS;
      if (buttonSWState == LOW)
      {
        state = menu;
        lcd.clear();
        lastState = 0;
      }
    }
  }
  lastState = readSWS;

  }

 

  if(state == about){
    displayImageSetup(images[3]);
    lcd.setCursor(0, 0);
    lcd.print("INFO: ");
    letter = joyStickScroll(letter);
   //From 0 to upto n-16 characters supply to below function
  if( letter <= (lenMsg - 16) )
    showLetters(0, letter);
   
   readSWSS = digitalRead(pinSW);
   if (readSWSS != lastState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastState = readSWSS;
  }
  if (millis() - lastDebounceTime > debounceTime)
  {
    if (readSWSS != buttonSWState)
    {
      buttonSWState = readSWSS;
      if (buttonSWState == LOW)
      {
        state = menu;
        lcd.clear();
        lastState = 0;
      }
    }
  }
  lastState = readSWSS;

  }


  if(state == highScore){
    displayImageSetup(images[10]);

    currentPoz = joyStickHigh(currentPoz);

    if(currentPoz != lastCurrentPoz)
       lcd.clear(); 
      lcd.setCursor(0, 0);
      lcd.print((currentPoz+1));
      lcd.print("  ");
      lcd.print(scoreNames[currentPoz]);
      lcd.print(" : ");
      lcd.print(scores[currentPoz]);
      lcd.setCursor(0, 1);
      lcd.print((currentPoz+2));
      lcd.print("  ");
      lcd.print(scoreNames[currentPoz + 1]);
      lcd.print(" : ");
      lcd.print(scores[currentPoz + 1]);

      lastCurrentPoz = currentPoz;

       readSWH = digitalRead(pinSW);
   if (readSWH != lastState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastState = readSWH;
  }
  if (millis() - lastDebounceTime > debounceTime)
  {
    if (readSWH != buttonSWState)
    {
      buttonSWState = readSWH;
      if (buttonSWState == LOW)
      {
        state = menu;
        lcd.clear();
        lastState = 0;
      }
    }
  }
  lastState = readSWH;



  }//EEPROM

  if(state == setBright){
    displayImageSetup(images[2]);
  matrixBrightness = joyStickBright(matrixBrightness);
  EEPROM.update( BRIGHT_ADDR , matrixBrightness );
  lc.setIntensity(0, matrixBrightness);
     readSWB = digitalRead(pinSW);
   if (readSWB != lastState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastState = readSWB;
  }
  if (millis() - lastDebounceTime > debounceTime)
  {
    if (readSWB != buttonSWState)
    {
      buttonSWState = readSWB;
      if (buttonSWState == LOW)
      {
        state = settings;
        lcd.clear();
        lastState = 0;
      }
    }
  }
  lastState = readSWB;


    //matrixBrightness creste sau scade -> joystick 

  } //EEPROM

  if(state == setDifficulty){



   displayImageSetup(images[15]);
    activeDifficulty = joyStickDif(activeDifficulty);
   EEPROM.update( DIFFIC_ADDR , activeDifficulty);
 readSWD = digitalRead(pinSW);
   if (readSWD != lastState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastState = readSWD;
  }
  if (millis() - lastDebounceTime > debounceTime)
  {
    if (readSWD != buttonSWState)
    {
      buttonSWState = readSWD;
      if (buttonSWState == LOW)
      {
        state = settings;
        lcd.clear();
        lastState = 0;
      }
    }
  }
  lastState = readSWD;


  } //EEPROM

  if(state == soundOnOf){

   lcd.setCursor(0, 0);
   lcd.print("js L/R -> ON/OFF");

   sound = joyStickSound(sound);
   EEPROM.update( SOUND_ADDR , sound );

   readSWSD = digitalRead(pinSW);
   if (readSWSD != lastState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastState = readSWSD;
  }
  if (millis() - lastDebounceTime > debounceTime)
  {
    if (readSWSD != buttonSWState)
    {
      buttonSWState = readSWSD;
      if (buttonSWState == LOW)
      {
        state = settings;
        lcd.clear();
        lastState = 0;
      }
    }
  }
  lastState = readSWSD;

  }

 if( state == resetHighsc){
  
  lcd.setCursor(0,0);
  lcd.print(" RIGHT=RESET ");

  opt = joyStickOPT(opt);

  if(opt == ON){
  
   for (int i = 0; i < 5; i++)
    EEPROM.update((scadress + i) , 0);

  for (int i = 0; i < 5; i++)
    scores[i] = EEPROM.read((scadress + i));

  String str1 = "AAA ";
  String str2 = "BBB";
  String str3 = "CCC";
  String str4 = "DDD";
  String str5 = "EEE";
  int nm1 = writeStringToEEPROM(adress, str1);
  int nm2 = writeStringToEEPROM(nm1, str2);
  int nm3 = writeStringToEEPROM(nm2, str3);
  int nm4 = writeStringToEEPROM(nm3, str4);
  writeStringToEEPROM(nm4, str5);


  int num1 = readStringFromEEPROM(adress, &st1);
  int num2 = readStringFromEEPROM(num1, &st2);
  int num3 = readStringFromEEPROM(num2, &st3);
  int num4 = readStringFromEEPROM(num3, &st4);  
  readStringFromEEPROM(num4, &st5);

  st1.toCharArray(scoreNames[0],4);
  st2.toCharArray(scoreNames[1],4);
  st3.toCharArray(scoreNames[2],4);
  st4.toCharArray(scoreNames[3],4);
  st5.toCharArray(scoreNames[4],4);
  }

     readSWRH = digitalRead(pinSW);
   if (readSWRH != lastState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    // save the the last flickerable state
    lastState = readSWRH;
  }
  if (millis() - lastDebounceTime > debounceTime)
  {
    if (readSWRH != buttonSWState)
    {
      buttonSWState = readSWRH;
      if (buttonSWState == LOW)
      {
        state = settings;
        lcd.clear();
        lastState = 0;
      }
    }
  }
  lastState = readSWRH;

 }

  if (state == exits){
     state = menu;
  }

  if (state == game){

   if(intro == 0){
   lastMiillis++;
   displayImageSetup(images[0]);
   lcd.setCursor(3, 0);
   lcd.print("Get ready");
   lcd.setCursor(3, 1);
   lcd.print("to dance!");
   if(lastMiillis == interval)
    {intro = 1; lastMiillis = 0;}

   }
   if(intro == 1) { 
     lastMiillis++;
     lcd.clear();
     displayImageSetup(images[1]);
  if(lastMiillis == interval) {
      intro = 2;
      }
   }
   if(intro == 2){

    
   lcd.setCursor(0, 0);
   lcd.print("lives:");

   for(int i=0; i< nrlives; i++)
     lcd.write(byte(1)); 
   lcd.setCursor(0, 1);
   lcd.print("score: ");
   lcd.print(score);
   displayImageSetup(images[8]);
   joyStickGame(nrlives,score);
   buttonLeftPress();
   buttonRightPress();

   if(nrlives == 0){
     isItHigh(score, ii, scoreStat);
     if( scoreStat != highS)
    {  
      lcd.setCursor(0, 0);
      lcd.print("GAME OVER");
      noTone(buzzerPin);
     delay(1000);
     lcd.clear();
     intro = 0;
     lastMiillis = 0;
     nrlives = 4;
     score = 0;
     scoreStat = 0;
     ii = 0;
     pozChr = 0;
     state = choice;
    }
    else
    { 
      for(int i = ii; i < 4; i=i+2){
      EEPROM.update((scadress + i+1) , scores[i]);
      scores[i+1] = EEPROM.read((scadress + i + 1));
       }
      EEPROM.update((scadress + ii) , score);
      scores[ii] = EEPROM.read((scadress + ii));

    noTone(buzzerPin);
     delay(1000);
     lcd.clear();
     intro = 0;
     lastMiillis = 0;
     nrlives = 4;
     score = 0;
     scoreStat = 0;
     ii = 0;
     pozChr = 0;
     state = choice;


      }

     
     }

   }

  }


}

void  isItHigh(int score, int &ii, int &scoreStat)
{ 
  
   while(ii < 5 && scoreStat == 0 && score != 0){
    if(score > scores[ii]){
      scoreStat = 1; 
      ii--;
    }
    ii++;
   }

  
}
void printSettingsName(String str)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set name");
    lcd.setCursor(0, 1);
    lcd.print(str);
    lcd.setCursor(pozChr, 1);
    lcd.blink();
}


String joyStickStrCh( String &str, int &pozChr){
  joyXSS = analogRead(joyXPin);
  char name[4]; // str = String(name);
  str.toCharArray(name,4);
  

   if(joyXSS < joyDownThreshold && joyIsNeutral) { 
     Serial.println("up");
     joyStkSound();
     joyIsNeutral = false;
     if(name[pozChr] < 'Z')
     name[pozChr] ++;
     else
     name[pozChr] = 'A';
     str = String(name);
     printSettingsName(str);
     return str;

   }
    if(joyXSS > joyUpThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      joyStkSound();
      Serial.println("down");
      if(name[pozChr] > 'A')
       name[pozChr] --;
      else
       name[pozChr] = 'Z';
      str = String(name);
      printSettingsName(str);
      return str;

    }


    
     if(joyY > joyRightThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("left");
      joyStkSound();
      if(pozChr > 0)
        pozChr--;
      printSettingsName(str);
      return str;

    }
    if(joyY < joyLeftThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("right");
      joyStkSound();
      if(pozChr < 3)
        pozChr++;
      printSettingsName(str);
      return str;

    }
    
     if(joyLeftThreshold <= joyY && joyY <= joyRightThreshold && joyDownThreshold <= joyX && joyX <= joyUpThreshold) {
       joyIsNeutral = true; 
       printSettingsName(str);
       return str;
    }

}
void showLetters(int print, int start1)
{  
    lcd.setCursor(print, 1);
   for (int letter = start1; letter <= start1 + 15; letter++) 
  {
    lcd.write(pgm_read_byte_near(messagePadded + letter));
  }
    lcd.print(" ");

  
}

void showLetters3(int printStart, int startLetter)
{
  lcd.setCursor(printStart, 1);
  for (int letter3 = startLetter; letter3 <= startLetter + 15; letter3++) 
  {
    lcd.write(pgm_read_byte_near(messagePadded3 + letter3));
  }

  lcd.print(" ");
 

}

void buttonRightPress(){
 readRight= digitalRead(buttonRight);
  
  if (millis() - lastDebounceTime > debounceTime)
  {
    if (readRight != buttonRightState)
    {
      buttonRightState = readRight;
      if (buttonRightState == LOW)
      {
          Serial.println("rightB");
      }
    }
  }
  lastReadRight = readRight;

}

void buttonLeftPress(){
   readLeft= digitalRead(buttonLeft);
  
  if (millis() - lastDebounceTime > debounceTime)
  {
    if (readLeft != buttonLeftState)
    {
      buttonLeftState = readLeft;
      if (buttonLeftState == LOW)
      {
          Serial.println("leftB");;
      }
    }
  }
  lastReadLeft = readLeft;

}


byte joyStickOPT(byte opt){ 
     
     joyYRH = analogRead(joyYPin);

   if(joyYRH > joyRightThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("LEFT");
      joyStkSound();
      lcd.setCursor(0, 1);
      lcd.print("No thanks      ");
      opt = OFF;
      return opt;
   
    }
    if(joyYRH < joyLeftThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("RIGHT");
      joyStkSound();
      lcd.setCursor(0, 1);
      lcd.print("RESET PENDING  ");
      opt = ON;
      return opt;
    
    }
    
     if(joyLeftThreshold <= joyYRH && joyYRH <= joyRightThreshold) {
       joyIsNeutral = true; 
       lcd.setCursor(0, 1);
       if(opt == OFF)
       lcd.print("NOPE          ");
       else
       lcd.print("RESET         ");
       return opt;
     
  }
}


int joyStickMenu(int aleg[], int n, int poz){ //for menu choices
     joyX = analogRead(joyXPin);
     joyY = analogRead(joyYPin);
   if(joyX < joyDownThreshold && joyIsNeutral) { 
     Serial.println("up");
     joyStkSound();
     joyIsNeutral = false;
     if(poz > 0)
     {
       poz--; 
       return poz;}
     else {
        
         return poz;
      }
   
   
   }
    if(joyX > joyUpThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("down");
      joyStkSound();
      if(poz < n-1)
        {poz++; 
      
        return poz;
        }
     else {
        
        return poz;
     }

    }
   if(joyY > joyRightThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("left");
      joyStkSound();
      displayImageSetup(images[7]);
      return poz;

    }
    if(joyY < joyLeftThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("right");
      displayImageSetup(images[7]);
      joyStkSound();
      return poz;

    }
    
     if(joyLeftThreshold <= joyY && joyY <= joyRightThreshold && joyDownThreshold <= joyX && joyX <= joyUpThreshold) {
       joyIsNeutral = true; 
       return poz;
     
       
  }
}

int joyStickHigh(int currentPoz){
     joyXH = analogRead(joyXPin);
   if(joyXH < joyDownThreshold && joyIsNeutral) { 
     Serial.println("up");
     joyIsNeutral = false;
     if(currentPoz > 0)
     {joyStkSound();
       currentPoz--; 
       return currentPoz;}
     else {
         joyStkSound();
         return currentPoz;
      }
   }
    if(joyXH > joyUpThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("down");
      if(currentPoz < 3)
        {currentPoz++; 
        joyStkSound();
        return currentPoz;
        }
     else {
        joyStkSound();
        return currentPoz;
     }

    }
    
     if(joyDownThreshold <= joyXH && joyXH <= joyUpThreshold) {
       joyIsNeutral = true; 
       return currentPoz;
  }
}


int joyStickMenuList(int choices[], int n, int poz2){ //for menu list choices
      joy2X = analogRead(joyXPin);
      joy2Y = analogRead(joyYPin);
   if(joy2X < joyDownThreshold && joyIsNeutral) { 
     Serial.println("up");
     joyIsNeutral = false;
     if(poz2 > 0)
     {joyStkSound();
       poz2--; 
       return poz2;}
     else {
         joyStkSound();
         return poz2;
      }
   
   
   }
    if(joy2X > joyUpThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("down");
      if(poz2 < n-1)
        {poz2++; 
        joyStkSound();
        return poz2;
        }
     else {
        joyStkSound();
        return poz2;
     }

    }
   if(joy2Y > joyRightThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("left");
      joyStkSound();
      displayImageSetup(images[7]);
      return poz2;

    }
    if(joy2Y < joyLeftThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("right");
       joyStkSound();
      displayImageSetup(images[7]);
      return poz2;

    }
    
     if(joyLeftThreshold <= joy2Y && joy2Y <= joyRightThreshold && joyDownThreshold <= joy2X && joy2X <= joyUpThreshold) {
       joyIsNeutral = true; 
       return poz2;
     
       
  }
}

int joyStickSettingsList(int choices[], int n, int poz22){ //for menu list choices
     joy22X = analogRead(joyXPin);
     joy22Y = analogRead(joyYPin);
   if(joy22X < joyDownThreshold && joyIsNeutral) { 
     Serial.println("up");
     joyIsNeutral = false;
     if(poz22 > 0)
     {joyStkSound();
       poz22--; 
       return poz22;}
     else {
         joyStkSound();
         return poz22;
      }
   
   
   }
    if(joy22X > joyUpThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("down");
      if(poz22 < n-1)
        {poz22++; 
        joyStkSound();
        return poz22;
        }
     else {
        joyStkSound();
        return poz22;
     }

    }
   if(joy22Y > joyRightThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("left");
      joyStkSound();
      displayImageSetup(images[7]);
      return poz22;

    }
    if(joy22Y < joyLeftThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("right");
       joyStkSound();
      displayImageSetup(images[7]);
      return poz22;

    }
    
     if(joyLeftThreshold <= joy22Y && joy22Y <= joyRightThreshold && joyDownThreshold <= joy22X && joy22X <= joyUpThreshold) {
       joyIsNeutral = true; 
       return poz22;
     
       
  }
}

void joyStickGame(int &nr, int &score){ //for game
     
     joyGX = analogRead(joyXPin);
     joyGY = analogRead(joyYPin);
   if(joyGX < joyDownThreshold && joyIsNeutral) { 
     lcd.clear();
      nr++;
     joyIsNeutral = false;
     Serial.println("UP");
     joyStkSound();   //pause
   }
    if(joyGX > joyUpThreshold && joyIsNeutral) {
      lcd.clear(); 
      score--;
      joyIsNeutral = false;
      Serial.println("DOWN");
      joyStkSound();   //get out of pause
    }
   if(joyGY > joyRightThreshold && joyIsNeutral) { 
      lcd.clear();
      joyIsNeutral = false;
      Serial.println("LEFT");
      nr--;
      joyStkSound();
    }
    if(joyGY < joyLeftThreshold && joyIsNeutral) { 
      lcd.clear();
      joyIsNeutral = false;
      score++;
      Serial.println("RIGHT");
      joyStkSound();

    }
    
     if(joyLeftThreshold <= joyGY && joyGY <= joyRightThreshold && joyDownThreshold <= joyGX && joyGX <= joyUpThreshold) {
       joyIsNeutral = true; 
     
       
  }
}

byte joyStickSound(byte sound){ 
     
     joyYSD = analogRead(joyYPin);

   if(joyYSD > joyRightThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("LEFT");
      joyStkSound();
      lcd.setCursor(0, 1);
      lcd.print("ON ");
      sound = ON;
      return sound;
   
    }
    if(joyYSD < joyLeftThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("RIGHT");
      joyStkSound();
      lcd.setCursor(0, 1);
      lcd.print("OFF");
      sound = OFF;
      return sound;
    
    }
    
     if(joyLeftThreshold <= joyYSD && joyYSD <= joyRightThreshold) {
       joyIsNeutral = true; 
       lcd.setCursor(0, 1);
       if(sound == OFF)
       lcd.print("OFF");
       else
       lcd.print("ON ");
       return sound;
     
  }
}


int joyStickDif(int activeDifficulty){ 
     
     joyYD = analogRead(joyYPin);

   if(joyYD > joyRightThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("LEFT");
      joyStkSound();
      lcd.setCursor(0, 1);
      lcd.print(activeDifficulty);
      if(activeDifficulty > minDifficulty)
      activeDifficulty--;
      return activeDifficulty;
   
    }
    if(joyYD < joyLeftThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("RIGHT");
      joyStkSound();
      lcd.setCursor(0, 1);
      lcd.print(activeDifficulty);

      if(activeDifficulty < maxDifficulty)
      activeDifficulty++;

      return activeDifficulty;
    
    }
    
     if(joyLeftThreshold <= joyYD && joyYD <= joyRightThreshold) {
       joyIsNeutral = true; 
       lcd.setCursor(0, 1);
       lcd.print(activeDifficulty);
       return activeDifficulty;
     
  }
}

int joyStickBright(int matrixBrightness){ 
     
     joyYB = analogRead(joyYPin);

   if(joyYB > joyRightThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("LEFT");
      joyStkSound();
      lcd.setCursor(0, 1);
      if(matrixBrightness < 10)
      lcd.print(" ");
      lcd.print(matrixBrightness);
      if(matrixBrightness >= 2)
      matrixBrightness = matrixBrightness - 2 ;
      return matrixBrightness;
   
    }
    if(joyYB < joyLeftThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("RIGHT");
      joyStkSound();
      lcd.setCursor(0, 1);
      if(matrixBrightness < 10)
      lcd.print(" ");
      lcd.print(matrixBrightness);
      if(matrixBrightness <= 13)
      matrixBrightness = matrixBrightness + 2;
      return matrixBrightness;
    
    }
    
     if(joyLeftThreshold <= joyYB && joyYB <= joyRightThreshold) {
       joyIsNeutral = true; 
       lcd.setCursor(0, 1);
       if(matrixBrightness < 10)
       lcd.print(" ");
       lcd.print(matrixBrightness);
       return matrixBrightness;
     
  }
}

int joyStickScroll(int start){ 
     
     joyGY1 = analogRead(joyYPin);

   if(joyGY1 > joyRightThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("LEFT");
      joyStkSound();
      if(start <=  (lenMsg - 16 - 11))
      start=start + 11;
      return start;
   
    }
    if(joyGY1 < joyLeftThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      if(start>=11)
     {start = start - 11;}
      Serial.println("RIGHT");
      joyStkSound();
      return start;
    
    }
    
     if(joyLeftThreshold <= joyGY1 && joyGY1 <= joyRightThreshold) {
       joyIsNeutral = true; 
       return start;
     
  }
}

int joyStickScroll2(int start2){ 
     
     joyGY2 = analogRead(joyYPin);

   if(joyGY2 > joyRightThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("LEFT");
      joyStkSound();
      if(start2 <= lenMsg3 - 16 - 11)
      start2 = start2 + 11;
      return start2;

    }
    if(joyGY2 < joyLeftThreshold && joyIsNeutral) { 
      joyIsNeutral = false;
      Serial.println("RIGHT");
      joyStkSound();
      if(start2 >= 11 )
      start2 = start2 - 11;
      return start2;
    }
    
     if(joyLeftThreshold <= joyGY2 && joyGY2 <= joyRightThreshold) {
       joyIsNeutral = true; 
       return start2;
     
  }
}

void joyStkSound()
{ 
  if(sound == 1)
  tone(buzzerPin, NOTE_G3, 10);
  else
  noTone(buzzerPin);
  
}

int writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.update(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.update(addrOffset + 1 + i, strToWrite[i]);
  }
  return addrOffset + 1 + len;
}

int readStringFromEEPROM(int addrOffset, String *strToRead)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0'; 
  *strToRead = String(data);
  return addrOffset + 1 + newStrLen;
}







