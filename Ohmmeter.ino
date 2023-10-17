int analogPin = A0;
float Vin = 5.0; // the Voltage of the Arduino's 5V pin
float knownResistance = 1E6; // the value of R1 in ohms
float Vout;
float sensorValue;
float resistance;

void setup() {
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  sensorValue = analogRead(analogPin);
  Vout = sensorValue * (Vin/1023.0); // calculate Vout
  Serial.print("Measured Vout (not in volts): ");
  Serial.println(sensorValue);
  Serial.print("true Vout after R1 (in volts): ");
  Serial.println(Vout);
  resistance = (Vout * knownResistance) / (Vin - Vout); // calculate resistance
}

void loop() {
  sensorValue = analogRead(analogPin);
  Vout = sensorValue * (Vin / 1023.0); // calculate Vout
  resistance = (Vout * knownResistance) / (Vin - Vout); // calculate resistance
  Serial.print("Resistance of unknown resistor: ");
  Serial.print(resistance);
  Serial.println(" Ohms");
  delay(1500);
}
