/*
 * timer.h
 *
 *  Created on: 5 thg 10, 2021
 *      Author: ASUS
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

uint8_t get_flag_Timer1(void);
uint8_t get_flag_Timer2(void);

void setTimer2 (int duration);
void setTimer1 (int duration);

void timer_run();


#endif /* INC_TIMER_H_ */
