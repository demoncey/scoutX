#include <bluetooth.h>
#include <supervisor.h>
#include <task.h>

#define RX 12 //tx blue
#define TX 11 //rx blue 
//motor
#define ENA 10
#define IN1 9
#define IN2 8
#define SPEEDA 200
// motor two
#define ENB 5
#define IN3 7
#define IN4 6
#define SPEEDB 180

//ultra sonic sensor HC-SR04
#define TRIG 4
#define ECHO 3




Bluetooth bluetooth(RX,TX,100);

Supervisor supervisor("ScoutX supervisor");
//major tasks
Task sendMsgTask(&send_msg);
Task recvMsgTask(&recv_msg);
Task calcDistTask(&calcDistance);






void setup() {
  Serial.begin(9600);
    while (!Serial) {
    ; 
  }
  //setup motor
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  bluetooth.init();
  //shitty builder
  supervisor.addTask(sendMsgTask.setPriority(P_HIGH));//by ptr
  supervisor.addTask(recvMsgTask.setPriority(P_HIGH));//by ptr
  supervisor.addTask(calcDistTask.setPriority(P_HIGH));//by ptr
}

void loop() {
  // put your main code here, to run repeatedly:
  supervisor.execute();
  delay(2000);

}




void send_msg() {
  int id = random(1,65536);
  Serial.println("Heartbeat msg: "+String(id,HEX));
  bluetooth.send("Heartbeat msg: "+String(id,HEX));
}

void recv_msg() {
  String msg = bluetooth.recv();
  if (msg != "") {
    Serial.println("Message from Bluetooth: "+msg);
    if(msg== String('1')){
      //start
      Task *mStart=new Task(&motorStart);
      mStart->setMode(MODE_ONCE);
      supervisor.addTask(*mStart);
      return;
    }
    if(msg== String('2')){
      //stop
      Task *mStop=new Task(&motorStop);
      mStop->setMode(MODE_ONCE);
      supervisor.addTask(*mStop);
      return;
    }
    if(msg== String('r')){
      //right
      Task *mRight=new Task(&motorRight);
      mRight->setMode(MODE_ONCE);
      supervisor.addTask(mRight);//via ptr
      return;
    }
    if(msg== String('l')){
      //left
      Task *mLeft=new Task(&motorLeft);
      mLeft->setMode(MODE_ONCE);
      supervisor.addTask(mLeft);//via ptr
      return;
    }
  }
}


void motorStop(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  Serial.println("Motor stopped");
  bluetooth.send("Motor stopped");
}

void motorStart(){ 

  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENA,SPEEDA);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENB,SPEEDB);
  Serial.println("Motor started");
  bluetooth.send("Motor started");
}


void motorRight(){ 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  analogWrite(ENB,SPEEDB);
  Serial.println("Motor left");
  bluetooth.send("Motor left");
}

void motorLeft(){
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(ENA,SPEEDA);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  Serial.println("Motor right");
  bluetooth.send("Motor right");
}



void calcDistance(){
  long t , distance;
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  t = pulseIn(ECHO, HIGH);
  distance = t / 58;
}








