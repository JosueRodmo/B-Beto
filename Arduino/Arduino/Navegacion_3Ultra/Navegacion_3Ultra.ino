#include <ros.h>
#include <std_msgs/Int32.h>
#include <HCSR04.h>
ros::NodeHandle nh;

byte triggerPin = 4;
byte echoCount = 3;
byte lUltra = 15;
byte fUltra = 16;
byte rUltra = 23;
byte* echoPins = new byte[echoCount] {lUltra, fUltra, rUltra};

int mini;
int prevmini;
int prevminiiz;
int prevminider;
int resultados[4];
unsigned int pos;

float x;
int dir = 0;

#define ENCA1 5 // Red
#define ENCB1 17 // Black

#define ENCA2 25 // Red
#define ENCB2 26 // Black

int pos1 = 0;
int pos2 = 0;

const int rightforw = 32;
const int leftback = 19;
const int leftforw = 18;
const int rightback = 33;

const int freq = 5000;
const int ledChannel1 = 0;
const int ledChannel2 = 1;
const int ledChannel3 = 2;
const int ledChannel4 = 3;
const int resolution = 8;
int pwr1 = 70;


void setup() {
  attachInterrupt(digitalPinToInterrupt(ENCA1), readEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCA2), readEncoder2, RISING);
  pinMode(ENCA1, INPUT);
  pinMode(ENCB1, INPUT);
  pinMode(ENCA2, INPUT);
  pinMode(ENCB2, INPUT);
  HCSR04.begin(triggerPin, echoPins, echoCount);
  //Serial.begin(57600);

  ledcSetup(ledChannel1, freq, resolution);
  ledcSetup(ledChannel2, freq, resolution);
  ledcSetup(ledChannel3, freq, resolution);
  ledcSetup(ledChannel4, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(rightforw, ledChannel1);
  ledcAttachPin(rightback, ledChannel2);
  ledcAttachPin(leftforw, ledChannel3);
  ledcAttachPin(leftback, ledChannel4);
}

void loop() {
  miniD();
  //Serial.print(pos);
  //Serial.print(" - ");
  //Serial.println(resultados[0]);
  if((resultados[0] < 20)&&(pos == 1)) {
    right();
  }else if((resultados[0] < 20)&&(pos == 3)) {
    left();
  } else if((resultados[0] < 15)&&(pos == 2)){
    if(resultados[2] < resultados[3]){
      right();
      delay(100);
    }else if(resultados[2] > resultados[3]){
      left();
      delay(100);
    }
  }else{
    front();
  }
}

void front()
{
    ledcWrite(ledChannel1, pwr1);
    ledcWrite(ledChannel2, 0);
    ledcWrite(ledChannel3, pwr1);
    ledcWrite(ledChannel4, 0);
    
}
void back()
{
    ledcWrite(ledChannel1, 0);
    ledcWrite(ledChannel2, pwr1);
    ledcWrite(ledChannel3, 0);
    ledcWrite(ledChannel4, pwr1); 
}
void left()
{
    ledcWrite(ledChannel1, pwr1+35);
    ledcWrite(ledChannel2, 0);
    ledcWrite(ledChannel3, 0);
    ledcWrite(ledChannel4, pwr1+35); 

}
void right()
{   
    ledcWrite(ledChannel1, 0);
    ledcWrite(ledChannel2, pwr1+35);
    ledcWrite(ledChannel3, pwr1+35);
    ledcWrite(ledChannel4, 0); 
}
void die()
{
    ledcWrite(ledChannel1, 0);
    ledcWrite(ledChannel2, 0);
    ledcWrite(ledChannel3, 0);
    ledcWrite(ledChannel4, 0); 
}

void miniD(){
  double* distances = HCSR04.measureDistanceCm();

  
  if (distances[0]== -1){
    prevminiiz = prevminiiz;
  }
  prevminiiz = distances[0];

  if (distances[2]== -1){
    prevminider = prevminider;
  }
  prevminider = distances[2];

  if (distances[1]== -1){
    prevmini = prevmini;
  }
  prevmini = distances[1];
  
  if((prevminiiz <= distances[1]) && (prevminiiz <= prevminider)){
    mini = prevminiiz;
    pos = 1;
  } else if((distances[1] <= prevminiiz) && (distances[1] <= prevminider)){
    mini = prevmini;
    pos = 2;
  }else{
    mini = prevminider;
    pos = 3;
  }


  resultados[0] = mini;
  resultados[1] = pos;
  resultados[2] = prevminiiz;
  resultados[3] = prevminider;
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
