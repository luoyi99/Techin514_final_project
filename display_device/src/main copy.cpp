// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// #define SCREEN_WIDTH 128
// #define SCREEN_HEIGHT 32

// // Define variables for pins
// const int led = 8;
// const int switch_pin = 9; // Fixed variable name

// // Define OLED display pins
// #define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// #define OLED_ADDR1 0x3C
// #define OLED_ADDR2 0x3C
// Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_ADDR1);
// Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_ADDR2);


// void setup() {

//   Serial.begin(115200);
//   Serial.println("Starting BLE work!");
//   // Set LED pin as output
//   pinMode(led, OUTPUT); // Fixed pinMode function call
  
//   // Set switch pin as input
//   pinMode(switch_pin, INPUT); // Fixed pinMode function call

//     // Initialize displays
//   if(!display1.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR1)) {
//     Serial.println(F("SSD1306 allocation failed"));
//     for(;;);
//   }
//   display1.display();
//   delay(2000); // Pause for 2 seconds
  
//   if(!display2.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR2)) {
//     Serial.println(F("SSD1306 allocation failed"));
//     for(;;);
//   }
//   display2.display();
//   delay(2000); // Pause for 2 seconds
  
//   // Set LED pin as output
//   pinMode(led, OUTPUT);
  
//   // Set switch pin as input
//   pinMode(switch_pin, INPUT);

//   // Clear the buffer
//   display1.clearDisplay();
//   display2.clearDisplay();
// }

// void loop() {
//   // Read switch state
//   int switch_state = digitalRead(switch_pin); // Fixed variable name and digitalRead function call
//   Serial.println(switch_state); // Fixed serial.println function call
//   // Turn LED on or off depending on state
//   if (switch_state == HIGH) {
//     Serial.println("LED is on"); 

//       // Display messages on displays
//     display1.clearDisplay();
//     display1.setTextSize(1);
//     display1.setTextColor(SSD1306_WHITE);
//     display1.setCursor(0, 0);
//     display1.println("Display 1 Text");
//     display1.display();
    
//     // display2.clearDisplay();
//     // display2.setTextSize(1);
//     // display2.setTextColor(SSD1306_WHITE);
//     // display2.setCursor(0, 0);
//     // display2.println("Display 2 Text");
//     // display2.display();
  
//     // Fixed serial.println function call
//   } else {
//     Serial.println("LED is off"); // Fixed serial.println function call
//   }



// //   delay(1000); // Fixed delay function call
// // }

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


// #include <iostream>
// #include <sstream>
// #include <vector>
// #include <string>
// #include <cstdlib>

// struct JumpingJackData {
//   int total_jumps;
//   unsigned long time;
//   bool exerciseSessionStarted;
// };


// // Helper function to split a string by a delimiter
// std::vector<std::string> splitString(const std::string& str, char delimiter) {
//     std::vector<std::string> tokens;
//     std::string token;
//     std::istringstream tokenStream(str);

//     while (std::getline(tokenStream, token, delimiter)) {
//         tokens.push_back(token);
//     }

//     return tokens;
// }

// // OLED Screen -----------------------------------------------------------
// // -----------------------------------------------------------------------
// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels


// #define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
// Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// // Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// // #define MUX_ADDRESS 0x70 // I2C address of the TCA9548A

// // void selectOLED(uint8_t channel) {
// //   if (channel > 7) return; // The TCA9548A only has 8 channels (0-7)

// //   Wire.beginTransmission(MUX_ADDRESS);
// //   Wire.write(1 << channel); // Send command byte to select the channel
// //   Wire.endTransmission();
// // }
// // -----------------------------------------------------------------------


// // Stepper Motor Pin ---------------------------------------------------------
// #define stepperPin1 1
// #define stepperPin2 2
// #define stepperPin3 3
// #define stepperPin4 4

// // LED Pin-----------------------------------------------------------------------  
// const int ledPin = D9; // the number of the LED pin

