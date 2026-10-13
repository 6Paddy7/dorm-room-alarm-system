#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LED_GPIO GPIO_NUM_4

static const char *TAG = "main";

void app_main(void)
{
    ESP_LOGI(TAG, "Dorm room alarm system: LED test");

    gpio_reset_pin(LED_GPIO);                        // put the pin in a known default state
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);  // make it an output

    int level = 0;
    while (1) {
        level = !level;                              // flip between 0 and 1
        gpio_set_level(LED_GPIO, level);             // 1 = 3.3 V (on), 0 = 0 V (off)
        ESP_LOGI(TAG, "LED %s", level ? "on" : "off");
        vTaskDelay(pdMS_TO_TICKS(500));              // wait 500 ms
    }
}