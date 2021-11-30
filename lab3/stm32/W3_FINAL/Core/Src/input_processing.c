# include "main.h"
# include "input_processing.h"
# include "input_reading.h"
# include "traffic_light.h"
# include "timer.h"
# define N0_OF_BUTTONS 3

#define BUTTON1 	0
#define BUTTON2 	1
#define BUTTON3 	2

enum ButtonState { BUTTON_RELEASED , BUTTON_PRESSED , BUTTON_PRESSED_MORE_THAN_1_SECOND } ;
static enum ButtonState buttonState[N0_OF_BUTTONS] = {BUTTON_RELEASED , BUTTON_RELEASED , BUTTON_RELEASED};

#define NORMAL_MODE 	1
#define MODIFY_RED		2
#define MODIFY_YELLOW	3
#define MODIFY_GREEN	4
#define WRONG_MODE		5

static uint8_t modeBuffer;

uint8_t get_mode (void){
	return modeBuffer;
}


void button_init(){
	//modeBuffer = NORMAL_MODE;
	buttonState[BUTTON1] = BUTTON_RELEASED;
	buttonState[BUTTON2] = BUTTON_RELEASED;
	buttonState[BUTTON3] = BUTTON_RELEASED;
}

void fsm_for_input_processing ( void ){
for (int i = 0; i < N0_OF_BUTTONS; i++) {
switch (i) {
	case BUTTON1:{
		switch (buttonState[i]){
			case BUTTON_RELEASED :{
				if( is_button_pressed (BUTTON1)){
					buttonState[i] = BUTTON_PRESSED ;

					modeBuffer++;

					if (modeBuffer == WRONG_MODE){
						reset_DELTA();
						init_after_modifying();
						setTimer2(1010);
						setTimer1(10);
						modeBuffer = NORMAL_MODE;
					}
				}

				break;
			}

			case BUTTON_PRESSED :{
				if (! is_button_pressed (BUTTON1)){
					buttonState[i] = BUTTON_RELEASED ;
				} else {
					if( is_button_pressed_1s (BUTTON1) ){
						buttonState[i] = BUTTON_PRESSED_MORE_THAN_1_SECOND ;
					}
				}
				break ;
			}

			case BUTTON_PRESSED_MORE_THAN_1_SECOND :{
				if (! is_button_pressed (BUTTON1)){
					buttonState[i] = BUTTON_RELEASED ;
				}
				// todo
				break ;
			}
		}

		break;
	}

	case BUTTON2: {
		switch ( buttonState[i] ){
			case BUTTON_RELEASED : {
				if( is_button_pressed (BUTTON2)){
					buttonState[i] = BUTTON_PRESSED;

					if (modeBuffer != NORMAL_MODE){
						switch (modeBuffer) {
							case MODIFY_RED:
								modify_RED();
								break;
							case MODIFY_YELLOW:
								modify_YELLOW();
								break;
							case MODIFY_GREEN:
								modify_GREEN();
								break;
							default:
								break;
						}
					}
				}

				break ;
			}

			case BUTTON_PRESSED :{
				if (! is_button_pressed (BUTTON2)){
					buttonState[i] = BUTTON_RELEASED ;
				} else {
					if( is_button_pressed_1s (BUTTON2) ){
						buttonState[i] = BUTTON_PRESSED_MORE_THAN_1_SECOND ;
					}
				}
				break ;
			}

			case BUTTON_PRESSED_MORE_THAN_1_SECOND :
				if (! is_button_pressed (BUTTON2)){
					buttonState[i] = BUTTON_RELEASED ;
				}
				// todo
				break ;
		}

	break;
	}

	case BUTTON3:{
		switch ( buttonState[i] ){
			case BUTTON_RELEASED :{
				if( is_button_pressed (BUTTON3)){
					buttonState[i] = BUTTON_PRESSED ;

					if (modeBuffer != NORMAL_MODE && modeBuffer != WRONG_MODE){
						init_after_modifying();
						setTimer2(1010);
						setTimer1(10);
						modeBuffer = NORMAL_MODE;
					}
				}
			}

				break ;

			case BUTTON_PRESSED :{
				if (! is_button_pressed (BUTTON3)){
					buttonState[i] = BUTTON_RELEASED ;
				} else {
					if( is_button_pressed_1s (BUTTON3) ){
						buttonState[i] = BUTTON_PRESSED_MORE_THAN_1_SECOND ;
					}
				}
				break ;
			}

			case BUTTON_PRESSED_MORE_THAN_1_SECOND :{
				if (! is_button_pressed (BUTTON3)){
					buttonState[i] = BUTTON_RELEASED ;
				}
				// todo
				break ;
			}
		}


	break;
	}

	default:
		break;
}

}
}
