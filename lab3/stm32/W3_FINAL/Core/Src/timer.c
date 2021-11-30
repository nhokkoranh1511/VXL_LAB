# include "main.h"
# include "input_reading.h"
# include "timer.h"

static int timer1_counter = 0;
static int timer1_flag = 0;

static int timer2_counter = 0;
static int timer2_flag = 0;

static int TIMER_CYCLE = 10;

void setTimer1 (int duration){
	timer1_counter = duration / TIMER_CYCLE ;
	timer1_flag = 0;
}

void setTimer2 (int duration){
	timer2_counter = duration / TIMER_CYCLE ;
	timer2_flag = 0;
}

void timer_run(){
	if(timer1_counter > 0){
			timer1_counter --;

			if( timer1_counter == 0){
				timer1_flag = 1;
			}
	}

	if(timer2_counter > 0){
			timer2_counter --;

			if( timer2_counter == 0){
				timer2_flag = 1;
			}
	}
}


uint8_t get_flag_Timer1(void)
{
	return timer1_flag;
}

uint8_t get_flag_Timer2(void)
{
	return timer2_flag;
}

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	if(htim -> Instance == TIM2 ){
		timer_run();
		button_reading();
	}
}
