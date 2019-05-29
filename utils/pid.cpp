#include "pid.h"
#include <stdio.h>

PID::PID(double p , double i, double d, double sp) : proportion(0), integral(0) , derivative(0) , prev_error(0) 
, kp(p), ki(i), kd(d), setpoint(sp){

	int res = gettimeofday(&(this->prev_time) , NULL);
}




int PID::ComputePID(PID* p){

	/*calculate time*/
	double error = p->setpoint - p->in;

	/*calculate the current time */
	struct timeval dtime;
	int res = gettimeofday(&dtime , NULL);
			/*find the difference and save to prev time*/
	#ifndef DEBUG
		if (res < 0)
			puts("Error in gettimeofday function");
	#endif
	struct timeval results;
	(void)TimevalSubtract(&results, &dtime , &(this->prev_time));
	long int delta = results.tv_usec / 1000; /*convert to ms*/
	p->integral += error * delta;
	p->derivative = (error - p->prev_error) / delta;

	/*we have computed all time based functions*/
	p->prev_error = error;
			/*now updating time*/
	res = gettimeofday(&(p->prev_time) , NULL);
	#ifndef DEBUG
			if (res < 0)
				puts("Error in gettimeofday function");
	#endif

	double kpo = p->kp * error;
	double kio = p->ki * p->integral; 
	double kdo = p->kd * p->derivative;
	#ifndef DEBUG
		std::cout << "calculated prportion : " << kpo << std::endl;
		std::cout << "calculated integral : " << kpi << std::endl;
		std::cout << "calculated derivative : " << kpd << std::endl;
	#endif
	double calc_out = kpo + kio + kdo;
	if ( calc_out > CLAMPED_VALUE_MAX){
		p->out = CLAMPED_VALUE_MAX;
		#ifndef DEBUG
			std::cout << "clamping output MAX" << std::endl;
		#endif	
	} else if (calc_out < CLAMPED_VALUE_MIN) {
		p->out = CLAMPED_VALUE_MIN;
		#ifndef DEBUG
			std::cout << "clamping output MIN" << std::endl;
		#endif
	} else {

		p->out = static_cast<int>(calc_out);
	}

	return 1 ;
}


/*function taken from GNU man page*/
int PID::TimevalSubtract(struct timeval *result, struct timeval *x, struct timeval *y){
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}

