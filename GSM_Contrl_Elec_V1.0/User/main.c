/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"

void clear_Buf(void);
void delay_time(void);
int JudgeStringCmp(const char *strLong, const char *strShort);
#define Buf1_Max 60 					  //����1���泤��
#define Buf2_Max 200 					  //����2���泤��
char Number2Uart2_Bufing[50][2] = {"1","2","3","4","5","6","7","8","9","10",\
	"11","12","13","14","15","16","17","18","19","20",\
	"21","22","23","24","25","26","27","28","29","30",\
	"31","32","33","34","35","36","37","38","39","40",\
	"41","42","43","44","45","46","47","48","49","50"};
/*************  ���ر�������	**************/
char Uart2_Buf[100];//����2���ջ���

u8 Times=0,First_Int = 0,shijian=0;

vu8 Timer0_start;	//��ʱ��0��ʱ����������
vu8 Uart2_Start;	//����2��ʼ��������
vu8 Uart2_End;	  //����2�������ݽ���
extern u8 GSM_Config_Flag;
extern u8 GSM_Tx_Counter;
u8 Step_Flag = 0;
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
//������PA9
//USART1_TX --- TXD
//USART1_RX --- RXD
	u8 i = 0;
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	/* ����SysTick Ϊ10us�ж�һ�� */
	SysTick_Init();	
//���SIM���Ƿ�ע��ɹ�
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
			//ע��ɹ�
			break;
		}
	}	
	GSM_Config_Flag = 0xA5;
	clear_Buf();
	GSM_Tx_Counter = 0;
//ȡ������	
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
			//���յ�����
			for(i = 0;i < 50;i++)
			{
				if(JudgeStringCmp(Number2Uart2_Bufing[i],Uart2_Buf))
				{
					//ȷ���ǵڼ�������
					clear_Buf();
					GSM_Tx_Counter = 0;
					while(0xA5 == GSM_Config_Flag)
					{
						//ͨ��ָ���ȡ��������
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
							//�򿪼ҵ�
						}
						else if(JudgeStringCmp("esolc",Uart2_Buf))
						{
							i = 101;
							//�رռҵ�
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
* ������ : CLR_Buf
* ����   : �������1��������
* ����   : 
* ���   : 
* ����   : 
* ע��   : 
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




