#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H
#include <Arduino.h>
#include <WiFiClient.h>

class SocketClient {
public:
    SocketClient() = default;
    ~SocketClient() {disconnect();}
    bool connectToServer(const String& ip, uint16_t port);
    void disconnect();
    bool isConnected();
    bool sendData(const String& data);
    void maintainConnection();
    void reset();

private:
    WiFiClient client;
    String serverIP = "";
    uint16_t serverPort = 0;
    unsigned long lastReconnectAttempt = 0;
    const unsigned long reconnectInterval = 3000;
    bool connected = false;
};

#endif //CPR_TEST_SOCKETMANAGER_H