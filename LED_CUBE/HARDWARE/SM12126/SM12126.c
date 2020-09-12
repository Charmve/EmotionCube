/**
  ******************************************************************************
  * @file    SM12126.c
  * $Author: SFZ $
  * $Revision: 1 $
  * $Date:: 2018-11-18 16:16:48 +0800 #$
  * @brief   ������.
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "SM12126.h"

/*******************************************************************************
* Function Name  : SM12126_GPIO_Init(void)
* Description    : SM12126оƬ�ܽų�ʼ��
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/

void SM12126_GPIO_Init(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(SDI1_GPIO_CLK|SDI2_GPIO_CLK|SDI3_GPIO_CLK|CLK_GPIO_CLK|LE_GPIO_CLK|OE_GPIO_CLK , ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType= GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed= GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Pin  = SDI1_GPIO_PIN;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = SDI2_GPIO_PIN;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = SDI3_GPIO_PIN;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin  = CLK_GPIO_PIN;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	CLK = 0;
//	delay_us(1);
	
	GPIO_InitStructure.GPIO_Pin  = LE_GPIO_PIN;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	LE = 0;
//	delay_us(1);
	
	GPIO_InitStructure.GPIO_Pin  = OE_GPIO_PIN;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	OE = 1;
//	delay_us(1);
}

/*******************************************************************************
* Function Name  : WriteData(unsigned short Data16Bits_1,unsigned short Data16Bits_2,unsigned short Data16Bits_3)
* Description    : ��оƬд��һ��16λ���ݣ����λ�ȴ��䣬��ӦOUT15-���λ��OUT14-�θ�λ...OUT0-���λ
* Input          : 4λ16��������0xXXXX
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void WriteData(unsigned char Data_A,unsigned char Data_B,unsigned char Data_C)
{
	SDI1 = Data_A;
	SDI2 = Data_B;
	SDI3 = Data_C;
//	delay_us(1);
	CLK = 1;
//	delay_us(1);
	CLK = 0;
//	delay_us(1);
}

/*******************************************************************************
* Function Name  : OpenLED(void)
* Description    : ���������������
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void OpenLED(void)
{
	LE = 1;
	LE = 0;
	OE = 0;
}

/*******************************************************************************
* Function Name  : CloseLED(void)
* Description    : �ر����
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void CloseLED(void)
{
	OE = 1;
}

void StartLatch(void)
{
	LE = 1;
//	delay_us(1);
	LE = 0;
//	delay_us(1);
}
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
