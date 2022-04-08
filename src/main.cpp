#include <Arduino.h>
#include <Servo.h>
#include <NoDelay.h>
#include "HwMotor/HwMotorIn.h"

//Pin Assignments
//int vPin = A0;
//int iPin = A1;
int pwmPin = 3;
int ssrPin = 7;
HwMotorIn motor1(&Serial1);
HwMotorIn motor2(&Serial2);
HwMotorIn motor3(&Serial3);


//vars we care about
int pwmval = 1000;
//float volts = 0;
//float amps = 0;
//float armedThreshold = 0.95;
unsigned int testno = 0; //what test are we on
unsigned int successful[3] = {0}; //how many successful tests have we done
unsigned int failures[3] = {0}; //have we had any failures?

//state machine
int state = 0;

void record() { //print to serial studio
  Serial.print("/*");
  Serial.print(state);
  Serial.print(',');
  Serial.print(testno);
  Serial.print(',');
  Serial.print(successful[0]);
  Serial.print(',');
  Serial.print(failures[0]);
  Serial.print(',');
  Serial.print(successful[1]);
  Serial.print(',');
  Serial.print(failures[1]);
  Serial.print(',');
  Serial.print(successful[2]);
  Serial.print(',');
  Serial.print(failures[2]);
  Serial.println("*/");
}

Servo esc;



noDelay write(100,record);

void spindown() {
  state = 4;
}

noDelay stopDelay(3000, spindown);

void checkspin() {
  testno++;
  if(motor1.get_rpm() >= 0) {
    successful[0]++;
  }else {
    failures[0]++;
  }
  if(motor2.get_rpm() >= 0) {
    successful[1]++;
  }else {
    failures[1]++;
  }  
  if(motor3.get_rpm() >= 0) {
    successful[2]++;
  }else {
    failures[2]++;
  }
  state = 3;
  stopDelay.start();
  return;
}
noDelay runDelay(5000,checkspin);

void prearm2arm() {
  pwmval = 1500;
  digitalWrite(ssrPin, HIGH);
  state = 2;
  runDelay.start();
  return;
}

noDelay prearmDelay(5000,prearm2arm);

void setup() {
  pinMode(ssrPin,OUTPUT);
  pinMode(pwmPin,OUTPUT);
  digitalWrite(ssrPin, LOW); // ensure SSR is off before beginning
  Serial.begin(9600);
  esc.attach(pwmPin);
  esc.writeMicroseconds(pwmval);
}

void off2prearm() {
  pwmval = 1000;
  digitalWrite(ssrPin, HIGH);
  state = 1;
  prearmDelay.start();
  return;
}
noDelay offDelay(5000,off2prearm);



void loop() {
  esc.writeMicroseconds(pwmval);
  motor1.update_telem();
  motor2.update_telem();
  motor3.update_telem();
  write.update();


  if (state == 0) {
    offDelay.update();
  }

  if (state == 1) {
    prearmDelay.update();
  }

  if (state == 2) {
    runDelay.update();
  }
  
  if (state == 3) {
    pwmval = 1100;
    //digitalWrite(ssrPin, LOW);
    //state = 0;
    //offDelay.start();
    stopDelay.update();
  }

  if (state == 4) {
    pwmval = 900;
    digitalWrite(ssrPin, LOW);
    state = 0;
    offDelay.start();
  }
}