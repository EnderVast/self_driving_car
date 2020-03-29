#include <Wire.h>
int data;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void receiveEvent(int bytes) {
  data = Wire.read();
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(data);
}
