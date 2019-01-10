#include "string.h"
const int stringarraysize = 50;

const char TransmissionBeginCharacter = '['; //1;
const char TransmissionEndCharacter = ']'; //2;
const char UnitStartCharacter = '('; //3;
const char UnitEndCharacter = ')'; //4;

struct keyvaluepair{
  char naam[stringarraysize];
  char value[stringarraysize];
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SendStringData("String", "Started");
  
  SendStringData("String", "Data");
  SendIntData("Int", 5000);
  SendFloatData("Float", 1.5677);
  SendBoolData("Bool", true);
}

void loop() {
}

//receiving

int ReadFullTransmission(){
  //array of string arrays
  while(Serial.read() != TransmissionBeginCharacter && Serial.available() > 0){}
  if(Serial.available() <= 0){
    return 0;
  }
  //while not at transmission end, do readvalue
  while(Serial.peek() != UnitStartCharacter){
    
  }
}

int ReadValue(){
  while(Serial.read() != UnitStartCharacter){}
  char *string = new char[stringarraysize];
  Serial.readBytesUntil(UnitEndCharacter, string, stringarraysize);
}

//sending

void SendIntData(const char value_name[], int value){
  StartTransmission();
  SendString(value_name);
  SendInt(value);
  EndTransmission();
}
void SendFloatData(const char value_name[], float value){
  StartTransmission();
  SendString(value_name);
  SendFloat(value);
  EndTransmission();
}
void SendBoolData(const char value_name[], bool value){
  StartTransmission();
  SendString(value_name);
  SendBool(value);
  EndTransmission();
}
void SendStringData(const char value_name[], const char value[]){
  StartTransmission();
  SendString(value_name);
  SendString(value);
  EndTransmission();
}

void SendInt(int value){
  char string[stringarraysize] = {0};
  sprintf(string, "%i", value);
  SendString(string);
}
void SendFloat(float value){
  char string[stringarraysize];
  dtostrf(value, 40, 20, string);
  SendString(string);
}
void SendBool(bool value){
  if(value){
    SendString("True");
    }
  else{
    SendString("False");
  }
}
void SendString(const char value[]){
  StartValue();
  SendRawString(value);
  EndValue();
}
void SendRawString(const char value[]){
  for (int i = 0; i < strlen(value) && value[i] != 0; i++)
  {
    Serial.write(value[i]);   // Push each char 1 by 1 on each loop pass
  }
}

void StartTransmission(){
  Serial.write(TransmissionBeginCharacter);
}
void EndTransmission(){
  Serial.write(TransmissionEndCharacter);
  SendRawString("\n");
}
void StartValue(){
  Serial.write(UnitStartCharacter);
}
void EndValue(){
  Serial.write(UnitEndCharacter);
}
