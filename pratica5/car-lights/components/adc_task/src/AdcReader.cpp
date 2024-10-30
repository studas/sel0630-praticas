#include "esp_log.h"

#include "AdcReader.hpp"

AdcReader::AdcReader(adc2_channel_t channel, int* adcValuePtr)
    : _channel(channel), _adcValuePtr(adcValuePtr), _taskHandle(nullptr){
    adc2_config_channel_atten(_channel, ADC_ATTEN_DB_11);  // No attenuation
    
    ESP_LOGI("ADC Task", "Starting ADC Reader");
    xTaskCreate(adcTask, "ADC Task", 2048, this, 2, &_taskHandle);
}

AdcReader::~AdcReader() {

}

void AdcReader::stopTask() {
    if (_taskHandle != nullptr) {
        vTaskDelete(_taskHandle);
        ESP_LOGI("ADC Task", "ADC Task stopped");
        *_adcValuePtr = 0;
        _taskHandle = nullptr;
    }
}

void AdcReader::resumeTask() {
    if (_taskHandle != nullptr) {
        xTaskCreate(adcTask, "ADC Task", 2048, this, 2, &_taskHandle);
        ESP_LOGI("ADC Task", "ADC Task resumed");
    }
}

void AdcReader::adcTask(void* pvParameter) {
    AdcReader* reader = static_cast<AdcReader*>(pvParameter);
    ESP_LOGI("ADC Task", "ADC Task running");

    while (true) {
        reader->readAdc();
        vTaskDelay(pdMS_TO_TICKS(1000/24));  // Adjust the delay as needed
    }
}

void AdcReader::readAdc() {
    if (_adcValuePtr != nullptr) {
        adc2_get_raw(_channel, ADC_WIDTH_BIT_12, _adcValuePtr);
    }else{
        ESP_LOGE("ADC Task", "ADC Value pointer is null");
    }
}
