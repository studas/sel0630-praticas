#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "CarLightsControl.hpp"

int potentiometer_value = NULL;
AdcReader *adc_potentiometer = nullptr;
LedController *green_led = nullptr;
LedController *red_led = nullptr;
int ldr_value = NULL;
AdcReader *adc_ldr = nullptr;
Button *toggler = nullptr;
TaskHandle_t ldrTaskHandle = nullptr;

void onButtonPressed() {
    ESP_LOGI("ButtonCallback", "Button toggled ON");
    adc_potentiometer->resumeTask();
    green_led->resumeTask();
    red_led->resumeTask();
}

void onButtonReleased() {
    ESP_LOGI("ButtonCallback", "Button toggled OFF");
    adc_potentiometer->stopTask();
    green_led->stopTask();
    red_led->stopTask();
}

void ldrControlTask(void* pvParameter) {
    ESP_LOGI("LDR Task", "Starting LDR Task");

    while (true) {
        if(ldr_value < 1000){
            if(!toggler->getToggleVar()){
                toggler->toggleVar(true);
                onButtonPressed();
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000/24));  // Update every 100ms
    }
}

void start_light_control(){
    potentiometer_value = 0;
    ldr_value = 0;

    ESP_LOGI("Light Control", "Starting light control");

    adc_potentiometer = new AdcReader(ADC2_CHANNEL_3, &potentiometer_value);
    green_led = new LedController(GPIO_NUM_16, LEDC_CHANNEL_0, LEDC_TIMER_0, 5000, 12, &potentiometer_value);
    red_led = new LedController(GPIO_NUM_17, LEDC_CHANNEL_0, LEDC_TIMER_0, 5000, 12, &potentiometer_value);
    toggler = new Button(GPIO_NUM_4, onButtonPressed, onButtonReleased);

    adc_ldr = new AdcReader(ADC2_CHANNEL_2, &ldr_value);

    xTaskCreate(ldrControlTask, "LED Control Task", 2048, NULL, tskIDLE_PRIORITY, &ldrTaskHandle);
}
