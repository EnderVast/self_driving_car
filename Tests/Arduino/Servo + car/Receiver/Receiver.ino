#include <Servo.h>

#include <SPI.h>
#include "RF24.h"

Servo myservo;
RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};

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
int pos = 0;
int steering_angle = 0;

void setup() {
  Serial.begin(9600);

  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ;
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();

  myservo.attach(3);
}

void loop() {
  steering_angle++;
  
  while (myRadio.available())
  {
    myRadio.read(&data, sizeof(data));
  }
  Serial.println(data.connection);
  if (data.connection == 3)
  {
    checkSignal();
  }

  //int steering_angle = map(data.joy_x, 1, 1016, 35, 145);
  myservo.write(steering_angle);
  delay(15);
//  Serial.println(data.joy_x);
//  Serial.println(data.joy_y);
//  Serial.println(data.pot);
//  Serial.println(data.button);
//  Serial.println(data.top_button);
  //Serial.println(data.connection);
  if (steering_angle == 180)
  {
    steering_angle = 0;
  }
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