// // BLE Client ------------------------------------------------------------
// // -----------------------------------------------------------------------
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

// // TODO: define a new function for data aggregation


// // Function to set the state of each pin
// void setStepperPins(int pin1, int pin2, int pin3, int pin4) {
//   digitalWrite(stepperPin1, pin1);
//   digitalWrite(stepperPin2, pin2);
//   digitalWrite(stepperPin3, pin3);
//   digitalWrite(stepperPin4, pin4);
// }

// // Basic full-step sequence
// void stepMotor(int step) {
//   switch(step) {
//     case 0:
//       setStepperPins(HIGH, LOW, LOW, LOW);
//       break;
//     case 1:
//       setStepperPins(LOW, HIGH, LOW, LOW);
//       break;
//     case 2:
//       setStepperPins(LOW, LOW, HIGH, LOW);
//       break;
//     case 3:
//       setStepperPins(LOW, LOW, LOW, HIGH);
//       break;
//   }
// }

// // Function to move the stepper a certain number of steps
// void moveStepper(int steps) {
//   for (int i = 0; i < steps; i++) {
//     stepMotor(i % 4);
//     // delay(100); // Adjust delay for speed
//   }
// }


// static void notifyCallback(
//   BLERemoteCharacteristic* pBLERemoteCharacteristic,
//   uint8_t* pData,
//   size_t length,
//   bool isNotify) {
//     // TODO: add codes to handle the data received from the server, and call the data aggregation function to process the data

//     // TODO: change the following code to customize your own data format for printing
//     // Serial.print("Notify callback for characteristic ");
//     // Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
//     // Serial.print(" of data length ");
//     // Serial.println(length);

//     // std::vector<std::string> massage = splitString(F(pdata), ',');

//     // Serial.print("data: ");
//     // Serial.write(pData, length);
//     // Serial.println();
//     // Serial.write(pData,length);
//     // Serial.println();
//     // Assuming `receivedData` is the byte array you received
//     JumpingJackData receivedSensorData;
//     memcpy(&receivedSensorData, pData, sizeof(JumpingJackData));

//     int totalJumps = receivedSensorData.total_jumps;
//     Serial.print("total jumps: ");
//     Serial.println(totalJumps);
//     Serial.print("time: ");
//     Serial.println(receivedSensorData.time);
//     Serial.print("exerciseSessionStarted: ");
//     Serial.println(receivedSensorData.exerciseSessionStarted);
//     // std::string receivedData(reinterpret_cast<char*>(pData), length);

//     // std::vector<std::string> messages = splitString(receivedData, ',');

//     // // Print each item in the vector one by one
//     // int totalJumps = std::stoi(messages[0]);
//     // int elapsedTime = std::stoi(messages[1]);
//     // int status = std::stoi(messages[2]);
//     // float elapsedTimeMinutes = elapsedTime / 60000.0; // 60000 milliseconds in a minute

//     // if (status == 1) {
//     //   digitalWrite(ledPin, HIGH);
//     // } else {
//     //   digitalWrite(ledPin, LOW);
//     // }

    
//     // int jumpingRate = static_cast<int>(totalJumps / elapsedTimeMinutes);
//     // Serial.println(totalJumps);

//     // // Serial.println(messages[0].c_str());
//     // // Serial.println(messages[1].c_str());
//     // Serial.println(elapsedTime);
//     // Serial.println(elapsedTimeMinutes);
//     // Serial.println(jumpingRate);

    
//     // display1.clearDisplay();
//     // display1.setTextSize(1);
//     // display1.setTextColor(SSD1306_WHITE);
//     // display1.setCursor(0,0);
//     // display1.println("Total Jumps:");
//     // display1.println();
//     // display1.setTextSize(4);
//     // display1.println(totalJumps);
//     // display1.display();

//     // int stepsToMove = map(jumpingRate, 35, 70, 0, 35);
//     // moveStepper(stepsToMove);

//     // Display the received data on screen2

