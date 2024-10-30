#ifndef LED_CONTROLLER_HPP
#define LED_CONTROLLER_HPP

#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class LedController {
public:
    LedController(gpio_num_t gpioPin, ledc_channel_t channel, ledc_timer_t timer, uint32_t pwmFrequency = 5000, uint8_t pwmResolutionBits = 12, int* adcValuePtr = nullptr);
    ~LedController();

    void stopTask();     // Stop the LED control task
    void resumeTask();   // Resume the task if previously stopped

private:
    static void ledTask(void* pvParameter);  // Task function
    void updateLedIntensity();

    gpio_num_t _gpioPin;
    ledc_channel_t _channel;
    uint32_t _maxDutyCycle;
    int* _adcValuePtr;
    TaskHandle_t _taskHandle;
    bool _isTaskRunning;
};

#endif  // LED_CONTROLLER_HPP
