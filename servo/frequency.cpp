#include <iostream>
#include <wiringPi.h>

int main()
{
  if (wiringPiSetupGpio() == -1) {
    std::cout << "cannot setup gpio." << std::endl;
    return 1;
  }

  pinMode(18, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(64);
  pwmSetRange(100);
  pwmWrite(18, 50);

  return 0;
}
