#include "rpiServo.h"

// reference: http://www.hertaville.com/rpiservo.html


int unsigned const delayUs = 2000000;
/*
int main(void){

    rpiServo servo;
// Increase angle by 18 deg every 'delayUs' microseconds from 90 to 180
    servo.setAngle(90); // set servo to centre
    usleep(delayUs);
    servo.setAngle(108);
    usleep(delayUs);
    servo.setAngle(126);
    usleep(delayUs);
    servo.setAngle(144);
    usleep(delayUs);
    servo.setAngle(162);
    usleep(delayUs);
    servo.setAngle(180);
    usleep(delayUs);
// Decrease angle by 18 deg every 'delayUs' microseconds from 180 to 90
    servo.setAngle(162);
    usleep(delayUs);
    servo.setAngle(144);
    usleep(delayUs);
    servo.setAngle(126);
    usleep(delayUs);
    servo.setAngle(108);
    usleep(delayUs);
    servo.setAngle(90);
    usleep(delayUs);
// Decrease angle by 18 deg every 'delayUs' microseconds from 90 to 0
    servo.setAngle(72);
    usleep(delayUs);
    servo.setAngle(54);
    usleep(delayUs);
    servo.setAngle(36);
    usleep(delayUs);
    servo.setAngle(18);
    usleep(delayUs);
    servo.setAngle(0);
    usleep(delayUs);
// Increase angle by 18 deg every 'delayUs' microseconds from 0 to 90
    servo.setAngle(18);
    usleep(delayUs);
    servo.setAngle(36);
    usleep(delayUs);
    servo.setAngle(54);
    usleep(delayUs);
    servo.setAngle(72);
    usleep(delayUs);
    servo.setAngle(90);
    usleep(delayUs);
    return 0;
}
*/