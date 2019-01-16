//#define Verhagencomm_h

#include "Arduino.h"
#include "Verhagencomm.h"

int messagereceivedelay = 1000;

using SendMessage = std::tuple<int,char[stringarraysize],char[stringarraysize]>;

//ListNode<SendMessage> *SendAwaitingConfirm = new ListNode<SendMessage>();

//ListNode

const char TransmissionBeginCharacter = '['; //1;
const char TransmissionEndCharacter = ']'; //2;
const char UnitStartCharacter = '('; //3;
const char UnitEndCharacter = ')'; //4; 

//LINKED LIST

template <class T>
void ListNode<T>::DeleteList(){
  if(next != 0){
    next->DeleteList();
    delete next;
  }
  delete value;
}
template <class T>
int ListNode<T>::Length(){
  if(next != 0){
    return next->Length() + 1;
  }
  return 1;
}
template <class T>
void ListNode<T>::AddValue(T *toadd){
  if(next != 0){
    next->AddValue(toadd);
  }
  else{
    next = new ListNode();
    value = toadd;
  }
}


//COMMON CODE
bool CharEquality(const char a[], const char b[], int length){
  for(int i = 0; i < length; i++){
    if(a[i] == 0 && b[i] == 0){
      return true; //end of string, rest can be garbage but string would still be equal
    }
    if(a[i] != b[i]){
      return false;
    }
  }
  return true;
}

bool StringEquality(const char a[], const char b[]){
  return CharEquality(a, b, stringarraysize);
}

//STRUCT IMPLEMENTATION

int keyvaluepair::ValueAsInt(){
  return atoi(value);
}
bool keyvaluepair::ValueAsBool(){
  if(StringEquality(value, "True")){
    return true;
  }
  return false;
}
float keyvaluepair::ValueAsFloat(){
  return atof(value);
}


//SENDING
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

//RECEIVING

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

struct ListNode<char>* ReadFullTransmissionNew(){
  while(Serial.peek() != TransmissionBeginCharacter && Serial.available() > 0){
    Serial.read();
    }
  if(Serial.available() <= 0){
    return 0;
  }
  Serial.read(); //read transmissiobegincharacter
  delay(messagereceivedelay); //wait for full message to be transmitted
  bool DataIsValid = true;
  struct ListNode<char> root = ListNode<char>(); //dummy node with no value that acts as a container object for the list;
  while(Serial.peek() != TransmissionEndCharacter && Serial.available() > 0){
    while(Serial.peek() != UnitStartCharacter && Serial.peek() != TransmissionEndCharacter && Serial.available() > 0){
      Serial.read();
    }
    if(Serial.peek() == UnitStartCharacter){
      char* readvalue = ReadValue();
      if(readvalue == 0){
        DataIsValid = false;
      }
      else{
        root.AddValue(readvalue);
      }
      delete readvalue;
    }
  }

  if(!DataIsValid){
    root.DeleteList();
    return 0;
  }
  if(Serial.read() == TransmissionEndCharacter){
    return root.next;
  }
}

void ReadKeyValuePairNew(struct keyvaluepair *fill_in){
  struct ListNode<char> *root = ReadFullTransmissionNew();
  if(root != 0){
    SendIntData("DebugMessage: received amount of elements:", root->Length());

    
    
    
    root->DeleteList();
    delete root;
  }
}

//MESSAGE RECEIVE CONTROLLER
