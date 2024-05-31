#include <Adafruit_MotorShield.h>

const int max_speed = 255;
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor = AFMS.getMotor(3);

void setMotor(Adafruit_DCMotor *motor, int speed, bool dir)
{
  if(speed == 0)
  {
    motor->setSpeed(0);
    motor->run(RELEASE);
    return;
  }

  if(speed > max_speed)
    speed = max_speed;

  motor->setSpeed(speed);
  
  if(dir)
    motor->run(FORWARD);
  else
    motor->run(BACKWARD);
}


void setup() {

  if (!AFMS.begin()) 
  {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
}

void loop() {
  setMotor(motor,100,true);
  delay(100);
}
