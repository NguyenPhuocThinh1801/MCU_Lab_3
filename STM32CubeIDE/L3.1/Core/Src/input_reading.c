/*
 * input_reading.c
 *
 *  Created on: Nov 5, 2021
 *      Author: hello
 */

#include "main.h"

#define NO_OF_BUTTONS		3

#define BUTTON_PRESSED		GPIO_PIN_RESET

static GPIO_PinState buttonBuffer[NO_OF_BUTTONS];

static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];

void button_reading(void){
	for(int i = 0; i < NO_OF_BUTTONS; i++){
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		switch (i) {
		case 0:
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13);
			break;
		case 1:
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_14);
			break;
		case 2:
			debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);
			break;
		default: break;
		}
		if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
			buttonBuffer[i] = debounceButtonBuffer1[i];
	}
}

unsigned char is_button_pressed(int index){
	if(index >= NO_OF_BUTTONS) return 0;
	return (buttonBuffer[index] == BUTTON_PRESSED)? 1: 0;
}
