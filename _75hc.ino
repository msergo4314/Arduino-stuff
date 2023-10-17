
// define the LED digit patterns, from 0 - 9
// 1 = LED on, 0 = LED off, in this order:
//                74HC595 pin     Q0,Q1,Q2,Q3,Q4,Q5,Q6,Q7 
//                Mapping to      a,b,c,d,e,f,g of Seven-Segment LED
byte seven_seg_digits[16] = { B11111100,  // = 0
                              B01100000,  // = 1
                              B11011010,  // = 2
                              B11110010,  // = 3
                              B01100110,  // = 4
                              B10110110,  // = 5
                              B10111110,  // = 6
                              B11100000,  // = 7
                              B11111110,  // = 8
                              B11100110,   // = 9
                              B11101110,  // = 10 (A) 
                              B00111110,  // = 11 (B)
                              B10011100,  // = 12 (C)
                              B01111010,   // = 13 (D)
                              B10011110,  // = 14 (E)
                              B10001110,  // = 15 (F)
                             };

int numberPins[4] = {
  8,
  7,
  6,
  5,
};
 
// connect to the ST_CP of 74HC595 (pin 3,latch pin)
int latchPin = 3;
// connect to the SH_CP of 74HC595 (pin 4, clock pin)
int clockPin = 4;
// connect to the DS of 74HC595 (pin 2)
int dataPin = 2;
 
byte setButton = 9;

byte resetButton = 10;

byte autoPin = 11;

byte potPin = A0;

bool isAuto = false;

float potPercent = 0.0;

void updateAutoLED() {
  switch(isAuto) {
    case true:
      digitalWrite(autoPin, HIGH);
      break;
    case false:
      digitalWrite(autoPin, LOW);
      break;
  }
  return;
}

void setup() {
  // Set latchPin, clockPin, dataPin as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(potPin, INPUT);

  for (int i = 0; i < (sizeof(numberPins) / sizeof(int)); i++) {
    pinMode(numberPins[i], INPUT_PULLUP);
  }

  pinMode(setButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);
  pinMode(autoPin, OUTPUT);
  Serial.begin(9600);
  updateAutoLED();
}
 
// display a number on the digital segment display
void sevenSegWrite(byte digit) {
  // set the latchPin to low potential, before sending data
  digitalWrite(latchPin, LOW);
     
  // the original data (bit pattern)
  shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]);  
 
  // set the latchPin to high potential, after sending data
  digitalWrite(latchPin, HIGH);
}

byte readNum() {
  byte num = 0;

  for (int i = 0; i < 4; i++) {
    if (digitalRead(numberPins[i]) == LOW) {
      num |= (1 << i);
    }
  }
  return num;
}

void findAuto() {
  bool set = digitalRead(setButton) == LOW;
  bool reset = digitalRead(resetButton) == LOW;

  if (set && !reset) {
    isAuto = true;
    Serial.println("set!");
  } else if (!set && reset) {
    isAuto = false;
    Serial.println("reset!");
  }
  updateAutoLED();
}

void loop() {     

  findAuto();

  if (isAuto) {
    // count from 0 to 15
    for (byte digit = 0; digit <= 15; digit++) {
      findAuto();
      if (!isAuto) {
        break;
      }
      potPercent = 1.0 - (float)analogRead(potPin) / 1023.0;
      sevenSegWrite(digit);
      //Serial.println(potPercent);
      delay(2000 * potPercent);   
    }
  }
  else {
    byte digit;
    digit = readNum();
    sevenSegWrite(digit);
  }
}
