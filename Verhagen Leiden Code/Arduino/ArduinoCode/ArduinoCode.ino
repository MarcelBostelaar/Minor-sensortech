#include "Verhagencomm.h"
#include "HandlingLibrary.h"

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  SendStringData("String", "Started");
  
  SendStringData("String", "Data");
  SendFloatData("Float", 1.5677);
  SendBoolData("Bool", true);
  SendIntData("Int", 5000);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  ReadKeyValuePairNew(0);
//  HandleBoolMessage("Groen", GroenLed);
//  HandleBoolMessage("Rood", RoodLed);
//  HandleBoolMessage("Blauw", BlauwLed);
  }

void GroenLed(bool state){
  if(state){
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }
}
void RoodLed(bool state){
  if(state){
    digitalWrite(11, HIGH);
  }
  else{
    digitalWrite(11, LOW);
  }
}
void BlauwLed(bool state){
  if(state){
    digitalWrite(12, HIGH);
  }
  else{
    digitalWrite(12, LOW);
  }
}
