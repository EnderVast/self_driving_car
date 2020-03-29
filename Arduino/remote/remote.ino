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

int forward = 2;
int joyx;
int joyy;
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

if(digitalRead(forward) == HIGH)
{
  val = 1;
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
