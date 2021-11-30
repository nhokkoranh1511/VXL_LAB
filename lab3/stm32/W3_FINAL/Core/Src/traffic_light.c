# include "main.h"
# include "traffic_light.h"
# include "output_display.h"
# include "input_reading.h"
# include "input_processing.h"
# include "timer.h"

enum traffic_light_State 							{RED , YELLOW , GREEN};

static int time_in_State[2] 						= {0, 0};

static enum traffic_light_State light_State[2] 		= {RED, GREEN};

static uint8_t RED_DURATION[2] 						= {5, 5};
static uint8_t YELLOW_DURATION[2] 					= {2, 2};
static uint8_t GREEN_DURATION[2]					= {3, 3};

static uint8_t RED_DELTA[2]							= {0, 0};
static uint8_t YELLOW_DELTA[2]						= {0, 0};
static uint8_t GREEN_DELTA[2]						= {0, 0};

static int NUM[10][7]={
		{0,0,0,0,0,0,1},
		{1,0,0,1,1,1,1},
		{0,0,1,0,0,1,0},
		{0,0,0,0,1,1,0},
		{1,0,0,1,1,0,0},
		{0,1,0,0,1,0,0},
		{0,1,0,0,0,0,0},
		{0,0,0,1,1,1,1},
		{0,0,0,0,0,0,0},
		{0,0,0,0,1,0,0},
};

void display7SEG_1(int num)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, NUM[num][0]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, NUM[num][1]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, NUM[num][2]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, NUM[num][3]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, NUM[num][4]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, NUM[num][5]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, NUM[num][6]);
}

void display7SEG_2(int num)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, NUM[num][0]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, NUM[num][1]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, NUM[num][2]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, NUM[num][3]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, NUM[num][4]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, NUM[num][5]);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, NUM[num][6]);
}

// THIS FUNCTION WAS CALLED TO INITIAL TRAFFIC LIGHT
void traffic_light_init(){
	RED_DELTA[0] = 0;
	RED_DELTA[1] = 0;
	YELLOW_DELTA[0] = 0;
	YELLOW_DELTA[1] = 0;
	GREEN_DELTA[0] = 0;
	GREEN_DELTA[1] = 0;

	RED_DURATION[0] 	= 5;
	YELLOW_DURATION[0] 	= 2;
	GREEN_DURATION[0] 	= 3;

	RED_DURATION[1] 	= 5;
	YELLOW_DURATION[1] 	= 2;
	GREEN_DURATION[1] 	= 3;

	HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 1);
	HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, 1);
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);

	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 1);
	HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, 1);
	HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 0);

	light_State[0] 		= RED;
	time_in_State[0] 	= RED_DURATION[0];

	light_State[1] 		= GREEN;
	time_in_State[1] 	= GREEN_DURATION[1];
}

void init_after_modifying(void){
	RED_DURATION[0] 	= RED_DURATION[0] 		+ RED_DELTA[0];
	YELLOW_DURATION[0] 	= YELLOW_DURATION[0] 	+ YELLOW_DELTA[0];
	GREEN_DURATION[0] 	= GREEN_DURATION[0] 	+ GREEN_DELTA[0];

	RED_DURATION[1] 	= RED_DURATION[1] 		+ RED_DELTA[1];
	YELLOW_DURATION[1] 	= YELLOW_DURATION[1] 	+ YELLOW_DELTA[1];
	GREEN_DURATION[1] 	= GREEN_DURATION[1] 	+ GREEN_DELTA[1];

	HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 1);
	HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, 1);
	HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);

	HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 1);
	HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, 1);
	HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 0);

	light_State[0] 		= RED;
	time_in_State[0] 	= RED_DURATION[0];

	light_State[1] 		= GREEN;
	time_in_State[1] 	= GREEN_DURATION[1];

	RED_DELTA[0] 		= 0;
	YELLOW_DELTA[0] 	= 0;
	GREEN_DELTA[0] 		= 0;
	RED_DELTA[1] 		= 0;
	YELLOW_DELTA[1] 	= 0;
	GREEN_DELTA[1] 		= 0;
}

