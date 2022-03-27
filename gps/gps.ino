/*file for gps input to inform users, officials, of
 * where the areas with fire inducing conditions,
 * or fires, are
 */
#include <SoftwareSerial.h>
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
//static const GPSBaud is set Baud constant for the hardware itself

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);
void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
}
void loop()
{
  // Output raw GPS data to the serial monitor
  while (ss.available() > 0){
    Serial.write(ss.read());
  }
}
//hi
