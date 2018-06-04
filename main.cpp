#include "mbed.h"
#include "BMP280.h"
#include "hts221.h"
#include "lis3mdl.h"
#include "VEML6030.h"
#include "VL53L0X.h"
#include "LSM6DSLSensor.h"

#ifndef VEML6030_I2C_ADDRESS
#define VEML6030_I2C_ADDRESS 0x10
#endif

static BMP280   bmp280(I2C0_SDA, I2C0_SCL);
static HTS221   hts221(I2C0_SDA, I2C0_SCL);
static LIS3MDL  lis3mdl(I2C0_SDA, I2C0_SCL);
static VEML6030 veml6030(I2C0_SDA, I2C0_SCL, VEML6030_I2C_ADDRESS);

static I2C devI2c(I2C0_SDA, I2C0_SCL);
static DigitalOut shutdown_pin(GPIO_A0_A3);
static VL53L0X range(&devI2c, &shutdown_pin, GPIO_A2_A2);

static LSM6DSLSensor acc_gyro(&devI2c, LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW); // low address

volatile AxesRaw_TypeDef MAG_Value;

int main() {

    /* Print LIS3MDL sensor ID */
    printf("LIS3MDL ID  = 0x%x\n", lis3mdl.ReadID());

    /* Initial VEML6030 */
    veml6030.setALSConf(0x0000) ;
    veml6030.setPowerSaving(0x0000) ;

    /* Initial LSM6DSL */
    int32_t axes[3];
    uint8_t id;
    acc_gyro.init(NULL);
    acc_gyro.enable_x();
    acc_gyro.enable_g();
    acc_gyro.read_id(&id);

    printf("LSM6DSL ID  = 0x%x\n", id);

    /* Initial VL53L0X */
    range.init_sensor(VL53L0X_DEFAULT_ADDRESS);

    while(1) {

        /* Read BMP280 Temperature and Pressure information */
        printf("BMP280   [temperature]:            %d°C\n", (int)bmp280.getTemperature());
        printf("BMP280   [pressure]:               %dhPa\n", (int)bmp280.getPressure());

        /* Read HTS221 Temperature and Humidity information */
        float temp, humi;
        hts221.GetTemperature(&temp);
        hts221.GetHumidity(&humi);
        printf("HTS221   [temperature]:            %d°C\n", (int)temp);
        printf("HTS221   [humidity]:               %d%%\n", (int)humi);

        /* Read LIS3MDL Magnetometer information */
        lis3mdl.GetAxes((AxesRaw_TypeDef *)&MAG_Value);
        printf("LIS3MDL  [Magnetometer/mGauss]:     X: %d, Y: %d, Z: %d\r\n", (int)MAG_Value.AXIS_X,
                                                                              (int)MAG_Value.AXIS_Y,
                                                                              (int)MAG_Value.AXIS_Z);

        /* Read VEML6030 ambient light information */
        uint16_t als = veml6030.getALS() ;
        uint16_t white = veml6030.getWHITE() ;
        printf("VEML6030 [ALS]:                    %d\n", als) ;
        printf("VEML6030 [white]:                  %d\n", white) ;

        /* Read LSM6DSL 3D digital accelerometer and 3D digital gyroscope information */
        acc_gyro.get_x_axes(axes);
        printf("LSM6DSL  [acc/mg]:                 %d, %d, %d\r\n", (int)axes[0], (int)axes[1], (int)axes[2]);

        acc_gyro.get_g_axes(axes);
        printf("LSM6DSL  [gyro/mdps]:              %d, %d, %d\r\n", (int)axes[0], (int)axes[1], (int)axes[2]);

        /* Read VL53L0X Time-of-Flight ranging information */
        uint32_t distance;
        int status = range.get_distance(&distance);

        if (status == VL53L0X_ERROR_NONE) {
            printf("VL53L0X  [mm]:                    %d\r\n", (int)distance);
        } else {
            printf("VL53L0X  [mm]:                     --\r\n");
        }

        wait(1);
        printf("\n");
    }

    return 0;
}
