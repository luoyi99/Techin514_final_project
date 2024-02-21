#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// Define variables for pins
const int led = 8;
const int switch_pin = 9; // Fixed variable name

// Define OLED display pins
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_ADDR1 0x3C
#define OLED_ADDR2 0x3C
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_ADDR1);
Adafruit_SSD1306 display2(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_ADDR2);


void setup() {

  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  // Set LED pin as output
  pinMode(led, OUTPUT); // Fixed pinMode function call
  
  // Set switch pin as input
  pinMode(switch_pin, INPUT); // Fixed pinMode function call

    // Initialize displays
  if(!display1.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR1)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display1.display();
  delay(2000); // Pause for 2 seconds
  
  if(!display2.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR2)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display2.display();
  delay(2000); // Pause for 2 seconds
  
  // Set LED pin as output
  pinMode(led, OUTPUT);
  
  // Set switch pin as input
  pinMode(switch_pin, INPUT);

  // Clear the buffer
  display1.clearDisplay();
  display2.clearDisplay();
}

void loop() {
  // Read switch state
  int switch_state = digitalRead(switch_pin); // Fixed variable name and digitalRead function call
  Serial.println(switch_state); // Fixed serial.println function call
  // Turn LED on or off depending on state
  if (switch_state == HIGH) {
    Serial.println("LED is on"); 

      // Display messages on displays
    display1.clearDisplay();
    display1.setTextSize(1);
    display1.setTextColor(SSD1306_WHITE);
    display1.setCursor(0, 0);
    display1.println("Display 1 Text");
    display1.display();
    
    // display2.clearDisplay();
    // display2.setTextSize(1);
    // display2.setTextColor(SSD1306_WHITE);
    // display2.setCursor(0, 0);
    // display2.println("Display 2 Text");
    // display2.display();
  
    // Fixed serial.println function call
  } else {
    Serial.println("LED is off"); // Fixed serial.println function call
  }



  delay(1000); // Fixed delay function call
}
