#include <stdio.h>

#include "CarLightsControl.hpp"

extern "C" void app_main(void)
{

//interrupt that awaits for the button at GPIO4 to be pressed, it stops the interrupt and calls a toggle task that toggles the lights and then reenables the interrupt, deactivates the LDR task if it activated the lights

//adc task reading the potentiometer value and setting the duty cycle of the PWM signal, it's activated or deactived by the button interrupt

//adc task that reads the LDR value and toggles the lights if the value is below a certain threshold
//if after the light being toggled the user uses the button to turn off the lights, the LDR task will not turn them on again

//task that sends the pwm signal to the LEDS, it's activated or deactivated by the button interrupt
    start_light_control();

}