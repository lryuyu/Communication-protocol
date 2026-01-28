#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "BluetoothManager.h"
#include "config.h"
#include "SensorFilter.h"
#include "SocketManager.h"
#include "WiFiManager.h"

SensorConfig sensor0 = {A_SENS_LP_0_PIN, {}, 0, xSemaphoreCreateMutex()};
SensorConfig sensor1 = {A_SENS_LP_1_PIN, {}, 0, xSemaphoreCreateMutex()};
SensorConfig sensor2 = {A_SENS_LP_2_PIN, {}, 0, xSemaphoreCreateMutex()};
SensorConfig sensor3 = {A_SENS_LP_3_PIN, {}, 0, xSemaphoreCreateMutex()};
SensorConfig sensor4 = {A_SENS_LP_4_PIN, {}, 0, xSemaphoreCreateMutex()};
SensorConfig sensor5 = {A_SENS_LP_5_PIN, {}, 0, xSemaphoreCreateMutex()};
SensorConfig sensor6 = {A_SENS_LP_6_PIN, {}, 0, xSemaphoreCreateMutex()};
SensorConfig sensor7 = {A_SENS_LP_7_PIN, {}, 0, xSemaphoreCreateMutex()};

SensorConfig sensor8 = {A_SENS_PP_0_PIN,{},0,xSemaphoreCreateMutex()};
SensorConfig sensor9 = {A_SENS_PP_1_PIN, {}, 0, xSemaphoreCreateMutex()};

SensorConfig sensor_AF_0 = {A_SENS_LP_2_PIN, {}, 0, xSemaphoreCreateMutex()};

SensorConfig sensor_HEAD_0 = {A_SENS_LP_2_PIN, {}, 0, xSemaphoreCreateMutex()};

SensorConfig* allSensors[15] = {

};


BluetoothManager bleManager;
WiFiManager wifiManager;
SocketClient socketClient;

constexpr unsigned long sendInterval = 100;
unsigned long lastSendTime = 0;
bool wifiConfigured = false;

void creatSensorTasks() {
    xTaskCreatePinnedToCore(sensorTask,"Sensor1",4096,&sensor1,1,nullptr,0);
    xTaskCreatePinnedToCore(sensorTask,"Sensor3",4096,&sensor3,1,nullptr,0);
    xTaskCreatePinnedToCore(sensorTask,"Sensor5",4096,&sensor5,1,nullptr,0);
    xTaskCreatePinnedToCore(sensorTask,"Sensor7",4096,&sensor7,1,nullptr,0);
    xTaskCreatePinnedToCore(sensorTask,"Sensor2",4096,&sensor2,1,nullptr,1);
    xTaskCreatePinnedToCore(sensorTask,"Sensor4",4096,&sensor4,1,nullptr,1);
    xTaskCreatePinnedToCore(sensorTask,"Sensor6",4096,&sensor6,1,nullptr,1);
    xTaskCreatePinnedToCore(sensorTask,"Sensor8",4096,&sensor8,1,nullptr,1);
}

void setup() {
    Serial.begin(115200);

    pinMode(sensor1.pin,INPUT);
    pinMode(sensor2.pin,INPUT);
    pinMode(sensor3.pin,INPUT);
    pinMode(sensor4.pin,INPUT);
    pinMode(sensor5.pin,INPUT);
    pinMode(sensor6.pin,INPUT);
    pinMode(sensor7.pin,INPUT);
    pinMode(sensor8.pin,INPUT);

    bleManager.begin();

    creatSensorTasks();

}

void loop() {
    if (bleManager.hasNewConfig()) {
        const BLEConfig cfg = bleManager.getConfig();
        bleManager.clearNewConfigFlag();

        wifiConfigured = false;
        wifiManager.reset();
        socketClient.reset();

        wifiManager.begin(cfg.ssid,cfg.password);
    }

    wifiManager.maintainConnection();
    socketClient.maintainConnection();

    if (WiFiManager::isConnected() && !wifiConfigured) {
        wifiConfigured = true;
    }
    if (wifiConfigured && !socketClient.isConnected()) {
        const BLEConfig cfg = bleManager.getConfig();
        socketClient.connectToServer(cfg.ip,cfg.port);
    }

    const unsigned long now = millis();
    if (socketClient.isConnected()&& now - lastSendTime >= sendInterval) {
        lastSendTime = now;
        int values[8] = {0};
        SensorConfig* sensorArray[8] = {&sensor1,&sensor2,&sensor3,&sensor4,&sensor5,&sensor6,&sensor7,&sensor8};
        for (int i = 0; i < 8; i++) {
            if (xSemaphoreTake(sensorArray[i]->mutex, (TickType_t)10) == pdTRUE) {
                values[i] = sensorArray[i]->latesValue;
                xSemaphoreGive(sensorArray[i]->mutex);
            }
        }
        for (int i = 0; i < 8; i++) {
            String sensorType;
            switch(i) {
                case 0:sensorType = "λ����";break;
                case 1:sensorType = "λ����";break;
                case 2:sensorType = "λ����";break;
                case 3:sensorType = "λ����";break;
                case 4:sensorType = "λ����";break;
                case 5:sensorType = "������ѹ";break;
                case 6:sensorType = "����";break;
                case 7:sensorType = "��Ⱦ���";break;
                default: sensorType = "unknown";
            }
            String jsonData = R"({"timestamp":)" + String (now) + R"(,"sensor_type":")"+ sensorType + R"(","raw_val":)" + String (values [i]) + R"(})";
            if (!socketClient.sendData (jsonData))
                {
                socketClient.disconnect ();
                break;
                }
        }

        char buffer[128] = {0};
        int offset = 0;
        for (int i = 0; i < 8; i++) {
            offset += snprintf( buffer + offset, sizeof(buffer) - offset ,"%d,", values[i] );
            if (i<7)offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%d,", values[i] );
        }
        buffer[offset++] = '\n';

        if (!socketClient.sendData(String(buffer))) {
            socketClient.disconnect();
        }



    }
}