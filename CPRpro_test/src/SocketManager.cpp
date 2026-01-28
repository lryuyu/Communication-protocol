#include "SocketManager.h"
#include <WiFiClient.h>

//连接服务器
bool SocketClient::connectToServer(const String &ip, uint16_t port) {
    if (client.connected()) client.stop();
    const bool result = client.connect(ip.c_str(),port);
    connected = result;
    if (result) {
        serverIP = ip;
        serverPort = port;
    }
    return result;
}
//断开服务器
void SocketClient::disconnect() {
    if (client.connected())client.stop();
    connected = false;
}
//判断是否连接
bool SocketClient::isConnected() {
    if (connected && !client.connected()) connected = false;
    return connected;
}
//发送数据
bool SocketClient::sendData(const String& data) {
    if (!isConnected())return false;
    const size_t bytesSent = client.print(data);
    client.flush();
    return bytesSent == data.length();
}
//维护Socket连接，3s
void SocketClient::maintainConnection() {
    if (!isConnected() && !serverIP.isEmpty() && serverPort != 0) {
        const unsigned long now = millis();
        if (now - lastReconnectAttempt >= reconnectInterval) {
            connectToServer(serverIP,serverPort);
            lastReconnectAttempt = now;
        }
    }
}
//重置
void SocketClient::reset() {
    disconnect();
    serverIP = "";
    serverPort = 0;
    lastReconnectAttempt = 0;
}
