#include "drive.h"

void setup()
{
  prizm.PrizmBegin();
  Serial.begin(115200);
}

void loop()
{
  ps4.getPS4();
  updateDrive();
}