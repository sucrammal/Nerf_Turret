#include <IRremote.h>  //including infrared remote header file     
#include <Servo.h>

Servo myServoBottom;
Servo myServoTop;
IRrecv IR(3);

const int solenoidPin = 2;
const int flyWheelPin = 6;

// these two values are the servo positions.
int bottomPos = 90;
int topPos = 100;

int flyWheelPower = 0;
String buttonInput = "";
boolean toggle = true;

void setup() {
  myServoBottom.attach(5);
  myServoTop.attach(9);

  IR.enableIRIn();

  pinMode(solenoidPin, OUTPUT);
  pinMode(flyWheelPin, OUTPUT);



  Serial.begin(9600);


}

void DecodeIRSignal() {
  if (IR.decode()) { // returns true if received signal.
    //Serial.println(IR.decodedIRData.decodedRawData, HEX);
    switch (IR.decodedIRData.decodedRawData) {
      case 0xBA45FF00:
        buttonInput = "Safety";
        break;
      case 0xBB44FF00:
        buttonInput = "Left";
        break;
      case 0xBF40FF00:
        buttonInput = "Right";
        break;
      case 0xBC43FF00:
        buttonInput = "Shoot";
        break ;
      case 0xF807FF00:
        buttonInput = "Up";
        break;
      case 0xE718FF00:
        buttonInput = "Power1";
        break;
      case 0xA15EFF00:
        buttonInput = "Power2" ;
        break;
      case 0xEA15FF00:
        buttonInput = "Down";
        break;
      case 0xF30CFF00:
        buttonInput = "Power0";
        break;
      case 0xF708FF00:
        buttonInput = "PowerMax";
        break;
      default:
        Serial.println("INVALID");
        break;
    }
    Serial.println(buttonInput);
    delay(20);
    IR.resume();
  }
}


void TopServoMovement() {
  if ((buttonInput.equals("Up")) && (topPos < 115)) {
    topPos = topPos + 10;
  } else if ((buttonInput.equals("Down")) && (topPos > 70)) {
    topPos = topPos - 10;
  }
  myServoTop.write(topPos);


}

void BottomServoMovement() {
  if ((buttonInput.equals("Left")) && (bottomPos > 0)) {
    bottomPos = bottomPos - 10;
  } else if ((buttonInput.equals("Right")) && (bottomPos < 180)) {
    bottomPos = bottomPos + 10;
  }
  myServoBottom.write(bottomPos);

}

void flywheelControl() {
  if (buttonInput.equals("Power0")) {
    flyWheelPower = 0;
  } else if (buttonInput.equals("Power1")) {
    flyWheelPower = HIGH;
  } else if (buttonInput.equals("Power2")) {
    flyWheelPower = 200;
  } else if (buttonInput.equals("PowerMax")) {
    //flyWheelPower = 255;
  }
  DecodeIRSignal();
}

void solenoidControl() {
  if (buttonInput.equals("Shoot")) {
    digitalWrite(solenoidPin, HIGH);
    delay(100);
    digitalWrite(solenoidPin, LOW);
  }
}

void toggleSafety() {
  if (buttonInput.equals("Safety")) {
    Serial.println("SWITCH!");
    if (toggle) {
      toggle = false;
    } else if (!toggle) {
      toggle = true;
    }
  }
}

void loop() {
  DecodeIRSignal();
  //toggleSafety();
  //  if (!toggle) {
  //    analogWrite(flyWheelPin, flyWheelPower);
  //  } else {
  //    analogWrite(flyWheelPin, 0);
  //  }
  digitalWrite(flyWheelPin, flyWheelPower);
  flywheelControl();
  TopServoMovement();
  BottomServoMovement();
  solenoidControl();
  if (!(buttonInput.equals("reset"))) {
    Serial.println(buttonInput);
  }
  delay(10);
  buttonInput = "reset";

}
