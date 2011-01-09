/*******************************************************************************
* �ļ����ƣ�jack2.c
* ��Ŀ    ���������
* ����	  ���Ŷ���
* ����	  ��2011��1��9��
* ��Ҫ���ܣ���Ŀ�в˵���ʾ���жϷ�������ʵ��
********************************************************************************/

/*ͷ�ļ�*/
#include "jack2.h" 
#include "stm32f10x_type.h"
#include "myfonts.h"
#include "lcd.h"
#include "dong.h"

/*������ɫ�궨��*/
#define BKCOLOR 0xe555 //HomePage ������ɫ������Ϲ�ģ�
#define GREEN2 0x05e0   //"��ʾ"�ı߿���ɫ
#define BLUE2 0xe7d7   // ������ʾ������ɫ
#define SHU_COLOR Red  //���塰��������ɫ
#define MA_COLOR Yellow  //���塰�롱����ɫ
#define XIANG_COLOR Magenta  //���塰�ࡱ����ɫ
#define KUANG_COLOR Green  //���塰�򡱵���ɫ
#define NAME_COLOR Blue2  //������������ʾ��ɫ
#define YANSHI_ZITI_COLOR Blue     //����ʾ��������ɫ
#define YANSHI_BK_COLOR	 BKCOLOR&0xfa50	 //����ʾ��������ɫ 
#define BOTTOM_COLOR 0xe555   // �׿���ɫ
#define BOTTOM_ZITI_COLOR Blue //�׿�������ɫ
#define MENU_ZITI_COLOR	Black		//�˵�������ɫ
#define MENU_BK_COLOR	Blue2		//�˵����屳��
#define MENU_BIANKUANG_COLOR  0xe555//�˵��߿���ɫ

/*ȫ�ֱ�������*/
extern unsigned char GlobalStateFlag;
extern unsigned char MenuFlag;
extern const unsigned char *Pic_Addr;
extern const unsigned char *FirstPic_Store;

/* ��������*/
/*******************************************************************************
* ��	��: static void  Delay (u32 nCount)
* ��	��: Setups the LCD.
* ��ڲ���: nCount		��ʱ����
* ���ڲ�������
* ˵    ����
* ���÷�����Delay (u32 nCount);
*******************************************************************************/
static void  Delay (u32 nCount)
{
  for(; nCount != 0; nCount--);
}

/****************************************************************************
* ��    �ƣ�void SetPoint(u16 x, u16 y, u16 point)
* ��    �ܣ���ָ�����껭��
* ��ڲ�����x      ������
*           y      ������
*           point  �����ɫ
* ���ڲ�������
* ˵    ����
* ���÷�����SetPoint(10, 10, 0x0fe0);
****************************************************************************/
void SetPoint(u16 x, u16 y, u16 point)
{
  LCD_WriteReg(32, y);
  LCD_WriteReg(33, x);
  LCD_WriteIndex(34);
  LCD_WriteRAM(point);  
}

