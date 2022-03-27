/*
 * Temperature & Humidity Sensor integration was coded in reference to ArduinoGetStarted.com
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-temperature-humidity-sensor
 */

#include "DHT.h"
#include <SoftwareSerial.h>

#define DHTPIN 2
#define DHTTYPE DHT11
const int buzzerPin = 8;

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
// The serial connection to the GPS device

DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial ss(RXPin, TXPin);

void setup() 
{
  Serial.begin(9600);
  ss.begin(GPSBaud); //initialize the GPS
  /*while (ss.available() > 0){
    Serial.write(ss.read());
  }*/ 
  //gps program will not parse into SmokeIEEE
  dht.begin(); // initialize the sensor
  pinMode(buzzerPin, OUTPUT); // set buzzer as an output
}

void loop() 
{
  // wait a few seconds between measurements.
  delay(1000);
  
  // read humidity
  float humi  = dht.readHumidity();
  // read temperature as Celsius
  float tempC = dht.readTemperature();
  // read temperature as Fahrenheit
  float tempF = dht.readTemperature(true);

  // check if any reads failed
  if (isnan(humi) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Print out humidity and temperature in C and F
    Serial.print("Humidity: ");
    Serial.print(humi);
    Serial.print("%");

    Serial.print("  |  "); 

    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print("°C ~ ");
    Serial.print(tempF);
    Serial.println("°F");

    // Buzz if temperature exceeds 80
    if (tempF > 80) {
      while (tempF<85)
      {
        beep(1000, 5000);
      }
    }
    else {
      noTone(buzzerPin);
    }
  }
}

// Turns buzzer on at freq Hz for delay_ms
void beep(unsigned char delay_ms, unsigned char freq) {
  tone(buzzerPin, freq); // Sounds the buzzer
  delay(delay_ms); // Delay for delay
}

/*void gps()
{
  while (ss.available() > 0){
  Serial.write(ss.read());
  }
}*/
