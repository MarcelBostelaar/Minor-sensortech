#define Verhagencomm_h

#include "Arduino.h"
#include "Verhagencomm.h"

int messagereceivedelay = 1000;

const char TransmissionBeginCharacter = '['; //1;
const char TransmissionEndCharacter = ']'; //2;
const char UnitStartCharacter = '('; //3;
const char UnitEndCharacter = ')'; //4; 



//sending
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
void SendString(const char value[]){
  StartValue();
  SendRawString(value);
  EndValue();
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

bool CharEquality(char a[], char b[], int length){
  for(int i = 0; i < length; i++){
    if(a[i] != b[i]){
      return false;
    }
  }
  return true;
}

bool StringEquality(char a[], char b[]){
  return CharEquality(a, b, stringarraysize);
}

int GetCommon(char a[], char b[], char c[]){
  if(StringEquality(a,b)){
    return 1;
  }
  if(StringEquality(a,c)){
    return 1;
  }
  if(StringEquality(b,c)){
    return 2;
  }
  return 0;
}

void ReadTriple(struct keyvaluepair *fill_in){
  fill_in->is_valid = false;
  if(Serial.available() <= 0){
    return;
  }
  struct keyvaluepair readvalues[3];
  ReadKeyValuePair(&readvalues[0]);
  ReadKeyValuePair(&readvalues[1]);
  ReadKeyValuePair(&readvalues[2]);
  int name = GetCommon(readvalues[1].naam, readvalues[1].naam, readvalues[2].naam);
  int value = GetCommon(readvalues[1].value,  readvalues[1].value, readvalues[2].value);
  
  if(name == 0 || value == 0){
    return;
  }
  fill_in->is_valid = true;
  memcpy(fill_in->naam, readvalues[name-1].naam, stringarraysize);
  memcpy(fill_in->value, readvalues[value-1].value, stringarraysize);
}