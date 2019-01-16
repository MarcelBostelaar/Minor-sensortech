#include "Verhagencomm.h"

void HandleIntMessage(const char messagename[], void (*function)(int)){
  struct keyvaluepair value;
  ReadKeyValuePair(&value);
  if(value.is_valid == true){
    if(StringEquality(value.naam, messagename)){
      function(value.ValueAsInt());
    }
  }
}
void HandleFloatMessage(const char messagename[], void (*function)(float)){
  struct keyvaluepair value;
  ReadKeyValuePair(&value);
  if(value.is_valid == true){
    if(StringEquality(value.naam, messagename)){
      function(value.ValueAsFloat());
    }
  }
}
void HandleBoolMessage(const char messagename[], void (*function)(bool)){
  struct keyvaluepair value;
  ReadKeyValuePair(&value);
  if(value.is_valid == true){
    if(StringEquality(value.naam, messagename)){
      SendStringData("DebugMessage:", "Valid naam");
      function(value.ValueAsBool());
    }
  }
}
void HandleStringMessage(const char messagename[], void (*function)(char[])){
  struct keyvaluepair value;
  ReadKeyValuePair(&value);
  if(value.is_valid == true){
    if(StringEquality(value.naam, messagename)){
      function(value.value);
    }
  }
}
