#include "servo.h"
#include "SysTick.h"
#include "math.h"
#include "beep.h"

#define SERVO_MIN_ANGLE 0   // 舵机最小角度
#define SERVO_MIDDLE_ANGLE 90 //中值
#define SERVO_MAX_ANGLE 180  // 舵机最大角度

float servo_angle[2] = {SERVO_MIDDLE_ANGLE , SERVO_MIDDLE_ANGLE};
int hitflag=0;
int lasthitflag=0;
int16_t lastopenmv[2]={0};
// 目标位置和激光位置
int targetX = 0;
int targetY = 0;
int laserX = 0;
int laserY = 0;

// PID 控制参数
float Kp = 0.1, Ki = 0, Kd = 0;
float panErrorSum = 0, tiltErrorSum = 0;
float lastPanError = 0, lastTiltError = 0;

void SetServoAngle(uint32_t channel, uint32_t angle)
{
    uint32_t compare =50+angle*200/180;
    switch(channel)
    	{
    	case 5:
    		  TIM14_SetCompare(5,compare);
    		break;
    	case 6:
    		TIM14_SetCompare(6,compare);
    		break;
    	default:
    		break;
    	}

}

void servo_init(void)
{
    SetServoAngle(5, SERVO_MIDDLE_ANGLE);
    SetServoAngle(6, SERVO_MIDDLE_ANGLE);
}

float PID_Control(float error, float *errorSum, float* lastError) {
    *errorSum += error;  // 积分部分
    float dError = error - *lastError;  // 微分部分
    *lastError = error;  // 记录上一个误差

    // 返回 PID 控制计算结果
    return Kp * error + Ki * (*errorSum) + Kd * dError;
}

void lasertrack(int nodenum) {

	if(openmv[6]<250 && openmv[6]>0 && openmv[7]<250 && openmv[7]>0)
	{
	//hitflag=0;
	targetX=openmv[2*nodenum-1];
	targetY=openmv[2*nodenum];
	laserX=openmv[6];
	laserY=openmv[7];
	int panError = targetX - laserX;
	int tiltError = targetY - laserY;

    // 计算 PID 输出
    float panOutput = PID_Control(panError, &panErrorSum, &lastPanError);
    float tiltOutput = PID_Control(tiltError, &tiltErrorSum, &lastTiltError);

    // 将输出应用于舵机
    servo_angle[1] -= panOutput;  // 水平
    servo_angle[0] -= tiltOutput;   //垂直
    anglelimit(&servo_angle[1]);
    anglelimit(&servo_angle[0]);
	}
	else if( (  (lastopenmv[1]<250&&lastopenmv[1]>0&&openmv[7]>250) || (lastopenmv[0]<250&&lastopenmv[0]>0&&openmv[6]>250)  )&& hitflag==lasthitflag)
	{
		hitflag++;
		BEEP=!BEEP;
		delay_ms(500);
		BEEP=!BEEP;
		//LED3=!LED3;
	}
	lastopenmv[0]=openmv[6];
	lastopenmv[1]=openmv[7];
	lasthitflag=hitflag;
	delay_ms(500);
}

void anglelimit(float* angle)
{
	if(*angle >SERVO_MAX_ANGLE)
		*angle=SERVO_MAX_ANGLE;
	if(*angle <SERVO_MIN_ANGLE)
		*angle=SERVO_MIN_ANGLE;
}
