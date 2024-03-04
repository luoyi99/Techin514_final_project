// #include <Arduino.h>
// #include <BLEDevice.h>
// #include <BLEUtils.h>
// #include <BLEScan.h>
// #include <BLEAdvertisedDevice.h>
// // Client Code
// #include "BLEDevice.h"
// //#include "BLEScan.h"

// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>


// // Define variables for pins
// const int led = 8;
// const int switch_pin = 9; // Fixed variable name


// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 64

// // Define OLED display pins
// #define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// #define OLED_ADDR1 0x3C
// #define OLED_ADDR2 0x3C
// Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_ADDR1);
// Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_ADDR2);



// // TODO: change the service UUID to the one you are using on the server side.

// // The remote service we wish to connect to.
// static BLEUUID serviceUUID("014805bf-7587-47e5-8965-b11fef29d012");
// // The characteristic of the remote service we are interested in.
// static BLEUUID    charUUID("47b36193-f67b-4a77-ad27-0cafb5dd7a91");


// static boolean doConnect = false;
// static boolean connected = false;
// static boolean doScan = false;
// static BLERemoteCharacteristic* pRemoteCharacteristic;
// static BLEAdvertisedDevice* myDevice;

// // TODO: define new global variables for data collection

// struct JumpingJackData {
//   int total_jumps;
//   unsigned long time;
//   bool exerciseSessionStarted;
// };


// // TODO: define a new function for data aggregation

// static void notifyCallback(
//   BLERemoteCharacteristic* pBLERemoteCharacteristic,
//   uint8_t* pData,
//   size_t length,
//   bool isNotify) {
//     // TODO: add codes to handle the data received from the server, and call the data aggregation function to process the data
//     JumpingJackData receivedSensorData;
//     memcpy(&receivedSensorData, pData, sizeof(JumpingJackData));

//     int totalJumps = receivedSensorData.total_jumps;
//     Serial.print("total jumps: ");
//     Serial.println(totalJumps);
//     Serial.print("time: ");
//     Serial.println(receivedSensorData.time);
//     Serial.print("exerciseSessionStarted: ");
//     Serial.println(receivedSensorData.exerciseSessionStarted);

//     display1.clearDisplay();
//     display1.setTextSize(1);
//     display1.setTextColor(SSD1306_WHITE);
//     display1.setCursor(0,0);
//     display1.println("Total Jumps:");
//     display1.println();
//     display1.setTextSize(4);
//     display1.println(totalJumps);
//     display1.display();


    
    
// }

// class MyClientCallback : public BLEClientCallbacks {
//   void onConnect(BLEClient* pclient) {
//   }

//   void onDisconnect(BLEClient* pclient) {
//     connected = false;
//     Serial.println("onDisconnect");
//   }
// };

// bool connectToServer() {
//     Serial.print("Forming a connection to ");
//     Serial.println(myDevice->getAddress().toString().c_str());

//     BLEClient*  pClient  = BLEDevice::createClient();
//     Serial.println(" - Created client");

//     pClient->setClientCallbacks(new MyClientCallback());

//     // Connect to the remove BLE Server.
//     pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
//     Serial.println(" - Connected to server");
//     pClient->setMTU(517); //set client to request maximum MTU from server (default is 23 otherwise)

//     // Obtain a reference to the service we are after in the remote BLE server.
//     BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
//     if (pRemoteService == nullptr) {
//       Serial.print("Failed to find our service UUID: ");
//       Serial.println(serviceUUID.toString().c_str());
//       pClient->disconnect();
//       return false;
//     }
//     Serial.println(" - Found our service");

//     // Obtain a reference to the characteristic in the service of the remote BLE server.
//     pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
//     if (pRemoteCharacteristic == nullptr) {
//       Serial.print("Failed to find our characteristic UUID: ");
//       Serial.println(charUUID.toString().c_str());
//       pClient->disconnect();
//       return false;
//     }
//     Serial.println(" - Found our characteristic");

//     // Read the value of the characteristic.
//     if(pRemoteCharacteristic->canRead()) {
//       std::string value = pRemoteCharacteristic->readValue();
//       Serial.print("The characteristic value was: ");
//       Serial.println(value.c_str());
//     }

//     if(pRemoteCharacteristic->canNotify())
//       pRemoteCharacteristic->registerForNotify(notifyCallback);

//     connected = true;
//     return true;
// }
// /**
//  * Scan for BLE servers and find the first one that advertises the service we are looking for.
//  */
// class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
//   /**
//    * Called for each advertising BLE server.
//    */
//   void onResult(BLEAdvertisedDevice advertisedDevice) {
//     Serial.print("BLE Advertised Device found: ");
//     Serial.println(advertisedDevice.toString().c_str());

//     // We have found a device, let us now see if it contains the service we are looking for.
//     if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {

