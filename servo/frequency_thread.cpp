#include <iostream>
#include <wiringPi.h>
#include <thread>
#include <exception>

void do_worker1 () {
        pinMode(18, PWM_OUTPUT);
		pwmSetMode(PWM_MODE_MS);
		pwmSetClock(64);
		pwmSetRange(100);
		pwmWrite(18, 50);
}
void do_worker2 () {
        pinMode(19, PWM_OUTPUT);
		pwmSetMode(PWM_MODE_MS);
		pwmSetClock(128);
		pwmSetRange(100);
		pwmWrite(19, 50);
}

int main()
{
  if (wiringPiSetupGpio() == -1) {
    std::cout << "cannot setup gpio." << std::endl;
    return 1;
  }

  try {
	std::thread t1(do_worker1);
	std::thread t2(do_worker2);
	t1.join();
	t2.join();
  } catch (std::exception &ex) {
	std::cerr << ex.what() << std::endl;
  }

  return 0;
}
