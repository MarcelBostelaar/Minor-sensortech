#define Verhagencomm_h

#include "Arduino.h"

const int stringarraysize = 50;

struct keyvaluepair{
  bool is_valid;
  char naam[stringarraysize];
  char value[stringarraysize];
};
void ReadTriple(struct keyvaluepair *fill_in);
void ReadKeyValuePair(struct keyvaluepair *fill_in);

void SendIntData(const char value_name[], int value);
void SendCharData(const char value_name[], char value);
void SendFloatData(const char value_name[], float value);
void SendBoolData(const char value_name[], bool value);
void SendStringData(const char value_name[], const char value[]);