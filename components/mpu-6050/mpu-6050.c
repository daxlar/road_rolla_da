#include <stdio.h>
#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "esp_system.h"



#define I2C_MASTER_SCL_PIN  5
#define I2C_MASTER_SDA_PIN  4
#define X_DELAY_1000MS      pdMS_TO_TICKS(1000)

const char MPU6050_TAG[] = "MPU-6050";


void print_hello(){
    printf("hello from mpu-6050");
}

void mpu_6050_i2c_master_init(){

    esp_err_t err;
    err = i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER);
    if(err == ESP_ERR_INVALID_ARG){
        ESP_LOGI(MPU6050_TAG, "invalid driver install parameter");
        vTaskDelay(X_DELAY_1000MS);
        esp_restart();
    }
    if(err == ESP_FAIL){
        ESP_LOGI(MPU6050_TAG, "driver install error");
        vTaskDelay(X_DELAY_1000MS);
        esp_restart();
    }

    i2c_config_t i2c_param_conf;
    i2c_param_conf.mode = I2C_MODE_MASTER;
    i2c_param_conf.sda_io_num = I2C_MASTER_SDA_PIN;
    i2c_param_conf.sda_pullup_en = 1;
    i2c_param_conf.scl_io_num = I2C_MASTER_SCL_PIN;
    i2c_param_conf.scl_pullup_en = 1;
    i2c_param_conf.clk_stretch_tick = 300;

    err = i2c_param_config(I2C_NUM_0, &i2c_param_conf);
    if(err == ESP_ERR_INVALID_ARG){
        ESP_LOGI(MPU6050_TAG, "invalid param config parameter");
        vTaskDelay(X_DELAY_1000MS);
        esp_restart();
    }
}


