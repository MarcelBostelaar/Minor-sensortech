/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"                      // Include simple tools
#include "abdrive.h"

// 1 tick = 0.325 cm
// ticks = distance / 0.325

int main()                                    // Main function
{
  // Add startup code here.
  int distance = 23; 

  int ticks = distance / 0.325;
    
  pause(5000);
  
  drive_goto(ticks, ticks);
  
  pause(200);
  
  int ticks_neg = -ticks;
    
  drive_goto(ticks_neg, ticks_neg); 
}
