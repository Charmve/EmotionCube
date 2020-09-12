#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "TFCard.h"
#include "LED_CUBE.h"
#include "TIM.h"

/* ---------------------------Private variables ------------------------------*/

/* ---------------------------Funcation describ ------------------------------*/
//��̬��ʾ						//��ѭ��������ʾ������ǰ�����־λ
//ShowALL();          //ȫ��
//ShowNone();					//ȫ��
//ShowMAGIC();				//ħ��
//ShowJJ();						//�й���

//��̬��ʾ
//	ShowCOUNT();			//����ʱ54321
//	ShowCUBE();				//������
//	ShowSPIRAL();			//����
//	ShowSWIRLS();			//����
//	ShowRIPPLE();			//���
//	ShowIMP();				//��ը
//	ShowSIN();				//����   (��ѭ��)
//	ShowFPGA();				//FPGA

int main(void)
{
/* Function Init  ------------------------------------------------------------*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	MSD0_SPI_Configuration();
	delay_init(168);
	uart1_init(9600);
	uart3_init(9600);
	SM12126_GPIO_Init();
	Level_GPIO_Init();
	
	//������ʾ�й��ݾ�̬ͼ
	while(Cube_Index==9) ShowJJ();

	while(1)
	{
		switch(Cube_Index)
		{
			case 1: Cube_Index = 100;
							ShowFPGA();									//FPGA(Сʯͷ)
							SentInstruction();
							break;	
			
			case 2: Cube_Index = 100;
							ShowCOUNT();
							ShowSIN();									//����ʱ(��̬��ʾ)
//							ShowCUBE();								
							ShowSPIRAL();
							ShowSWIRLS();
							ShowRIPPLE();
							//ShowIMP();
							SentInstruction();
							break;	
			
			case 3: Cube_Index = 100;
							ShowCUBE();									//�����壨�ƶ��ռ䣩
							SentInstruction();
							break;	
			
			case 4: Cube_Index = 100;
							ShowSPIRAL();								//������DNAģ��/Ⱦɫ�壩
							SentInstruction();
							break;	
			
			case 5: Cube_Index = 100;
							ShowSWIRLS();								//���ˣ�ˮľ�廪��
							SentInstruction();
							break;	
			
			case 6: Cube_Index = 100;
							ShowRIPPLE();ShowRIPPLE();	//��Σ�ʱ�����꣩
							SentInstruction();
							break;	
			
			case 7: Cube_Index = 100;
							ShowIMP();									//��ը�����ʯ��
							SentInstruction();
							break;	
			
			case 8: Cube_Index = 100;
							ShowSIN();ShowSIN();				//���ң�����ˮ�£�
							SentInstruction();
							break;
							
			case 13: Cube_Index = 100;
							ShowMagicDy();ShowMagicDy();	 //��Ϸħ����ʾ
							ShowMagicDy();ShowMagicDy();ShowMagicDy();
							SentInstruction();
							break;
							
			case 9: JJ_flag=0; while(Cube_Index==9) ShowJJ();  //�й��ݾ�̬ͼ
							break;
			case 10: ALL_flag=0; while(Cube_Index==10) ShowALL(); //ȫ��
							break;
			case 11: NONE_flag=0; while(Cube_Index==11) ShowNONE(); //�ر�
							break;
			case 12: MAGIC_flag=0; while(Cube_Index==12) ShowMAGIC(); //ħ����̬ͼ
							break;
							
			default:break;
		}
	}
}
