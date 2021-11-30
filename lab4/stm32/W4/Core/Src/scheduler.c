#include "main.h"
#include "scheduler.h"
#include "timer.h"

typedef struct {
	void ( *pTask) ( void ) ;
	uint32_t Delay ;
	uint32_t Period ;
	uint8_t RunMe;
	uint32_t TaskID ;
} sTask ;

// MUST BE ADJUSTED FOR EACH NEW PROJECT
#define SCH_MAX_TASKS 	5
#define NO_TASK_ID 		0

#define ERROR_SCH_CANNOT_DELETE_TASK	1

static sTask SCH_tasks_G[SCH_MAX_TASKS];
static unsigned char Error_code_G = 0;

uint8_t tBuffer[50]={"Task has PID =     at tick              \r\n"};
#define PID_index 			14
#define PID_length 			3
#define tick_index 			26
#define tick_length 		12


void updateBuffer(int tid, int tick) {
	for (int i=0;  i< PID_length;i++) {
		tBuffer[PID_length + PID_index - i] = tid%10+48;
		tid/=10;
	}

	for (int i = 0; i < tick_length; i++) {
		tBuffer[tick_length + tick_index - i] = tick%10+48;
		tick/=10;
	}
}

// --------------- Scheduler ------------------ //
void SCH_Update( void ) {
	// NOTE: calculations are in *TICKS* ( not milliseconds )
	for (unsigned char Index = 0; Index < SCH_MAX_TASKS; Index++) {
		// Check if there is a task at this location
		if (SCH_tasks_G [Index].pTask) {
			if ( SCH_tasks_G[Index].Delay == 0) {
				// The task is due to run
				// Inc . the ’RunMe ’ flag
				SCH_tasks_G[Index].RunMe++;
				if  ( SCH_tasks_G [Index].Period ) {
					// Schedule periodic tasks to run again
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period ;
				}
			} else {
				// Not yet ready to run : just decrement the delay
				SCH_tasks_G[Index].Delay--;

			}
		}
	}
}

uint32_t SCH_Add_Task(void(*pFunction)() ,
		unsigned int DELAY,	unsigned int PERIOD)
{
	unsigned char Index = 0;
	while (( SCH_tasks_G[Index].pTask != 0) && ( Index < SCH_MAX_TASKS))
	{
		Index++;
	}
	if (Index == SCH_MAX_TASKS)
	{
		return SCH_MAX_TASKS;
	}

	SCH_tasks_G[Index].pTask 	= pFunction ;
	SCH_tasks_G[Index].Delay 	= DELAY;
	SCH_tasks_G[Index].Period 	= PERIOD;
	SCH_tasks_G[Index].RunMe 	= 0 ;

	return SCH_tasks_G[Index].TaskID;
}

void SCH_Dispatch_Tasks(UART_HandleTypeDef *huart1 )
{
	unsigned char Index ;

	for ( Index = 0; Index < SCH_MAX_TASKS; Index++) {
		if (SCH_tasks_G[Index].RunMe > 0) {
			(*SCH_tasks_G[Index].pTask)() ; // Run the task
			SCH_tasks_G[Index].RunMe--; // Reset / reduce RunMe flag

			updateBuffer(SCH_tasks_G[Index].TaskID, HAL_GetTick());
			HAL_UART_Transmit(huart1, tBuffer, 50, 100);


			if ( SCH_tasks_G[Index].Period == 0)
			{
				SCH_Delete_Task(Index);
			}
		}
	}
}

/*−−−−−−−−−−−−−−−−−−Delete−−−−−−−−−−−−−−−−−−−−−*/
#define RETURN_NORMAL 	0
#define RETURN_ERROR  	1

uint8_t SCH_Delete_Task(uint8_t taskID) {
	unsigned char TASK_INDEX = -1;

	for (unsigned char Index = 0; Index < SCH_MAX_TASKS; Index++){
		if (SCH_tasks_G[Index].TaskID == taskID) {
			TASK_INDEX = Index;
			break;
		}
	}

	if (TASK_INDEX == -1) {
		return RETURN_ERROR;
	}

	unsigned char Return_code ;

	if (SCH_tasks_G[TASK_INDEX].pTask == 0) {
		Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
		Return_code = RETURN_ERROR;
	} else {
		Return_code = RETURN_NORMAL;
	}

	SCH_tasks_G[TASK_INDEX].pTask 	= 0x0000 ;
	SCH_tasks_G[TASK_INDEX].Delay 	= 0;
	SCH_tasks_G[TASK_INDEX].Period 	= 0;
	SCH_tasks_G[TASK_INDEX].RunMe 	= 0;

	return Return_code;
}

// ---------------- Init-------------------//
void SCH_Init ( void ) {
	for (unsigned char Index = 0; Index < SCH_MAX_TASKS; Index++){
		SCH_tasks_G[Index].TaskID = Index;
	}

	unsigned char i ;
	for (i = 0 ; i < SCH_MAX_TASKS; i ++) {
		SCH_Delete_Task(i);
	}

	Error_code_G = 0;
}

void System_Initialization(void) {
	// Init LED
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
}

