#!/usr/bin/env python

# servo.py
# 2015-05-20
# Public Domain

import time

import pigpio

SERVO = [18, 19]     # Servos connected to gpios 4, 11, 18
PW    = [1000, 1500]

pi = pigpio.pi() # Connect to local Pi.

for x in SERVO:
   pi.set_mode(x, pigpio.OUTPUT) # Set gpio as an output.

start = time.time()

while (time.time() - start) < 60: # Spin for 60 seconds.

   for x in range (len(SERVO)): # For each servo.
	  pi.set_PWM_dutycycle(SERVO[x], 128)
      pi.set_servo_pulsewidth(SERVO[x], PW[x])

for x in SERVO:
   pi.set_servo_pulsewidth(x, 0) # Switch servo pulses off.

pi.stop()