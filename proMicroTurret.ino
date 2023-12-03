#include <Servo.h>

Servo myServoBottom;
Servo myServoTop;

// constants won't change
const int solenoidPin = 2;  // the Arduino pin, which connects to the IN pin of relay
const int buttonPin = 3;
const int flyWheelPin = 6;
const int potenPin = A0;
const int xPin = A1;
const int yPin = A2;
const int togglePin = 4;


int potenRaw = 0;
int potenMappedValue = 0;
int joyX = 0;
int joyY = 0;
int posX = 0;
int posY = 0;
int toggleSwitchState = HIGH;


// the setup function runs once when you press reset or power the board
void setup() {

  myServoBottom.attach(5);
  myServoTop.attach(9);

  // initialize digital pin as an output.
  pinMode(solenoidPin, OUTPUT);
  pinMode(flyWheelPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(potenPin, INPUT);
  pinMode(togglePin, INPUT);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);


  Serial.begin(9600);

}


void switchAndMotorPower() {  // if switch is off, don't power motor

  //  toggleSwitchState = digitalRead(togglePin);
  //  if (toggleSwitchState == HIGH) {
  //    Serial.println("The switch: OFF");
  //    analogWrite(flyWheelPin, 0);
  //  }
  //  else {
  //    Serial.println("The switch: ON");
  //    potenRaw = analogRead(potenPin);
  //    potenMappedValue = map(potenRaw, 0, 1023, 0, 255);
  //    Serial.println(potenMappedValue);
  //    analogWrite(flyWheelPin, potenMappedValue);
  //  }
  potenRaw = analogRead(potenPin);
  potenMappedValue = map(potenRaw, 0, 1023, 0, 255);
  Serial.println(potenMappedValue);
  analogWrite(flyWheelPin, potenMappedValue);

}


void servoControl() {

  joyX = analogRead(xPin);
  joyY = analogRead(yPin);

  int joyYRangeShrink = map(joyX, 0, 1023, 30, 150);
  int joyXRangeShrink = map(joyY, 0, 1023, 90, 110) ;

  myServoBottom.write(joyYRangeShrink);
  myServoTop.write(joyXRangeShrink);

  delay(15);

  Serial.println(joyXRangeShrink, joyYRangeShrink);

}


void solenoidControl() {
  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(solenoidPin, HIGH);
  } else {
    digitalWrite(solenoidPin, LOW);
  }

}


// the loop function runs over and over again forever
void loop() {

  switchAndMotorPower();
  servoControl();
  solenoidControl();



  //  myServoBottom.write(posX);
  //  myServoTop.write(posY);
  //Serial.println(posX);


}
