/*
 * led_display.c
 *
 *  Created on: Nov 5, 2021
 *      Author: hello
 */


#include "main.h"

#define ON			GPIO_PIN_RESET
#define OFF			GPIO_PIN_SET

uint8_t nums[10] = {
		0x0,	// 0
		0x1,	// 1
		0x2,	// 2
		0x3,	// 3
		0x4,	// 4
		0x5,	// 5
		0x6,	// 6
		0x7,	// 7
		0x8,	// 8
		0x9		// 9
};

int count_LED_12;
int count_LED_34;
unsigned char init_mode_1 = 0;


enum LedType led_type_LED_12;
enum LedType led_type_LED_34;

void turn_off()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, OFF);
	init_mode_1 = 0;
}


void display_value_7seg(int coo, int num) {
		int t1 = num / 10;
		int t2 = num % 10;
	switch (coo) {
	case LED_12:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, (nums[t1] >> 3) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, (nums[t1] >> 2) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, (nums[t1] >> 1) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (nums[t1] >> 0) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (nums[t2] >> 3) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (nums[t2] >> 2) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (nums[t2] >> 1) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, (nums[t2] >> 0) & 0x1);
		break;
	case LED_34:
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, (nums[t1] >> 3) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, (nums[t1] >> 2) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (nums[t1] >> 1) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, (nums[t1] >> 0) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, (nums[t2] >> 3) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, (nums[t2] >> 2) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, (nums[t2] >> 1) & 0x1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, (nums[t2] >> 0) & 0x1);
		break;
	}
}

void blinking_single_led(int led)
{
	if(get_timer0_flag()) {
		switch (led) {
		case RED:
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, OFF);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, OFF);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, OFF);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, OFF);
			break;
		case YELLOW:
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, OFF);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, OFF);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, OFF);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, OFF);
			break;
		case GREEN:
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, OFF);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, OFF);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, OFF);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, OFF);
			break;
		default:
			break;
		}
		setTimer0(250);
	}
}

void display_traffic_light() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, OFF);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, OFF);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, OFF);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, OFF);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, OFF);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, OFF);
	switch (led_type_LED_12) {
	case RED:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, ON);
		break;
	case YELLOW:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, ON);
		break;
	case GREEN:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, ON);
		break;
	default:
		break;
	}

	switch (led_type_LED_34) {
	case RED:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, ON);
		break;
	case YELLOW:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, ON);
		break;
	case GREEN:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, ON);
		break;
	default:
		break;
	}
}

void start_mode_1()
{
	if(!init_mode_1) {
		count_LED_12 = get_timer_of_led(RED);
		count_LED_34 = get_timer_of_led(GREEN);
		led_type_LED_12 = RED;
		led_type_LED_34 = GREEN;
		init_mode_1 = 1;
	}
}

void run_traffic_light() {
	if(get_timer0_flag()) {
		display_traffic_light();
		display_value_7seg(LED_12, count_LED_12--);
		if(count_LED_12 <= 0) {
			switch (led_type_LED_12) {
			case RED:
				led_type_LED_12 = GREEN;
				count_LED_12 = get_timer_of_led(GREEN);
				break;
			case YELLOW:
				led_type_LED_12 = RED;
				count_LED_12 = get_timer_of_led(RED);
				break;
			case GREEN:
				led_type_LED_12 = YELLOW;
				count_LED_12 = get_timer_of_led(YELLOW);
				break;
			default:
				break;
			}
		}
		display_value_7seg(LED_34, count_LED_34--);
		if(count_LED_34 <= 0) {
			switch (led_type_LED_34) {
			case RED:
				led_type_LED_34 = GREEN;
				count_LED_34 = get_timer_of_led(GREEN);
				break;
			case YELLOW:
				led_type_LED_34 = RED;
				count_LED_34 = get_timer_of_led(RED);
				break;
			case GREEN:
				led_type_LED_34 = YELLOW;
				count_LED_34 = get_timer_of_led(YELLOW);
				break;
			default:
				break;
			}
		}
		setTimer0(1000);
	}
}


void display_mode(int mode) {
	switch (mode) {
	case MODE_1:
		if(init_mode_1 == 0)
			start_mode_1();
		run_traffic_light();
		break;
	case MODE_2:
		if(init_mode_1 == 1)
			turn_off();
		blinking_single_led(RED);
		display_value_7seg(LED_12, 2);
		break;
	case MODE_3:
		blinking_single_led(YELLOW);
		display_value_7seg(LED_12, 3);
		break;
	case MODE_4:
		blinking_single_led(GREEN);
		display_value_7seg(LED_12, 4);
		break;
	default:
		break;
	}
}
