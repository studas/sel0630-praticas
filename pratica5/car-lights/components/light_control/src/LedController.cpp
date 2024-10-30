#include "esp_log.h"

#include "LedController.hpp"

LedController::LedController(gpio_num_t gpioPin, ledc_channel_t channel, ledc_timer_t timer, uint32_t pwmFrequency, uint8_t pwmResolutionBits, int* adcValuePtr)
    : _gpioPin(gpioPin), _channel(channel), _adcValuePtr(adcValuePtr), _taskHandle(nullptr), _isTaskRunning(true) {
    
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_HIGH_SPEED_MODE,
        .duty_resolution  = static_cast<ledc_timer_bit_t>(pwmResolutionBits),
        .timer_num        = timer,
        .freq_hz          = pwmFrequency,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .gpio_num       = _gpioPin,
        .speed_mode     = LEDC_HIGH_SPEED_MODE,
        .channel        = _channel,
        .timer_sel      = timer,
        .duty           = 0,        // Start with LED off
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);

    _maxDutyCycle = (1 << pwmResolutionBits) - 1;

    // Start the task during instantiation
    xTaskCreate(ledTask, "LED Control Task", 2048, this, tskIDLE_PRIORITY, &_taskHandle);
}

LedController::~LedController() {
}

void LedController::stopTask() {
    if (_isTaskRunning && _taskHandle != nullptr) {
        vTaskDelete(_taskHandle);
        _taskHandle = nullptr;
        _isTaskRunning = false;
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, _channel, 0);  // Turn off LED when stopping the task
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, _channel);
    }
}

void LedController::resumeTask() {
    if (!_isTaskRunning) {
        xTaskCreate(ledTask, "LED Control Task", 2048, this, tskIDLE_PRIORITY, &_taskHandle);
        _isTaskRunning = true;
    }
}

void LedController::ledTask(void* pvParameter) {
    LedController* led = static_cast<LedController*>(pvParameter);

    ESP_LOGI("LED Task", "Starting LED Task");

    while (true) {
        led->updateLedIntensity();
        vTaskDelay(pdMS_TO_TICKS(1000/24));  // Update every 100ms
    }
}

void LedController::updateLedIntensity() {
    if (_adcValuePtr != nullptr) {
        int adcValue = *_adcValuePtr;  // Get the current ADC value
        uint32_t duty = static_cast<uint32_t>((adcValue / 4095.0) * _maxDutyCycle);  // Assuming 12-bit ADC (0-4095)
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, _channel, duty);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, _channel);
    }
}
