const int buttonPin = 7;
const int buzzerPin = 8;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  noTone(buzzerPin);
}

void loop() {
  // put your main code here, to run repeatedly:

  int buttonState = digitalRead(buttonPin);
  
  if (buttonState != HIGH) {
    beep(1000);
  }
  else {
    noTone(buzzerPin);
  }
}

void beep(unsigned char delay_ms) { //creating function
  tone(buzzerPin, 5000); // Sounds the buzzer
  delay(delay_ms); // Delay for delay
}
