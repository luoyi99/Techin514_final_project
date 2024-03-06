#include <Adafruit_MPU6050.h>
#include <Wire.h>

// Bluetooth
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <stdlib.h>

#include <iostream> 


//  Variables
const int PushButtonPin = D8; // Push button connected to digital pin 8
bool exerciseSessionStarted = true;

// Jumping jacks data
bool isJumping = false;
float lastAccZ = 0;
int total_jumps = 0;
int valid_jumps = 0;
String message = "";

// MPU6050 sensor
Adafruit_MPU6050 mpu;


// BLE
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
unsigned long previousMillis = 0;
const long interval = 500;

// Time interval
unsigned long startTime;
unsigned long currentTime;

struct JumpingJackData {
  int total_jumps;
  unsigned long time;
  bool exerciseSessionStarted;
};




#define SERVICE_UUID        "014805bf-7587-47e5-8965-b11fef29d012"
#define CHARACTERISTIC_UUID "47b36193-f67b-4a77-ad27-0cafb5dd7a91"

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
        deviceConnected = false;
    }
};

// Function to count the number of jumping jacks
void processSensorData(sensors_event_t a, float threshold) {
    // If there's a significant positive change in acceleration, we might be starting a jump
    float accX = a.acceleration.x;
    float accY = a.acceleration.y;
    float accZ = a.acceleration.z;
    Serial.print(lastAccZ);
    Serial.print(" ");
    Serial.println(accZ);

    if (accZ - lastAccZ > threshold && !isJumping) {
        isJumping = true;
    }
    // If we're in a jump and there's a significant negative change, the jump is ending
    else if (isJumping && lastAccZ - accZ > threshold) {
        isJumping = false; // Reset jump state
        total_jumps++;       // Increment the jump count
        std::cout << "Jumping Jacks Count: " << total_jumps << std::endl;
    }

    // Update the last acceleration value for the next call
    lastAccZ = accZ;

}




void setup() {   

  Serial.begin(115200);          // For Serial Monitor
  

  pinMode(PushButtonPin, INPUT_PULLUP);  // Initialize the push button pin as an input with internal pull-up resistor


  // MPU6050 sensor
  // while (!Serial)
  //   delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }


  // BLE
  Serial.println("Starting BLE work!");

  // TODO: name your device to avoid conflictions
  BLEDevice::init("Yi_L_XIAO_ESP32S3");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE |
      BLECharacteristic::PROPERTY_NOTIFY
  );
  pCharacteristic->addDescriptor(new BLE2902());
  pCharacteristic->setValue("Connected");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");

  startTime = millis();



}



void loop() {


  bool pushButtonState = digitalRead(PushButtonPin);  // Read the state of the push button
  // Serial.print(pushButtonState);

  // If the push button is pressed, change the exercise session state. 
  // If the exercise session has started, stop it. If it hasn't started, start it.
  if (pushButtonState  == 01 ) {
    if (exerciseSessionStarted){
      Serial.println("Exercise session stopped");
      exerciseSessionStarted = false;
    }
    else {
      Serial.println("Exercise session started");
      exerciseSessionStarted = true;
      startTime = millis();
      total_jumps = 0;
      valid_jumps = 0;
      lastAccZ = 0;
    }
  } 

  // If the exercise session has started, process jumping jacks data
  if (exerciseSessionStarted){
    // if(mpu.getMotionInterruptStatus()) {
      /* Get new sensor events with the readings */
      currentTime = millis();
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);

      /* Print out the values */
      processSensorData(a, 12);
    

  } 

  if (deviceConnected) {
      // Send new readings to database
      // TODO: change the following code to send your own readings and processed data
     
      JumpingJackData data = {total_jumps, currentTime - startTime, exerciseSessionStarted};
      Serial.println(total_jumps);
      Serial.println(data.total_jumps);
      Serial.println(data.time);
      Serial.println(data.exerciseSessionStarted);

      uint8_t message[sizeof(JumpingJackData)];
      memcpy(message, &data, sizeof(JumpingJackData));
      
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
      pCharacteristic->setValue(message, sizeof(JumpingJackData));
      pCharacteristic->notify();
      Serial.print("Notify value: ");
      Serial.println(data.total_jumps);
      previousMillis = currentMillis;
      }
  }
  // disconnecting
  if (!deviceConnected && oldDeviceConnected) {
      delay(500);  // give the bluetooth stack the chance to get things ready
      pServer->startAdvertising();  // advertise again
      Serial.println("Start advertising");
      oldDeviceConnected = deviceConnected;
  }
  // connecting
  if (deviceConnected && !oldDeviceConnected) {
      // do stuff here on connecting
      oldDeviceConnected = deviceConnected;
  }

  delay(200);                    // considered best practice in a simple sketch.

}
