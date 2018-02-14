#include "Arduino.h"
#include "motor.h"



extern Motor motor;




Motor::Motor(Engine a,Engine b):engine_a(a),engine_b(b){
}




void Motor::initialize(){
	pinMode(engine_a.ENX, OUTPUT);
	pinMode(engine_b.ENX, OUTPUT);
	pinMode(engine_a.IN1, OUTPUT);
	pinMode(engine_a.IN2, OUTPUT);
	pinMode(engine_b.IN1, OUTPUT);
	pinMode(engine_b.IN1, OUTPUT);
}

void chuj(){};

