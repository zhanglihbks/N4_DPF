/******************头文件包含*****************/
#include "stm32f10x_lib.h"
#include "lcd.h"
#include "SPI_Flash.h"
//#include "jack2.h"
#include "INIT.h"
#include "dong.h"

/*******************定义全局变量****************/
unsigned char GlobalStateFlag;
void HomePage_Disp(void);
unsigned char MenuFlag;
const unsigned char *Pic_Addr;
const unsigned char *FirstPic_Store;
/**********主程序*******/
int  main()
{
#ifdef DEBUG
    debug();
#endif
	/* System Clocks Configuration */
	SystemInit();

	/* Enable the FSMC Clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);    

	/* Configure FSMC */
	FSMC_LCD_Init();

	/* Init for LCD */
	LCD_Setup();
	EXTI_Config();
	SPI_Flash_Init();
    NVIC_Configuration();

	/*变量初始化*/
	GlobalStateFlag=0;
	MenuFlag=1;
	Pic_Addr=gImage_picture1;
	HomePage_Disp();
    /* Infinite loop */
    while (1)
    {
    }
}




#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
