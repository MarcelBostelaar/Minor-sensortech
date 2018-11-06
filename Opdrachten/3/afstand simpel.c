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
  //speedtest();
  blockcheck();
}

void blockcheck(){
  int checkbuffer = 1000;
  int counter = 0;
  print("Hand ervoor\n");
  pause(2000);
  print("Hand weg\n");
  pause(2000);
  while(counter < checkbuffer){
    print("%d:", ping_cm(10));
    counter++;
    }
    print("\nKlaar met printen");
  }

void speedtest(){
  int cycles = 1000;
  int counter = 0;
  int buttonvalue = 0;
  int pressed = 0;
  int lastvalue = 0;
  //int numberoftimespressed = 0;
  int starttime = clock();
  while(counter < cycles)
  {
    buttonvalue = ping_cm(10);
    counter++;
    //pressed += buttonvalue;
    //if(lastvalue-buttonvalue == -1){
    //  numberoftimespressed++;
    //  }
      
    //print("%d", buttonvalue);
  }
  int endtime = clock();
  float elapsedtime = (float)(endtime - starttime)/(float)CLOCKS_PER_SEC;
  print("%f\n", elapsedtime);
  print("gemeten: %d\n", counter);
  float frequentie = ((float)cycles / elapsedtime);
  print("Frequentie: %f\n", frequentie);
  print("Gemeten afstand: %d", ping_cm(10));
  }