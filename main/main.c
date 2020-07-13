#include <stdio.h>
#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"


const char TAG[] = "app_main";

void app_main(void){
    const TickType_t xDelay1000ms = pdMS_TO_TICKS(1000);
    while(1){
        vTaskDelay(xDelay1000ms);
        ESP_LOGI(TAG, "hello world");
    }
}