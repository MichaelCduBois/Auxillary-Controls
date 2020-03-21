// Michael duBois
// 2020-03-10
#include <Joystick.h>

// First pin connected
const int startPin = 0;

// How many buttons for the controller
const int buttonCount = 10;
const int resetPin = 10;

// Initialize the button state
int lastButtonState[buttonCount] = {};

// Setup button types and associated PINS
int manualButton[0] = {}; // Buttons in a constant state
int toggleButton[0] = {}; // Buttons treated as a toggle
int holdButton[0] = {}; // Buttons held for defined duration
int resetButton[0] = {}; // Button that does not allow joystick commands to be sent

// Duration in Seconds
const int toggleDuration = 50;
const int holdDuration = 1000;

// Create the Joystick
Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID, // Reports Joystick HID
  JOYSTICK_TYPE_JOYSTICK, // Joystick Type
  buttonCount, // Number of Buttons
  0, // Number of Hat Switches
  false, // X-Axis Available
  false, // Y-Axis Available
  false, // Z-Axis Available
  false, // X-Rotational-Axis Available
  false, // Y-Rotational-Axis Available
  false, // Z-Rotational-Axis Available
  false, // Rudder Available
  false, // Throttle Available
  false, // Accelerator Available
  false, // Break Available
  false // Steering Available
);

void setup() {
  // Sets Used Pins to INPUT_PULLUP
  for (int index = 0; index < buttonCount; index++) {
    pinMode(index, INPUT_PULLUP);
  }

  // INPUT_PULLUP to reset pin
  pinMode(resetPin, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
}



void loop() {
  for (int index = 0; index < buttonCount; index++) {
    int currentButtonState = !digitalRead(index + startPin);
    if (currentButtonState != lastButtonState[index]) {
      if (digitalRead(resetPin)) {
        // If toggleButton switch
        for (int pin = 0; pin < sizeof(toggleButton) / sizeof(toggleButton[0]); pin++) {
          if (index == toggleButton[pin]) {
            Joystick.pressButton(index);
            delay(toggleDuration);
            Joystick.releaseButton(index);
          }
        }
        // If holdButton switch
        for (int pin = 0; pin < sizeof(holdButton) / sizeof(holdButton[0]); pin++) {
          if (index == holdButton[pin]) {
            Joystick.pressButton(index);
            delay(holdDuration);
            Joystick.releaseButton(index);
          }
        }
        // If manualButton switch
        for (int pin = 0; pin < sizeof(manualButton) / sizeof(manualButton[0]); pin++) {
          if (index == manualButton[pin]) {
            Joystick.setButton(index, currentButtonState);
          }
        }
      }
      lastButtonState[index] = currentButtonState;
    }
  }

  // // Reads the value of pin A0 -- Range 0 - 1023
  // int sensorValue = analogRead(A0);
  // // Inverts value of pin A0 to change direction mapping range from 0-1023 as 100 - 0
  // // int sensorValue = map(analogRead(A0), 0, 1023, 100, 0);
  // // Sets throttle to value
  // Joystick.setZAxis(sensorValue);
  // Serial.println(sensorValue);

  delay(50);
}
