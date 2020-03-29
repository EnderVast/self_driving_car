#include <Wire.h>
#include <SPI.h>  
#include "RF24.h"


RF24 radio (7, 8); 
const byte addresses[][6] = {"0"};

struct package
{
  int joyx;
  int joyy;
  int button;
};

typedef struct package Package;
Package data;

int x;
int y;
int val;
int steering_angle;
int motorA = 9;
int motorB = 10;
int motor_speed = 5;


void setup() {
Serial.begin(115200);
Wire.begin();
radio.begin();
radio.setChannel(115);
radio.setDataRate( RF24_250KBPS ) ; 
radio.setPALevel(RF24_PA_MAX);
radio.openReadingPipe(1, addresses[0]);
radio.startListening();
pinMode(motorA, OUTPUT);
pinMode(motorB, OUTPUT);
pinMode(motor_speed, OUTPUT);
}


void loop() 
{
if (radio.available()) 
  {
    while(radio.available())
    {
     radio.read(&data, sizeof(data));
    }
    x = data.joyx;
    y = data.joyy;
    val = data.button;    
//    Serial.println(x);
//    Serial.println(y);
//    Serial.println(val);
    
    steering_angle = map(x, 1, 1016, 35, 145);
    transmiti2c();
//    Serial.write(steering_angle);
    Serial.println(steering_angle);
    delay(30);
    //Serial.flush();

    if (val == 1)
    {
      analogWrite(motor_speed, 150);
      digitalWrite(motorA, HIGH);
      digitalWrite(motorB, LOW);
    }

    else if (val == 2)
    {
      analogWrite(motor_speed, 150);
      digitalWrite(motorA, LOW);
      digitalWrite(motorB, HIGH);
    }
    
    else
    {
      digitalWrite(motorA, LOW);
      digitalWrite(motorB, LOW);
    }
  }
}

void transmiti2c() {
  Wire.beginTransmission(8);
  Wire.write(steering_angle);
  Wire.endTransmission();
}
