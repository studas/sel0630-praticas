#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"

class Servo {
private:
    int running;
    int gpio_pin;
    ledc_channel_t channel;

public:
    Servo(int gpio_pin, ledc_channel_t channel);
    ~Servo();
    void set_angle(int angle);
    void update();

    int angle;
    uint32_t min_pulse_width, max_pulse_width;
};
