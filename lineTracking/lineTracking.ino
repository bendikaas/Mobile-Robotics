#include <Servo.h>

#define D10 10 // Left Wheel
#define D11 11 // Right Wheel
#define D12 12 // Left arm
#define D13 13 // Right arm
#define A0_PIN A0 // IR sensor analog input

// Global Variables
Servo _servoD10; // Left wheel
Servo _servoD11; // Right wheel
Servo _servoD12; // Left arm
Servo _servoD13; // Right arm

int velocity = 8;
int gain = 10;
int leftSpeed = 90;
int rightSpeed = 90;

const int trigPin = 3; // sonar
const int echoPin = 4; // sonar
const int distanceThreshold = 20; // Distance threshold in cm

// Functions
void move_base_D10_D11(int speed, int turn);
int follow(int light, int gain);
void armsIn();
void armsOut();
void armsStraight();
void driveStraight();
void driveBackwards();
int getDistance();
bool obsticleDetected();

void setup() {
  Serial.begin(9600);

  _servoD10.attach(D10);
  _servoD11.attach(D11);
  _servoD12.attach(D12);
  _servoD13.attach(D13);
  pinMode(A0_PIN, INPUT);
  pinMode(trigPin, OUTPUT); //SONAR
  pinMode(echoPin, INPUT); //SONAR

  _servoD10.write(leftSpeed); // Stop position
  _servoD11.write(rightSpeed); // Stop position
  _servoD12.write(90); // arm straight
  _servoD13.write(90); // arm straight

  delay(1000); // Give some time for setup
}

void loop(){
  lineTracking();
  delay(100); // Small delay for smoother operation
}

bool obsticleDetected(){
  int distance = getDistance();
  return (distance < distanceThreshold);
}

int getDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = (duration * 0.0343) / 2; // [cm]
  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;
}

void armsIn(){
  _servoD12.write(50);
  _servoD13.write(130);
}

void armsOut(){
  _servoD12.write(140);
  _servoD13.write(40);
}

void armsStraight(){
  _servoD12.write(90);
  _servoD13.write(90);
}

void driveStraight(){
  _servoD10.write(100); // left wheel
  _servoD11.write(75); // right wheel
}

void driveBackwards(){
  _servoD10.write(80); // left wheel
  _servoD11.write(93); // right wheel
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
  int white = 50;  // Below this is white

  if (light > black) { // Black detected -> turn right
    return -gain; // turn  = -20
  } 
  else if (light < white) { // White detected -> turn left
    return gain; // turn  = 20
  } 
  else { // In the middle section -> Drive straight ahead
    return 0; // No turn
  }
}

void move_base_D10_D11(int speed, int turn){
  if (turn == 0){
    driveStraight();
  } 
  else {
    leftSpeed = 90 - turn;
    rightSpeed = 90 - turn;
    _servoD10.write(leftSpeed);
    _servoD11.write(rightSpeed);
  }

  Serial.print("Left Wheel: ");
  Serial.print(leftSpeed);
  Serial.print(" | Right Wheel: ");
  Serial.println(rightSpeed);
}
