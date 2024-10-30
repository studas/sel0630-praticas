#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <functional>

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class Button {
public:
    using Callback = std::function<void()>;

    explicit Button(gpio_num_t pin, Callback onCallback = nullptr, Callback offCallback = nullptr);

    bool getToggleVar() const;        // Function to get the state of toggle_var

    void toggleVar(bool state) {      // Function to set the state of toggle_var
        toggle_var = state;
    }

private:
    gpio_num_t button_pin;  // GPIO pin assigned to the button
    bool toggle_var;        // Variable to toggle on each interrupt
    Callback onCallback;    // Callback for toggle ON
    Callback offCallback;   // Callback for toggle OFF

    static void IRAM_ATTR gpio_isr_handler(void* arg);      // ISR handler function for button press
    static void reenableInterruptTask(void* pvParameter);   // Task to re-enable the interrupt after delay
};

#endif // BUTTON_HPP
