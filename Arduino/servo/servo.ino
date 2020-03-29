#include <Wire.h>
#include <Servo.h>

Servo steerservo;
int steering_angle;
int steering_angle1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  steerservo.attach(3);
  steerservo.write(100);
  delay(1000);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void receiveEvent(int bytes) {
  steering_angle = Wire.read();
}

void loop() {
  // put your main code here, to run repeatedly:
  steering_angle1 = int(steering_angle);
  Serial.println(steering_angle1);
  steerservo.write(steering_angle1);
  delay(20);
}
