#define USE_ROS

#ifdef USE_ROS
#include <busyboard.h>
#endif

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

#ifdef USE_ROS
void motor_cb(const std_msgs::Int16& speed)
{
  int set_speed = abs(speed.data);
  bool direction = speed.data >= 0;
  setMotor(motor,set_speed,direction);
}
ros::Subscriber<std_msgs::Int16> motorSub("motor",motor_cb);
#endif

void setup() {
  #ifdef USE_ROS
  setupROS();
  nh.subscribe(motorSub);
  #endif

  if (!AFMS.begin()) 
  {
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
}

void loop() {
  #ifdef USE_ROS
  #else
  setMotor(motor,100,true);
  #endif
  delay(100);
}
