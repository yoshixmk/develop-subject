#ifndef HARDWARE_MOTOR_DRIVER_H
#define HARDWARE_MOTOR_DRIVER_H

namespace Hardware
{
class MotorDriver
{
private:
	int pulse_gpio_pin;

	int cw_ccw_gpio_pin;


public:
	void output();

	void setPulse();

	void setCwCcw(int h_or_l);

};

}  // namespace Hardware
#endif
