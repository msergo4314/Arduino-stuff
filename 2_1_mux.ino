// bytes are 0-255
const byte selA = 2; // Selection line A (bits 1 and 0 set to 1 and 0, respectively)
const byte selB = 3; // Selection line B (bits 1 and 0 set to 0, respectively)
const byte Y = 4;

void _2_1_mux(byte sel0, byte sel1, byte output);
void multiplyBy2(int a, int b);

bool en = false;

void setup() {
  pinMode(Y, OUTPUT); // output Y
  pinMode(selA, INPUT); // sel 0
  pinMode(selB, INPUT); // sel 1;
  Serial.begin(9600);

  if (en) {
    multiplyBy2(1, 2);
  }

}

void loop() {

  _2_1_mux(selA, selB, Y);

}

void _2_1_mux(byte pinA, byte pinB, byte outputPin) {

  byte myByteA = digitalRead(pinA) ? 1 : 0; // use ternary operator
  byte myByteB = digitalRead(pinB) ? 1 : 0;

  byte myString = (myByteA << 1) | myByteB;

  switch (myString) {
    case 0B00:
      digitalWrite(outputPin, LOW);
    break;
    case 0B01:
      digitalWrite(outputPin, HIGH);
    break;
    case 0B10:
      digitalWrite(outputPin, LOW);
    break;
    default:
      digitalWrite(outputPin, HIGH);
    break;
  }

  return;
}

void multiplyBy2(int numToMultiply, int numTimes) {

  byte A = numToMultiply << numTimes; // each shift is multiplying by 2

  Serial.print(numToMultiply);
  Serial.print(" multiplied by 2 ");
  Serial.print(numTimes);
  Serial.print(" times is: ");
  Serial.println(A);
  //Serial.print(A, BIN);

  return;
}