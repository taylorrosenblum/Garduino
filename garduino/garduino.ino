#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int motorPin = 3; // pin that turns on the motor
const int blinkPin = 13; // pin that turns on the LED
int watertime = 5; // how long it will be watering (in seconds)
int waittime = 1; // how long to wait between watering (in minutes)
int loop_count = 0; // loop count


void setup() {
  Serial.begin(115200);

  // display setup
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  // sensor and relay setup
  pinMode(motorPin, OUTPUT);
  pinMode(blinkPin, OUTPUT);
}

// Function to update the OLED display with loop counter
void updateDisplay(int counter, int moisture, bool motorState, bool ledState) {
  
  // clear display and set text params
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  // Value 1
  display.setCursor(0, 5);
  display.print("Loops: ");
  display.print(counter);
  display.println(" loops");

  // Value 2
  display.setCursor(0, 15);
  display.print("Moisture: ");
  display.print(moisture);
  display.println(" val");

  // Value 3
  display.setCursor(0, 25);
  display.print("Motor: ");
  display.print(motorState);

    // Value 3
  display.setCursor(0, 35);
  display.print("LED: ");
  display.print(ledState);
  
  // Update the display
  display.display(); 
}

void loop() {
  
  // COMMENT
  int moisturePin = analogRead(A0); //read analog value of moisture sensor
  int moisture = ( 100 - ( (moisturePin / 1023.00) * 100 ) ); //convert analog value to percentage
  Serial.println(moisture);
  if (moisture > 50) { //change the moisture threshold level based on your calibration values
    digitalWrite(motorPin, HIGH); // turn on the motor
    digitalWrite(blinkPin, HIGH); // turn on the LED
    //delay(watertime * 1000);      // multiply by 1000 to translate seconds to milliseconds
  }
  else {
    digitalWrite(motorPin, LOW);  // turn off the motor
    digitalWrite(blinkPin, LOW);  // turn off the LED
    delay(100);
    //delay(waittime * 60000);      // multiply by 60000 to translate minutes to milliseconds
  }

  bool motorState = digitalRead(motorPin);
  bool ledState = digitalRead(blinkPin);
  
  // Increment the loop counter
  loop_count++;
  updateDisplay(loop_count, moisture, motorState, ledState);
  delay(100);
}