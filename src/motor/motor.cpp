#include "Arduino.h"
#include "motor.h"
void Motor::initialize(Engine a,Engine b){
	engine_a=a;
	engine_b=b;
	pinMode(engine_a.ENX, OUTPUT);
	pinMode(engine_b.ENX, OUTPUT);
	pinMode(engine_a.IN1, OUTPUT);
	pinMode(engine_a.IN2, OUTPUT);
	pinMode(engine_b.IN1, OUTPUT);
	pinMode(engine_b.IN1, OUTPUT);
}

Engine Motor::engine_a={0,0,0,2};
Engine Motor::engine_b={0,0,0,3};


