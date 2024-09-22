#ifndef INC_SERVOPWM_H_
#define INC_SERVOPWM_H_

#include "system.h"

void TIM14_CH1_PWM_Init(u16 per,u16 psc);
void TIM14_SetCompare(u32 channel,u32 compare);

#endif /* INC_SERVOPWM_H_ */
