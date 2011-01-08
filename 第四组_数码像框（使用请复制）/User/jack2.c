/*头文件*/
#include "stm32f10x_type.h"
#include "myfonts.h"
#include "jack2.h"
#include "lcd.h"

/*各种颜色宏定义*/
#define BKCOLOR 0xe555 //HomePage 背景颜色（请勿瞎改）
#define GREEN2 0x05e0   //"演示"的边框颜色
#define BLUE2 0xe7d7   // 姓名显示的字体色
#define SHU_COLOR Red  //定义“数”的颜色
#define MA_COLOR Yellow  //定义“码”的颜色
#define XIANG_COLOR Magenta  //定义“相”的颜色
#define KUANG_COLOR Green  //定义“框”的颜色
#define NAME_COLOR Blue2  //定义姓名的显示颜色
#define YANSHI_ZITI_COLOR Blue     //“演示”字体颜色
#define YANSHI_BK_COLOR	 BKCOLOR&0xfa50	 //“演示”背景颜色 
#define BOTTOM_COLOR Green   // 底框颜色
#define BOTTOM_ZITI_COLOR Blue //底框字体颜色
#define MENU_ZITI_COLOR	Black		//菜单字体颜色
#define MENU_BK_COLOR	Blue		//菜单字体背景
#define MENU_BIANKUANG_COLOR  Red//菜单边框颜色

/* 函数定义*/

/*******************************************************************************
* 名	称: static void  Delay (u32 nCount)
* 功	能: Setups the LCD.
* 入口参数: nCount		延时参数
* 出口参数：无
* 说    明：
* 调用方法：Delay (u32 nCount);
*******************************************************************************/
static void  Delay (u32 nCount)
{
  for(; nCount != 0; nCount--);
}

/****************************************************************************
* 名    称：void SetPoint(u16 x,u16 y,u16 point)
* 功    能：在指定座标画点
* 入口参数：x      行座标
*           y      列座标
*           point  点的颜色
* 出口参数：无
* 说    明：
* 调用方法：SetPoint(10,10,0x0fe0);
****************************************************************************/
void SetPoint(u16 x,u16 y,u16 point)
{
  LCD_WriteReg(32, y);
  LCD_WriteReg(33, x);
  LCD_WriteIndex(34);
  LCD_WriteRAM(point);  
}

/****************************************************************************
* 名    称：void DispHanZi_32(unsigned int x,unsigned int y,unsigned char const *tab_p,
								unsigned int charColor,unsigned int bkColor)
* 功    能：在指定座标(x,y)显示1个32*32汉字
* 入口参数：x          行座标
*           y          列座标
			tab_p	   数组地址
*           charColor  字符的颜色
*           bkColor    字符背景颜色
* 出口参数：无
* 说    明：显示32*32的汉字（变色显示）
* 调用方法：DispHanZi_32(10, 10, HanZi, 0x0000, 0xffff);
****************************************************************************/
void DispHanZi_32(unsigned int x,unsigned int y,unsigned char const *tab_p,unsigned int charColor,unsigned int bkColor)
{
   unsigned int i=0, j=0;
   u32 tmp_char=0;
   unsigned char k;
   for (i=0;i<32;i++)
   {	
   		tmp_char=0;
	 	for(k =0;k<3;k++)
		{
			tmp_char = tmp_char|tab_p[k];
			tmp_char=tmp_char<<8;
		}
							   
		tmp_char=tmp_char|tab_p[k];
				
		for (j=0;j<32;j++)
		{
		     if ( (tmp_char >>32 - j) & 0x00000001 == 0x00000001)
		     {
		           SetPoint(y+j,x+i,charColor*(i*(j%3))); // 字符颜色
		     }
		      else
		      {
		           SetPoint(y+j,x+i,bkColor); // 背景颜色/
		      }
		}
		tab_p=tab_p+4;
	}
}
/****************************************************************************
* 名    称：void DispHanZi_24(unsigned int x,unsigned int y,unsigned char const *tab_p,
								unsigned int charColor,unsigned int bkColor)
* 功    能：在指定座标(x,y)显示1个24*24汉字
* 入口参数：x          行座标
*           y          列座标
			tab_p	   数组地址
*           charColor  字符的颜色
*           bkColor    字符背景颜色
* 出口参数：无
* 说    明：显示24*24的汉字
* 调用方法：DispHanZi_24(10, 10, HanZi, 0x0000, 0xffff);
****************************************************************************/

