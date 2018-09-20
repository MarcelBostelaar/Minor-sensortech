/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"    
#include "time.h"                     

int main()                                    
{
  speedtest();
  //blockcheck();
}

void blockcheck(){
  int checkbuffer = 1000;
  int counter = 0;
  print("Druk nu in\n");
  pause(2000);
  print("Laat nu los\n");
  pause(2000);
  while(counter < checkbuffer){
    print("%d", input(0));
    counter++;
    }
    print("\nKlaar met printen");
  }

void speedtest(){
  int cycles = 100000;
  int counter = 0;
  int buttonvalue = 0;
  int pressed = 0;
  int lastvalue = 0;
  int numberoftimespressed = 0;
  int starttime = clock();
  while(counter < cycles)
  {
    lastvalue = buttonvalue;
    buttonvalue = input(0);
    counter++;
    pressed += buttonvalue;
    if(lastvalue-buttonvalue == -1){
      numberoftimespressed++;
      }
      
    //print("%d", buttonvalue);
  }
  int endtime = clock();
  float elapsedtime = (float)(endtime - starttime)/(float)CLOCKS_PER_SEC;
  print("%f\n", elapsedtime);
  print("gemeten: %d\ngedrukt_gemeten:%d\naantal_keren_ingedrukt:%d\n", counter, pressed, numberoftimespressed);
  float frequentie = ((float)cycles / elapsedtime);
  print("Frequentie: %f", frequentie);
  }