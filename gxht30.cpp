#include <stdio.h>
#include "gxht30.h"
#include <stdint.h>
#include <stddef.h>
#include "esp_system.h"

bool GXHT30_Class::getTemperatureHumidity(uint16_t& Temperature, uint16_t& Humidity)
{
	last_i2c_err = ESP_OK;
    // low resolution
    uint8_t reg[2] = {0x2c, 0x10};
    uint8_t data[6] = {};
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, GXHT30_WRITE_ADDR, true);
	i2c_master_write_byte(cmd, reg[0], true);
	i2c_master_write_byte(cmd, reg[1], true);
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, GXHT30_READ_ADDR, true);
	i2c_master_read(cmd, data, sizeof(data), I2C_MASTER_LAST_NACK);
	i2c_master_stop(cmd);
	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
	last_i2c_err = ret;
    printf("GXHT30_Class::getTemperatureHumidity %02x, %02x, %02x, %02x, %02x, %02x \n",
    data[0], data[1], data[2], data[3], data[4], data[5]);
    // check crc before assign value?
    uint16_t tmp = (data[0] << 8) | data[1];
    uint16_t hum = (data[3] << 8) | data[4];
    Temperature = tmp;
    Humidity = hum;
	printf("last_i2c_err %d\n", last_i2c_err);
    // return ret;
    if(ret == ESP_OK)
        return true;
    else
        return false;
}

bool GXHT30_Class::getTemperatureHumidity(float& Temperature, float& Humidity)
{
	last_i2c_err = ESP_OK;
    // low resolution
    uint8_t reg[2] = {0x2c, 0x10};
    uint8_t data[6] = {};
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, GXHT30_WRITE_ADDR, true);
	i2c_master_write_byte(cmd, reg[0], true);
	i2c_master_write_byte(cmd, reg[1], true);
	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, GXHT30_READ_ADDR, true);
	i2c_master_read(cmd, data, sizeof(data), I2C_MASTER_LAST_NACK);
	i2c_master_stop(cmd);
	esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
	last_i2c_err = ret;
    // check crc before assign value?
    uint16_t tmp = (data[0] << 8) | data[1];
    uint16_t hum = (data[3] << 8) | data[4];
    Temperature = tmp;
    Temperature = Temperature / 65535 *175 - 45;
    Humidity = hum;
    Humidity = Humidity / 65535 * 100;
    printf("GXHT30_Class::getTemperatureHumidity %3.2f, %3.2f\n", Temperature, Humidity);
	printf("last_i2c_err %d\n", last_i2c_err);
    if(ret == ESP_OK)
        return true;
    else
        return false;
}
