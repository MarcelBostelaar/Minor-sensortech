#include <Verhagencomm.h>

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
  ReadTriple(&value);
  if(value.is_valid == true){
    SendStringData("Success", "Data is as following:");
    SendStringData(value.naam, value.value);
  }
}
