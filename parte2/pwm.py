import RPi.GPIO as gpio
import time
 
#Configuring don’t show warnings 
gpio.setwarnings(False)
 
#Configuring GPIO
gpio.setmode(gpio.BCM)
gpio.setup(18,gpio.OUT)

 
#Configure the pwm objects and initialize its value
pwmLed = gpio.PWM(18,100)
pwmLed.start(0)
 
#Create the dutycycle variables
duty_cycle = 0

increase = True

#Loop infinite
try:
    while True:
   
        #increment gradually the luminosity
        pwmLed.ChangeDutyCycle(duty_cycle)
        time.sleep(0.05)
        if increase:
            duty_cycle = duty_cycle + 1
        else:
            duty_cycle = duty_cycle - 1
        
        if duty_cycle >= 100:
            increase = False
        
        elif duty_cycle <= 0:
            increase = True

except KeyboardInterrupt:
    pass

finally:
    gpio.cleanup()

