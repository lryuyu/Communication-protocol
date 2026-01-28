#ifndef BLUETOOTHMANAGER_H
#define BLUETOOTHMANAGER_H
#include <Arduino.h>
#include <BLEServer.h>

struct BLEConfig {
    String ssid;
    String password;
    String ip;
    uint16_t port = 0;
    bool hasNewConfig = false;
};

class BluetoothManager {
public:
    BluetoothManager()= default;
    void begin();
    BLEConfig getConfig();
    bool hasNewConfig() const;
    void clearNewConfigFlag();

private:
    BLEServer* pServer = nullptr;
    BLECharacteristic* pCharacteristic = nullptr;
    BLEConfig config;
    void setupBLE();


    class ConfigCharacteristicCallbacks : public BLECharacteristicCallbacks {
        BluetoothManager* manager;
    public:
        explicit ConfigCharacteristicCallbacks(BluetoothManager* mgr) : manager(mgr){}
            void onWrite(BLECharacteristic *pCharacteristic) override;
    };
    class ConnectionServerCallbacks : public BLEServerCallbacks {
        BluetoothManager* manager;
    public:
        explicit ConnectionServerCallbacks(BluetoothManager* mgr) : manager(mgr) {}
        void onDisconnect(BLEServer* server) override {
            server->getAdvertising()->start();
        }
    };
};

#endif //BLUETOOTHMANAGER_H