#ifndef motor_h
#define motor_h
#include "Arduino.h"

struct Engine {
	uint8_t ENX;
	uint8_t IN1;
	uint8_t IN2;
	uint8_t SPEED;
};



class Motor
{
	public:
		Motor(Engine a,Engine b);
		void initialize();
		static void test(){
			if(!Serial){return;}
				Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
				Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
		};
	private:
		Engine engine_a,engine_b;
};

 void chuj();


#endif
