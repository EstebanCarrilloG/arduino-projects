#include "HandleLed.h"
HandleLed led1(12, 5);
HandleLed led2(13, 0);

void setup()
{
}
void loop()
{
  led1.handleLed();
  led2.handleLed();
}