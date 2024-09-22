#ifndef _led_H
#define _led_H


#include "system.h"

/*  LEDʱ�Ӷ˿ڡ����Ŷ��� */
#define LED1_PORT 				GPIOF   
#define LED1_PIN 				GPIO_PIN_9
#define LED1_PORT_RCC_ENABLE	__HAL_RCC_GPIOF_CLK_ENABLE()

#define LED2_PORT 				GPIOF   
#define LED2_PIN 				GPIO_PIN_10
#define LED2_PORT_RCC_ENABLE	__HAL_RCC_GPIOF_CLK_ENABLE()

#define LED3_PORT 				GPIOF
#define LED3_PIN 				GPIO_PIN_6
#define LED3_PORT_RCC_ENABLE	__HAL_RCC_GPIOF_CLK_ENABLE()

#define LED1 PFout(9)  	
#define LED2 PFout(10) 
#define LED3 PFout(6)//laser

void LED_Init(void);

#endif
