#include <Servo.h>

#define D10 10 // Left Wheel
#define D11 11 // Right Wheel
#define A0_PIN A0 // IR sensor analog input

// Global Variables
Servo _servoD10;
Servo _servoD11;

int velocity = 15;
int gain = 8;
int leftSpeed = 90;
int rightSpeed = 90;

// Line following functions
void move_base_D10_D11(int speed, int turn);
int follow(int light, int gain);

void setup() {
  Serial.begin(9600);
  _servoD10.attach(D10);
  _servoD11.attach(D11);
  pinMode(A0_PIN, INPUT);

  _servoD10.write(leftSpeed); // Stop position
  _servoD11.write(rightSpeed); // Stop position

  delay(1000); // Give some time for setup
}

void loop(){
  lineTracking();
  
  delay(100); // Small delay for smoother operation
}

void lineTracking(){
  int light = analogRead(A0_PIN);
  int turn = follow(light, gain);
  move_base_D10_D11(velocity, turn);
}

int follow(int light, int gain) {
  Serial.print("Light Value: ");
  Serial.println(light);

  int black = 100; // Above this is black
  int white = 35;  // Below this is white
  // int mean = (black + white) / 2;
  // int deadZone = 30;

  if (light > black) {// Black detected -> turn right
    return -gain; // turn  = -8
  }
  
  else if (light < white) {// White detected -> turn left
    return gain;
  }
  
  else { // In the middle section -> Drive straight ahead
    return 0; // No turn
  }
}

void move_base_D10_D11(int speed, int turn){
  if (turn == 0){
    leftSpeed = 95;
    rightSpeed = 80;
  }
  else{
    leftSpeed = 90 - turn;
    rightSpeed = 90 - turn;
  }
  _servoD10.write(leftSpeed);
  _servoD11.write(rightSpeed);

  Serial.print("Left Wheel: ");
  Serial.print(leftSpeed);
  Serial.print(" | Right Wheel: ");
  Serial.println(rightSpeed);
}