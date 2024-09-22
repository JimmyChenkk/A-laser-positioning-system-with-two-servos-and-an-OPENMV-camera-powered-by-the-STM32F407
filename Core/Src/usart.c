#include "usart.h"

 int16_t TargerNum;
 int16_t Find_Task;
 int16_t LoR;
UART_HandleTypeDef UART1_Handler;

u8 USART1_RX_BUF[USART1_REC_LEN];

u16 USART1_RX_STA=0;
u8 aRxBuffer[RXBUFFERSIZE];
int16_t openmv[9]={0};
uint8_t RxIndex = 0;
u8 indx = 0;

void USART1_Init(u32 bound)
{	
	UART1_Handler.Instance=USART1;
	UART1_Handler.Init.BaudRate=bound;
	UART1_Handler.Init.WordLength=UART_WORDLENGTH_8B;
	UART1_Handler.Init.StopBits=UART_STOPBITS_1;
	UART1_Handler.Init.Parity=UART_PARITY_NONE;
	UART1_Handler.Init.HwFlowCtl=UART_HWCONTROL_NONE;
	UART1_Handler.Init.Mode=UART_MODE_TX_RX;
	HAL_UART_Init(&UART1_Handler);
	
	HAL_UART_Receive_IT(&UART1_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE);//�ú����Ὺ�������жϣ���־λUART_IT_RXNE���������ý��ջ����Լ����ջ���������������
  
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	if(huart->Instance==USART1)
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_USART1_CLK_ENABLE();
	
		GPIO_InitStructure.Pin=GPIO_PIN_9|GPIO_PIN_10;			//PA9
		GPIO_InitStructure.Mode=GPIO_MODE_AF_PP;
		GPIO_InitStructure.Pull=GPIO_PULLUP;
		GPIO_InitStructure.Speed=GPIO_SPEED_FAST;
		GPIO_InitStructure.Alternate=GPIO_AF7_USART1;
		HAL_GPIO_Init(GPIOA,&GPIO_InitStructure);
		
		HAL_NVIC_EnableIRQ(USART1_IRQn);
		HAL_NVIC_SetPriority(USART1_IRQn,3,3);

	}

}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)//如果是USART1
	{
		if((USART1_RX_STA&0x8000)==0)//16位不是1 说明接受未完毕
		{
			if(USART1_RX_STA&0x4000)//14位是1 说明已经接收到帧头0x0d
			{
				if (indx<7)
				{
					indx++;
					openmv[indx]=aRxBuffer[0];
				}
				else
				{
					if( aRxBuffer[0]==0x0a)
					{
						indx=0;
						USART1_RX_STA &= ~0x4000;  // 将第14位清除为0
					}
					else
					{
						USART1_RX_STA=0;
					}
				}
			}
			else
			{
				if(aRxBuffer[0]==0x0d)USART1_RX_STA|=0x4000;//接收到帧头0x0d
				else
				{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=aRxBuffer[0] ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;
				}
			}
		}
	}
}

void USART1_IRQHandler(void)                	
{ 
	u32 timeout=0;
	
	HAL_UART_IRQHandler(&UART1_Handler);
	
	timeout=0;
    while (HAL_UART_GetState(&UART1_Handler) != HAL_UART_STATE_READY)
	{
		timeout++;
		if(timeout>HAL_MAX_DELAY) break;		
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&UART1_Handler, (u8 *)aRxBuffer, RXBUFFERSIZE) != HAL_OK)
	{
		timeout++;
		if(timeout>HAL_MAX_DELAY) break;	
	}
}
