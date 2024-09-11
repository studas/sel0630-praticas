import RPi.GPIO as gpio
import time
 
#Configuring don’t show warnings 
gpio.setwarnings(False)
 
#Configuring GPIO
pio.setmode(gpio.BOARD)
gpio.setup(38,gpio.OUT)
gpio.setup(40,gpio.OUT)
 
#Configure the pwm objects and initialize its value
pwmBlue = gpio.PWM(38,100)
pwmBlue.start(0)
 
pwmRed = gpio.PWM(40,100)
pwmRed.start(100)
 
#Create the dutycycle variables
dcBlue = 0
dcRed  = 100
 
#Loop infinite
while True:
   
    #increment gradually the luminosity
    pwmBlue.ChangeDutyCycle(dcBlue)
    time.sleep(0.05)
    dcBlue = dcBlue + 1
    if dcBlue == 100:
        dcBlue = 0
 
    #decrement gradually the luminosity
    pwmRed.ChangeDutyCycle(dcRed)
    time.sleep(0.05)
    dcRed = dcRed - 1
    if dcRed == 0:
        dcRed = 100
    
#End code
gpio.cleanup()
exit()