void DispHanZi_24(unsigned int x,unsigned int y,unsigned char const *tab_p,unsigned int charColor,unsigned int bkColor)
{
   unsigned int i=0, j=0;
   u32 tmp_char=0;
   unsigned char k;
   for (i=0;i<24;i++)
   {	
   		tmp_char=0;
	 	for(k =0;k<2;k++)
		{
			tmp_char = tmp_char|tab_p[k];
			tmp_char=tmp_char<<8;
		}
							   
		tmp_char=tmp_char|tab_p[k];
				
		for (j=0;j<24;j++)
		{
		     if ( (tmp_char >>24 - j) & 0x00000001 == 0x00000001)
		     {
		           SetPoint(y+j,x+i,charColor); // 字符颜色
		     }
		      else
		      {
		           SetPoint(y+j,x+i,bkColor ); // 背景颜色/
		      }
		}
		tab_p=tab_p+3;
	}
}

/****************************************************************************
* 名    称：void HomePage_Disp(void)
* 功    能：负责第一画面的显示
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：void HomePage_Disp();
****************************************************************************/
void HomePage_Disp()
{
	  LCD_Clear(BKCOLOR);
	 /*显示数码相框*/	 
	  DispHanZi_32(52, 215, &ShuMaXiangKuang_32[0], SHU_COLOR,BKCOLOR);
	  DispHanZi_32(86, 215, &ShuMaXiangKuang_32[128], MA_COLOR,BKCOLOR);
	  DispHanZi_32(120, 215, &ShuMaXiangKuang_32[256], XIANG_COLOR,BKCOLOR);
	  DispHanZi_32(154, 215, &ShuMaXiangKuang_32[384], KUANG_COLOR,BKCOLOR);
	 /*显示张东杰*/
	  DispHanZi_24(36, 170, Name_24[0], NAME_COLOR,BKCOLOR);
	  DispHanZi_24(60, 170,Name_24[1], NAME_COLOR,BKCOLOR);
	  DispHanZi_24(84, 170, Name_24[2], NAME_COLOR,BKCOLOR);
	  /*显示张振山*/
	  DispHanZi_24(132, 170, Name_24[0], NAME_COLOR,BKCOLOR);
	  DispHanZi_24(156, 170,Name_24[3], NAME_COLOR,BKCOLOR);
	  DispHanZi_24(180, 170, Name_24[4], NAME_COLOR,BKCOLOR);
	  /*显示董西田*/
	  DispHanZi_24(36, 134, Name_24[5], NAME_COLOR,BKCOLOR);
	  DispHanZi_24(60, 134,Name_24[6], NAME_COLOR,BKCOLOR);
	  DispHanZi_24(84, 134, Name_24[7], NAME_COLOR,BKCOLOR);
	  /*显示张力*/
	  DispHanZi_24(132, 134, Name_24[0], NAME_COLOR,BKCOLOR);
	  DispHanZi_24(180, 134,Name_24[8], NAME_COLOR,BKCOLOR);
	  /*画矩形框*/
	  LCD_DrawRectFill(86, 63, 72,40, GREEN2);//画边框
	  /*显示演示*/
	  DispHanZi_32(90, 67,YanShi_32[0], YANSHI_ZITI_COLOR, YANSHI_BK_COLOR);
	  DispHanZi_32(122, 67,YanShi_32[1], YANSHI_ZITI_COLOR, YANSHI_BK_COLOR);
}