//     // selectOLED(2); // Select channel 2 for the second OLED
//     // display1.clearDisplay();
//     // display1.setTextSize(1);
//     // display1.setTextColor(SSD1306_WHITE);
//     // display1.setCursor(0,0);
//     // display1.println(F("screen 2"));
//     // display1.println(F(pData));
//     // display1.display();
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

// // -----------------------------------------------------------------------

// // Function to set the motor's pins to one of the steps ---------------------------------------------------------
// // Define the sequence steps
// // int steps[4][4] = {
// //   {HIGH, LOW, LOW, LOW},
// //   {LOW, HIGH, LOW, LOW},
// //   {LOW, LOW, HIGH, LOW},
// //   {LOW, LOW, LOW, HIGH},
// // };

// // void setStep(int step) {
// //   digitalWrite(stepperPin1, steps[step][0]);
// //   digitalWrite(stepperPin2, steps[step][1]);
// //   digitalWrite(stepperPin3, steps[step][2]);
// //   digitalWrite(stepperPin4, steps[step][3]);
// // }


// // // Function to rotate the motor
// // void rotate(int stepsToMove, int delayTime) {
// //   for (int i = 0; i < stepsToMove; i++) {
// //     for (int step = 0; step < 4; step++) {
// //       setStep(step);
// //       delay(delayTime);
// //     }
// //   }
// // }


// // Setup function   ------------------------------------------------------
// // -----------------------------------------------------------------------
// void setup() {
//     Serial.begin(115200);
//     Wire.begin();

//     Serial.println("Starting Arduino BLE Client application...");
//     BLEDevice::init("");

//     // Retrieve a Scanner and set the callback we want to use to be informed when we
//     // have detected a new device.  Specify that we want active scanning and start the
//     // scan to run for 5 seconds.
//     BLEScan* pBLEScan = BLEDevice::getScan();
//     pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
//     pBLEScan->setInterval(1349);
//     pBLEScan->setWindow(449);
//     pBLEScan->setActiveScan(true);
//     pBLEScan->start(15, false);

//     // OLED Screen setup
//     // Initialize OLED on channel 0
//     // selectOLED(1); // Select channel 0 for the first OLED
//     if(!display1.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
//         Serial.println(F("SSD1306 allocation failed for display 1"));
//         for(;;); // Don't proceed, loop forever
//     }
//     display1.clearDisplay();
//     display1.setTextSize(2);
//     display1.setTextColor(SSD1306_WHITE);
//     display1.setCursor(0,0);
//     display1.println(F("Screen initializing"));
//     display1.display();
//     Serial.println("Screen 1 initialized");

//     pinMode(ledPin, OUTPUT);

//     // // Initialize OLED on channel 1
//     // selectOLED(2); // Select channel 1 for the second OLED
//     // if(!display2.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
//     //     Serial.println(F("SSD1306 allocation failed for display 2"));
//     //     for(;;); // Don't proceed, loop forever
//     // }
//     // display2.clearDisplay();
//     // display2.setTextSize(1);
//     // display2.setTextColor(SSD1306_WHITE);
//     // display2.setCursor(0,0);
//     // display2.println(F("Hi screen 2"));
//     // display2.display();

//     // Stepper Motor setup
//     pinMode(stepperPin1, OUTPUT);
//     pinMode(stepperPin2, OUTPUT);
//     pinMode(stepperPin3, OUTPUT);
//     pinMode(stepperPin4, OUTPUT);

// } // End of setup.

// // -----------------------------------------------------------------------


// // Loop function   -------------------------------------------------------
// // -----------------------------------------------------------------------
// // This is the Arduino main loop function.
// void loop() {
//   // If the flag "doConnect" is true then we have scanned for and found the desired
//   // BLE Server with which we wish to connect.  Now we connect to it.  Once we are
//   // connected we set the connected flag to be true.

//   // rotate(512, 10);
//   // Serial.println("Rotated 512 steps");

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
// } 

// // End of loop
// // -----------------------------------------------------------------------

