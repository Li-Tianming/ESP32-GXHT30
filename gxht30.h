
#include "driver/i2c.h"

#ifndef gxht30_h
#define gxht30_h

#define GXHT30_SLAVE_ADDRESS   (0x44) //7-bit I2C Address
#define GXHT30_READ_ADDR    ((GXHT30_SLAVE_ADDRESS << 1) | I2C_MASTER_READ)
#define GXHT30_WRITE_ADDR   ((GXHT30_SLAVE_ADDRESS << 1) | I2C_MASTER_WRITE)

class GXHT30_Class
{
public:
    bool getTemperatureHumidity(uint16_t& Temperature, uint16_t& Humidity);
    bool getTemperatureHumidity(float& Temperature, float& Humidity);
private:
    esp_err_t last_i2c_err = ESP_OK;
};

#endif //gxht30_h