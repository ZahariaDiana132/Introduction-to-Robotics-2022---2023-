//potentiometrele
const int redControlPin = A5;
int rControlValue = 0;
const int greenControlPin = A3;
int gControlValue = 0;
const int blueControlPin = A0;
int bControlValue = 0;
//RGB led
const int redLedPin = 5;
int rLedValue = 0;
const int greenLedPin = 6;
int gLedValue = 0;
const int blueLedPin = 9;
int bLedValue = 0;
//max, min constante valori potentiometru si led

const int maxControlValue=1023;
const int minControlValue=0;
const int maxLedValue=255;
const int minLedValue=0;

void setup() {
  pinMode(redControlPin, INPUT);
  pinMode(greenControlPin, INPUT);
  pinMode(blueControlPin, INPUT);

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  rControlValue = rgbRead(rControlValue, redControlPin);
  gControlValue = rgbRead(gControlValue, greenControlPin);
  bControlValue = rgbRead(bControlValue, blueControlPin);
  rLedValue = rgbMap(rControlValue, redControlPin);
  gLedValue = rgbMap(gControlValue, greenControlPin);
  bLedValue = rgbMap(bControlValue, blueControlPin);
  rgbWrite(rLedValue, redControlPin, redLedPin);
  rgbWrite(gLedValue, greenControlPin, greenLedPin);
  rgbWrite(bLedValue, blueControlPin, blueLedPin);
}

int rgbRead(int readControlValue, int controlPin) {
   readControlValue = analogRead(controlPin);
   return readControlValue;
   //Serial.println(controlValue);
}

int rgbMap(int mapControlValue, int controlPin) {
   mapControlValue = map(mapControlValue, minControlValue, maxControlValue, minLedValue, maxLedValue);
   return mapControlValue;
}
 
void rgbWrite(int controlValue, int controlPin, int ledPin) {
   analogWrite(ledPin, controlValue);
}
