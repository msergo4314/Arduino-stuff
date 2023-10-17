#include <LiquidCrystal.h> // LCD display
#include <dht_nonblocking.h> // for DHT sensor
#define DHT_SENSOR_TYPE DHT_TYPE_11

//int tempPin = 0;
static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

//                BS E  D4 D5  D6  D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup() {
  lcd.begin(16, 2); // setup for LCD
}

static bool measure_environment( float *temperature, float *humidity ) {
  static unsigned long measurement_timestamp = millis(); // get current time

  /* Measure once every three seconds. */
  /* the sensor takes a long time to change temperature/humidity
     so large temperature and humidity changes will take a few minutes to stablilize
  */

  if(millis() - measurement_timestamp > 3000ul) // "ul" for unsigned long
  {
    if(dht_sensor.measure(temperature, humidity) == true)
    {
      measurement_timestamp = millis(); // update the timestamp
      return(true);
    }
  }

  return(false);
}

void loop() {
  //int tempReading = analogRead(tempPin);
  float tempC = 0.0;
  float tempK = 0.0;
  float humidity_percent = 0.0;
  //double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  //tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
  //tempC = tempK - 273.15;            // Convert Kelvin to Celcius
  //float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  /*  replaced
    float tempVolts = tempReading * 5.0 / 1024.0;
    float tempC = (tempVolts - 0.5) * 10.0;
    float tempF = tempC * 9.0 / 5.0 + 32.0;
  */

  if(measure_environment(&tempC, &humidity_percent)) {
    lcd.setCursor(0, 0);
    lcd.print("Temp         C  ");
    lcd.setCursor(6, 0);
    lcd.print(tempC);
    tempK = tempC + 273.15;
    lcd.setCursor(6, 1);
    lcd.print(tempK);
    lcd.print(" K");
  }
}
