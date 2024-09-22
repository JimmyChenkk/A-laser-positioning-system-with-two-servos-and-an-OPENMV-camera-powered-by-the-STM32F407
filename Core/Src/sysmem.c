#include "system.h"



//Ê±ÖÓÏµÍ³ÅäÖÃº¯Êý
//Fvco=Fs*(plln/pllm);
//SYSCLK=Fvco/pllp=Fs*(plln/(pllm*pllp));
//Fusb=Fvco/pllq=Fs*(plln/(pllm*pllq));

//Fvco:VCOÆµÂÊ
//SYSCLK:ÏµÍ³Ê±ÖÓÆµÂÊ
//Fusb:USB,SDIO,RNGµÈµÄÊ±ÖÓÆµÂÊ
//Fs:PLLÊäÈëÊ±ÖÓÆµÂÊ,¿ÉÒÔÊÇHSI,HSEµÈ.
//plln:Ö÷PLL±¶ÆµÏµÊý(PLL±¶Æµ),È¡Öµ·¶Î§:64~432.
//pllm:Ö÷PLLºÍÒôÆµPLL·ÖÆµÏµÊý(PLLÖ®Ç°µÄ·ÖÆµ),È¡Öµ·¶Î§:2~63.
//pllp:ÏµÍ³Ê±ÖÓµÄÖ÷PLL·ÖÆµÏµÊý(PLLÖ®ºóµÄ·ÖÆµ),È¡Öµ·¶Î§:2,4,6,8.(½öÏÞÕâ4¸öÖµ!)
//pllq:USB/SDIO/Ëæ»úÊý²úÉúÆ÷µÈµÄÖ÷PLL·ÖÆµÏµÊý(PLLÖ®ºóµÄ·ÖÆµ),È¡Öµ·¶Î§:2~15.

//Íâ²¿¾§ÕñÎª8MµÄÊ±ºò,ÍÆ¼öÖµ:plln=336,pllm=8,pllp=2,pllq=7.
//µÃµ½:Fvco=8*(336/8)=336Mhz
//     SYSCLK=336/2=168Mhz
//     Fusb=336/7=48Mhz
//·µ»ØÖµ:0,³É¹¦;1,Ê§°Ü
void SystemClock_Init(u32 pllm,u32 plln,u32 pllp,u32 pllq)
{
    HAL_StatusTypeDef ret = HAL_OK;
    RCC_OscInitTypeDef RCC_OscInitStructure;
    RCC_ClkInitTypeDef RCC_ClkInitStructure;

    __HAL_RCC_PWR_CLK_ENABLE(); //Ê¹ÄÜPWRÊ±ÖÓ

    //ÏÂÃæÕâ¸öÉèÖÃÓÃÀ´ÉèÖÃµ÷Ñ¹Æ÷Êä³öµçÑ¹¼¶±ð£¬ÒÔ±ãÔÚÆ÷¼þÎ´ÒÔ×î´óÆµÂÊ¹¤×÷
    //Ê±Ê¹ÐÔÄÜÓë¹¦ºÄÊµÏÖÆ½ºâ¡£
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);//ÉèÖÃµ÷Ñ¹Æ÷Êä³öµçÑ¹¼¶±ð1

    RCC_OscInitStructure.OscillatorType=RCC_OSCILLATORTYPE_HSE;    //Ê±ÖÓÔ´ÎªHSE
    RCC_OscInitStructure.HSEState=RCC_HSE_ON;                      //´ò¿ªHSE
    RCC_OscInitStructure.PLL.PLLState=RCC_PLL_ON;//´ò¿ªPLL
    RCC_OscInitStructure.PLL.PLLSource=RCC_PLLSOURCE_HSE;//PLLÊ±ÖÓÔ´Ñ¡ÔñHSE
    RCC_OscInitStructure.PLL.PLLM=pllm; //Ö÷PLLºÍÒôÆµPLL·ÖÆµÏµÊý(PLLÖ®Ç°µÄ·ÖÆµ),È¡Öµ·¶Î§:2~63.
    RCC_OscInitStructure.PLL.PLLN=plln; //Ö÷PLL±¶ÆµÏµÊý(PLL±¶Æµ),È¡Öµ·¶Î§:64~432.
    RCC_OscInitStructure.PLL.PLLP=pllp; //ÏµÍ³Ê±ÖÓµÄÖ÷PLL·ÖÆµÏµÊý(PLLÖ®ºóµÄ·ÖÆµ),È¡Öµ·¶Î§:2,4,6,8.(½öÏÞÕâ4¸öÖµ!)
    RCC_OscInitStructure.PLL.PLLQ=pllq; //USB/SDIO/Ëæ»úÊý²úÉúÆ÷µÈµÄÖ÷PLL·ÖÆµÏµÊý(PLLÖ®ºóµÄ·ÖÆµ),È¡Öµ·¶Î§:2~15.
    ret=HAL_RCC_OscConfig(&RCC_OscInitStructure);//³õÊ¼»¯

    if(ret!=HAL_OK) while(1);

    //Ñ¡ÖÐPLL×÷ÎªÏµÍ³Ê±ÖÓÔ´²¢ÇÒÅäÖÃHCLK,PCLK1ºÍPCLK2
    RCC_ClkInitStructure.ClockType=(RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStructure.SYSCLKSource=RCC_SYSCLKSOURCE_PLLCLK;//ÉèÖÃÏµÍ³Ê±ÖÓÊ±ÖÓÔ´ÎªPLL
    RCC_ClkInitStructure.AHBCLKDivider=RCC_SYSCLK_DIV1;//AHB·ÖÆµÏµÊýÎª1
    RCC_ClkInitStructure.APB1CLKDivider=RCC_HCLK_DIV4; //APB1·ÖÆµÏµÊýÎª4
    RCC_ClkInitStructure.APB2CLKDivider=RCC_HCLK_DIV2; //APB2·ÖÆµÏµÊýÎª2
    ret=HAL_RCC_ClockConfig(&RCC_ClkInitStructure,FLASH_LATENCY_5);//Í¬Ê±ÉèÖÃFLASHÑÓÊ±ÖÜÆÚÎª5WS£¬Ò²¾ÍÊÇ6¸öCPUÖÜÆÚ¡£

    if(ret!=HAL_OK) while(1);

	 //STM32F405x/407x/415x/417x Z°æ±¾µÄÆ÷¼þÖ§³ÖÔ¤È¡¹¦ÄÜ
	if (HAL_GetREVID() == 0x1001)
	{
		__HAL_FLASH_PREFETCH_BUFFER_ENABLE();  //Ê¹ÄÜflashÔ¤È¡
	}
}
