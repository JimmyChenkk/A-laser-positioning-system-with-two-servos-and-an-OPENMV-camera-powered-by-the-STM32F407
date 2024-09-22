#ifndef _beep_H
#define _beep_H

#include "system.h"

/*  蜂鸣器时钟端口、引脚定义 */
#define BEEP_PORT 				GPIOF   
#define BEEP_PIN 				GPIO_PIN_8
#define BEEP_PORT_RCC_ENABLE	__HAL_RCC_GPIOF_CLK_ENABLE()

#define BEEP PFout(8)

void BEEP_Init(void);


#endif
