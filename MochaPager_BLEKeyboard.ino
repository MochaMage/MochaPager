/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("MochaPager", "Audio Mocha", 69);
int leftPin = 4;
int rightPin = 22;
int isLeftPressed = false;
int isRightPressed = false;

void setup() {
  bleKeyboard.begin();
  Serial.begin(115200);
  Serial.println("Bluetooth engaged");
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
}

void loop() {
  if(bleKeyboard.isConnected()) {
    int leftState = digitalRead(leftPin);
    int rightState = digitalRead(rightPin);

    if (!rightState && leftState == HIGH && !isLeftPressed){
      isLeftPressed = true;
      bleKeyboard.write(KEY_LEFT_ARROW);
      Serial.println("Left Button pressed");
    } else if (leftState == LOW && isLeftPressed) {
      isLeftPressed = false;
      Serial.println("Left Button released");
    }

    if (!leftState && rightState == HIGH && !isRightPressed){
      isRightPressed = true;
      bleKeyboard.write(KEY_RIGHT_ARROW);
      Serial.println("Right Button pressed");
    } else if (rightState == LOW && isRightPressed) {
      isRightPressed = false;
      Serial.println("Right Button released");
    }

    delay(50);
  }
}
