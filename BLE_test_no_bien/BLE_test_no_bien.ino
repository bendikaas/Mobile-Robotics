#include <SoftwareSerial.h>

#define BT_TX_PIN 8 //TX pin of bluetooth module
#define BT_RX_PIN 9 //RX pin of bluetooth module

SoftwareSerial bt_device(BT_TX_PIN, BT_RX_PIN);

void setup() {
  // put your setup code here, to run once:
  bt_device.begin(9600);
  bt_device.flush();

  Serial.begin(4800);
  Serial.println("The beginning of reciving stuff from BLE");

}

void loop() {
  // put your main code here, to run repeatedly:
  if (bt_device.available())
  {
    unsigned char c;
    c = (char)bt_device.read();
    Serial.println("The recived data is: ");
    Serial.println(c);
  }
  delay(500);

}
