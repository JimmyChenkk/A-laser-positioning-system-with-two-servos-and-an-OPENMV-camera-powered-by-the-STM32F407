/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "system.h"
#include "led.h"
#include "SysTick.h"
#include "servopwm.h"
#include "servo.h"
#include "key.h"
#include "usart.h"
#include "tftlcd.h"
#include "beep.h"

#define step 10

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int lighton=0;

void delay(u32 i)
{
	while(i--);
}
int main(void)
{
	u8 i=0;
	u8 key=0;
	HAL_Init();
	MX_GPIO_Init();
	SystemClock_Init(8,336,2,7);
	LED_Init();
	KEY_Init();
	SysTick_Init(168);
	TIM3_Init(20000-1,16800-1);  //2s
	USART1_Init(115200);
	TIM14_CH1_PWM_Init(1000-1,1680-1);//20ms
	servo_init();
	TFTLCD_Init();
	BEEP_Init();
	FRONT_COLOR=BLACK;
	delay_ms(1000);
	LED3=!LED3;

	while(1)
	{
		key=KEY_Scan(0);
		switch(key)
		{
		case KEY_UP_PRESS:
			servo_angle[0]+=step;
			break;
		case KEY1_PRESS:
			servo_angle[0]-=step;
			break;
		case KEY2_PRESS:
			servo_angle[1]+=step;
			break;
		case KEY0_PRESS:
			servo_angle[1]-=step;
			break;
		default:
			break;
		}

		LCD_ShowNum(10,220,openmv[0],24,24);
		LCD_ShowNum(10,240,openmv[1],24,24);
		LCD_ShowNum(10,260,openmv[2],24,24);
		LCD_ShowNum(10,280,openmv[3],24,24);
		LCD_ShowNum(10,300,openmv[4],24,24);
		LCD_ShowNum(10,320,openmv[5],24,24);
		LCD_ShowNum(10,340,openmv[6],24,24);
		LCD_ShowNum(10,360,openmv[7],24,24);
		LCD_ShowNum(10,380,openmv[8],24,24);
		LCD_ShowNum(40,400,servo_angle[1],24,24);
		LCD_ShowNum(40,420,servo_angle[0],24,24);

		switch(openmv[5])
		{
		case 0:
			if(lighton==1)
			{
				LED3=!LED3;
				lighton=0;
			}
			servo_angle[0]=90;
			servo_angle[1]=90;
			break;
		case 1:
			if(lighton==0)
			{
				LED3=!LED3;
				lighton=1;
			}
			lasertrack(1);
			break;
		case 2:
			if(lighton==0)
			{
				LED3=!LED3;
				lighton=1;
			}
			if(hitflag==0)
			lasertrack(1);
			else if(hitflag==1)
			lasertrack(2);
			break;
		case 3:
			if(lighton==1)
			{
				LED3=!LED3;
				lighton=0;
			}
			LCD_Fill(10,60,160,200,WHITE);
			LCD_ShowString(10,100,tftlcd_data.width,tftlcd_data.height,24,"Triangle");
			break;
		case 4:
			if(lighton==1)
			{
				LED3=!LED3;
				lighton=0;
			}
			LCD_Fill(10,60,160,200,WHITE);
			LCD_ShowString(10,120,tftlcd_data.width,tftlcd_data.height,24,"Square");
			break;
		case 5:
			if(lighton==1)
			{
				LED3=!LED3;
				lighton=0;
			}
			LCD_Fill(10,60,160,200,WHITE);
			LCD_ShowString(10,140,tftlcd_data.width,tftlcd_data.height,24,"Pentagon");
			break;
		case 6:
			if(lighton==1)
			{
				LED3=!LED3;
				lighton=0;
			}
			LCD_Fill(10,60,160,200,WHITE);
			LCD_ShowString(10,160,tftlcd_data.width,tftlcd_data.height,24,"Hexagon");
			break;
		default:
			break;
		}
		SetServoAngle(5, servo_angle[1]);
		SetServoAngle(6, servo_angle[0]);

		i++;
		if(i%10==0)
		{
			LED1=!LED1;
		}
		delay_ms(10);
	}
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
