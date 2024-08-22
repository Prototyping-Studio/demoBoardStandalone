#define USE_ROS

#ifdef USE_ROS
#include <ros.h>
#include <std_msgs/Bool.h>

ros::NodeHandle nh;

void led_cb(const std_msgs::Bool& onOff)
{
  if(onOff.data)
    ledOn();
  else
    ledOff();
}
ros::Subscriber<std_msgs::Bool> ledSub("led",led_cb);

void setupROS()
{
  nh.initNode();
  nh.subscribe(ledSub);
}
#endif

void ledOn()
{
    digitalWrite(LED_BUILTIN, HIGH); 
}

void ledOff()
{
    digitalWrite(LED_BUILTIN, LOW);  
}

// the setup function runs once when you press reset or power the board
void setup() {
  #ifdef USE_ROS
  setupROS();
  #endif
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() 
{
  #ifdef USE_ROS
  nh.spinOnce();
  #endif

  delay(1);
}
