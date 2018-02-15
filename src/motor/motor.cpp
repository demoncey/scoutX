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
	pinMode(engine_b.IN2, OUTPUT);
}


void Motor::motorLeft(){
	digitalWrite(engine_a.IN1,HIGH);
	digitalWrite(engine_a.IN2,LOW);
	analogWrite(engine_a.ENX,engine_a.SPEED);
	digitalWrite(engine_b.IN1,LOW);
	digitalWrite(engine_b.IN2,LOW);
	Serial.println("Motor right");
}

void Motor::motorRight(){
	digitalWrite(engine_a.IN1,LOW);
	digitalWrite(engine_a.IN2,LOW);
	digitalWrite(engine_b.IN1,HIGH);
	digitalWrite(engine_b.IN2,LOW);
	analogWrite(engine_b.ENX,engine_b.SPEED);
	Serial.println("Motor left");
}


void Motor::motorStart(){
	digitalWrite(engine_a.IN1,HIGH);
	digitalWrite(engine_a.IN2,LOW);
	analogWrite(engine_a.ENX,engine_a.SPEED);
	digitalWrite(engine_b.IN1,HIGH);
	digitalWrite(engine_b.IN2,LOW);
	analogWrite(engine_b.ENX,engine_b.SPEED);
	Serial.println("Motor started");
}

void Motor::motorStop(){
	digitalWrite(engine_a.IN1,LOW);
	digitalWrite(engine_a.IN2,LOW);
	digitalWrite(engine_b.IN1,LOW);
	digitalWrite(engine_b.IN2,LOW);
	Serial.println("Motor stopped");
}

Engine Motor::engine_a={0,0,0,2};
Engine Motor::engine_b={0,0,0,3};


