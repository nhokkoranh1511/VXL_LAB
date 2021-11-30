/*
 * traffic_light.h
 *
 *  Created on: 5 thg 10, 2021
 *      Author: ASUS
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

void display7SEG_1(int num);
void display7SEG_2(int num);

void traffic_light_init();
void reset_DELTA(void);
void init_after_modifying(void);

void traffic_light_update_1(void);
void traffic_light_update_2(void);

void modify_RED (void);
void modify_YELLOW (void);
void modify_GREEN (void);

uint8_t get_TIME_1(void);
uint8_t get_TIME_2(void);

uint8_t get_RED_DURATION(void);
uint8_t get_YELLOW_DURATION(void);
uint8_t get_GREEN_DURATION(void);

#endif /* INC_TRAFFIC_LIGHT_H_ */