// THIS FUNCTION WAS CALLED AFTER 1s
void traffic_light_update_1(void){
switch (light_State[0]) {
	case RED:{
		if (--time_in_State[0] == 0){
			time_in_State[0] = GREEN_DURATION[0];
			light_State[0] = GREEN;

			HAL_GPIO_WritePin(RED1_GPIO_Port, 		RED1_Pin, 		1);
			HAL_GPIO_WritePin(YELLOW1_GPIO_Port, 	YELLOW1_Pin, 	1);
			HAL_GPIO_WritePin(GREEN1_GPIO_Port, 	GREEN1_Pin, 	0);
		}
		break;
	}

	case GREEN:
		if (--time_in_State[0] == 0){
			time_in_State[0] = YELLOW_DURATION[0];
			light_State[0] = YELLOW;

			HAL_GPIO_WritePin(RED1_GPIO_Port, 		RED1_Pin, 		1);
			HAL_GPIO_WritePin(GREEN1_GPIO_Port, 	GREEN1_Pin, 	1);
			HAL_GPIO_WritePin(YELLOW1_GPIO_Port, 	YELLOW1_Pin, 	0);
		}

		break;

	case YELLOW:
		if (--time_in_State[0] == 0){
			time_in_State[0] = RED_DURATION[0];
			light_State[0] = RED;

			HAL_GPIO_WritePin(YELLOW1_GPIO_Port, 	YELLOW1_Pin, 	1);
			HAL_GPIO_WritePin(GREEN1_GPIO_Port, 	GREEN1_Pin, 	1);
			HAL_GPIO_WritePin(RED1_GPIO_Port, 		RED1_Pin, 		0);
		}

		break;


	default:
		break;
}
}

// THIS FUNCTION WAS CALLED AFTER 1s
void traffic_light_update_2(void){
switch (light_State[1]) {
	case RED:{
		if (--time_in_State[1] == 0){
			time_in_State[1] = GREEN_DURATION[1];
			light_State[1] = GREEN;

			HAL_GPIO_WritePin(RED2_GPIO_Port, 		RED2_Pin, 		1);
			HAL_GPIO_WritePin(YELLOW2_GPIO_Port, 	YELLOW2_Pin, 	1);
			HAL_GPIO_WritePin(GREEN2_GPIO_Port, 	GREEN2_Pin, 	0);
		}
		break;
	}

	case GREEN:
		if (--time_in_State[1] == 0){
			time_in_State[1] = YELLOW_DURATION[1];
			light_State[1] = YELLOW;

			HAL_GPIO_WritePin(RED2_GPIO_Port, 		RED2_Pin, 		1);
			HAL_GPIO_WritePin(GREEN2_GPIO_Port, 	GREEN2_Pin, 	1);
			HAL_GPIO_WritePin(YELLOW2_GPIO_Port, 	YELLOW2_Pin, 	0);
		}

		break;

	case YELLOW:
		if (--time_in_State[1] == 0){
			light_State[1] = RED;
			time_in_State[1] = RED_DURATION[1];

			HAL_GPIO_WritePin(YELLOW2_GPIO_Port, 	YELLOW2_Pin, 	1);
			HAL_GPIO_WritePin(GREEN2_GPIO_Port, 	GREEN2_Pin, 	1);
			HAL_GPIO_WritePin(RED2_GPIO_Port, 		RED2_Pin, 		0);
		}

		break;

	default:
		break;
}
}

void modify_RED (void){
	if (RED_DURATION[0] + RED_DELTA[0] > 99){
		return;;
	}

	RED_DELTA[0]++;
	GREEN_DELTA[1]++;
}
void modify_YELLOW (void){
	if (YELLOW_DURATION[0] + YELLOW_DELTA[0]> 99){
		 return;
	}

	YELLOW_DELTA[0]++;
	RED_DELTA[1]++;
}
void modify_GREEN (void){
	if (GREEN_DURATION[0] + GREEN_DELTA[0] > 99){
		 return;
	}

	GREEN_DELTA[0]++;
	RED_DELTA[1]++;
}
void reset_DELTA(void) {
	RED_DELTA[0] 		= 0;
	YELLOW_DELTA[0] 	= 0;
	GREEN_DELTA[0] 		= 0;
	RED_DELTA[1] 		= 0;
	YELLOW_DELTA[1] 	= 0;
	GREEN_DELTA[1] 		= 0;
}

uint8_t get_TIME_1(void){
	return time_in_State[0];
}
uint8_t get_TIME_2(void){
	return time_in_State[1];
}

uint8_t get_RED_DURATION(void){
	return RED_DURATION[0] 		+ 	RED_DELTA[0];
}

uint8_t get_YELLOW_DURATION(void){
	return YELLOW_DURATION[0] 	+ 	YELLOW_DELTA[0];
}

uint8_t get_GREEN_DURATION(void){
	return GREEN_DURATION[0] 	+ 	GREEN_DELTA[0];
}
