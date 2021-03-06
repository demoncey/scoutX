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
		static void initialize(Engine a,Engine b);
		static void test(){
			if(!Serial){return;}
				Serial.println("--------------------------------------------------------");
				Serial.println(String(engine_b.SPEED));
				Serial.println(String(engine_b.SPEED));
				Serial.println("--------------------------------------------------------");
		};
		static void motorLeft(void *p);
		static void motorRight(void *p);
		static void motorStart(void *p);
		static void motorStop(void *p);
		
		
	private:
		static Engine engine_b,engine_a;
};
#endif
