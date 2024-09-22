#ifndef _usart_H
#define _usart_H


#include "system.h"
#include "led.h"

#define USART1_REC_LEN  			200  	//�����������ֽ��� 200
	  	
extern u8  USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART1_RX_STA;         		//����״̬���	
extern UART_HandleTypeDef UART1_Handler; //UART���


extern int16_t TargerNum;
extern int16_t Find_Task;
extern int16_t LoR;

extern int16_t openmv[9];

#define RXBUFFERSIZE   1 //�����С
extern u8 aRxBuffer[RXBUFFERSIZE];//HAL��USART����Buffer
extern u8 indx;
void USART1_Init(u32 bound);
#endif
