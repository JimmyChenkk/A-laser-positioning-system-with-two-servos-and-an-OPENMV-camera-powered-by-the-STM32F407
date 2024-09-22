#include "servopwm.h"

TIM_HandleTypeDef TIM9_Handler;
TIM_OC_InitTypeDef TIM9_CH1Handler;
TIM_OC_InitTypeDef TIM9_CH2Handler;

void TIM14_CH1_PWM_Init(u16 per,u16 psc)
{
	TIM9_Handler.Instance=TIM9;
	TIM9_Handler.Init.Prescaler=psc;
	TIM9_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;
	TIM9_Handler.Init.Period=per;
	TIM9_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
	HAL_TIM_PWM_Init(&TIM9_Handler);

	TIM9_CH1Handler.OCMode=TIM_OCMODE_PWM1;
	TIM9_CH1Handler.Pulse=per/2;
	TIM9_CH1Handler.OCPolarity=TIM_OCPOLARITY_HIGH;
	HAL_TIM_PWM_ConfigChannel(&TIM9_Handler,&TIM9_CH1Handler,TIM_CHANNEL_1);

	TIM9_CH2Handler.OCMode = TIM_OCMODE_PWM1;
	TIM9_CH2Handler.Pulse = per / 2;
	TIM9_CH2Handler.OCPolarity = TIM_OCPOLARITY_HIGH;
	HAL_TIM_PWM_ConfigChannel(&TIM9_Handler, &TIM9_CH2Handler, TIM_CHANNEL_2);

	// 启动PWM
	HAL_TIM_PWM_Start(&TIM9_Handler,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&TIM9_Handler,TIM_CHANNEL_2);

}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_Initure;
	__HAL_RCC_TIM9_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();

	GPIO_Initure.Pin=GPIO_PIN_5;
	GPIO_Initure.Mode=GPIO_MODE_AF_PP;
	GPIO_Initure.Pull=GPIO_PULLUP;
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;
	GPIO_Initure.Alternate= GPIO_AF3_TIM9;
	HAL_GPIO_Init(GPIOE,&GPIO_Initure);

	GPIO_Initure.Pin=GPIO_PIN_6;
	GPIO_Initure.Mode=GPIO_MODE_AF_PP;
	GPIO_Initure.Pull=GPIO_PULLUP;
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;
	GPIO_Initure.Alternate= GPIO_AF3_TIM9;
	HAL_GPIO_Init(GPIOE,&GPIO_Initure);
}

void TIM14_SetCompare(u32 channel, u32 compare)
{
	switch(channel)
	{
	case 5:
		TIM9->CCR1=compare;
		break;
	case 6:
		TIM9->CCR2=compare;
		break;
	default:
		break;
	}
}
