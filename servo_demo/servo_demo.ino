#include <Servo.h>
#include <busyboard.h>

int SERVO1_PIN = 9;
Servo servo1;
int currentAngle = 0;
int targetAngle = 0;
const int MAX_ANGLE = 178;
const int MIN_ANGLE = 2;
const int step_min = 2;
uint8_t topic;
char rxBytes[32];

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

void processMessage(uint8_t topic)
{
  if(topic == 0)
  {
    targetAngle = String(rxBytes).toInt();
    Serial.print("Target Angle: ");
    Serial.println(targetAngle);
  }
}

void commSetup()
{
  const char * nodeType = "${SERIAL,I:0:INT:servo}";
  Serial.println(nodeType);
}

void setup() {
  Serial.begin(57600);
  while(!Serial){};
  commSetup();

  servo1.attach(SERVO1_PIN);
  setServo(&servo1,currentAngle);
}

void loop() 
{
  if(bb::receiveMessage(topic,rxBytes))
    processMessage(topic);

  if(currentAngle != targetAngle)
  {
    if(currentAngle < targetAngle)
      setServo(&servo1,currentAngle + step_min);
    else if(currentAngle > targetAngle)
      setServo(&servo1,currentAngle - step_min);
    delay(15);
  }

  delay(1);
}
