#define D6 6
#include <Adafruit_NeoPixel.h>
#define D12 12
#define D13 13
#define A0 A0
#include <Servo.h>

/***   Global variables   ***/
Adafruit_NeoPixel _led_strip_D6(7,D6, NEO_GRB + NEO_KHZ800);
Servo _servoD12;
Servo _servoD13;
int black = 600;
int white = 30;

/***   Function declaration   ***/
void clearpixels(Adafruit_NeoPixel *led_strip);
void writepixels(Adafruit_NeoPixel *led_strip, uint32_t data0, uint32_t data1, uint32_t data2, uint32_t data3, uint32_t data4, uint32_t data5, uint32_t data6);
void happy();
void sad();
int follow(int light, int gain);
void move_base_D12_D13(int speed, int advance, int turn);
void lineFollowing();

void setup() {
  Serial.begin(9600);
  _led_strip_D6.begin();
  clearpixels(&_led_strip_D6);
  _led_strip_D6.setBrightness(map(10,0,100,0,255));
  writepixels(&_led_strip_D6, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000);

  _servoD12.attach(D12);
  _servoD13.attach(D13);
}

void loop() {
    //happy();
    //lineFollowing();
    //test();
    _servoD12.write(90);
    _servoD13.write(90);
}

/***   Function definition   ***/
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

void happy() {
  writepixels(&_led_strip_D6, 0x000000, 0x000000, 0xffffff, 0xffffff, 0xffffff, 0xffffff, 0x000000);
}

void sad() {
  writepixels(&_led_strip_D6, 0x000000, 0xffffff, 0xffffff, 0x000000, 0x000000, 0xffffff, 0xffffff);
}

int follow(int light, int gain){
  int target = (black + white) / 2;
  int error = target - light;
  int turn = (error * gain) / 100;

  // Clamp the turn value to ensure it stays within a reasonable range
  if (turn > 50) turn = 50;
  if (turn < -50) turn = -50;

  return turn;
}

void move_base_D12_D13(int speed, int advance, int turn){
  _servoD12.write(90 + (65 * (speed * (advance - turn)) / 10000));
  _servoD13.write(90 - (65 * (speed * (advance + turn)) / 10000));
}

void test(){
  int light = analogRead(A0);
  if (light > 100){
    _servoD12.write(100);
    _servoD13.write(100);
  }
  if (light < 100){
    _servoD12.write(80);
    _servoD13.write(80);
  }
  Serial.print("Light: ");
  Serial.println(light);
}

void lineFollowing() {
  int light = analogRead(A0);
  int turn = follow(light, 10);

  // Debugging output
  Serial.print("Light: ");
  Serial.print(light);
  Serial.print(" Turn: ");
  Serial.println(turn);

  move_base_D12_D13(20, 50, turn);
}
