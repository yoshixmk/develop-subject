#!/usr/bin/env python

# servo.py
# 2015-05-20
# Public Domain

import time

import pigpio

SERVO = [18, 19]     # Servos connected to gpios 4, 11, 18
FREQ    = [1500, 3000]

pi = pigpio.pi() # Connect to local Pi.

for x in SERVO:
   pi.set_mode(x, pigpio.OUTPUT) # Set gpio as an output.

start = time.time()

for x in range (len(SERVO)): # For each servo.
   pi.set_PWM_dutycycle(SERVO[x], 128)
   pi.set_PWM_frequency(SERVO[x], FREQ[x])

while True: # Spin for 60 seconds.
   print "ok"

pi.stop()