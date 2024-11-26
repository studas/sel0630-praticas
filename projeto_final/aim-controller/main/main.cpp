#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "driver/gpio.h"
#include "ServoController.hpp"

static const char *TAG = "i2c-slave";

#define LED_PIN 2

#define I2C_SLAVE_SCL_IO 22               /*!< gpio number for I2C master clock */
#define I2C_SLAVE_SDA_IO 21               /*!< gpio number for I2C master data  */
#define I2C_SLAVE_FREQ_HZ 100000        /*!< I2C master clock frequency */
#define I2C_SLAVE_TX_BUF_LEN 255                        /*!< I2C master doesn't need buffer */
#define I2C_SLAVE_RX_BUF_LEN 255                           /*!< I2C master doesn't need buffer */
#define ESP_SLAVE_ADDR 0x0A

#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1                            /*!< I2C nack value */

int i2c_slave_port = 0;
static esp_err_t i2c_slave_init(void)
{
    i2c_config_t conf_slave = {
        .mode = I2C_MODE_SLAVE,
        .sda_io_num = I2C_SLAVE_SDA_IO,          // select GPIO specific to your project
        .scl_io_num = I2C_SLAVE_SCL_IO,          // select GPIO specific to your project
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .slave{
            .addr_10bit_en = 0,
            .slave_addr = ESP_SLAVE_ADDR,      // address of your project
        },
        .clk_flags = 0,
    };
    esp_err_t err = i2c_param_config(I2C_NUM_0, &conf_slave);
    if (err != ESP_OK) {
        return err;
    }
    return i2c_driver_install(I2C_NUM_0, conf_slave.mode, I2C_SLAVE_RX_BUF_LEN, I2C_SLAVE_TX_BUF_LEN, 0);
}

extern "C" void app_main(void)
{
    Servo servo0(13, LEDC_CHANNEL_0);
    servo0.min_pulse_width = 500;
    servo0.max_pulse_width = 2500;
    Servo servo1(12, LEDC_CHANNEL_1);
    servo1.min_pulse_width = 500;
    servo1.max_pulse_width = 2500;

    Servo servos[] = {servo0, servo1};

    uint8_t  received_data[I2C_SLAVE_RX_BUF_LEN] = {0};

    ESP_ERROR_CHECK(i2c_slave_init());
    ESP_LOGI(TAG, "I2C Slave initialized successfully");
    
    while(1)
    {
        i2c_slave_read_buffer(I2C_NUM_0, received_data, I2C_SLAVE_RX_BUF_LEN, 100 / portTICK_PERIOD_MS);
        i2c_reset_rx_fifo(I2C_NUM_0);

        //check size of received data
        if (strlen((char *)received_data) == 0) {
            continue;
        }

        printf("Received data: %s\n", received_data);

        char* token;
        char* saveptr;
        int index = -1;
        int angle = -1;

        // Get the first token (index)
        token = strtok_r((char *)received_data, " ", &saveptr);
        if (token != NULL) {
            index = atoi(token);
            // Get the second token (angle)
            token = strtok_r(NULL, " ", &saveptr);
            if (token != NULL) {
                angle = atoi(token);
            } else {
                ESP_LOGE(TAG, "Error: Angle value is missing.\n");
                continue;  // Exit or handle the error as needed
            }
        } else {
            ESP_LOGE(TAG, "Error: Index value is missing.\n");
            continue;  // Exit or handle the error as needed
        }

        servos[index].set_angle(angle);

        memset(received_data, 0, I2C_SLAVE_RX_BUF_LEN);
        received_data[0] = '\0';
    }

}