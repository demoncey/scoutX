#include <bluetooth.h>
#include <supervisor.h>
#include <task.h>

#define RX 12 //tx blue
#define TX 11 //rx blue 



void send_msg();


Bluetooth bluetooth(RX,TX,100);

Supervisor supervisor("ScoutX supervisor");
Task sMsgTask(&send_msg);






void setup() {
  Serial.begin(9600);
    while (!Serial) {
    ; 
  }
  bluetooth.init();
  supervisor.addTask(sMsgTask);
  sMsgTask.setPriority(P_HIGH);
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