/****************************************************************************
* ��    �ƣ�void DispHanZi_32(unsigned int x, unsigned int y, unsigned char const *tab_p,
								unsigned int charColor, unsigned int bkColor)
* ��    �ܣ���ָ������(x, y)��ʾ1��32*32����
* ��ڲ�����x          ������
*           y          ������
			tab_p	   �����ַ
*           charColor  �ַ�����ɫ
*           bkColor    �ַ�������ɫ
* ���ڲ�������
* ˵    ������ʾ32*32�ĺ��֣���ɫ��ʾ��
* ���÷�����DispHanZi_32(10, 10, HanZi, 0x0000, 0xffff);
****************************************************************************/
void DispHanZi_32(unsigned int x, unsigned int y, unsigned char const *tab_p, unsigned int charColor, unsigned int bkColor)
{
   unsigned int i = 0, j = 0;
   u32 tmp_char = 0;
   unsigned char k;
   for(i =0 ; i < 32; i++)
   {	
   		tmp_char = 0;
	 	for(k = 0; k <3 ; k++)
		{
			tmp_char = tmp_char|tab_p[k];
			tmp_char = tmp_char<<8;
		}
							   
		tmp_char = tmp_char|tab_p[k];
				
		for (j = 0; j < 32 ;j ++)
		{
		     if ((tmp_char >> 32 - j) & 0x00000001 == 0x00000001)
		     {
		           SetPoint(y+j, x+i, charColor*(i*(j%3))); // �ַ���ɫ
		     }
		      else
		      {
		           SetPoint(y+j, x+i, bkColor); // ������ɫ/
		      }
		}
		tab_p = tab_p + 4;
	}
}
/****************************************************************************
* ��    �ƣ�void DispHanZi_24(unsigned int x, unsigned int y, unsigned char const *tab_p,
								unsigned int charColor, unsigned int bkColor)
* ��    �ܣ���ָ������(x, y)��ʾ1��24*24����
* ��ڲ�����x          ������
*           y          ������
			tab_p	   �����ַ
*           charColor  �ַ�����ɫ
*           bkColor    �ַ�������ɫ
* ���ڲ�������
* ˵    ������ʾ24*24�ĺ���
* ���÷�����DispHanZi_24(10, 10, HanZi, 0x0000, 0xffff);
****************************************************************************/

void DispHanZi_24(unsigned int x, unsigned int y, unsigned char const *tab_p, unsigned int charColor, unsigned int bkColor)
{
   unsigned int i=0, j=0;
   u32 tmp_char=0;
   unsigned char k;
   for (i = 0; i < 24; i++)
   {	
   		tmp_char = 0;
	 	for(k = 0; k < 2; k++)
		{
			tmp_char = tmp_char|tab_p[k];
			tmp_char = tmp_char<<8;
		}
							   
		tmp_char = tmp_char|tab_p[k];
				
		for (j = 0;j < 24; j++)
		{
		     if ( (tmp_char >>24 - j) & 0x00000001 == 0x00000001)
		     {
		           SetPoint(y+j, x+i, charColor); // �ַ���ɫ
		     }
		      else
		      {
		           SetPoint(y+j, x+i, bkColor); // ������ɫ/
		      }
		}
		tab_p = tab_p+3;
	}
}

/****************************************************************************
* ��    �ƣ�void HomePage_Disp(void)
* ��    �ܣ������һ�������ʾ
* ��ڲ�������
* ���ڲ�������
* ˵    ����
* ���÷�����void HomePage_Disp();
****************************************************************************/
void HomePage_Disp()
{
	  LCD_Clear(BKCOLOR);
	 /*��ʾ�������*/	 
	  DispHanZi_32(52, 215, &ShuMaXiangKuang_32[0], SHU_COLOR,BKCOLOR);
	  DispHanZi_32(86, 215, &ShuMaXiangKuang_32[128], MA_COLOR,BKCOLOR);
	  DispHanZi_32(120, 215, &ShuMaXiangKuang_32[256], XIANG_COLOR,BKCOLOR);
	  DispHanZi_32(154, 215, &ShuMaXiangKuang_32[384], KUANG_COLOR,BKCOLOR);
	 /*��ʾ�Ŷ���*/
	  DispHanZi_24(36, 170, Name_24[0], NAME_COLOR, BKCOLOR);
	  DispHanZi_24(60, 170, Name_24[1], NAME_COLOR, BKCOLOR);
	  DispHanZi_24(84, 170, Name_24[2], NAME_COLOR, BKCOLOR);
	  /*��ʾ����ɽ*/
	  DispHanZi_24(132, 170, Name_24[0], NAME_COLOR, BKCOLOR);
	  DispHanZi_24(156, 170, Name_24[3], NAME_COLOR, BKCOLOR);
	  DispHanZi_24(180, 170, Name_24[4], NAME_COLOR, BKCOLOR);
	  /*��ʾ������*/
	  DispHanZi_24(36, 134, Name_24[5], NAME_COLOR, BKCOLOR);
	  DispHanZi_24(60, 134, Name_24[6], NAME_COLOR, BKCOLOR);
	  DispHanZi_24(84, 134, Name_24[7], NAME_COLOR, BKCOLOR);
	  /*��ʾ����*/
	  DispHanZi_24(132, 134, Name_24[0], NAME_COLOR, BKCOLOR);
	  DispHanZi_24(180, 134, Name_24[8], NAME_COLOR, BKCOLOR);
	  /*�����ο�*/
	  LCD_DrawRectFill(86, 63, 72, 40, GREEN2);//���߿�
	  /*��ʾ��ʾ*/
	  DispHanZi_32(90, 67, YanShi_32[0], YANSHI_ZITI_COLOR, YANSHI_BK_COLOR);
	  DispHanZi_32(122, 67, YanShi_32[1], YANSHI_ZITI_COLOR, YANSHI_BK_COLOR);
}

