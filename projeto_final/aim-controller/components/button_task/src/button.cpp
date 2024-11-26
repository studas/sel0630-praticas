#include "Button.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// Constructor with callbacks for toggle ON and OFF
Button::Button(gpio_num_t pin, Callback onCallback, Callback offCallback) 
    : button_pin(pin), toggle_var(false), onCallback(onCallback), offCallback(offCallback) {
    
    // Configure button pin as input with pull-up
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_NEGEDGE;  // Trigger on falling edge (button press)
    io_conf.pin_bit_mask = (1ULL << button_pin);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);

    // Create interrupt
    gpio_install_isr_service(0);
    gpio_isr_handler_add(button_pin, gpio_isr_handler, this);
}

// ISR handler
void IRAM_ATTR Button::gpio_isr_handler(void* arg) {
    Button* self = static_cast<Button*>(arg);
    gpio_isr_handler_remove(self->button_pin);  // Disable interrupt
    xTaskCreate(reenableInterruptTask, "Reenable Interrupt Task", 2048, self, tskIDLE_PRIORITY, NULL);
}

// Get toggle_var state
bool Button::getToggleVar() const {
    return toggle_var;
}

// Task to re-enable the interrupt
void Button::reenableInterruptTask(void* pvParameter) {
    Button* self = static_cast<Button*>(pvParameter);

    self->toggle_var = !self->toggle_var;  // Toggle the variable

    // Call the appropriate callback based on the new state of toggle_var
    if (self->toggle_var && self->onCallback) {
        self->onCallback();
    } else if (!self->toggle_var && self->offCallback) {
        self->offCallback();
    }

    vTaskDelay(pdMS_TO_TICKS(100));  // Wait for 100ms (debounce delay)
    gpio_isr_handler_add(self->button_pin, gpio_isr_handler, self);  // Re-enable interrupt

    vTaskDelete(nullptr);  // Delete the task after completion
}
