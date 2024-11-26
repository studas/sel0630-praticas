#ifndef ADC_READER_HPP
#define ADC_READER_HPP

#include "driver/adc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class AdcReader {
public:
    AdcReader(adc2_channel_t channel, int* adcValuePtr);
    ~AdcReader();

    void stopTask();     // Stop ADC reading task
    void resumeTask();   // Resume the task if previously stopped

private:
    static void adcTask(void* pvParameter);  // Task function
    void readAdc();

    adc2_channel_t _channel;
    int* _adcValuePtr;
    TaskHandle_t _taskHandle;
};

#endif  // ADC_READER_HPP