/****************************************************************************
* ��    �ƣ�void Draw_Bottom(unsigned char mod)
* ��    �ܣ�������ĵױ߿���ʾ
* ��ڲ�����mod		�׿�ģʽ����
* ���ڲ�������
* ˵    ����
* ���÷�����Draw_Bottom(mod);
****************************************************************************/
void Draw_Bottom(unsigned char mod)
{
	 LCD_DrawRectFill(0, 0, 240, 24, BOTTOM_COLOR); 	//���׿� 
	 switch(mod)
	 {
		 case 2:
			 DispHanZi_24(96, 0, QueDing_24[0], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 DispHanZi_24(120, 0, QueDing_24[1], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
		 case 1:	 
			 DispHanZi_24(0, 0, XuanZe_24[0], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 DispHanZi_24(24, 0, XuanZe_24[1], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 DispHanZi_24(192, 0, FanHui_24[0], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 DispHanZi_24(216, 0, FanHui_24[1],  BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 break;
		 case 0:
		 	 DispHanZi_24(0, 0, XuanZe_24[0], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 DispHanZi_24(24, 0, XuanZe_24[1], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 break;
	 }
}

/****************************************************************************
* ��    �ƣ�unsigned char XuanZhongXianShi(unsigned char index_old,
*											unsigned char index_new)
* ��    �ܣ����˵�
* ��ڲ�����index_old  ��һ״̬ѡ����
*			index_new  ��ǰ״̬ѡ����
* ���ڲ�����index_new  ��ǰ״̬ѡ����
* ˵    ����������ʾѡ����
* ���÷�����XuanZhongXianShi(1, 2);
****************************************************************************/
unsigned char XuanZhongXianShi(unsigned char index_old, unsigned char index_new)
{
	switch(index_new)
	{
		  	case 1:	//�õ�Ƭ
				LCD_DrawRectFill(0, 132, 77, 27, Magenta);
				DispHanZi_24(2, 133, HuanDengPian_24[0], Black, Green);
				DispHanZi_24(26, 133, HuanDengPian_24[1], Black, Green);
				DispHanZi_24(50, 133, HuanDengPian_24[2], Black, Green);
				break;
			case 2:	//��һ��
				LCD_DrawRectFill(0, 105, 77, 27, Magenta);
	  			DispHanZi_24(2, 106, Di_24, Black, Green);
			    DispHanZi_24(26, 106, YiErSan_24[0], Black, Green);
			    DispHanZi_24(50, 106, Name_24[0], Black, Green);
				break;
			case 3:	//�ڶ���
				LCD_DrawRectFill(0, 78, 77, 27, Magenta);
			    DispHanZi_24(2, 79, Di_24, Black, Green);
			    DispHanZi_24(26, 79, YiErSan_24[1], Black, Green);
			    DispHanZi_24(50, 79, Name_24[0], Black, Green);
				break;
			case 4:	//������
				LCD_DrawRectFill(0, 51, 77, 27, Magenta);
			    DispHanZi_24(2, 52, Di_24, Black, Green);
			    DispHanZi_24(26, 52, YiErSan_24[2], Black, Green);
			    DispHanZi_24(50, 52, Name_24[0], Black, Green);
				break;
			case 5:	//ȡ��
				LCD_DrawRectFill(0, 24, 77, 27, Magenta);
			    DispHanZi_24(2, 25, QiaoXiao_24[0], Black, Green);
			    DispHanZi_24(26, 25, Kong_24, Black, Green);
			    DispHanZi_24(50, 25, QiaoXiao_24[1], Black, Green);
				break;
	}
	switch(index_old)
	{
		  	case 1:	//�õ�Ƭ
				LCD_DrawRectFill(0, 132, 77, 27, MENU_BIANKUANG_COLOR);
				DispHanZi_24(2, 133, HuanDengPian_24[0], MENU_ZITI_COLOR, MENU_BK_COLOR);
				DispHanZi_24(26, 133, HuanDengPian_24[1], MENU_ZITI_COLOR, MENU_BK_COLOR);
				DispHanZi_24(50, 133, HuanDengPian_24[2], MENU_ZITI_COLOR, MENU_BK_COLOR);
				break;
			case 2:	//��һ��
				LCD_DrawRectFill(0, 105, 77, 27, MENU_BIANKUANG_COLOR);
	  			DispHanZi_24(2, 106, Di_24, MENU_ZITI_COLOR, MENU_BK_COLOR);
			    DispHanZi_24(26, 106, YiErSan_24[0], MENU_ZITI_COLOR, MENU_BK_COLOR);
			    DispHanZi_24(50, 106, Name_24[0], MENU_ZITI_COLOR,  MENU_BK_COLOR);
				break;
			case 3:	//�ڶ���
				LCD_DrawRectFill(0, 78, 77, 27, MENU_BIANKUANG_COLOR);
			    DispHanZi_24(2, 79, Di_24, MENU_ZITI_COLOR , MENU_BK_COLOR);
			    DispHanZi_24(26, 79, YiErSan_24[1], MENU_ZITI_COLOR, MENU_BK_COLOR);
			    DispHanZi_24(50, 79, Name_24[0], MENU_ZITI_COLOR, MENU_BK_COLOR);
				break;
			case 4:	//������
				LCD_DrawRectFill(0, 51, 77,27, MENU_BIANKUANG_COLOR);
			    DispHanZi_24(2, 52, Di_24, MENU_ZITI_COLOR,  MENU_BK_COLOR);
			    DispHanZi_24(26, 52, YiErSan_24[2], MENU_ZITI_COLOR, MENU_BK_COLOR);
			    DispHanZi_24(50, 52, Name_24[0], MENU_ZITI_COLOR, MENU_BK_COLOR);
				break;
			case 5:	//ȡ��
				LCD_DrawRectFill(0, 24, 77, 27, MENU_BIANKUANG_COLOR);
			    DispHanZi_24(2, 25, QiaoXiao_24[0], MENU_ZITI_COLOR,  MENU_BK_COLOR);
			    DispHanZi_24(26, 25, Kong_24, MENU_ZITI_COLOR,  MENU_BK_COLOR);
			    DispHanZi_24(50, 25, QiaoXiao_24[1], MENU_ZITI_COLOR,  MENU_BK_COLOR);
				break;
	}

	return 	index_new;
}
/****************************************************************************
* ��    �ƣ�void Draw_Menu(void)
* ��    �ܣ����˵�
* ��ڲ�������
* ���ڲ�������
* ˵    �������Ʋ˵���,����ʶѡ����
* ���÷�����Draw_Menu();
****************************************************************************/
void Draw_Menu(void)
{
	 //  LCD_DrawRectFill(0, 24, 78, 137, Green);
/*ѡ��5 ȡ��*/
	   LCD_DrawRectFill(0, 24, 77, 27, MENU_BIANKUANG_COLOR);
	   DispHanZi_24(2, 25, QiaoXiao_24[0], MENU_ZITI_COLOR, MENU_BK_COLOR);
	   DispHanZi_24(26, 25, Kong_24, MENU_ZITI_COLOR, MENU_BK_COLOR);
	   DispHanZi_24(50, 25, QiaoXiao_24[1], MENU_ZITI_COLOR, MENU_BK_COLOR);
	   Delay(1000);
/*ѡ��4 ������*/
	   LCD_DrawRectFill(0, 51, 77,27, MENU_BIANKUANG_COLOR);
	   DispHanZi_24(2, 52,Di_24, MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(26, 52,YiErSan_24[2], MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(50, 52,Name_24[0], MENU_ZITI_COLOR,MENU_BK_COLOR);
	   Delay(1000);
/*ѡ��3 �ڶ���*/
	   LCD_DrawRectFill(0, 78, 77, 27, MENU_BIANKUANG_COLOR);
	   DispHanZi_24(2, 79, Di_24, MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(26, 79, YiErSan_24[1], MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(50, 79, Name_24[0], MENU_ZITI_COLOR,MENU_BK_COLOR);
   	   Delay(1000);
/*ѡ��2 ��һ��*/
	   LCD_DrawRectFill(0, 105, 77, 27, MENU_BIANKUANG_COLOR);
	   DispHanZi_24(2, 106, Di_24, MENU_ZITI_COLOR, MENU_BK_COLOR);
	   DispHanZi_24(26, 106, YiErSan_24[0], MENU_ZITI_COLOR, MENU_BK_COLOR);
	   DispHanZi_24(50, 106, Name_24[0], MENU_ZITI_COLOR, MENU_BK_COLOR);
	   Delay(1000);
/*ѡ��1 �õ�Ƭ */
	   LCD_DrawRectFill(0, 132, 77, 27, MENU_BIANKUANG_COLOR);
	   DispHanZi_24(2, 133, HuanDengPian_24[0], MENU_ZITI_COLOR, MENU_BK_COLOR);
	   DispHanZi_24(26, 133, HuanDengPian_24[1], MENU_ZITI_COLOR, MENU_BK_COLOR);
	   DispHanZi_24(50, 133, HuanDengPian_24[2], MENU_ZITI_COLOR, MENU_BK_COLOR);
}
/****************************************************************************
* ��    �ƣ�void Menu_1(void)
* ��    �ܣ���
* ��ڲ�������
* ���ڲ�������
* ˵    �����պ���
* ���÷�����Menu_1();
****************************************************************************/
void Menu_1(void)
{}

/****************************************************************************
* ��    �ƣ�void Menu_2(void)
* ��    �ܣ�ʵ�ֲ˵�2�Ĺ���
* ��ڲ�������
* ���ڲ�������
* ˵    ������һ��
* ���÷�����Menu_2();
****************************************************************************/
void Menu_2(void)
{
	Pic_Addr = XiaoGuo_10();
	MenuFlag = 1;
	Draw_Bottom(1);
	GlobalStateFlag = 1;
}
	
/****************************************************************************
* ��    �ƣ�void Menu_3(void)
* ��    �ܣ�ʵ�ֲ˵�3�Ĺ���
* ��ڲ�������
* ���ڲ�������
* ˵    �����õ�Ƭ
* ���÷�����Menu_3();
****************************************************************************/
void Menu_3(void)
{
	Pic_Addr = XiaoGuo_5();
	MenuFlag = 1;
	Draw_Bottom(1);
	GlobalStateFlag = 1;	
}
	
/****************************************************************************
* ��    �ƣ�void Menu_4(void)
* ��    �ܣ�ʵ�ֲ˵�4�Ĺ���
* ��ڲ�������
* ���ڲ�������
* ˵    �����õ�Ƭ
* ���÷�����Menu_4();
****************************************************************************/
void Menu_4(void)
{
	Pic_Addr = XiaoGuo_3();
	MenuFlag = 1;
	Draw_Bottom(1);
	GlobalStateFlag = 1;
}
	
/****************************************************************************
* ��    �ƣ�void Menu_5(void)
* ��    �ܣ�ʵ�ֲ˵�5�Ĺ���
* ��ڲ�������
* ���ڲ�������
* ˵    �����õ�Ƭ
* ���÷�����Menu_5();
****************************************************************************/
void Menu_5(void)
{
	XiaoGuo_13(Pic_Addr);
	Draw_Bottom(1);
	MenuFlag = 1;
	Draw_Bottom(1);
	GlobalStateFlag = 1;
}	
	
/****************************************************************************
* ��    �ƣ�void ChuPing_IT(void)
* ��    �ܣ������ж�
* ��ڲ�������
* ���ڲ�������
* ˵    ���������жϷ������
* ���÷�����ChuPing_IT();
****************************************************************************/				  
void ChuPing_IT(void)
{
	switch(GlobalStateFlag)
	{
		case 0:{
			FirstPic_Store = XiaoGuo_10();
			Draw_Bottom(1);
			GlobalStateFlag = 1;
			break;	
		}
		case 1:{
			break;							  
		}
		case 2:{
			

			switch(MenuFlag)
			{
				case 1:{//�õ�Ƭ
					Pic_Addr = XiaoGuo_1();
					GlobalStateFlag = 3;
					break;	
				}
				case 2:{//��һ��
					Menu_2();
					break;
				}
				case 3:{//�ڶ���
					Menu_3();
					break;
				}
				case 4:{//������
					Menu_4();
					break;
				}
				case 5:{//ȡ��
					Menu_5();
					break;
				}

			}
			break;
		}
		case 3:{
			Pic_Addr = XiaoGuo_2();
			GlobalStateFlag = 4;
			break;
		}
		case 4:{
			Pic_Addr = XiaoGuo_6();
			GlobalStateFlag = 5;
			break;
		}
		case 5:{
			Pic_Addr = XiaoGuo_7();
			GlobalStateFlag = 6;
			break;
		}
		case 6:{
			Pic_Addr = XiaoGuo_8();
			GlobalStateFlag = 7;
			break;
		}
		case 7:{
			Pic_Addr = XiaoGuo_9();
			GlobalStateFlag = 8;
			break;
		}
		case 8:{
			Pic_Addr = XiaoGuo_4();
			GlobalStateFlag = 9;
			break;
		}
		case 9:{
			Pic_Addr = XiaoGuo_11();
			GlobalStateFlag = 10;
			break;
		}
		case 10:{
			Pic_Addr = XiaoGuo_12();
			GlobalStateFlag = 1;
			MenuFlag = 1;
			Draw_Bottom(1);
			break;
		}
	}
}
/****************************************************************************
* ��    �ƣ�void ZuoJian_IT(void)
* ��    �ܣ�����ж�
* ��ڲ�������
* ���ڲ�������
* ˵    ��������жϷ������
* ���÷�����ZuoJian_IT();
****************************************************************************/
void ZuoJian_IT(void)
{
	switch(GlobalStateFlag)
	{
		case 0:{
			break;	
		}
		case 1:{
			Draw_Bottom(2);
			Draw_Menu();

			XuanZhongXianShi(MenuFlag-1, MenuFlag);
			GlobalStateFlag = 2;
			break;
		}
		case 2:{
			MenuFlag++;
			if(MenuFlag == 6)
			{
				MenuFlag=1;
				XuanZhongXianShi(5, 1);
			}
			else
				XuanZhongXianShi(MenuFlag-1, MenuFlag);
			break;
		}
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			GlobalStateFlag = 1;
			MenuFlag = 1;
			Draw_Bottom(1);
			break;
	}
}
/****************************************************************************
* ��    �ƣ�void YouJian_IT(void)
* ��    �ܣ��Ҽ��ж�ʹ����״̬�������״̬
* ��ڲ�������
* ���ڲ�������
* ˵    �����Ҽ��жϷ������
* ���÷�����YouJian_IT();
****************************************************************************/
void YouJian_IT()
{
	GlobalStateFlag = 0;
	MenuFlag = 1;
	Pic_Addr = FirstPic_Store;
	LCD_Clear(BKCOLOR); 
	HomePage_Disp();
}



