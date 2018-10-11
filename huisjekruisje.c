
/*
  Blank Simple Project.c
  http://learn.parallax.com/propeller-c-tutorials 
*/
#include "simpletools.h"                      // Include simple tools
#include "abdrive.h"
#include "math.h"

// 1 tick = 0.325 cm
// ticks = distance / 0.325

int main()                                    // Main function
{
  // Add startup code here.
  int dist_wall = 20;
  int dist_cross = sqrt(2*pow(dist_wall,2)); //28
  print("dist_cross: %d", dist_cross);
  int dist_roof = sqrt(2*pow(0.5 * dist_wall,2)); // 14
  print("dist_roof: %d", dist_roof);
  
  int ticks_walls = dist_wall / 0.325;
  int ticks_cross = dist_cross / 0.325;
  int ticks_roof = dist_roof / 0.325;
  drive_speed(64,64);

  pause(1000);

  drive_goto(ticks_walls, ticks_walls); // rechtdoor AB

  pause(200);
  
  drive_goto(13, -12); //dak rechtsomhoog
  drive_goto(ticks_roof, ticks_roof); // rechtdoor BC

  pause(200);

  drive_goto(26, -25); //dak 90 gr (top)
  drive_goto(ticks_roof, ticks_roof); // rechtdoor CD

  pause(200);

  drive_goto(13, -12); //dak rechtsomlaag
  drive_goto(ticks_walls, ticks_walls); // rechtdoor DE

  pause(200);
  
  drive_goto(39, -38); //draai rechtsom
  drive_goto(ticks_cross, ticks_cross); // rechtdoor EB

  pause(200);

  drive_goto(39, -38); //draai rechtsom
  drive_goto(ticks_walls, ticks_walls); // rechtdoor BD

  pause(200);

  drive_goto(39, -38); //draai rechtsom
  drive_goto(ticks_cross, ticks_cross); // rechtdoor DA
  
  drive_goto(-38, 39); //draai linksom
  drive_goto(ticks_walls, ticks_walls); // rechtdoor AE
}
