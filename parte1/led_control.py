import RPi.GPIO as GPIO
import time

LED_PIN = 18
BUTTON_PIN = 27

GPIO.setmode(GPIO.BCM)

GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

try:
    while True:
        if GPIO.input(BUTTON_PIN) == GPIO.HIGH:
            GPIO.output(LED_PIN, GPIO.LOW)
        else:
            GPIO.output(LED_PIN, GPIO.HIGH)
        
        time.sleep(0.1)

except KeyboardInterrupt:
    pass

finally:
    GPIO.cleanup()
