#include "beep.h"

/*******************************************************************************
* 函 数 名         : BEEP_Init
* 函数功能		   : 蜂鸣器初始化
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void BEEP_Init(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	BEEP_PORT_RCC_ENABLE;
	
	GPIO_InitStructure.Pin=BEEP_PIN; 
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_InitStructure.Pull=GPIO_PULLUP;          //上拉
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(BEEP_PORT,&GPIO_InitStructure);
	
	HAL_GPIO_WritePin(BEEP_PORT,BEEP_PIN,GPIO_PIN_RESET);
}

