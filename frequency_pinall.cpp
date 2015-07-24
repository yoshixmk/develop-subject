#include <iostream>
#include <wiringPi/wiringPi.h>

int main()
{
  if (wiringPiSetupGpio() == -1) {
    std::cout << "cannot setup gpio." << std::endl;
    return 1;
  }
  pinMode(12, PWM_OUTPUT);
  pinMode(13, PWM_OUTPUT);
  pinMode(18, PWM_OUTPUT);
  pinMode(19, PWM_OUTPUT);
  pwmSetMode(PWM_MODE_MS);
  pwmSetClock(3000);
  pwmSetRange(1024);

  while (true) {
    int num;
    std::cin >> num;

    if (num == -1) {
      break;
    }

    pwmWrite(18, num);
  }

  return 0;
}
 