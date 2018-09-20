#include "simpletools.h" 
#include "stdbool.h"
#include "ping.h"

int main()
{
  bool dowiskers = true;

  while (true)
  {
    int burton = input(0);
    if (burton == 1) {
      dowiskers = !dowiskers;
      pause(1000);
    }
    if (dowiskers) {
      wiskers();
    } else {
      afstand();
    }
  }
}

void wiskers() {
  int wL = input(8); 
  int wR = input(6);
  if (wL == 0 && wR == 0) {
    print("frontal hit. whoops.");
  } else if (wL == 0) {
    print("you're hitting something on the left");
  } else if (wR == 0) {
    print("you're hitting something on the right");
  } else {
    print("smooth ride");
  }
  print("\n");
  pause(200);
}

void afstand() {

  int cmDist = ping_cm(10);
  if (cmDist < 20) {
    print("zo dichtbij!\t");
  } else {
    print("prima afstand!\t");
  }
  print("%d\n", cmDist);
  pause(200);

}