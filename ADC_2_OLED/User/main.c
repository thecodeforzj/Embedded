/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   测试led
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
#include "stm32f10x.h"
#include "bsp_led.h"
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "bsp_adc.h"

void show_float(int coordinate_x,int coordinate_y,float num);
void float_to_tring(int num,char *result);
// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[NOFCHANEL];        

// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

#define SOFT_DELAY Delay(0x0FFFFF);

//void Delay(__IO u32 nCount); 

/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void)
{	
	char adc1[4];
	char adc2[4];
	char adc3[4];
	char adc4[4];
	char adc5[4];
	delay_init();	    	 //延时函数初始化	  
	/* LED 端口初始化 */
	LED_GPIO_Config();	 

	OLED_Init();			//初始化OLED  

		// ADC 初始化
	ADCx_Init();
	
	OLED_Clear(); 
	
	while (1)
	{
		LED1_ON;			  // 亮

		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3 * 2;
//	key0电压
//	ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3 * 2;
		ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3 * 2;
		ADC_ConvertedValueLocal[3] =(float) ADC_ConvertedValue[3]/4096*3.3 * 2;
		ADC_ConvertedValueLocal[4] =(float) ADC_ConvertedValue[4]/4096*3.3 * 2;
		ADC_ConvertedValueLocal[5] =(float) ADC_ConvertedValue[5]/4096*3.3 * 2;

			delay_ms(100);
//			OLED_Clear();
//第一行		
		OLED_ShowCHinese(32,0,0);//电
		OLED_ShowCHinese(48,0,1);//源
		OLED_ShowCHinese(64,0,2);//遥
		OLED_ShowCHinese(80,0,3);//测
//第二行第一列数据
			OLED_ShowString(0,2,"+5vd");
			OLED_Min_ShowChar(32,2,1);
			show_float(36,2,ADC_ConvertedValueLocal[0]);
			OLED_Min_ShowChar(60,2,2);
//第二行第二列数据		
			OLED_ShowString(64+8,2,"-5vz");
			OLED_Min_ShowChar(96+8,2,1);
			show_float(100+8,2,ADC_ConvertedValueLocal[2]);
			
			OLED_Min_ShowChar(60,3,2);			
			
//第三行第一列数据			
			OLED_ShowString(0,4,"+12v");
			OLED_Min_ShowChar(32,4,1);
			show_float(36,4,ADC_ConvertedValueLocal[3]);
			OLED_Min_ShowChar(60,4,2);
//第三行第二列数据			
			OLED_ShowString(64+8,4,"-5vb");
			OLED_Min_ShowChar(96+8,4,1);
			show_float(100+8,4,ADC_ConvertedValueLocal[4]);
			
			OLED_Min_ShowChar(60,5,2);			
			
//第四行第一列数据			
			OLED_ShowString(0,6,"+5va");
			OLED_Min_ShowChar(32,6,1);
			show_float(36,6,ADC_ConvertedValueLocal[5]);
			OLED_Min_ShowChar(60,6,2);
			
			LED1_OFF;		   // 灭

	}
}


void show_float(int coordinate_x,int coordinate_y,float num)
{
	u8 C_Table[] = {'0','1','2','3','4','5','6','7','8','9'};
	int i = 0;
	int temp;
	i = num * 100;
	if(0.2 < num)
	{
		temp = num * 10;
		if((i % 10) > 4)
		{
			temp++;
		}
		OLED_ShowChar(coordinate_x,coordinate_y,C_Table[temp / 10]);
		OLED_Min_ShowChar(coordinate_x + 8,coordinate_y,0);
		OLED_ShowChar(coordinate_x + 11,coordinate_y,C_Table[temp % 10]);
	}
	else
	{
		OLED_ShowChar(coordinate_x,coordinate_y,'0');
	}
//	OLED_ShowChar();

}
/*********************************************END OF FILE**********************/
