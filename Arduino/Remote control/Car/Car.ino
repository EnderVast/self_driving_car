#define MOTOR_A 9
#define MOTOR_B 10
#define MOTOR_SPEED 5
#define SERVO_PIN 3

#include <SPI.h>
#include "RF24.h"
#include <Servo.h>

Servo steer;
RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};
int steering_angle = 0;

typedef struct package
{
  int joy_x;
  int joy_y;
  int pot;
  int button;
  bool top_button;
  int connection;
} package;

package data;

void setup() {
  Serial.begin(115200);
  steer.attach(SERVO_PIN);
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();

  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);
  pinMode(MOTOR_SPEED, OUTPUT);
}

void loop() {
  while (myRadio.available())
  {
    myRadio.read(&data, sizeof(data));
  }
  if (data.connection == 3)
  {
    checkSignal();
  }

  movement();
  Serial.write(steering_angle);
}

void movement()
{
  if (data.button == 2)  //forward
  {
    analogWrite(MOTOR_SPEED, 150);
    digitalWrite(MOTOR_A, HIGH);
    digitalWrite(MOTOR_B, LOW);
  }

  else if (data.button == 4) //reverse
  {
    analogWrite(MOTOR_SPEED, 150);
    digitalWrite(MOTOR_A, LOW);
    digitalWrite(MOTOR_B, HIGH);
  }
  
  else
  {
    digitalWrite(MOTOR_A, LOW);
    digitalWrite(MOTOR_B, LOW);
  }

  steering_angle = map(data.joy_x, 1, 1016, 35, 145);
  steer.write(steering_angle);
  //Serial.println(steering_angle);
  
//  Serial.println(data.joy_x);
//  Serial.println(data.joy_y);
//  Serial.println(data.pot);
//  Serial.println(data.button);
//  Serial.println(data.top_button);
}

void checkSignal()
{
  unsigned long currentTime = millis();
  unsigned long duration = currentTime + 100;
  myRadio.stopListening();
  myRadio.openWritingPipe(addresses[0]);
  while(currentTime < duration)
  {
    data.connection = 1;
    myRadio.write(&data, sizeof(data));
    currentTime = millis();
  }
  myRadio.startListening();
  myRadio.openReadingPipe(1, addresses[0]);
}
