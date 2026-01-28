#include "BluetoothManager.h"
#include <BLEDevice.h>
#include "config.h"

//特征值回调
void BluetoothManager::ConfigCharacteristicCallbacks::onWrite(BLECharacteristic *pcharacteristic) {
    const std::string rxValue = pcharacteristic->getValue();
    if (rxValue.empty()) return;

    const String received = String(rxValue.c_str());
    const int idx1 = received.indexOf(',');
    const int idx2 = received.indexOf('.',idx1+1);
    const int idx3 = received.indexOf('+',idx2+1);
    if (idx1 <= 0 || idx2 <= idx1 || idx3 <= idx2) return;

    manager->config.ssid = received.substring(0,idx1);
    manager->config.password = received.substring(idx1+1,idx2);
    manager->config.ip = received.substring(idx2+1,idx3);
    manager->config.port = static_cast<uint16_t>(received.substring(idx3 + 1).toInt());
    manager->config.hasNewConfig = true;

}
//初始化BLE
void BluetoothManager::setupBLE() {
    BLEDevice::init(BLE_CONFIG_NAME);
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new ConnectionServerCallbacks(this));

    BLEService *pService = pServer->createService(BLE_SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
        BLE_CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ
    );
    pCharacteristic->setCallbacks(new ConfigCharacteristicCallbacks(this));
    pService->start();
    pServer->getAdvertising()->start();
}
//初始化
void BluetoothManager::begin() {
    setupBLE();
}
//获取最新配置
BLEConfig BluetoothManager::getConfig() {
    return config;
}
//判断是否有新配置
bool BluetoothManager::hasNewConfig() const{
    return config.hasNewConfig;
}
//清空新配置
void BluetoothManager::clearNewConfigFlag() {
    config.hasNewConfig = false;
}
