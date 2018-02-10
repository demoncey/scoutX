#include <supervisor.h>
#include <task.h>
void send_msg();



Supervisor supervisor("scoutX supervisor");
Task sMsgTask(&send_msg);






void setup() {
  Serial.begin(9600);
    while (!Serial) {
    ; 
  }
  supervisor.addTask(sMsgTask);
  sMsgTask.setPriority(P_HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  supervisor.execute();
  delay(1000);

}




void send_msg() {
  int id = random(1, 1000000000);
  Serial.println("Heartbeat msg: "+String(id));
}
