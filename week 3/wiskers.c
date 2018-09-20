#include "simpletools.h" 
#include "stdbool.h"
#include "ping.h"

int main()
{
  int counter = 0;
  while(true){
    int wL = input(8); 
    print("%d:%d\n", counter, wL);
    counter++;
    pause(5);
    }
}