# include "main.h"
# include "output_display.h"
# include "input_reading.h"
# include "input_processing.h"
# include "traffic_light.h"
# include "timer.h"

#define NORMAL_MODE 	1
#define MODIFY_RED		2
#define MODIFY_YELLOW	3
#define MODIFY_GREEN	4

enum NUMBER {FIRST, SECOND};
enum NUMBER number_state = FIRST;

void update_traffic_light (void){
switch (get_mode()) {
	case NORMAL_MODE:
		traffic_light_update_1();
		traffic_light_update_2();

		setTimer2(1000);
		break;

	case MODIFY_RED:
		HAL_GPIO_TogglePin(RED1_GPIO_Port, RED1_Pin);
		HAL_GPIO_TogglePin(RED2_GPIO_Port, RED2_Pin);

		HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 1);
		HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, 1);
		HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, 1);
		HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 1);

		setTimer2(500);
		break;

	case MODIFY_YELLOW:
		HAL_GPIO_TogglePin(YELLOW1_GPIO_Port, YELLOW1_Pin);
		HAL_GPIO_TogglePin(YELLOW2_GPIO_Port, YELLOW2_Pin);
		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 1);
		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 1);
		HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, 1);
		HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 1);

		setTimer2(500);
		break;

	case MODIFY_GREEN:
		HAL_GPIO_TogglePin(GREEN1_GPIO_Port, GREEN1_Pin);
		HAL_GPIO_TogglePin(GREEN2_GPIO_Port, GREEN2_Pin);
		HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 1);
		HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 1);
		HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 1);
		HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, 1);

		setTimer2(500);
		break;

	default:
		break;
}
}

void scan_led_7seg(void){
	switch (get_mode()) {
		case NORMAL_MODE:
			switch (number_state) {
				case FIRST:
					HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
					HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);

					display7SEG_1(get_TIME_1()/10);
					display7SEG_2(get_TIME_2()/10);

					HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
					HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);

					number_state = SECOND;
					break;
				case SECOND:
					HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
					HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);

					display7SEG_1(get_TIME_1()%10);
					display7SEG_2(get_TIME_2()%10);

					HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
					HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);

					number_state = FIRST;
					break;
			}

			break;

		case MODIFY_RED:
			switch (number_state) {
				case FIRST:
					HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
					HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);

					display7SEG_1(get_RED_DURATION()/10);
					display7SEG_2(get_mode()/10);

					HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
					HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);

					number_state = SECOND;
					break;
				case SECOND:
					HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
					HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);

					display7SEG_1(get_RED_DURATION()%10);
					display7SEG_2(get_mode()%10);

					HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
					HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);

					number_state = FIRST;
					break;
			}

			break;

		case MODIFY_YELLOW:
			switch (number_state) {
				case FIRST:
					HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
					HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);

					display7SEG_1(get_YELLOW_DURATION()/10);
					display7SEG_2(get_mode()/10);

					HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
					HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);

					number_state = SECOND;
					break;
				case SECOND:
					HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
					HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);

					display7SEG_1(get_YELLOW_DURATION()%10);
					display7SEG_2(get_mode()%10);

					HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
					HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);

					number_state = FIRST;
					break;
			}

			break;

		case MODIFY_GREEN:
			switch (number_state) {
				case FIRST:
					HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
					HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 1);

					display7SEG_1(get_GREEN_DURATION()/10);
					display7SEG_2(get_mode()/10);

					HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
					HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 0);

					number_state = SECOND;
					break;
				case SECOND:
					HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
					HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, 1);

					display7SEG_1(get_GREEN_DURATION()%10);
					display7SEG_2(get_mode()%10);

					HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
					HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, 0);

					number_state = FIRST;
					break;
			}

			break;

		default:
			break;
	}

}
