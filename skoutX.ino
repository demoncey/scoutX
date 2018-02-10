#include <bluetooth.h>
#include <supervisor.h>
#include <task.h>

#define RX 12 //tx blue
#define TX 11 //rx blue 

Bluetooth bluetooth(RX,TX,100);

Supervisor supervisor("ScoutX supervisor");
//major tasks
Task sendMsgTask(&send_msg);
Task recvMsgTask(&recv_msg);






void setup() {
  Serial.begin(9600);
    while (!Serial) {
    ; 
  }
  bluetooth.init();
  supervisor.addTask(sendMsgTask);
  sendMsgTask.setPriority(P_HIGH);
  supervisor.addTask(recvMsgTask);
  recvMsgTask.setPriority(P_HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  supervisor.execute();
  delay(1000);

}




void send_msg() {
  int id = random(1,65536);
  Serial.println("Heartbeat msg: "+String(id,HEX));
  bluetooth.send("Heartbeat msg: "+String(id,HEX));
}

void recv_msg() {
  String msg = bluetooth.recv();
  Serial.println("Message from Bluetooth: "+msg);
}


