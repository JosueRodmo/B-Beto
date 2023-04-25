#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

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

void setup() {
//Inicializacion de Nodos
  nh.initNode();
  nh.advertise(right_ticks);
  nh.advertise(left_ticks);
  
  Serial.begin(9600);
  pinMode(ENCA1, INPUT);
  pinMode(ENCB1, INPUT);
  pinMode(ENCA2, INPUT);
  pinMode(ENCB2, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA1), readEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA2), readEncoder2, RISING);
}

void loop() {
  pose1.data = pos1;
  pose2.data = pos2;
  right_ticks.publish(&pose1);
  left_ticks.publish(&pose2);

  nh.spinOnce();
}

void readEncoder1(){
  int b1 = digitalRead(ENCB1);
  if(b1>0){
    pos1++;
  }
  else{
    pos1--;
  }
  
}

void readEncoder2(){
  int b2 = digitalRead(ENCB2);
  if(b2>0){
    pos2++;
  }
  else{
    pos2--;
  }  
}
