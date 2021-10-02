#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

// The remote service we wish to connect to.
static BLEUUID serviceUUID((uint16_t)0x1101);
int scanTime = 5; //In seconds
BLEScan* pBLEScan;

class PeripheralDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      if (advertisedDevice.haveServiceUUID() && advertisedDevice.getServiceUUID().equals(serviceUUID)) {
        Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
        Serial.println("Found our device - Stop scanning!"); 
        advertisedDevice.getScan()->stop();
      } // Found our server
    }
};

void scanTask(void *pvParam)
{
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new PeripheralDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value

  while(true)
  {
    // put your main code here, to run repeatedly:
    BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
    Serial.print("Devices found: ");
    Serial.println(foundDevices.getCount());
    Serial.println("Scan done!");
    pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
    delay(5000);
  }
}

static void halt(const char *msg)
{
    Serial.println(msg);
    Serial.flush();

    esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");

  if (xTaskCreate(scanTask, "scanner", 4096, NULL, 1, NULL) != pdPASS)
    halt("Error creating scan task!");
}

void loop() {
  delay(1000);
}