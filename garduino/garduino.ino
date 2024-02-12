#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int motorPin = 3; // pin that turns on the motor
int blinkPin = 13; // pin that turns on the LED
int watertime = 5; // how long it will be watering (in seconds)
int waittime = 1; // how long to wait between watering (in minutes)
int loop_count = 0; // loop count


void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
}

// Function to update the OLED display with loop counter
void updateDisplay(int counter) {
  
  // clear display and set text params
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // Value 1
  display.setCursor(0, 5);
  display.print("Row 1: ");
  display.print(counter);
  display.println(" loops");

  // Value 2
  display.setCursor(0, 15);
  display.print("Row 2: ");
  display.print(counter);
  display.println(" loops");

  // Value 3
  display.setCursor(0, 25);
  display.print("Row 3: ");
  display.print(counter);
  display.println(" loops");
  
  // Update the display
  display.display(); 
}

void loop() {
  // Increment the loop counter
  loop_count++;
  updateDisplay(loop_count);
  delay(100);
}