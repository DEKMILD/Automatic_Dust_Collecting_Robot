#include <Servo.h>

#define PWM_ML 2
#define in1_ML 3
#define in2_ML 4
#define in1_MR 5
#define in2_MR 6
#define PWM_MR 7

int right = 0;
int front = 90;
int left = 180;

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 11;

long duration;
int distanceFront;
int distanceLeft;
int distanceRight;
int SpeedR = 255;
int SpeedL = 255;

Servo myServo;

int measureDistance();

void setup() {
  pinMode(PWM_ML, OUTPUT);
  pinMode(in1_ML, OUTPUT);
  pinMode(in2_ML, OUTPUT);
  pinMode(in1_MR, OUTPUT);
  pinMode(in2_MR, OUTPUT);
  pinMode(PWM_MR, OUTPUT);

  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  myServo.attach(servoPin);
  myServo.write(90);

  delay(3000);
}

void loop() {
  distanceFront = measureDistance();

  Serial.print("Distance Front: ");
  Serial.print(distanceFront);
  Serial.println(" cm");

  delay(1000);

  if (distanceFront > 20) {
    moveForward();
  } else {
    stopMoving();
    checkLeft();
    checkRight();

    if (distanceLeft > distanceRight) {
      myServo.write(90);
      turnLeft();
    } else {
      myServo.write(90);
      turnRight();
    }
  }

  delay(100);
}

void checkLeft() {
  myServo.write(0);
  delay(1000);

  distanceLeft = measureDistance();

  Serial.print("Distance Left: ");
  Serial.print(distanceLeft);
  Serial.println(" cm");
}

void checkRight() {
  myServo.write(180);
  delay(1000);

  distanceRight = measureDistance();

  Serial.print("Distance Right: ");
  Serial.print(distanceRight);
  Serial.println(" cm");
}

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  int distance = duration * 0.034 / 2;

  return distance;
}

void moveForward() {
  digitalWrite(in1_ML, LOW);
  digitalWrite(in2_ML, HIGH);
  analogWrite(PWM_ML, SpeedL);

  digitalWrite(in1_MR, LOW);
  digitalWrite(in2_MR, HIGH);
  analogWrite(PWM_MR, SpeedR);
}

void stopMoving() {
  digitalWrite(in1_ML, LOW);
  digitalWrite(in2_ML, LOW);
  analogWrite(PWM_ML, 0);

  digitalWrite(in1_MR, LOW);
  digitalWrite(in2_MR, LOW);
  analogWrite(PWM_MR, 0);
}

void turnLeft() {
  digitalWrite(in1_ML, HIGH);
  digitalWrite(in2_ML, HIGH);
  analogWrite(PWM_ML, 0);

  digitalWrite(in1_MR, LOW);
  digitalWrite(in2_MR, HIGH);
  analogWrite(PWM_MR, 170);

  delay(250);

  myServo.write(90);
  delay(250);

  distanceFront = measureDistance();

  if (distanceFront > 20) {
    moveForward();
  } else {
    stopMoving();
  }
}

void turnRight() {
  digitalWrite(in1_ML, LOW);
  digitalWrite(in2_ML, HIGH);
  analogWrite(PWM_ML, 150);

  digitalWrite(in1_MR, HIGH);
  digitalWrite(in2_MR, HIGH);
  analogWrite(PWM_MR, 0);

  delay(250);

  myServo.write(90);
  delay(250);

  distanceFront = measureDistance();

  if (distanceFront > 20) {
    moveForward();
  } else {
    stopMoving();
  }
}
