#include "WiFiManager.h"
//初始化连接
void WiFiManager::begin(const String& ssid,const String& password) {
    currentSSID = ssid;
    currentPass = password;
    WiFi.begin(ssid.c_str(),password.c_str());
    lastReconnectAttempt = millis();
}
//判断wifi连接
bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
//维护wifi连接
void WiFiManager::maintainConnection() {
    if (WiFi.status() != WL_CONNECTED) {
        const unsigned long now = millis();
        if (now - lastReconnectAttempt >= reconnectInterval) {
            WiFi.disconnect();
            WiFi.begin(currentSSID.c_str(),currentPass.c_str());
            lastReconnectAttempt = now;
        }
    }
}
//重置
void WiFiManager::reset() {
    WiFi.disconnect(true);
    currentSSID = "";
    currentPass = "";
    lastReconnectAttempt = 0;
}



