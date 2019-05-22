#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

				
enum init_flags { DEFAULT, BROADCOM, P1PHYSICAL, CUSTOM}


/*this initializes the pi as needed by the wiringpi library, more info here:
http://wiringpi.com/reference/setup/ */
void initialize_pi(init_flags f){
	switch(f){
		DEFAULT: /*wiring default pin layout*/
			wiringPiSetup();
			break;
		BROADCOM: /*use the broadcom gpio numbers*/
			wiringPiSetupGpio();
			break;
		P1PHYSICAL: /*uses physical pin numbers on P1 connector*/
			wiringPiSetupPhys();
			break;
		CUSTOM: /* reads /sys/class/gpio for pin numbers*/
			wiringPiSetupSys();
			break;
		default:
			return 0;
	}	
	return 1 ;
}


int main(int argc, char** argv){

	if (!initialize_pi(DEFAULT)){
			puts("error on init");
		}

	return 0;
}

