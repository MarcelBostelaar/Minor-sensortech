/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"

#include "stdbool.h"
#include "ping.h"   
#include "time.h"                   // Include simple tools

int main()                                    // Main function
{
  // Add startup code here.

  int clock_t = clock();
  int counter = 0;
  
  while(counter < 1000)
  {
    int cmDist = ping_cm(10);
    counter++;
    print("%d:%d\n", counter, cmDist);
  }
  int end = clock();
  print("%d",( (float)(end-clock_t)) / CLOCKS_PER_SEC);
}
