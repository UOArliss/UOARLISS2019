#include "motor.h"
#include <stdio.h>


Motor::Motor(int s){
	this->is_pid = false;
	this->target_speed = s;
	this->pid = nullptr;
	if ( init_pwm()!= true){
		/*try again for some time*/
		int i = 1;
		while( i <= INIT_ATTEMPTS){
			if(init_pwm == true){
				#ifndef DEBUG
					std::cout << "Took " << i << " attempts to start PWM" << std::endl;
				#endif
				is_pwm = true;
				break;
			} else {
				#ifndef DEBUG
					std::cout << "Attempt " << i " failed" <<std::endl;
					#endif
				i++;
			}			
		}
	}
	/*pwm should be initialized otherwise we in trouble*/
	
}

Motor::Motor(double p, double i, double d, double sp, int s){
	this->is_pid = true;
	this->pid = create_pid(p,i,d,sp);	
	/*set up PWM on motor*/	
	this->target_speed = s;
	/*change this to a fxn later*/
		if ( init_pwm()!= true){
		/*try again for some time*/
		int i = 1;
		while( i <= INIT_ATTEMPTS){
			if(init_pwm == true){
				#ifndef DEBUG
					std::cout << "Took " << i << " attempts to start PWM" << std::endl;
				#endif
				is_pwm = true;
				break;
			} else {
				#ifndef DEBUG
					std::cout << "Attempt " << i " failed" <<std::endl;
					#endif
				i++;
			}			
		}
	}
}


Motor::~Motor(){
	if ( this->pid != nullptr)
		delete this->pid;
}

PID* Motor::create_pid(double p, double i, double d, double sp){
	p = new PID(p,i,d,sp);
	#ifndef DEBUG
	if (p == nullptr)
		std::cout << "Error creating PID " << std::endl;
	#endif
	return p;
}

bool Motor::init_pwm(){

	/*setup gpio pins check*/
	
	if ( wiringPiSetupGpio() != 0){
		#ifndef DEBUG
		std::cout << "Error in wiring pi setup" << std::endl;
		#endif
		return false;
	}
	pwmSetMode(PWM_MODE_MS); /*set up PWM in ms, enum from wiring pi*/
	softPwmCreate(RIGHT_MOTOR, INITIAL_PWM,PWM_RANGE);
	softPwmCreate(LEFT_MOTOR, INITIAL_PWM,PWM_RANGE);
	return true;
}	

/******** Movement FXN *******/ 

Motor::MoveRight(int s){
	#ifndef DEBUG
		std::cout << "moving right with speed " << s << std::endl;
	#endif
	if ( is_pid != true){
		softPwmWrite(RIGHT_MOTOR,);
		softPwmWrite(LEFT_MOTOR);
	}
		
}
Motor::MoveLeft(int s);
Motor::MoveFront(int s);
Motor::MoveBack(int s);
Motor::QuickStop(int s);
Motor::SlowStop(int s);


