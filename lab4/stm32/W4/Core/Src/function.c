#include "main.h"
#include "function.h"

void Led_Display_PA3() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
};

void Led_Display_PA4() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
};

void Led_Display_PA5() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
};

void Led_Display_PA6() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
};

void Led_Display_PA7() {
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
};


