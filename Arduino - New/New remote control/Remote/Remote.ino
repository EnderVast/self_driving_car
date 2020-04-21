#define BUTTON_UP 2
#define BUTTON_LEFT 3
#define BUTTON_DOWN 4
#define BUTTON_RIGHT 5
#define BUTTON_TOP 9
#define JOY_X A6
#define JOY_Y A7
#define POT A2
#define LED 6

#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};

typedef struct package
{
  int joy_x = 0;
  int joy_y = 0;
  int pot = 0;
  int button = 0;
  bool top_button = false;
  int connection = 0;   //signal status -> 1: good, 2: no signal, 3: request status
}package;

package data;

void setup() {  
  //Stating buttons are inputs
  for (int i = 2; i < 6; i++)
  {
    pinMode(i, INPUT);
  }
  pinMode(BUTTON_TOP, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(A3, INPUT);

  Serial.begin(9600);

  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe(addresses[0]);
}

void loop() {
  checkSignal();
  inputs();
  myRadio.write(&data, sizeof(data));  
}

void checkSignal()
{
  int counter = 0;
  data.connection = 3;
  myRadio.write(&data, sizeof(data));
  unsigned long currentTime = millis();
  unsigned long duration = currentTime + 200;
  while(currentTime < duration)  //wait for reply for 0.4 seconds
  {
    if (counter == 0) //switch to listening mode once
    {
      myRadio.openReadingPipe(1, addresses[0]);
      myRadio.startListening();
      counter++;
    } 
    myRadio.read(&data, sizeof(data));
    if (data.connection == 1)
    {
      signalStatus(true);
      Serial.println("good");
    }
    else 
    {
      signalStatus(false);
      Serial.println("bad");
    }
    currentTime = millis()/1000;
  }
  myRadio.stopListening();
  myRadio.openWritingPipe(addresses[0]);
}

void signalStatus(bool goodConnect)
{
  if (goodConnect == true)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    unsigned long timer = millis()/1000;
    int duration = timer + 0.5;
    if (timer > duration)
    {
      digitalWrite(LED, HIGH);
      timer = millis()/1000;
    }
    if (timer > duration)
    {
      digitalWrite(LED, LOW);
      timer = millis()/1000;
    }
  }
}

void inputs()
{
  //Reading which button is being pressed
  if (digitalRead(BUTTON_UP))
  {
    data.button = 2;
  }
  else if (digitalRead(BUTTON_LEFT))
  {
    data.button = 3;
  }
  else if (digitalRead(BUTTON_DOWN))
  {
    data.button = 4;
  }
  else if (digitalRead(BUTTON_RIGHT))
  {
    data.button = 5;
  }
  else
  {
    data.button = 0;
  }
  if (digitalRead(BUTTON_TOP))
  {
    data.top_button = true;
  }
  else
  {
    data.top_button = false;
  }
  
  data.joy_x = analogRead(JOY_X);
  data.joy_y = analogRead(JOY_Y);
  data.pot = analogRead(POT);
}
