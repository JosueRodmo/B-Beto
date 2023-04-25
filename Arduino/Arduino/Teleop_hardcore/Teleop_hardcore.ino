#include <ros.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
ros::NodeHandle nh;
geometry_msgs::Twist msg;

float move1;
float move2;
float vel;

//Envio de velocidad constante a ROS
std_msgs::Int32 pose1;
std_msgs::Int32 pose2;
ros::Publisher right_ticks("rwheel_ticks", &pose2);
ros::Publisher left_ticks("lwheel_ticks", &pose1);

#define ENCA1 5 // Red
#define ENCB1 17 // Black

#define ENCA2 25 // Red
#define ENCB2 26 // Black

int pos1 = 0;
int pos2 = 0;

void callback(const geometry_msgs::Twist& cmd_vel)
{
  vel = move1*100;
  move1 = cmd_vel.linear.x;
  move2 = cmd_vel.angular.z;
  if (move1 > 0 && move2 == 0)
  {
    front();
  }
  else if (move1 > 0 && move2 > 0 )
  {
    left();
  }
  else if (move1 > 0 && move2 < 0 )
  {
    right();
  }
  else if (move1 < 0)
  {
    back();
  }
  else
  {
    die();
  }
}

ros::Subscriber <geometry_msgs::Twist> sub("/cmd_vel", callback);

const int rightforw = 32;
const int leftback = 19;
const int leftforw = 18;
const int rightback = 33;

void setup() {
  attachInterrupt(digitalPinToInterrupt(ENCA1), readEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA2), readEncoder2, RISING);
  pinMode(ENCA1, INPUT);
  pinMode(ENCB1, INPUT);
  pinMode(ENCA2, INPUT);
  pinMode(ENCB2, INPUT);
  pinMode(leftforw, OUTPUT);
  pinMode(leftback, OUTPUT);
  pinMode(rightforw, OUTPUT);
  pinMode(rightback, OUTPUT);
  
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(right_ticks);
  nh.advertise(left_ticks);
}

void loop() {
  pose1.data = pos1;
  pose2.data = pos2;
  right_ticks.publish(&pose2);
  left_ticks.publish(&pose1);
  nh.subscribe(sub);
  nh.spinOnce();
  delay(1);
}

void front()
{
    analogWrite(leftforw, vel);
    analogWrite(rightforw, vel);
    analogWrite(leftback, LOW);
    analogWrite(rightback, LOW);
    
}
void back()
{
    vel = (vel*(-1.0));
    analogWrite(leftforw, LOW);
    analogWrite(rightforw, LOW);
    analogWrite(leftback, vel);
    analogWrite(rightback, vel); 
}
void left()
{
    analogWrite(leftforw, LOW);
    analogWrite(rightforw, vel);
    analogWrite(leftback, vel);
    analogWrite(rightback, LOW);

}
void right()
{   
    analogWrite(leftforw, vel);
    analogWrite(rightforw, LOW);
    analogWrite(leftback, LOW);
    analogWrite(rightback, vel); 
}
void die()
{
    analogWrite(leftforw, LOW);
    analogWrite(rightforw, LOW);
    analogWrite(leftback, LOW);
    analogWrite(rightback, LOW);
}

void readEncoder1() {
  int b1 = digitalRead(ENCB1);
  if (b1 > 0) {
    pos1++;
  }
  else {
    pos1--;
  }

}

void readEncoder2() {
  int b2 = digitalRead(ENCB2);
  if (b2 > 0) {
    pos2++;
  }
  else {
    pos2--;
  }
}
