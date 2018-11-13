

#include "simpletools.h"
#include "wavplayer.h"
    
int main()                                        
{
  int DO = 22, CLK = 23, DI = 24, CS = 25;        
  sd_mount(DO, CLK, DI, CS);                     
 
  const char programmeren[] = {"prog.wav"};       
  wav_play(programmeren);                             
 
  wav_volume(5);                                  
  pause(2000);

  wav_stop(); 
  const char robot[] = {"robot.wav"};       
  wav_play(robot);                                     
 
  wav_volume(5);                                  
  pause(5000);     
  wav_stop();                             
}