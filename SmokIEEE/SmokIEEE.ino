/*
 * Temperature & Humidity Sensor integration was coded in reference to ArduinoGetStarted.com
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-temperature-humidity-sensor
 */

#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
const int buttonPin = 7;
const int buzzerPin = 8;
int counter = 0;

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
// The serial connection to the GPS device

DHT dht(DHTPIN, DHTTYPE);


void setup() 
{
  Serial.begin(9600);
  //gps program will not parse into SmokeIEEE
  dht.begin(); // initialize the sensor
  pinMode(buttonPin, INPUT_PULLUP);
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

  // read button state
  int buttonState = digitalRead(buttonPin);

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

    if (tempF>=78 && tempF<=80)
    {
      counter++;
      if (counter%2==1)
      {
      beep (25, 1050);
      }
      if (counter%2==0)
      {
      beep (25, 1100);
      }

      // if button is pressed -> delay for a bit
      if (buttonState != HIGH) {
        Serial.println("button pressed");
        noTone(buzzerPin);
        delay(2000);
      }
    }
    
    // Buzz if temperature exceeds 80, once past 85 rickroll
    else if (tempF > 80) {
      if (tempF<85)
      {
        beep(1000, 5000);
      }
      else {
        rickroll();
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
}
