/*
 * input_processing.h
 *
 *  Created on: Nov 5, 2021
 *      Author: hello
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

enum ModeState {MODE_1, MODE_2, MODE_3, MODE_4};
enum LedType {RED, YELLOW, GREEN};
enum Coordinates {LED_12, LED_34};

void apply_time_to_traffic_light();
void fsm_for_input_processing();
enum ModeState getMode();

#endif /* INC_INPUT_PROCESSING_H_ */
