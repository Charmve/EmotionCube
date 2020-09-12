#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "TFCard.h"
#include "LED_CUBE.h"
#include "TIM.h"

/* ---------------------------Private variables ------------------------------*/

/* ---------------------------Funcation describ ------------------------------*/
//静态显示						//加循环反复显示，调用前情况标志位
//ShowALL();          //全亮
//ShowNone();					//全灭
//ShowMAGIC();				//魔方
//ShowJJ();						//中国馆

//动态显示
//	ShowCOUNT();			//倒计时54321
//	ShowCUBE();				//立方体
//	ShowSPIRAL();			//螺旋
//	ShowSWIRLS();			//波浪
//	ShowRIPPLE();			//雨滴
//	ShowIMP();				//爆炸
//	ShowSIN();				//正弦   (加循环)
//	ShowFPGA();				//FPGA

int main(void)
{
/* Function Init  ------------------------------------------------------------*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	MSD0_SPI_Configuration();
	delay_init(168);
	uart1_init(9600);
	uart3_init(9600);
	SM12126_GPIO_Init();
	Level_GPIO_Init();
	
	//开机显示中国馆静态图
	while(Cube_Index==9) ShowJJ();

	while(1)
	{
		switch(Cube_Index)
		{
			case 1: Cube_Index = 100;
							ShowFPGA();									//FPGA(小石头)
							SentInstruction();
							break;	
			
			case 2: Cube_Index = 100;
							ShowCOUNT();
							ShowSIN();									//倒计时(动态演示)
//							ShowCUBE();								
							ShowSPIRAL();
							ShowSWIRLS();
							ShowRIPPLE();
							//ShowIMP();
							SentInstruction();
							break;	
			
			case 3: Cube_Index = 100;
							ShowCUBE();									//立方体（移动空间）
							SentInstruction();
							break;	
			
			case 4: Cube_Index = 100;
							ShowSPIRAL();								//螺旋（DNA模型/染色体）
							SentInstruction();
							break;	
			
			case 5: Cube_Index = 100;
							ShowSWIRLS();								//波浪（水木清华）
							SentInstruction();
							break;	
			
			case 6: Cube_Index = 100;
							ShowRIPPLE();ShowRIPPLE();	//雨滴（时间煮雨）
							SentInstruction();
							break;	
			
			case 7: Cube_Index = 100;
							ShowIMP();									//爆炸（电光石火）
							SentInstruction();
							break;	
			
			case 8: Cube_Index = 100;
							ShowSIN();ShowSIN();				//正弦（镜花水月）
							SentInstruction();
							break;
							
			case 13: Cube_Index = 100;
							ShowMagicDy();ShowMagicDy();	 //游戏魔方演示
							ShowMagicDy();ShowMagicDy();ShowMagicDy();
							SentInstruction();
							break;
							
			case 9: JJ_flag=0; while(Cube_Index==9) ShowJJ();  //中国馆静态图
							break;
			case 10: ALL_flag=0; while(Cube_Index==10) ShowALL(); //全亮
							break;
			case 11: NONE_flag=0; while(Cube_Index==11) ShowNONE(); //关闭
							break;
			case 12: MAGIC_flag=0; while(Cube_Index==12) ShowMAGIC(); //魔方静态图
							break;
							
			default:break;
		}
	}
}
