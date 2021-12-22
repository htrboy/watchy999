#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "Watchy_Base.h"
#include <BLEScan.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#include <BLE2902.h>
#include <BLEAdvertisedDevice.h>

BLEScan *pBLEScan;

// The remote service we wish to connect to.
static BLEUUID serviceUUID("00001801-0000-1000-8000-00805f9b34fb");
// The characteristic of the remote service we are interested in.
static BLEUUID    charUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8");


#define SERVICE_UUID_ESPOTA       "cd77498e-1ac8-48b6-aba8-4161c7342fce"
#define CHARACTERISTIC_UUID_ID    "cd77498f-1ac8-48b6-aba8-4161c7342fce"

#define SERVICE_UUID_OTA                    "86b12865-4b70-4893-8ce6-9864fc00374d"
#define CHARACTERISTIC_UUID_FW              "86b12866-4b70-4893-8ce6-9864fc00374d"
#define CHARACTERISTIC_UUID_HW_VERSION      "86b12867-4b70-4893-8ce6-9864fc00374d"
#define CHARACTERISTIC_UUID_WATCHFACE_NAME  "86b12868-4b70-4893-8ce6-9864fc00374d"

#define FULL_PACKET 512
#define CHARPOS_UPDATE_FLAG 5

#define STATUS_CONNECTED 0
#define STATUS_DISCONNECTED 4
#define STATUS_UPDATING 1
#define STATUS_READY 2

static bool doConnect = false;
static bool connected = false;
static bool doScan = false;

RTC_DATA_ATTR bool deviceConnected = false;

static BLERemoteCharacteristic* pRemoteCharacteristic;
static BLEAdvertisedDevice* myDevice;

esp_err_t errRc = ::esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_N12);

static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
  if (debugger) {
    Serial.print("Notify callback for characteristic ");
    Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
    Serial.print(" of data length ");
    Serial.println(length);
    Serial.print("data: ");
    Serial.println((char*)pData);
  }
}

class MyClientCallback : public BLEClientCallbacks {
    void onConnect(BLEClient* pclient) {
    }

    void onDisconnect(BLEClient* pclient) {
      connected = false;
      Serial.println("onDisconnect");
    }
};

bool connectToServer() {
  if (debugger) {
    Serial.print("Forming a connection to ");
    Serial.println(myDevice->getAddress().toString().c_str());
  }
  BLEClient*  pClient  = BLEDevice::createClient();
  if (debugger) {
    Serial.println(" - Created client");
  }
  pClient->setClientCallbacks(new MyClientCallback());

  // Connect to the remove BLE Server.
  pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
  if (debugger) {
    Serial.println(" - Connected to server");
  }
  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr) {
    if (debugger) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
    }
    pClient->disconnect();
    return false;
  }
  if (debugger) {
    Serial.println(" - Found our service");
  }

  // Obtain a reference to the characteristic in the service of the remote BLE server.
  pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
  if (pRemoteCharacteristic == nullptr) {
    if (debugger) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID.toString().c_str());
    }
    pClient->disconnect();
    return false;
  }
  if (debugger) {
    Serial.println(" - Found our characteristic");
  }

  // Read the value of the characteristic.
  if (pRemoteCharacteristic->canRead()) {
    std::string value = pRemoteCharacteristic->readValue();
    if (debugger) {
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }
  }

  if (pRemoteCharacteristic->canNotify())
    pRemoteCharacteristic->registerForNotify(notifyCallback);

  connected = true;
  deviceConnected = true;
  return true;
}

/**
   Scan for BLE servers and find the first one that advertises the service we are looking for.
*/
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    /**
        Called for each advertising BLE server.
    */
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      if (debugger) {
      Serial.print("BLE Advertised Device found: ");
      Serial.println(advertisedDevice.toString().c_str());
      }

      // We have found a device, let us now see if it contains the service we are looking for.
      if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {

        BLEDevice::getScan()->stop();
        myDevice = new BLEAdvertisedDevice(advertisedDevice);
        doConnect = true;
        doScan = true;

      } // Found our server
    } // onResult
}; // MyAdvertisedDeviceCallbacks



















#endif
