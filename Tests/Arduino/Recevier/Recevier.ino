#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  //I2c
 Wire.begin();
//Virtual wire
Serial.println("Device is ready");

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 1; i < 190 ; i ++)
  {
  Wire.beginTransmission(8);
  Wire.write(i);
  Wire.endTransmission();
  Serial.println(i);
  delay(20);
  }
}