//       BLEDevice::getScan()->stop();
//       myDevice = new BLEAdvertisedDevice(advertisedDevice);
//       doConnect = true;
//       doScan = true;

//     } // Found our server
//   } // onResult
// }; // MyAdvertisedDeviceCallbacks

// void setup() {
//   Serial.begin(115200);
//   Serial.println("Starting Arduino BLE Client application...");
//   BLEDevice::init("");

//   // Retrieve a Scanner and set the callback we want to use to be informed when we
//   // have detected a new device.  Specify that we want active scanning and start the
//   // scan to run for 5 seconds.
//   BLEScan* pBLEScan = BLEDevice::getScan();
//   pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
//   pBLEScan->setInterval(1349);
//   pBLEScan->setWindow(449);
//   pBLEScan->setActiveScan(true);
//   pBLEScan->start(5, false);

//   if(!display1.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
//         Serial.println(F("SSD1306 allocation failed for display 1"));
//         for(;;); // Don't proceed, loop forever
//     }

//   display1.clearDisplay();
//   display1.setTextSize(2);
//   display1.setTextColor(SSD1306_WHITE);
//   display1.setCursor(0,0);
//   display1.println(F("Screen initializing"));
//   display1.display();
//   Serial.println("Screen 1 initialized");
// } // End of setup.

// // This is the Arduino main loop function.
// void loop() {
//   // If the flag "doConnect" is true then we have scanned for and found the desired
//   // BLE Server with which we wish to connect.  Now we connect to it.  Once we are
//   // connected we set the connected flag to be true.
//   if (doConnect == true) {
//     if (connectToServer()) {
//       Serial.println("We are now connected to the BLE Server.");
//     } else {
//       Serial.println("We have failed to connect to the server; there is nothin more we will do.");
//     }
//     doConnect = false;
//   }
 
//   // If we are connected to a peer BLE Server, update the characteristic each time we are reached
//   // with the current time since boot.
//   if (connected) {
//     String newValue = "Time since boot: " + String(millis()/1000);
//     Serial.println("Setting new characteristic value to \"" + newValue  + "\"");

//     // Set the characteristic's value to be the array of bytes that is actually a string.
//     pRemoteCharacteristic->writeValue(newValue.c_str(), newValue.length());
//   }else if(doScan){
//     BLEDevice::getScan()->start(0);  // this is just example to start scan after disconnect, most likely there is better way to do it in arduino
//   }

//   delay(500); // Delay a second between loops.
// } // End of loop


#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
// Client Code
#include "BLEDevice.h"
//#include "BLEScan.h"


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Stepper.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>

struct JumpingJackData {
  int total_jumps;
  unsigned long time;
  bool exerciseSessionStarted;
};


// OLED Screen -----------------------------------------------------------
// -----------------------------------------------------------------------
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// -----------------------------------------------------------------------


// Stepper Motor Pin ---------------------------------------------------------
#define stepperPin1 1
#define stepperPin2 2
#define stepperPin3 3
#define stepperPin4 4
const int stepsPerRevolution = 70; 
Stepper myStepper(stepsPerRevolution , stepperPin1, stepperPin2, stepperPin3, stepperPin4);
const int maxRate = 70; // 70 jumps per minute
const int minRate = 0; // 0 jumps per minute

// LED Pin-----------------------------------------------------------------------  
const int ledPin = D9; // the number of the LED pin

// BLE Client ------------------------------------------------------------
// -----------------------------------------------------------------------
// The remote service we wish to connect to.
static BLEUUID serviceUUID("014805bf-7587-47e5-8965-b11fef29d012");
// The characteristic of the remote service we are interested in.
static BLEUUID    charUUID("47b36193-f67b-4a77-ad27-0cafb5dd7a91");

static boolean doConnect = false;
static boolean connected = false;
static boolean doScan = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;
static BLEAdvertisedDevice* myDevice;


