#include "simpletools.h" 
#include "abdrive.h"          
#include "ping.h"             

const float mmPerTick = 3.25f;
const float WidthRobot = 105.8f;
const float ticksperdegree = 2.0f*PI*105.8f / 3.25f / 360.0f / 2.0f;

void TurnDegrees(int degrees){
  int ticks = CalculateTicks(degrees);
  drive_goto(ticks, -ticks);
}

void TurnTicks(int ticks){
  drive_goto(ticks, -ticks);
} 

int CalculateTicks(int degrees){
  return ticksperdegree * degrees;
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
  sleep(5);
 
  while(1)
  {
<<<<<<< HEAD:Radar.c
    sleep(5);
    int lowestvalueindex = 5;//-1;
    int lowestvalue = 500; //1km
    
    for(int intervalcounter = 0; intervalcounter < intervalamount; intervalcounter++){
=======
    int turn_in_ticks = CalculateTicks(degreeInterval);
    int lowestvalueindex = -1;//-1;
    int lowestvalue = 100000; //1km
    
    for(int intervalcounter = 0; intervalcounter < intervalamount; intervalcounter++){
      
>>>>>>> f61c1f70f4aaa22cae9ece34d130c216da27a306:Opdrachten/7/Radar.c
      int measuredvalue = ping_cm(pingpin);
      if(measuredvalue < lowestvalue){
        lowestvalue = measuredvalue; // Distance to object D
        lowestvalueindex = intervalcounter; //closest value angle interval, Rl = this * degreeinterval
      }
<<<<<<< HEAD:Radar.c
      TurnDegrees(degreeInterval); //turn interval degrees
    }
    //turning back in equal steps to found value
    for(int i = 0; i < (intervalamount - lowestvalueindex - 1); i++){
      TurnDegrees(-degreeInterval);
=======
      TurnTicks(turn_in_ticks); //turn interval degrees
>>>>>>> f61c1f70f4aaa22cae9ece34d130c216da27a306:Opdrachten/7/Radar.c
    }
    TurnTicks(-turn_in_ticks * (intervalamount - lowestvalueindex - 1));//turning back
    DriveCM(lowestvalue + PushdistanceCM); //drive to object D+PushdistanceCM
    DriveCM(-(lowestvalue + PushdistanceCM)); //drive back -(D+PushdistanceCM)
    TurnTicks(-turn_in_ticks * lowestvalueindex); //turn back to zero
  }  
}