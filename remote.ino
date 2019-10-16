#include <SPI.h>  
#include "RF24.h"

byte addresses[6] = {"0"};

RF24 radio (7, 8);


struct package
{
  int x = 0;
  int y = 0;
  int button = 0;
};

typedef struct package Package;
Package data;

int joyswitch = 6;
int frontswitch = 9;
int joyx;
int joyy;
int up = 5;
int down = 3;
int left = 4;
int right = 2;
int val;

void setup() {
Serial.begin(9600);
  radio.begin();  
  radio.setChannel(115);
  radio.setDataRate( RF24_250KBPS ) ; 
  radio.setPALevel(RF24_PA_MAX);; ;
  radio.openWritingPipe(addresses[0]);
  delay(100);
  for(int i = 2; i < 6; i++)
  {
    pinMode(i, INPUT);
  }
  pinMode(6, INPUT_PULLUP);
  pinMode(9, INPUT);
}

void loop() {
  
joyx = analogRead(A1);
joyy = analogRead(A2);

if(digitalRead(up) == HIGH)
{
  val = 1;
}

else if(digitalRead(down) == HIGH)
{
  val = 2;   
}

else if(digitalRead(left) == HIGH)
{
  val = 3;
}

else if(digitalRead(right) == HIGH)
{
  val = 4;
}

else if(digitalRead(joyswitch) == LOW)
{
  val = 5;
}

else if(digitalRead(frontswitch) == HIGH)
{
  val = 6;
}
else
{
  val = 0;
}

transmit();

}

void transmit()
{

  Serial.println("Package:");
  Serial.println(data.x);
  Serial.println(data.y);
  Serial.println(data.button);

  data.x = joyx;
  data.y = joyy;
  data.button = val;

  radio.write(&data, sizeof(data)); 

  delay(20);
}
