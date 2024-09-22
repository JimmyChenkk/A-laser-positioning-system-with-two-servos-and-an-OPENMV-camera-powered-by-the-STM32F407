#include "beep.h"

/*******************************************************************************
* �� �� ��         : BEEP_Init
* ��������		   : ��������ʼ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void BEEP_Init(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	BEEP_PORT_RCC_ENABLE;
	
	GPIO_InitStructure.Pin=BEEP_PIN; 
    GPIO_InitStructure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_InitStructure.Pull=GPIO_PULLUP;          //����
    GPIO_InitStructure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(BEEP_PORT,&GPIO_InitStructure);
	
	HAL_GPIO_WritePin(BEEP_PORT,BEEP_PIN,GPIO_PIN_RESET);
}

