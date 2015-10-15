# -*- coding: utf-8 -*-
import os
import time
import sys
import RPi.GPIO as GPIO
from pubnub import Pubnub

pubnub = Pubnub(publish_key='pub-c-35c23189-77f7-417a-967f-e00401cce82a', subscribe_key='sub-c-96d9098e-7064-11e5-98e8-0619f8945a4f')
channel = 'tempeon'

def callback(message):
    print(message)

#published in this fashion to comply with Eon
spi_clk  = 11
spi_mosi = 10
spi_miso = 9
spi_ss   = 8

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

GPIO.setup(spi_mosi, GPIO.OUT)
GPIO.setup(spi_miso, GPIO.IN)
GPIO.setup(spi_clk,  GPIO.OUT)
GPIO.setup(spi_ss,   GPIO.OUT)
while True:
    GPIO.output(spi_ss,   False)
    GPIO.output(spi_clk,  False)
    GPIO.output(spi_mosi, False)
    GPIO.output(spi_clk,  True)
    GPIO.output(spi_clk,  False)

    cmd = (0 | 0x18) << 3
    for i in range(5):
        if (cmd & 0x80):
            GPIO.output(spi_mosi, True)
        else:
            GPIO.output(spi_mosi, False)
        cmd <<= 1
        GPIO.output(spi_clk, True)
        GPIO.output(spi_clk, False)
    GPIO.output(spi_clk, True)
    GPIO.output(spi_clk, False)
    GPIO.output(spi_clk, True)
    GPIO.output(spi_clk, False)

    value = 0
    for i in range(12):
        value <<= 1
        GPIO.output(spi_clk, True)
        if (GPIO.input(spi_miso)):
            value |= 0x1
        GPIO.output(spi_clk, False)

    GPIO.output(spi_ss, True)
    value = 20.0 + (value - 700) / 8.0
    sys.stdout.write(str(value))

    sys.stdout.write("\n")

    print 'Temp={0:0.1f}*C'.format(value)
    pubnub.publish('tempeon', {
        'columns': [
            ['x', time.time()],
            ['temperature_celcius', value]
            ]
	    })

