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
void String2Num(char *str,char *zj_num);
void Send_Gsm_Cmd(char * str);

/*************  ���ر�������	**************/
char Uart2_Buf[100];//����2���ջ���

u8 Times=0,First_Int = 0,shijian=0;

vu8 Timer0_start;	//��ʱ��0��ʱ����������
vu8 Uart2_Start;	//����2��ʼ��������
vu8 Uart2_End;	  //����2�������ݽ���
extern u8 GSM_Config_Flag;
extern volatile u8 GSM_Tx_Counter;
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
	u8 zj_cnt = 0;
	char buff[2];
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	/* ����SysTick Ϊ10us�ж�һ�� */
	SysTick_Init();	
//���SIM���Ƿ�ע��ɹ�
	while(0xA5 == GSM_Config_Flag)
	{
			Send_Gsm_Cmd("AT+CREG?");
			Delay_us(10000);					
	}	
	GSM_Config_Flag = 0xA5;
	clear_Buf();
//ȡ������	
	while(0xA5 == GSM_Config_Flag)
	{
		Send_Gsm_Cmd("ATE0");
		Delay_us(10000);	
	}
	GSM_Config_Flag = 0xA5;
	clear_Buf();
	while(0xA5 == GSM_Config_Flag)
	{
		Send_Gsm_Cmd("AT+CMGF=1");
		Delay_us(10000);	
	}
	GSM_Config_Flag = 0xA5;
	clear_Buf();
	while(1)
	{
		Delay_us(100000);
		//���յ�����		
		if(JudgeStringCmp("+CMT",Uart2_Buf))
		{
					String2Num(Uart2_Buf,buff);
					clear_Buf();
					GSM_Config_Flag = 0xA5;
					while(0xA5 == GSM_Config_Flag)
					{
						//ͨ��ָ���ȡ��������
						Usart_SendString(DEBUG_USARTx,"AT+CMGR=");
						Usart_SendString(DEBUG_USARTx,buff);
						Usart_SendString(DEBUG_USARTx,"\r\n");
						Delay_us(10000);				
					}
					if(JudgeStringCmp("15665565341",Uart2_Buf))
					{
						if(JudgeStringCmp("open",Uart2_Buf))
						{
							//�򿪼ҵ�
							//���Գɹ�����
							GSM_Config_Flag = 0xA5;
							clear_Buf();
							while(0xA5 == GSM_Config_Flag)
							{
								Usart_SendString(DEBUG_USARTx,"AT+CSCA=\"+8613010314500\"");
								Usart_SendString( DEBUG_USARTx,"\r\n");
								Delay_us(10000);	
							}
							clear_Buf();
							while(1)
							{
								Usart_SendString(DEBUG_USARTx,"AT+CMGS=\"15665565341\"");
								Usart_SendString( DEBUG_USARTx,"\r\n");
								Delay_us(10000);	
								if(JudgeStringCmp(">",Uart2_Buf))
								{
									break;
								}									
							}
							GSM_Config_Flag = 0xA5;
							while(0xA5 == GSM_Config_Flag)
							{
								Usart_SendString(DEBUG_USARTx,"open successed");						
								Usart_SendByte(DEBUG_USARTx,0x1A);
								Usart_SendString(DEBUG_USARTx,"\r\n");
								Delay_us(1000000);
								if(JudgeStringCmp("+CMGS",Uart2_Buf))
								{
									GSM_Config_Flag = 0xA5;
									break;
								}
							}						
						}
						else if(JudgeStringCmp("close",Uart2_Buf))
						{
							//�رռҵ�
							//���Գɹ�����
							GSM_Config_Flag = 0xA5;
							clear_Buf();
							while(0xA5 == GSM_Config_Flag)
							{
								Usart_SendString(DEBUG_USARTx,"AT+CSCA=\"+8613010314500\"");
								Usart_SendString( DEBUG_USARTx,"\r\n");
								Delay_us(10000);	
							}
							clear_Buf();
							while(1)
							{
								Usart_SendString(DEBUG_USARTx,"AT+CMGS=\"15665565341\"");
								Usart_SendString( DEBUG_USARTx,"\r\n");
								Delay_us(10000);	
								if(JudgeStringCmp(">",Uart2_Buf))
								{
									break;
								}									
							}
							GSM_Config_Flag = 0xA5;
							while(0xA5 == GSM_Config_Flag)
							{
								Usart_SendString(DEBUG_USARTx,"close successed");						
								Usart_SendByte(DEBUG_USARTx,0x1A);
								Usart_SendString(DEBUG_USARTx,"\r\n");
								Delay_us(1000000);
								if(JudgeStringCmp("+CMGS",Uart2_Buf))
								{
									GSM_Config_Flag = 0xA5;
									break;
								}
							}
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
	GSM_Tx_Counter = 0;
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

void String2Num(char *str,char *zj_num)
{
	int num = 0;
	int i = 0;
	while(str[i] != '\0')
	{ 
		if (('0' <= str[i]) && (str[i] <= '9'))
		{
			*zj_num = str[i];
			zj_num++;
		}
		else
		{
			if (('0' <= str[i - 1]) && (str[i - 1] <= '9'))
			{
				break;
			}
		}
		i++;
	}
}

void Send_Gsm_Cmd(char * str)
{
	Usart_SendString(DEBUG_USARTx,str);
	Usart_SendString( DEBUG_USARTx,"\r\n");
}

