/*
 * timer.c
 *
 *  Created on: Nov 5, 2021
 *      Author: hello
 */

#include "main.h"

int timer0_counter = 0;
unsigned char timer0_flag = 0;
int TIMER_CYCLE = 10;

void setTimer0(int duration) {
	timer0_counter = duration / TIMER_CYCLE;
	timer0_flag = 0;
}

void timer0_run() {
	timer0_counter--;
	if(timer0_counter <= 0)
		timer0_flag = 1;
}


unsigned char get_timer0_flag() {
	return timer0_flag;
}
