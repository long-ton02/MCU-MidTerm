#include "display_7SEG.h"

int buffer_7SEG[BUFFER_SIZE] = {0};

void display_7SEG(int index){
	int num = buffer_7SEG[index];

	if (num < 0 || num > 9) return;

	HAL_GPIO_WritePin(SEG_A_GPIO_Port, SEG_A_Pin, (num == 1 || num == 4));
	HAL_GPIO_WritePin(SEG_B_GPIO_Port, SEG_B_Pin, (num == 5 || num == 6));
	HAL_GPIO_WritePin(SEG_C_GPIO_Port, SEG_C_Pin, (num == 2));
	HAL_GPIO_WritePin(SEG_D_GPIO_Port, SEG_D_Pin, (num == 1 || num == 4 || num == 7));
	HAL_GPIO_WritePin(SEG_E_GPIO_Port, SEG_E_Pin, !(num == 0 || num == 2 || num == 6 || num == 8));
	HAL_GPIO_WritePin(SEG_F_GPIO_Port, SEG_F_Pin, (num == 1 || num == 2 || num == 3 || num == 7));
	HAL_GPIO_WritePin(SEG_G_GPIO_Port, SEG_G_Pin, (num == 0 || num == 1 || num == 7));
}


