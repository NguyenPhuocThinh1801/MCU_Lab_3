/*
 * input_processing.c
 *
 *  Created on: Nov 5, 2021
 *      Author: hello
 */


#include "main.h"

enum Button {BUTTON_A, BUTTON_B, BUTTON_C};
enum ModeState modeState = MODE_1;
static int cnt;
static int traffic_light_time[3] = {0};
int release = 0;

void apply_time_to_traffic_light()
{
	if((traffic_light_time[1] + traffic_light_time[2]) == traffic_light_time[0] && traffic_light_time[0] != 0) {
		set_timer_of_led(RED, traffic_light_time[0]);
		set_timer_of_led(YELLOW, traffic_light_time[1]);
		set_timer_of_led(GREEN, traffic_light_time[2]);
	}

}

void fsm_for_input_processing(){
	switch(modeState){
	case MODE_1:
		if(!is_button_pressed(BUTTON_A)) {
			release = 1;
		}
		if(is_button_pressed(BUTTON_A)){
			if(release) {
				modeState = MODE_2;
				cnt = 0;
				display_value_7seg(LED_34, cnt);
				release = 0;
			}
		}
		break;
	case MODE_2:
		if(!is_button_pressed(BUTTON_A) && !is_button_pressed(BUTTON_B) && !is_button_pressed(BUTTON_C)) {
			release = 1;
		}
		else if(is_button_pressed(BUTTON_A)){
			if(release) {
				modeState = MODE_3;
				cnt = 0;
				display_value_7seg(LED_34, cnt);
				release = 0;
			}
		}
		else if(is_button_pressed(BUTTON_B)){
			if(release) {
				cnt++;
				if(cnt > 99) cnt = 0;
				display_value_7seg(LED_34, cnt);
				release = 0;
			}
		}
		else if(is_button_pressed(BUTTON_C)){
			if(release) {
				traffic_light_time[0] = cnt;
				release = 0;
			}
		}
		break;
	case MODE_3:
		if(!is_button_pressed(BUTTON_A) && !is_button_pressed(BUTTON_B) && !is_button_pressed(BUTTON_C)) {
			release = 1;
		}
		else if(is_button_pressed(BUTTON_A)){
			if(release) {
				modeState = MODE_4;
				cnt = 0;
				display_value_7seg(LED_34, cnt);
				release = 0;
			}
		}
		else if(is_button_pressed(BUTTON_B)){
			if(release) {
				cnt++;
				if(cnt > 99) cnt = 0;
				display_value_7seg(LED_34, cnt);
				release = 0;
			}
		}
		else if(is_button_pressed(BUTTON_C)){
			if(release) {
				traffic_light_time[1] = cnt;
				release = 0;
			}
		}
		break;
	case MODE_4:
		if(!is_button_pressed(BUTTON_A) && !is_button_pressed(BUTTON_B) && !is_button_pressed(BUTTON_C)) {
			release = 1;
		}
		else if(is_button_pressed(BUTTON_A)){
			if(release) {
				apply_time_to_traffic_light();
				modeState = MODE_1;
				release = 0;
			}
		}
		else if(is_button_pressed(BUTTON_B)){
			if(release) {
				cnt++;
				if(cnt > 99) cnt = 0;
				display_value_7seg(LED_34, cnt);
				release = 0;
			}
		}
		else if(is_button_pressed(BUTTON_C)){
			if(release) {
				traffic_light_time[2] = cnt;
				release = 0;
			}
		}
		break;
	default: break;
	}
}

enum ModeState getMode() {
	return modeState;
}
