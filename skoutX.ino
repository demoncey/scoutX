#include "src/motor/motor.h"
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
Engine m_a={ENA,IN1,IN2,SPEEDA};
Engine m_b={ENB,IN3,IN4,SPEEDB};

//Motor motor;

Supervisor supervisor("scoutx supervisor");
//major tasks
Task sendMsgTask(&send_msg);
Task recvMsgTask(&recv_msg);
Task calcDistTask(&calcDistance);
Task test(&Motor::test);

void setup() {
  Serial.begin(9600);
    while (!Serial) {
    ; 
  }
  //setup motor
  Motor::initialize(m_a,m_b);
  //init HC-SR04
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT); 
  bluetooth.init();//https://www.allaboutcircuits.com/projects/control-an-arduino-using-your-phone/
  //shitty builder
  supervisor.addTask(sendMsgTask.setPriority(P_HIGH));//by ptr
  supervisor.addTask(recvMsgTask.setPriority(P_HIGH));//by ptr
  supervisor.addTask(calcDistTask.setPriority(P_HIGH));//by ptr
  test.setPriority(P_HIGH);
  //using overloaded operator
  supervisor+test;
}

void loop() {
  supervisor.execute();
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
      Task *mStart=new Task(&Motor::motorStart);
      mStart->setMode(MODE_ONCE);
      supervisor.addTask(*mStart);
      return;
    }
    if(msg== String('2')){
      //stop
      Task *mStop=new Task(&Motor::motorStop);
      mStop->setMode(MODE_ONCE);
      supervisor.addTask(*mStop);
      return;
    }
    if(msg== String('r')){
      //right
      TaskBuilder builder;
      supervisor.addTask(builder.setCallback(&Motor::motorRight).setMode(MODE_ONCE).build());//via ptr
      return;
    }
    if(msg== String('l')){
      //left
      TaskBuilder builder;
      supervisor.addTask(builder.setCallback(&Motor::motorLeft).setMode(MODE_ONCE).build());//via ptr
      return;
    }
   if(msg== String('m')){
      //free ram memory messurment
      TaskBuilder builder;
      supervisor.addTask(builder.setCallback(&memory).setMode(MODE_ONCE).build());//via ptr
      return;
    }
  }
}
void calcDistance(){
  long t , distance;
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  t = pulseIn(ECHO, HIGH);
  distance = t / 58;
  if(t<10){
      TaskBuilder builder;
      supervisor.addTask(builder.setCallback(&Motor::motorStop).setMode(MODE_ONCE).build());
  }
  Serial.println("**********************");
  bluetooth.send("**********************");
  Serial.println("Distance: "+String(distance));
  bluetooth.send("Distance: "+String(distance));
  Serial.println("**********************");
  bluetooth.send("**********************");
}


void memory(){
  ////https://arduino.stackexchange.com/questions/355/how-much-can-i-recurse-how-much-can-i-recurse-how-much-caqfsdrfw
  extern int __heap_start, *__brkval; 
  //__brkval pointer to top of heap
  int last_stack_variable;
  int memory= (int)&last_stack_variable - ( __brkval == 0 ? (int) &__heap_start : (int) __brkval);
  Serial.println("**********************");
  bluetooth.send("**********************");
  Serial.println("Free memory: "+String(memory));
  bluetooth.send("Free memory: "+String(memory));
  Serial.println("**********************");
  bluetooth.send("**********************");
   
}







