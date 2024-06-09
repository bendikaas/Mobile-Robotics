#include "functions.h"
#include <Adafruit_NeoPixel.h>

#define D6 6

Adafruit_NeoPixel _led_strip_D6(7,D6, NEO_GRB + NEO_KHZ800);

void happy();
void sad();
void normal();
void stunned();
void light_on();
void light_off();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  _led_strip_D6.begin();
  clearpixels(&_led_strip_D6);
  _led_strip_D6.setBrightness(map(10,0,100,0,255));
  writepixels(&_led_strip_D6, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    char receivedChar = (char) Serial.read();
    Serial.print("The Recived char is: ");
    Serial.println(receivedChar);
    switch(receivedChar){
      case 'a':  break; 
      case 'b':  break;
      case 'c': happy(); break;
      case 'd': sad(); break;
      case 'e': normal(); break;
      case 'f': stunned(); break;
      case 'g': light_on(); break;
      case 'h': light_off(); break;
      case 'i':  break;
      case 'j':  break;
      case 'k':  break;
      case 'l':  break;
      case 'm':  break;
      case 'n':  break;
      case 'o':  break;
      case 'p':  break;
      case 'q':  break;
      case 'r':  break;
      case 's':  break;
      case 't':  break;
      case 'u':  break;
      case 'v':  break;
      case 'w':  break;
      case 'x':  break;
      case 'y':  break;
      case 'z':  break;
      default: break;
    }
    }
}

void happy() {
  writepixels(&_led_strip_D6, 0x000000, 0x000000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000);
}

void sad() {
  writepixels(&_led_strip_D6, 0x000000, 0xffffff, 0xffffff, 0x000000, 0x000000, 0xffffff, 0xffffff);
}

void normal() {
  writepixels(&_led_strip_D6, 0x000000, 0xffffff, 0xffffff, 0x000000, 0x000000, 0xffffff, 0xffffff);
}

void stunned() {
  writepixels(&_led_strip_D6, 0x000000, 0xffffff, 0xffffff, 0x000000, 0x000000, 0xffffff, 0xffffff);
}

void light_on() {
  writepixels(&_led_strip_D6, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000, 0xffffff, 0xffffff);
}

void light_off() {
  writepixels(&_led_strip_D6, 0x000000, 0xffffff, 0xffffff, 0x000000, 0x000000, 0xffffff, 0xffffff);
}

void clearpixels(Adafruit_NeoPixel *led_strip) {
  led_strip->fill(0, 0, led_strip->numPixels());
  led_strip->show();
}

void writepixels(Adafruit_NeoPixel *led_strip, uint32_t data0, uint32_t data1, uint32_t data2, uint32_t data3, uint32_t data4, uint32_t data5, uint32_t data6){
  led_strip->setPixelColor(0, led_strip->Color((data0 >> 16) & 0x0000ff, (data0 >> 8) & 0x0000ff, data0 & 0x0000ff));
  led_strip->setPixelColor(1, led_strip->Color((data1 >> 16) & 0x0000ff, (data1 >> 8) & 0x0000ff, data1 & 0x0000ff));
  led_strip->setPixelColor(2, led_strip->Color((data2 >> 16) & 0x0000ff, (data2 >> 8) & 0x0000ff, data2 & 0x0000ff));
  led_strip->setPixelColor(3, led_strip->Color((data3 >> 16) & 0x0000ff, (data3 >> 8) & 0x0000ff, data3 & 0x0000ff));
  led_strip->setPixelColor(4, led_strip->Color((data4 >> 16) & 0x0000ff, (data4 >> 8) & 0x0000ff, data4 & 0x0000ff));
  led_strip->setPixelColor(5, led_strip->Color((data5 >> 16) & 0x0000ff, (data5 >> 8) & 0x0000ff, data5 & 0x0000ff));
  led_strip->setPixelColor(6, led_strip->Color((data6 >> 16) & 0x0000ff, (data6 >> 8) & 0x0000ff, data6 & 0x0000ff));
  led_strip->show();
}
