#ifndef INC_SERVO_H_
#define INC_SERVO_H_

#include "system.h"
#include "servopwm.h"
#include "usart.h"

// 目标位置和激光位置
extern int targetX;
extern int targetY;
extern int laserX;
extern int laserY;
extern int hitflag;

extern float servo_angle[2];

void servo_init(void);
void SetServoAngle(uint32_t channel, uint32_t angle);
float PID_Control(float error, float *errorSum, float* lastError);
void lasertrack(int nodenum);
void anglelimit(float* angle);

#endif /* INC_SERVO_H_ */
