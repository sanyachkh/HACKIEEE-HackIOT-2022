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
    if (tempF > 88) {
      rickroll();
    }
    else if (tempF > 81) {
      beep(1000, 200);
      delay(1000);
      beep(1000, 250);
    }
    else if (tempF > 79) {
      beep(1000, 200);
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

void rickroll() {
  int note = 800;
  int g4 = 98;
  int a4 = 110;
  float b5 = 123.47;
  float c5 = 130.81;
  float e5 = 164.81;
  float d5 = 146.83;
  beep((note*1.00/16), g4);
  delay(100);
  beep(note*1.00/16, a4);
  delay(100);
  beep(note*1.00/16, c5);
  delay(100);
  beep(note*1.00/16, a4);
  delay(100);
  beep(note*3.00/8, e5);
  delay(100);
  beep(note*3.00/8, e5);
  delay(100);
  beep(note*3.00/8, d5);
  delay(100);
  beep(note*3.00/8, d5);
  delay(100);
  beep(note*1.00/16, g4);
  delay(100);
  beep(note*1.00/16, a4);
  delay(100);
  beep(note*1.00/16, c5);
  delay(100);
  beep(note*1.00/16, a4);
  delay(100);
  beep(note*3.00/16, d5);
  delay(100);
  beep(note*3.00/16, d5);
  delay(100);
  beep(note*3.00/16, d5);
  delay(100);
  beep(note*3.00/16, c5);
  delay(100);
  beep(note*1.00/16, b5);
  delay(100);
  beep(note*2.00/16, a4);
  delay(100);
}

/*void gps()
{
  while (ss.available() > 0){
  Serial.write(ss.read());
  }
}*/
