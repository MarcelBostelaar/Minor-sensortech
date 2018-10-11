#include "simpletools.h" 
#include "abdrive.h"          
#include "ping.h"             

const float mmPerTick = 3.25f;
const float WidthRobot = 105.8f;
const float ticksperdegree = 2.0f*PI*105.8f / 3.25f / 360.0f / 2.0f;

void TurnDegrees(int degrees){
  int ticks = ticksperdegree * degrees;
  drive_goto(ticks, -ticks);
}


void DriveCM(int distance){
  int ticks = distance* 10 / mmPerTick;
  drive_goto(ticks, ticks);
}

const int degreeInterval = 4;
const int TotalDegreeView = 120;
const int pingpin = 10;
const int PushdistanceCM = 5;
int main()                                 
{
  int intervalamount = TotalDegreeView / degreeInterval;
 
  while(1)
  {
    sleep(5);
    int lowestvalueindex = 5;//-1;
    int lowestvalue = 5; //1km
    
    for(int intervalcounter = 0; intervalcounter < intervalamount; intervalcounter++){
      /*
      int measuredvalue = ping_cm(pingpin);
      if(measuredvalue < lowestvalue){
        lowestvalue = measuredvalue; // Distance to object D
        lowestvalueindex = intervalcounter; //closest value angle interval, Rl = this * degreeinterval
      }*/
      TurnDegrees(degreeInterval); //turn interval degrees
    }
    //turning back in equal steps to found value
    for(int i = 0; i < intervalamount - lowestvalueindex - 1; i++){
      TurnDegrees(-degreeInterval);
    }
    DriveCM(lowestvalue + PushdistanceCM); //drive to object D+PushdistanceCM
    DriveCM(-(lowestvalue + PushdistanceCM)); //drive back -(D+PushdistanceCM)
    
    //turn back to zero
    for(int i = 0; i < lowestvalueindex; i++){
      TurnDegrees(-degreeInterval);
    }
  }  
}