static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
\
    JumpingJackData receivedSensorData;
    memcpy(&receivedSensorData, pData, sizeof(JumpingJackData));

    int totalJumps = receivedSensorData.total_jumps;
    float elapsedTime = receivedSensorData.time / 60000.0; // 60000 milliseconds in a minute


    if (receivedSensorData.exerciseSessionStarted == 1) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }

    
    int jumpingRate = static_cast<int>(totalJumps / elapsedTime);
    Serial.print("total jumps: ");
    Serial.println(totalJumps);
    Serial.print("time: ");
    Serial.println(elapsedTime);
    Serial.print("jumping rate: ");
    Serial.println(jumpingRate);
    Serial.print("exerciseSessionStarted: ");
    Serial.println(receivedSensorData.exerciseSessionStarted);

    
    display1.clearDisplay();
    display1.setTextSize(1);
    display1.setTextColor(SSD1306_WHITE);
    display1.setCursor(0,0);
    display1.println("Total Jumps:");
    display1.println();
    display1.setTextSize(4);
    display1.println(totalJumps);
    display1.display();

    // int stepsToMove = map(jumpingRate, minRate, maxRate, 0, stepsPerRevolution);
    // static int lastPosition = 0;
    // int moveSteps = stepsToMove - lastPosition;
    // myStepper.step(moveSteps);
    // lastPosition = stepsToMove;

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
    Serial.print("Forming a connection to ");
    Serial.println(myDevice->getAddress().toString().c_str());

    BLEClient*  pClient  = BLEDevice::createClient();
    Serial.println(" - Created client");

    pClient->setClientCallbacks(new MyClientCallback());

    // Connect to the remove BLE Server.
    pClient->connect(myDevice);  // if you pass BLEAdvertisedDevice instead of address, it will be recognized type of peer device address (public or private)
    Serial.println(" - Connected to server");
    pClient->setMTU(517); //set client to request maximum MTU from server (default is 23 otherwise)

    // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
    if (pRemoteService == nullptr) {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceUUID.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our service");

    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
    if (pRemoteCharacteristic == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charUUID.toString().c_str());
      pClient->disconnect();
      return false;
    }
    Serial.println(" - Found our characteristic");

    // Read the value of the characteristic.
    if(pRemoteCharacteristic->canRead()) {
      std::string value = pRemoteCharacteristic->readValue();
      Serial.print("The characteristic value was: ");
      Serial.println(value.c_str());
    }

    if(pRemoteCharacteristic->canNotify())
      pRemoteCharacteristic->registerForNotify(notifyCallback);

    connected = true;
    return true;
}
/**
 * Scan for BLE servers and find the first one that advertises the service we are looking for.
 */
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  /**
   * Called for each advertising BLE server.
   */
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    Serial.print("BLE Advertised Device found: ");
    Serial.println(advertisedDevice.toString().c_str());

    // We have found a device, let us now see if it contains the service we are looking for.
    if (advertisedDevice.haveServiceUUID() && advertisedDevice.isAdvertisingService(serviceUUID)) {

      BLEDevice::getScan()->stop();
      myDevice = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
      doScan = true;

    } // Found our server
  } // onResult
}; // MyAdvertisedDeviceCallbacks

// -----------------------------------------------------------------------


// Setup function   ------------------------------------------------------
// -----------------------------------------------------------------------
void setup() {
    Serial.begin(115200);
    Wire.begin();

    Serial.println("Starting Arduino BLE Client application...");
    BLEDevice::init("");

    // Retrieve a Scanner and set the callback we want to use to be informed when we
    // have detected a new device.  Specify that we want active scanning and start the
    // scan to run for 5 seconds.
    BLEScan* pBLEScan = BLEDevice::getScan();
    pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
    pBLEScan->setInterval(1349);
    pBLEScan->setWindow(449);
    pBLEScan->setActiveScan(true);
    pBLEScan->start(15, false);

    // OLED Screen setup
    if(!display1.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed for display 1"));
        for(;;); // Don't proceed, loop forever
    }
    display1.clearDisplay();
    display1.setTextSize(2);
    display1.setTextColor(SSD1306_WHITE);
    display1.setCursor(0,0);
    display1.println(F("Screen initializing"));
    display1.display();
    Serial.println("Screen 1 initialized");

    pinMode(ledPin, OUTPUT);


    // Stepper Motor setup
    myStepper.setSpeed(70);

} // End of setup.

// -----------------------------------------------------------------------


// Loop function   -------------------------------------------------------
// -----------------------------------------------------------------------
// This is the Arduino main loop function.
void loop() {
  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are
  // connected we set the connected flag to be true.

  // rotate(512, 10);
  // Serial.println("Rotated 512 steps");

  if (doConnect == true) {
    if (connectToServer()) {
      Serial.println("We are now connected to the BLE Server.");
    } else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
    }
    doConnect = false;
  }
 
  // If we are connected to a peer BLE Server, update the characteristic each time we are reached
  // with the current time since boot.
  if (connected) {
    myStepper.step(300);
    delay(500);
    myStepper.step(-300);
    delay(500);
    String newValue = "Time since boot: " + String(millis()/1000);
    Serial.println("Setting new characteristic value to \"" + newValue  + "\"");

    // Set the characteristic's value to be the array of bytes that is actually a string.
    pRemoteCharacteristic->writeValue(newValue.c_str(), newValue.length());
  }else if(doScan){
    BLEDevice::getScan()->start(0);  // this is just example to start scan after disconnect, most likely there is better way to do it in arduino
  }

  delay(500); // Delay a second between loops.
} 

// End of loop
// -----------------------------------------------------------------------

