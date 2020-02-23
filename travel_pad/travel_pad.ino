#include <Keyboard.h>

float leftSum = 0;
float downSum = 0;
float upSum = 0;
float rightSum = 0;
float leftThreshold, downThreshold, upThreshold, rightThreshold;

const byte leftPin = A0;
const byte downPin = A3;
const byte upPin = A1;
const byte rightPin = A2;
const byte leftLight = 12;
const byte downLight = 11;
const byte upLight = 10;
const byte rightLight = 9;

void setup() {
  Serial.begin(9600);
  pinMode(leftPin,INPUT);
  pinMode(downPin,INPUT);
  pinMode(upPin,INPUT);
  pinMode(rightPin,INPUT);
  pinMode(leftLight, OUTPUT);
  pinMode(downLight, OUTPUT);
  pinMode(upLight, OUTPUT);
  pinMode(rightLight, OUTPUT);
  Keyboard.begin();
//  digitalWrite(13, LOW);

  delay(1000);
  for (int i = 0; i < 1000; i++){
    leftSum += analogRead(leftPin) * (3.3 / 1023.0);
    downSum += analogRead(downPin) * (3.3 / 1023.0);
    upSum += analogRead(upPin) * (3.3 / 1023.0);
    rightSum += analogRead(rightPin) * (3.3 / 1023.0);
  }
  leftThreshold = leftSum/1000.0 + 1;
  downThreshold = downSum/1000.0 + 1;
  upThreshold = upSum/1000.0 + 1;
  rightThreshold = rightSum/1000.0 + 1;
}

bool leftHeld = false;
bool downHeld = false;
bool upHeld = false;
bool rightHeld = false;

void loop() {
  float left = analogRead(leftPin) * (3.3 / 1023.0);
  float down = analogRead(downPin) * (3.3 / 1023.0);
  float up = analogRead(upPin) * (3.3 / 1023.0);
  float right = analogRead(rightPin) * (3.3 / 1023.0);  

//  Serial.println(leftThreshold);
//  Serial.println(downThreshold);
//  Serial.println(upThreshold);
//  Serial.println(rightThreshold);
  Serial.println(left);
  Serial.println(down);
  Serial.println(up);
  Serial.println(right);
//  delay(1000);
//  Serial.println(down);
// to do: write some auto-calibration

  if (leftHeld) {
    if (left < leftThreshold){ // was 1.2
      Keyboard.release(216);
      leftHeld = false;
      Serial.println("left release");
      digitalWrite(leftLight, LOW);
    }
  } else if (left > leftThreshold){
    leftHeld = true;
    Keyboard.press(216);
    Serial.println("left");
    digitalWrite(leftLight, HIGH);
  }

  if (downHeld) {
    if (down < downThreshold){ // was 1.55
      Keyboard.release(217);
      downHeld = false;
      Serial.println("down release");
      digitalWrite(downLight, LOW);
    }
  } else if (down > downThreshold){
    downHeld = true;
    Keyboard.press(217);
    Serial.println("down");
    digitalWrite(downLight, HIGH);
  }
  
  if (upHeld) {
    if (up < upThreshold){ // was 1.0
      Keyboard.release(218);
      upHeld = false;
      Serial.println("up release");
      digitalWrite(upLight, LOW);
    }
  } else if (up > upThreshold){
    upHeld = true;
    Keyboard.press(218);
    Serial.println("up");
    digitalWrite(upLight, HIGH);
  }

  if (rightHeld) {
    if (right < rightThreshold){ // was 1.13
      Keyboard.release(215);
      rightHeld = false;
      Serial.println("right release");
      digitalWrite(rightLight, LOW);
    }
  } else if (right > rightThreshold){
    rightHeld = true;
    Keyboard.press(215);
    Serial.println("right");
    digitalWrite(rightLight, HIGH);
  }

  delay(5);
}
