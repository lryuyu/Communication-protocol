#ifndef CONFIG_H
#define CONFIG_H

#define SPI_SCLK 18;
#define SPI_MOSI 19;
#define SPI_MISO 23;
#define SPI_SS 5;

#define I2C_SDA 21
#define I2C_SCL 22

#define BLE_SERVICE_UUID  "12345678-1234-5678-1234-56789abcdef0"
#define BLE_CHARACTERISTIC_UUID  "abcdef01-1234-5678-1234-56789abcdef0"
#define BLE_ADV_APPEARANCE      0x0540
#define BLE_CONFIG_NAME  "EPHW:MSTESCPR001"

//位置压力传感器
#define A_SENS_LP_0_PIN  A0
#define A_SENS_LP_1_PIN  A1
#define A_SENS_LP_2_PIN  A2
#define A_SENS_LP_3_PIN  A3
#define A_SENS_LP_4_PIN  A4
#define A_SENS_LP_5_PIN  A5
#define A_SENS_LP_6_PIN  A6
#define A_SENS_LP_7_PIN  A7

//颈部压力传感器
#define A_SENS_PP_0_PIN  A8
#define A_SENS_PP_1_PIN  A9

//气流传感器
#define A_SENS_AF_0_PIN  A10

//额头-鼻翼L-鼻翼R-下巴
#define A_SENS_HEAD_0_PIN  A11
#define A_SENS_NOSE_0_PIN A12
#define A_SENS_NOSE_1_PIN A13
#define A_SENS_DIS_0_PIN A14

#define  FILTER_MAX 100;
#define WIFI_RECONNECT_INTERVAL 5000;
#define SOCKET_RECONNECT_INTERVAL 5000;
#define SEND_INTERVAL 100;

#endif