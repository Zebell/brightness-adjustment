#include <IRremote.h>

IRrecv IR(3);
int ledPin = 9;
bool lampOn = false;
int brightness = 10;

void setup() {
  IR.enableIRIn();
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (IR.decode()) {
    Serial.println(IR.decodedIRData.decodedRawData, HEX);

    if (IR.decodedIRData.decodedRawData == 0xE31CFF00) {
      lampOn = !lampOn;

      if (lampOn) {
        analogWrite(ledPin, brightness);
      } else {
        analogWrite(ledPin, 0);
      }
    }

    if (lampOn && IR.decodedIRData.decodedRawData == 0xE718FF00) {
      brightness += 50;

      if (brightness > 255) {
        brightness = 255;
      }
      analogWrite(ledPin, brightness);
    }
    if (lampOn && IR.decodedIRData.decodedRawData == 0xAD52FF00) {
        brightness -= 50;
        if (brightness < 20) {
          brightness = 20;
        }
        analogWrite(ledPin, brightness);
      }

    IR.resume();
  }
}
