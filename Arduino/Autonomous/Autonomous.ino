
#include <Servo.h>
#include <Wire.h> 

Servo steer;
String steering_angle;
float steering_angle1;
float steering_angle2;
float steering_angle3;
int steering_angle4;
int steer_angle;
int motorA = 9;
int motorB = 10;
int motor_speed = 5;
//LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
steer.attach(3);
steer.write(90);
delay(5000);
//lcd.init();
//lcd.backlight();
//lcd.setCursor(0, 0); // Set the cursor on the first column and first row.
pinMode(motorA, OUTPUT);
pinMode(motorB, OUTPUT);
pinMode(motor_speed, OUTPUT);
}

void loop() {  
if (Serial.available() > 0) {
  analogWrite(motor_speed, 130);
  digitalWrite(motorA, HIGH);
  digitalWrite(motorB, LOW);
  steering_angle = Serial.readStringUntil('\n');
  steering_angle1 = steering_angle.toFloat();
  steering_angle2 = steering_angle1/10000;
  steering_angle3 = steering_angle2 * (57.29578);
  steering_angle4 = (int) steering_angle3;
  if (steering_angle4 < 0){
    steer_angle = 90 + steering_angle4;
    steer.write(steer_angle);
  }
  else if (steering_angle4 > 0) {
    steer_angle = 90 + steering_angle4;
    steer.write(steer_angle);
  }
  else if (steering_angle == 0) {
    steer.write(90);
  }
  //lcd.print(steer_angle);
  delay(20);
  //lcd.clear();
}
else {
    Serial.read();
    digitalWrite(motorA, HIGH);
    digitalWrite(motorB, LOW);
    delay(20);
}
}