/****************************************************************************
* 名    称：void Draw_Bottom(unsigned char mod)
* 功    能：负责画面的底边框显示
* 入口参数：mod		底框模式编码
* 出口参数：无
* 说    明：
* 调用方法：Draw_Bottom(mod);
****************************************************************************/
void Draw_Bottom(unsigned char mod)
{
	 LCD_DrawRectFill(0, 0, 240,24, BOTTOM_COLOR); 	//画底框 
	 switch(mod)
	 {
		 case 2:
			 DispHanZi_24(96, 0, XiangXia_24[0], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 DispHanZi_24(120, 0,XiangXia_24[1], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
		 case 1:	 
			 DispHanZi_24(0, 0, XuanZe_24[0], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 DispHanZi_24(24, 0,XuanZe_24[1], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 DispHanZi_24(192, 0, FanHui_24[0], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 DispHanZi_24(216, 0,FanHui_24[1],  BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 break;
		 case 0:
		 	 DispHanZi_24(0, 0, XuanZe_24[0], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 DispHanZi_24(24, 0,XuanZe_24[1], BOTTOM_ZITI_COLOR, BOTTOM_COLOR);
			 break;
	 }
}

/****************************************************************************
* 名    称：void Draw_Menu(unsigned char index)
* 功    能：描绘菜单
* 入口参数：index		标识
* 出口参数：无
* 说    明：绘制菜单条,并标识选定项
* 调用方法：Draw_Menu(index);
****************************************************************************/
unsigned char XuanZhongXianShi(unsigned char index_old,unsigned char index_new)
{
	switch(index_new)
	{
		  	case 1:	//幻灯片
				LCD_DrawRectFill(0, 132, 77,27, Magenta);
				DispHanZi_24(2, 133,HuanDengPian_24[0], Black, Green);
				DispHanZi_24(26, 133,HuanDengPian_24[1], Black, Green);
				DispHanZi_24(50, 133,HuanDengPian_24[2], Black, Green);
				break;
			case 2:	//第一张
				LCD_DrawRectFill(0, 105, 77,27,Magenta);
	  			DispHanZi_24(2, 106,Di_24, Black, Green);
			    DispHanZi_24(26, 106,YiErSan_24[0], Black, Green);
			    DispHanZi_24(50, 106,Name_24[0], Black, Green);
				break;
			case 3:	//第二张
				LCD_DrawRectFill(0, 78, 77,27, Magenta);
			    DispHanZi_24(2, 79,Di_24, Black, Green);
			    DispHanZi_24(26, 79,YiErSan_24[1], Black, Green);
			    DispHanZi_24(50, 79,Name_24[0], Black, Green);
				break;
			case 4:	//第三张
				LCD_DrawRectFill(0, 51, 77,27, Magenta);
			    DispHanZi_24(2, 52,Di_24, Black, Green);
			    DispHanZi_24(26, 52,YiErSan_24[2], Black, Green);
			    DispHanZi_24(50, 52,Name_24[0], Black, Green);
				break;
			case 5:	//取消
				LCD_DrawRectFill(0, 24, 77,27, Magenta);
			    DispHanZi_24(2, 25, QiaoXiao_24[0], Black, Green);
			    DispHanZi_24(26, 25,Kong_24, Black, Green);
			    DispHanZi_24(50, 25, QiaoXiao_24[1], Black, Green);
				break;
	}
	switch(index_old)
	{
		  	case 1:	//幻灯片
				LCD_DrawRectFill(0, 132, 77,27, MENU_BIANKUANG_COLOR);
				DispHanZi_24(2, 133,HuanDengPian_24[0], MENU_ZITI_COLOR, MENU_BK_COLOR);
				DispHanZi_24(26, 133,HuanDengPian_24[1], MENU_ZITI_COLOR, MENU_BK_COLOR);
				DispHanZi_24(50, 133,HuanDengPian_24[2], MENU_ZITI_COLOR, MENU_BK_COLOR);
				break;
			case 2:	//第一张
				LCD_DrawRectFill(0, 105, 77,27, MENU_BIANKUANG_COLOR);
	  			DispHanZi_24(2, 106,Di_24, MENU_ZITI_COLOR, MENU_BK_COLOR);
			    DispHanZi_24(26, 106,YiErSan_24[0], MENU_ZITI_COLOR, MENU_BK_COLOR);
			    DispHanZi_24(50, 106,Name_24[0], MENU_ZITI_COLOR,  MENU_BK_COLOR);
				break;
			case 3:	//第二张
				LCD_DrawRectFill(0, 78, 77,27, MENU_BIANKUANG_COLOR);
			    DispHanZi_24(2, 79,Di_24, MENU_ZITI_COLOR , MENU_BK_COLOR);
			    DispHanZi_24(26, 79,YiErSan_24[1], MENU_ZITI_COLOR, MENU_BK_COLOR);
			    DispHanZi_24(50, 79,Name_24[0], MENU_ZITI_COLOR, MENU_BK_COLOR);
				break;
			case 4:	//第三张
				LCD_DrawRectFill(0, 51, 77,27, MENU_BIANKUANG_COLOR);
			    DispHanZi_24(2, 52,Di_24, MENU_ZITI_COLOR,  MENU_BK_COLOR);
			    DispHanZi_24(26, 52,YiErSan_24[2], MENU_ZITI_COLOR, MENU_BK_COLOR);
			    DispHanZi_24(50, 52,Name_24[0], MENU_ZITI_COLOR, MENU_BK_COLOR);
				break;
			case 5:	//取消
				LCD_DrawRectFill(0, 24, 77,27, MENU_BIANKUANG_COLOR);
			    DispHanZi_24(2, 25, QiaoXiao_24[0], MENU_ZITI_COLOR,  MENU_BK_COLOR);
			    DispHanZi_24(26, 25,Kong_24, MENU_ZITI_COLOR,  MENU_BK_COLOR);
			    DispHanZi_24(50, 25, QiaoXiao_24[1], MENU_ZITI_COLOR,  MENU_BK_COLOR);
				break;
	}
	return 	index_new;
}
/****************************************************************************
* 名    称：void Draw_Menu(unsigned char index)
* 功    能：描绘菜单
* 入口参数：index		标识
* 出口参数：无
* 说    明：绘制菜单条,并标识选定项
* 调用方法：Draw_Menu(index);
****************************************************************************/
void Draw_Menu(void)
{
	 //  LCD_DrawRectFill(0, 24, 78,137, Green);
/*选项5 取消*/
	   LCD_DrawRectFill(0, 24, 77,27, MENU_BIANKUANG_COLOR);
	   DispHanZi_24(2, 25, QiaoXiao_24[0], MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(26, 25,Kong_24, MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(50, 25, QiaoXiao_24[1], MENU_ZITI_COLOR,MENU_BK_COLOR);
	   Delay(1000);
/*选项4 第三张*/
	   LCD_DrawRectFill(0, 51, 77,27, MENU_BIANKUANG_COLOR);
	   DispHanZi_24(2, 52,Di_24, MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(26, 52,YiErSan_24[2], MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(50, 52,Name_24[0], MENU_ZITI_COLOR,MENU_BK_COLOR);
	   Delay(1000);
/*选项3 第二张*/
	   LCD_DrawRectFill(0, 78, 77,27, MENU_BIANKUANG_COLOR);
	   DispHanZi_24(2, 79,Di_24, MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(26, 79,YiErSan_24[1], MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(50, 79,Name_24[0], MENU_ZITI_COLOR,MENU_BK_COLOR);
   	   Delay(1000);
/*选项2 第一张*/
	   LCD_DrawRectFill(0, 105, 77,27, MENU_BIANKUANG_COLOR);
	   DispHanZi_24(2, 106,Di_24, MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(26, 106,YiErSan_24[0], MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(50, 106,Name_24[0], MENU_ZITI_COLOR,MENU_BK_COLOR);
	   Delay(1000);
/*选项1 幻灯片 */
	   LCD_DrawRectFill(0, 132, 77,27, MENU_BIANKUANG_COLOR);
	   DispHanZi_24(2, 133,HuanDengPian_24[0], MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(26, 133,HuanDengPian_24[1], MENU_ZITI_COLOR,MENU_BK_COLOR);
	   DispHanZi_24(50, 133,HuanDengPian_24[2], MENU_ZITI_COLOR,MENU_BK_COLOR);
}				  




