/*
 * set_timer_of_led.c
 *
 *  Created on: Nov 5, 2021
 *      Author: hello
 */


#include "main.h"
#include "set_timer_of_led.h"
#include "led_display.h"

static int redTimer = 5;
static int yellowTimer = 2;
static int greenTimer = 3;

void set_timer_of_led(int led, int duration) {
	switch (led) {
	case RED:
		redTimer = duration;
		break;
	case YELLOW:
		yellowTimer = duration;
		break;
	case GREEN:
		greenTimer = duration;
		break;
	default: break;
	}
}

int get_timer_of_led(int led) {
	switch (led) {
	case RED:
		return redTimer;
	case YELLOW:
		return yellowTimer;
	case GREEN:
		return greenTimer;
	default: return 0;
	}
}
