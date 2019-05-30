#ifndef _MOTOR_H
#define _MOTOR_H
#include "../utils/pid.h"

class Motor{

public:
	Motor(int s);
	/*default constructor for motor with PID loop*/
	Motor(double p, double i, double d, double sp);

	void SetSpeed(int s){this->target_speed = s;}

	~Motor();

	/******* MOVEMENT FXN *****/
	MoveRight(int s);
	MoveLeft(int s);
	MoveFront(int s);
	MoveBack(int s);
	QuickStop(int s);
	SlowStop(int s);

private:

	/*enumeration for PWM const and GPIO pins*/
	enum motor_pins{

		INITIAL_PWM = 0,
		MAX_PWM = 350,
		LEFT_MOTOR = 23,
		LEFT_MOTOR_1 = 24,
		RIGHT_MOTOR	= 27,	
		RIGHT_MOTOR_1 = 17,
		INIT_ATTEMPTS = 5
	};

	PID* create_pid(double p, double i, double d, double sp);

	bool init_pwm();

	PID* pid;

	int target_speed;
	bool is_pwm = false;
	bool is_pid;
};



#endif