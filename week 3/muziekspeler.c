/*
  SD Minimal.side

  Create test.txt, write characters in, read back out, display. 
  
  http://learn.parallax.com/propeller-c-simple-devices/sd-card-data
*/

#include "simpletools.h"#include "time.h"

int DO = 22, CLK = 23, DI = 24, CS = 25;
int buffersize = 5000;
int main(void) {
  sd_mount(DO, CLK, DI, CS);

  char buffer[buffersize];

  FILE * fp = fopen("tripol", "r");
  if (fp == 0) {
    print("Error opening file\n");
  } else {
    print("Opened file\n");
    size_t readbytes = fread(buffer, 1, buffersize, fp);
    printf("Read buffer %i bytes long\n", readbytes);
    fclose(fp);
    print("Closed file\n");
    print("%s\n", buffer);
    int i = 0xffffffffffffffff;
    printf("%x\n", i);
    printf("%i\n", 666);
    int framerate = parsebytestoint(buffer);
    int lenght = parsebytestoint(buffer + 4);
    print("Parsed Buffer\n");
    printf("framerate: %i\n", framerate);
    printf("lenght: %i\n", lenght);

    int sleepinterval = 1000000 / framerate;
    fp += 8; //set filepointer to start data
    printf("Lenght: %i", lenght);
    printf("Sleepinterval: %i", sleepinterval);
    while (lenght > 0) {
      int locallenght = buffersize < lenght ? buffersize : lenght;
      //printf("locallenght: %i", locallenght);
      fread(buffer, 1, locallenght, fp);
      fp += locallenght;
      for (int z = 0; z < locallenght; z++) {
        usleep(sleepinterval);
        buffer[z] ? high(4) : low(4);
      }
      lenght -= locallenght;
      print("cycle\n");
    }
    print("Finished");
  }
}
/*
int main(void)                                
{
  sd_mount(DO, CLK, DI, CS);                  

  char buffer[1000];

  FILE* fp = fopen("test.txt", "r");
  print("Opened file\n");
  fread(buffer, 1, 5, fp);
  print("Read buffer\n");
  fclose(fp);
  print("Closed file\n");
  print("%s\n", buffer);
  int i = 0xffffffffffffffff;
  printf("%x", i);
}  */

int parsebytestoint(char bytes[]) {
  int answer = 0;
  answer += bytes[0];
  answer = answer << 8;
  answer += bytes[1];
  answer = answer << 8;
  answer += bytes[2];
  answer = answer << 8;
  answer += bytes[3];
  return answer;
}