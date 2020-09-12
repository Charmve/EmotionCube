

#ifndef _SM12126_H
#define _SM12126_H


/* Includes ------------------------------------------------------------------*/
#include "sys.h"
#include "SM12126.h"
#include "delay.h"

//����ܽ�
/*
		SDI1 -- PC8
		SDI2 -- PE2
		SDI3 -- PE3
		CLK -- PC7
		LE  -- PC6
		OE  -- PD15
*/

/* Private define ------------------------------------------------------------*/

//��������λ�Ĵ����Ĵ�������1
#define SDI1							PCout(8)
#define	SDI1_GPIO_PORT	  GPIOC
#define SDI1_GPIO_CLK			RCC_AHB1Periph_GPIOC
#define	SDI1_GPIO_PIN			GPIO_Pin_8
//��������λ�Ĵ����Ĵ�������2
#define SDI2							PEout(2)
#define	SDI2_GPIO_PORT	  GPIOE
#define SDI2_GPIO_CLK			RCC_AHB1Periph_GPIOE
#define	SDI2_GPIO_PIN			GPIO_Pin_2
//��������λ�Ĵ����Ĵ�������3
#define SDI3	PEout(3)
#define	SDI3_GPIO_PORT	  GPIOE
#define SDI3_GPIO_CLK			RCC_AHB1Periph_GPIOE
#define	SDI3_GPIO_PIN			GPIO_Pin_3

//����ʱ���źţ�������ʱ����д����λ�Ĵ���
#define CLK	PCout(7)
#define CLK_GPIO_PORT	GPIOC
#define CLK_GPIO_CLK	RCC_AHB1Periph_GPIOC
#define	CLK_GPIO_PIN	GPIO_Pin_7
//��������������ˣ��ߵ�ƽʱ������͵�ƽʱ����
#define LE            PCout(6)
#define LE_GPIO_PORT	GPIOC
#define LE_GPIO_CLK	  RCC_AHB1Periph_GPIOC
#define LE_GPIO_PIN	  GPIO_Pin_6
//���ʹ���źţ��ߵ�ƽʱOUT0-15�رգ��͵�ƽʱOUT0-15��
#define OE	          PDout(15)
#define OE_GPIO_PORT	GPIOD
#define OE_GPIO_CLK	  RCC_AHB1Periph_GPIOD
#define OE_GPIO_PIN	  GPIO_Pin_15

/* Private function prototypes -----------------------------------------------*/
void SM12126_GPIO_Init(void);
void WriteData(unsigned char Data_A,unsigned char Data_B,unsigned char Data_C);
void OpenLED(void);
void CloseLED(void);
void StartLatch(void);
//void SelectLevel(unsigned char level);
#endif
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
