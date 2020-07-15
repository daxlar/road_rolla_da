#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOSConfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "esp_system.h"



#define I2C_MASTER_SCL_PIN  5
#define I2C_MASTER_SDA_PIN  4
#define X_DELAY_1000MS      pdMS_TO_TICKS(1000)

#define READ_OPERATION      0
#define WRITE_OPERATION     1
#define ENABLE_ACK_CHK      true
#define NACK_VAL            0x1

#define MPU6050_ADDRESS     0x68

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

void mpu_6050_read_from_register(uint8_t reg, uint8_t* data, uint8_t datalen){
    esp_err_t err;
    i2c_cmd_handle_t handle = i2c_cmd_link_create();
    err = i2c_master_start(handle);
    err = i2c_master_write_byte(handle, MPU6050_ADDRESS << 1 | WRITE_OPERATION, ENABLE_ACK_CHK);
    err = i2c_master_write_byte(handle, reg, ENABLE_ACK_CHK);
    err = i2c_master_cmd_begin(I2C_NUM_0, handle, 1000 / portTICK_RATE_MS);

    err = i2c_master_start(handle);
    err = i2c_master_write_byte(handle, MPU6050_ADDRESS << 1 | READ_OPERATION, ENABLE_ACK_CHK);
    err = i2c_master_read_byte(handle, data, NACK_VAL);
    err = i2c_master_stop(handle);
    err = i2c_master_cmd_begin(I2C_NUM_0, handle, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(handle);
}