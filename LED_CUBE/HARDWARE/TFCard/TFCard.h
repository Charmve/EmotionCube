#ifndef __TFCARD_H
#define __TFCARD_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "delay.h"
#include "sys.h"
#include "ff.h"
#include "usart.h"
#include "diskio.h"
#include "integer.h"
#include "ffconf.h"
#include "SPI_MSD0_Driver.h"
#include "SM12126.h"

/* Private define ------------------------------------------------------------*/
//����������С����
#define ReadFileNum 10368

/* Private variables ---------------------------------------------------------*/
extern	FATFS fs;			//Fatfs�ļ�ϵͳ����
extern	FIL fnew;			//�ļ�����
extern	UINT fnum;			//�ļ��ɹ���д������
extern	BYTE buffer[ReadFileNum];		//��������
extern unsigned char Face[4][5184];	//3*12*12*3

/* Private function prototypes -----------------------------------------------*/
void TFCard_Init(void);
void TFCard_Deinit(void);
void OpenFile(const char* Filename);
void ReadFile(void);
void CloseFile(void);
int convert(void);
#endif 

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
