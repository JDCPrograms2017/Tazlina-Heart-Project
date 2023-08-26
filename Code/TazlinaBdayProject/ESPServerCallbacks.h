#include <BLEDevice.h>
#include <BLEServer.h>

class ESPServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        Serial.println("Connected!");
    }

    void onDisconnect(BLEServer* pServer) {
        Serial.println("Disconnected...");
    }
};
