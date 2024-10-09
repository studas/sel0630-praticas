#/bin/python3

import RPi.GPIO as GPIO
import time

LED_PIN = 14

GPIO.setmode(GPIO.BCM)

GPIO.setup(LED_PIN, GPIO.OUT)

try:
    while True:
        GPIO.output(LED_PIN, GPIO.LOW)
        time.sleep(0.2)
        GPIO.output(LED_PIN, GPIO.HIGH)
        time.sleep(0.2)

except KeyboardInterrupt:
    pass

finally:
    GPIO.cleanup()
