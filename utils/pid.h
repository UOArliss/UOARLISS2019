#ifndef PID_H
#define PID_H
/*using timeval structs should be fine, maybe change later if clock
needs better precision*/
#include <sys/time.h>

#define DEBUG

#define CLAMPED_VALUE_MIN 350
#define CLAMPED_VALUE_MAX -350

class PID {

public:
	/* add later for easier setup with bitwise OR
	enum pidoptions{
	
	}*/
	
	PID(double p , double i, double d, double sp);
	/* right now no error checking is done, but later should change to return error and use int as lookup*/
	int ComputePID(PID* p);

private:
	/*timeval struct used from calculating inegral error*/
	struct timeval prev_time;

	/*output of pid loop, for now int because using for PWM*/
	int out ;


	double in;
	double setpoint;
	double prev_error; 

	/*constants for proportion, integral and derivative*/
	double kp;
	double ki;
	double kd;

	double proportion;
	double integral;
	double derivative;

	int TimevalSubtract(struct timeval *result, struct timeval *x, struct timeval *y); 
};


#endif