#include "string.h"
const int stringarraysize = 50;
const int messagereceivedelay = 1000;

const char TransmissionBeginCharacter = '['; //1;
const char TransmissionEndCharacter = ']'; //2;
const char UnitStartCharacter = '('; //3;
const char UnitEndCharacter = ')'; //4;

struct keyvaluepair{
  bool is_valid;
  char naam[stringarraysize];
  char value[stringarraysize];
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SendStringData("String", "Started");
  
  SendStringData("String", "Data");
  SendFloatData("Float", 1.5677);
  SendBoolData("Bool", true);
  SendIntData("Int", 5000);
}

void loop() {
  
  struct keyvaluepair value;
  ReadKeyValuePair(&value);
  //SendBoolData("DebugMessage: is_valid waarde", value.is_valid);
  if(value.is_valid == true){
    SendStringData("Success", "Data is as following:");
    SendStringData(value.naam, value.value);
  }
//  while(Serial.available() > 0){
//    Serial.write(Serial.read());
//  }
}

//receiving

void ReadKeyValuePair(struct keyvaluepair *fill_in){
  char** readvalues = ReadFullTransmission(2);
  if(readvalues == 0){
    //SendStringData("DebugMessage", "readvalues zijn null");
    fill_in->is_valid = false;
    //SendBoolData("DebugMessage: is_valid waarde", fill_in->is_valid);
    return;
  }
  memcpy(fill_in->naam, readvalues[0], stringarraysize);
  memcpy(fill_in->value, readvalues[1], stringarraysize);
  fill_in->is_valid = true;
  delete readvalues[0];
  delete readvalues[1];
  delete readvalues;
}

//returns a pointer to an array of char array pointers. Returns null if an error occurred during reading (ie too many datapacks).
char** ReadFullTransmission(int count){
  //SendIntData("DebugMessage: aantal chars available", Serial.available());
  while(Serial.peek() != TransmissionBeginCharacter && Serial.available() > 0){
    Serial.read();
    }
  if(Serial.available() <= 0){
    //SendStringData("DebugMessage", "Kan geen data lezen, geen chars available");
    return 0;
  }
  Serial.read(); //read transmissiobegincharacter
  delay(messagereceivedelay); //wait for full message to be transmitted
//  SendIntData("DebugMessage: aantal chars available", Serial.available());
  char** readvalues = new char*[stringarraysize]{0};
  for(int i =0; i < count; i++){
    while(Serial.peek() != UnitStartCharacter && Serial.peek() != TransmissionEndCharacter && Serial.available() > 0){
//      SendStringData("DebugMessage", "Sla  karakter over omdat het geen unitstart of transmission end karaker is");
      Serial.read();
    }
    if(Serial.peek() == UnitStartCharacter){
      readvalues[i] = ReadValue();
      //SendStringData("DebugMessage: gelezenwaarde", readvalues[i]);
    }
  }
  bool DataIntact = true;
  for(int i = 0; i < count; i++){
    if(readvalues[i] == 0){
      DataIntact = false;
    }
  }
  if(Serial.read() == TransmissionEndCharacter && DataIntact){
    return readvalues;
  }
  SendStringData("DebugMessage", "Data niet intact, cleaning up");
  for(int i = 0; i < count; i++){
    if(readvalues[i] == 0){
      delete readvalues[i];
    }
  }
  delete readvalues;
  return 0;
}

//returns a pointer to heap allocated char array. Returns zero/null pointer when no valid data could be read. Null pointer is cleaned up.
char* ReadValue(){
  if(Serial.peek() != UnitStartCharacter){
    //SendCharData("DebugMessage: Eerste character is niet het unitstartcharacter, maar", Serial.peek());
    return 0;
    }
  Serial.read();
  char *string = new char[stringarraysize]{0};
  int datafound = Serial.readBytesUntil(UnitEndCharacter, string, stringarraysize);
  //SendIntData("DebugMessage: Gelezen characters", datafound);
  //SendCharData("DebugMessage: Volgende character", Serial.peek());
  if(datafound == stringarraysize){
    delete string;
    return 0;
  }
  if(datafound == 0){
    delete string;
    return 0;
  }
  //Serial.read();
  return string;
}

//sending

void SendIntData(const char value_name[], int value){
  StartTransmission();
  SendString(value_name);
  SendInt(value);
  EndTransmission();
}
void SendCharData(const char value_name[], char value){
  StartTransmission();
  SendString(value_name);
  SendChar(value);
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

void SendChar(char value){
  char string[stringarraysize] = {0};
  sprintf(string, "%c", value);
  SendString(string);
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
