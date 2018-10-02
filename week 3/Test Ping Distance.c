/*
  Test Ping Distance.c
  
  Measure and display Ping))) Ultrasonic Distance Sensor distance measurements.
  
  http://learn.parallax.com/propeller-c-simple-devices/sense-distance-ping
*/

#include "simpletools.h"                      // Include simpletools header
#include "ping.h"                             // Include ping header

int main()                                    // main function
{
  while(2)                                    // Repeat indefinitely
  {
    int cmDist = ping_cm(8);                 // Get cm distance from Ping)))
    if (cmDist < 20){
      print("zo dichtbij!\t");
    } else {
      print("prima afstand!\t");
    }
    print("%d\n", cmDist);
    pause(200);                               
  }
}

