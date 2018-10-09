/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"                      // Include simple tools

int main()                                    // Main function
{
  // Add startup code here.

  const int duration = 3;
  const int pin = 3;
  while(1)
  {
    print("loop");
    /*for(int i = 400; i < 1000; i++){
      freqout(pin, duration, i);
      pause(duration);
      }
      pause(1000);*/
      
      
      
    /*for(int i = 1000; i > 400; i--){
      freqout(pin, duration, i);
      pause(duration);
      }*/
    const int start = 1000;
    const int loops = 5;
    const int decreasespeed = 4;
    for(int i = start*loops; i > 400; i -= decreasespeed){
      freqout(pin, duration, i%start);
      freqout(pin+1, duration, i%start + 200);
      pause(duration);
      }
      pause(1000);
  }  
}
