#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"

#include "ServoController.hpp"

#define SERVO_MIN_PULSEWIDTH_US 1000    // Minimum pulse width in microseconds
#define SERVO_MAX_PULSEWIDTH_US 3200   // Maximum pulse width in microseconds
#define SERVO_MAX_DEGREE 180           // Maximum angle of rotation
#define LEDC_FREQUENCY 50              // Frequency in Hertz (typical for servos)
#define LEDC_TIMER LEDC_TIMER_0        // Timer number
#define LEDC_MODE LEDC_HIGH_SPEED_MODE  // LEDC mode

Servo::Servo(int gpio_pin, ledc_channel_t channel) 
    : gpio_pin(gpio_pin), channel(channel){
    // Configure LEDC timer
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .timer_num = LEDC_TIMER,
        .freq_hz = LEDC_FREQUENCY,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // Configure LEDC channel
    ledc_channel_config_t ledc_channel = {
        .gpio_num = gpio_pin,
        .speed_mode = LEDC_MODE,
        .channel = channel,
        .timer_sel = LEDC_TIMER,
        .duty = 0,
        .hpoint = 0
    };
    ledc_channel_config(&ledc_channel);
}

Servo::~Servo() {
    // Clean up LEDC configuration
    ledc_stop(LEDC_MODE, channel, 0);
}

void Servo::set_angle(int angle) {
    this->angle = angle;
    this->update();
    printf("Setting servo %d to %d degrees\n", gpio_pin, angle);
}

void Servo::update() {
    if (this->angle < 0) this->angle = 0;
    if (this->angle > SERVO_MAX_DEGREE) this->angle = SERVO_MAX_DEGREE;

    uint32_t pulse_width = min_pulse_width +
                           (angle) * ((max_pulse_width - min_pulse_width) / SERVO_MAX_DEGREE);
    uint32_t duty = (pulse_width * 8192) / 20000;
    ledc_set_duty(LEDC_MODE, channel, duty);
    ledc_update_duty(LEDC_MODE, channel);
}
