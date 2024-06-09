#include "BluetoothSerial.h"

BluetoothSerial Serial_BT;

const int ledpin = 2;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial_BT.begin("ESP32 Bluetooth");
  pinMode(ledpin, OUTPUT);

}

void loop() {3
  // put your main code here, to run repeatedly:
  if (Serial_BT.available()){
    char input = (char) Serial_BT.read();
    if (input =='a'){
      digitalWrite(ledpin, HIGH);
    } else if (input == 'b'){
      digitalWrite(ledpin, LOW);
    }
    Serial.print(input);
  }
  delay(100);

}
