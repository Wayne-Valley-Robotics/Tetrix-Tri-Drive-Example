#include <Arduino.h>
#include <PRIZM.h>
#include <TELEOP.h>
PRIZM prizm;
EXPANSION exc;

// put function declarations here:
int myFunction(int, int);

void setup()
{
  // put your setup code here, to run once:
  prizm.PrizmBegin();
  int result = myFunction(2, 3);
}

void loop()
{
  // put your main code here, to run repeatedly:
  bool state = 0;
  while (!prizm.readStartButton())
  {
    state = !state;
    prizm.setGreenLED(state);
    delay(500);
  }
}

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}