/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
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
#include "bsp_usart.h"
#include "bsp_SysTick.h"

void clear_Buf(void);
void delay_time(void);
int JudgeStringCmp(const char *strLong, const char *strShort);
#define Buf1_Max 60 					  //串口1缓存长度
#define Buf2_Max 200 					  //串口2缓存长度
char Number2Uart2_Bufing[50][2] = {"1","2","3","4","5","6","7","8","9","10",\
	"11","12","13","14","15","16","17","18","19","20",\
	"21","22","23","24","25","26","27","28","29","30",\
	"31","32","33","34","35","36","37","38","39","40",\
	"41","42","43","44","45","46","47","48","49","50"};
/*************  本地变量声明	**************/
char Uart2_Buf[100];//串口2接收缓存

u8 Times=0,First_Int = 0,shijian=0;

vu8 Timer0_start;	//定时器0延时启动计数器
vu8 Uart2_Start;	//串口2开始接收数据
vu8 Uart2_End;	  //串口2接收数据结束
extern u8 GSM_Config_Flag;
extern u8 GSM_Tx_Counter;
u8 Step_Flag = 0;
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
//深蓝是PA9
//USART1_TX --- TXD
//USART1_RX --- RXD
	u8 i = 0;
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	/* 配置SysTick 为10us中断一次 */
	SysTick_Init();	
//检测SIM卡是否注册成功
	while(1)
	{
		if(0xA5 == GSM_Config_Flag)
		{
			Usart_SendString( DEBUG_USARTx,"AT+CREG?");
			Usart_SendString( DEBUG_USARTx,"\r\n");
			Delay_us(10000);					
		}
		else
		{
			//注册成功
			break;
		}
	}	
	GSM_Config_Flag = 0xA5;
	clear_Buf();
	GSM_Tx_Counter = 0;
//取消回显	
	while(0xA5 == GSM_Config_Flag)
	{

		Usart_SendString(DEBUG_USARTx,"ATE0");
		Usart_SendString( DEBUG_USARTx,"\r\n");
		Delay_us(10000);	
	}
	GSM_Config_Flag = 0xA5;
	clear_Buf();
	GSM_Tx_Counter = 0;
	while(0xA5 == GSM_Config_Flag)
	{
		Usart_SendString(DEBUG_USARTx,"AT+CMGF=1");
		Usart_SendString( DEBUG_USARTx,"\r\n");
		Delay_us(10000);	
	}
	GSM_Config_Flag = 0xA5;
	clear_Buf();
	GSM_Tx_Counter = 0;
  while(1)
	{	
		if(JudgeStringCmp("+CMT",Uart2_Buf))
		{
			//接收到短信
			for(i = 0;i < 50;i++)
			{
				if(JudgeStringCmp(Number2Uart2_Bufing[i],Uart2_Buf))
				{
					//确定是第几条短信
					clear_Buf();
					GSM_Tx_Counter = 0;
					while(0xA5 == GSM_Config_Flag)
					{
						//通过指令获取短信内容
						Usart_SendString(DEBUG_USARTx,"AT+CMGR=");
						Usart_SendString(DEBUG_USARTx,Number2Uart2_Bufing[i]);
//						Usart_SendString(DEBUG_USARTx,"13");
						Usart_SendString(DEBUG_USARTx,"\r\n");
						Delay_us(10000);				
					}
					if(JudgeStringCmp("14356556651",Uart2_Buf))
					{
						if(JudgeStringCmp("nepo",Uart2_Buf))
						{
							i = 100;
							//打开家电
						}
						else if(JudgeStringCmp("esolc",Uart2_Buf))
						{
							i = 101;
							//关闭家电
						}
					}
					break;
				} 
				
			}		
		}				
	}

		
}
/*********************************************END OF FILE**********************/
/*******************************************************************************
* 函数名 : CLR_Buf
* 描述   : 清除串口1缓存数据
* 输入   : 
* 输出   : 
* 返回   : 
* 注意   : 
*******************************************************************************/
void clear_Buf(void)
{
	int i;
	for(i = 0 ;i < 50 ;i++)
	{
		Uart2_Buf[i] = 0x00;		
	}
}


int JudgeStringCmp(const char *str2, const char *str1)
{
	char counter2 = 0;
	while (*str1 != '\0')
	{
		if (*str1 == *str2)
		{
			while (*str1 == str2[counter2])
			{
				str1++;
				counter2++;
				if ('\0' == str2[counter2])
				{
					return 1;
				}
			}
			counter2 = 0;
		}
		else
		{
			str1++;
		}
	}
	return 0;
}




