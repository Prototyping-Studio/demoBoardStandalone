#include <Servo.h>

const int SERVO1_PIN = 10;
Servo servo1;
int currentAngle = 0;
int targetAngle = 0;
const int MAX_ANGLE = 178;
const int MIN_ANGLE = 2;
const int step_min = 2;

void setServoAbs(Servo * servo, int angle)
{
  servo->write(angle);
}

void setServo(Servo * servo, int angle)
{
  int set_angle = angle;
  if(set_angle > MAX_ANGLE)
    set_angle = MAX_ANGLE;
  else if (set_angle < MIN_ANGLE)
    set_angle = MIN_ANGLE;

  servo->write(set_angle);
  currentAngle = set_angle;
}


void setup() {

  servo1.attach(SERVO1_PIN);
  setServo(&servo1,currentAngle);
}

void loop() {
  setServo(&servo1,MIN_ANGLE);
  delay(2000);
  setServo(&servo1,MAX_ANGLE);
  delay(2000);
}
