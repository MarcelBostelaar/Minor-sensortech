/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"                      // Include simple tools

int main()                                    // Main function
{
  // Add startup code here.

 int counter = 0;
 int geprest = 0;
  while(1)
  {
    int button = input(0);
    counter++;
    print("%d:%b\n", counter, button==1);
  }  
}
