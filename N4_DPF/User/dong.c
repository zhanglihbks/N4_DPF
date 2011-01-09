/*******************************************************************************
* �ļ����ƣ�dong.c
* ��Ŀ    ���������
* ����	  ��������
* ����	  ��2011��1��9��
* ��Ҫ���ܣ�ͼƬ�ĸ�����Ч��ʾ
********************************************************************************/

#include "lcd.h"
#include "stm32f10x_lib.h"
#include "dong.h"

extern void address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
extern void    LCD_WriteRAM(unsigned int val);

/*******************************************************************************
* ��������  : Delay1
* ˵��      : ��ʱ����
* ����      : ��ʱ
* ����      : int
* ���÷�ʽ  : ��
*******************************************************************************/
void  Delay1 (int nCount)
{
  	for(; nCount != 0; nCount--);
}
/*******************************************************************************
* ��������  : Delay_long
* ˵��      : ��ʱ����
* ����      : �ϳ�����ʱ
* ����      : int
* ���÷�ʽ  : ��
*******************************************************************************/
void  Delay_long(int nCount)
{
  	Delay1(nCount);
	Delay1(nCount);
	Delay1(nCount);
	Delay1(nCount);
}
/*******************************************************************************
* ��������  : gImage_Dis
* ˵��      : ��ʾͼƬÿһ������
* ����      : ��
* ����      : const unsigned char gImage_Dis[],int i,int j
* ���÷�ʽ  : ��
*******************************************************************************/
void gImage_Dis(const unsigned char gImage_Dis[],int i,int j)
{
	unsigned int dd;
  	dd=(0x00|gImage_Dis[j+i*2+1])<<8;
	dd=dd|gImage_Dis[j+i*2];
	LCD_WriteRAM(dd);
}
/*******************************************************************************
* ��������  : xiaoguo1
* ˵��      : ͼƬ�ɶ�����ײ�����
* ����      : ��Ч1
* ����      : ��
* ���÷�ʽ  : ��
*******************************************************************************/
const unsigned char * XiaoGuo_1(void)
{
	int i; 	
	LCD_WriteReg(0x0003, 0x1038); // ����ͼƬд�뷽ʽ 
//	LCD_Clear(Black);
	address_set(0,0,239,319);
   	for(i=0;i<153600/2;i++)
	{
		gImage_Dis(gImage_picture1,i,0);
		Delay1(0xf);
	}
	return gImage_picture1;
} 
 /*******************************************************************************
* ��������  : xiaoguo2
* ˵��      : ͼƬ�ɵײ��򶥲�����
* ����      : ��Ч2
* ����      : ��
* ���÷�ʽ  : ��
*******************************************************************************/
const unsigned char * XiaoGuo_2(void)
{
	int i; 	
	LCD_WriteReg(0x0003, 0x1008); // ����ͼƬд�뷽ʽ 
//	LCD_Clear(Black);
	address_set(0,0,239,319);
   	for(i=153600/2;i>0;i--)
	{
		gImage_Dis(gImage_picture2,i,0);
		Delay1(0xf);
	}
	return gImage_picture2;
}


/*******************************************************************************
* ��������  : xiaoguo3
* ˵��      : �����������
* ����      : ��Ч3
* ����      : ��
* ���÷�ʽ  : ��
*******************************************************************************/
const unsigned char *  XiaoGuo_3(void)
{	
	int i,d,b; 
	LCD_WriteReg(0x0003, 0x1038); 
	for(d=0;d<32;d++)
	{	
 		for(b=0;b<240;b++)
	    {  
			address_set(b,310-10*d,b,320-10*d);
			for(i=((310-10*d)+(b*320));i<=((320-10*d)+320*b);i++)	 
				gImage_Dis(gImage_picture3,i,0);	
		}
	}
	return gImage_picture3;
}
/*******************************************************************************
* ��������  : xiaoguo4
* ˵��      : �������ҽ���
* ����      : ��Ч4
* ����      : ��
* ���÷�ʽ  : ��
*******************************************************************************/
const unsigned char * XiaoGuo_4(void)
{
	int i,d,b; 
	LCD_WriteReg(0x0003, 0x1038); 
	for(d=0;d<32;d++)
	{	
		for(b=0;b<240;b++)	  
	    {  
			address_set(b,10*d,b,10+10*d);
			for(i=(10*d+(b*320));i<=((10+10*d)+320*b);i++)
	  		gImage_Dis(gImage_picture1,i,0);
		}
	}
	return gImage_picture1;
}
/*******************************************************************************
* ��������  : xiaoguo5
* ˵��      : ���Ͻǽ���
* ����      : ��Ч5
* ����      : ��
* ���÷�ʽ  : ��
*******************************************************************************/
const unsigned char *  XiaoGuo_5(void)
{
	int i,b,d; 
	LCD_WriteReg(0x0003, 0x1038); 
	for(d=0;d<24;d++)
	{	
	  
		address_set(d*10,0,d*10+10,319);
	    for(i = d*3200; i < (3200+d*3200); i++)	 
			  gImage_Dis(gImage_picture2,i,0);	 /*�ɺ�����ʾ*/
		  	 
	    for(b=0;b<230;b++)
	    {  
			address_set(10+b,310-10*d,10+b,320-10*d);
			for(i=((310-10*d)+((10+b)*320));i<=((320-10*d)+320*(10+b));i++)	 	 /*��������ʾ*/	 
			  	gImage_Dis(gImage_picture2,i,0);
		  	
		} 
		Delay1(0xaf);
	}
	return gImage_picture2;
}
/*******************************************************************************
* ��������  : xiaoguo6
* ˵��      : ��Ҷ��
* ����      : ��Ч6
* ����      : ��
* ���÷�ʽ  : ��
*******************************************************************************/
const unsigned char *  XiaoGuo_6(void)
{
	int i,d;
	LCD_WriteReg(0x0003, 0x1038); 
	for(d=0;d<40;d++)
	{	   
		address_set(d,0,d,319);
	    for(i=0;i<320;i++)
		 	  gImage_Dis(gImage_picture3, i,d*640);	 
			  	
		address_set(40+d,0,d+40,319);
	    for(i=0;i<320;i++)
			  gImage_Dis(gImage_picture3, i,(d+40)*640);		 
		address_set(d+80,0,d+80,319);
	    for(i=0;i<320;i++)
			  gImage_Dis(gImage_picture3, i,(d+80)*640);
		 
		address_set(d+120,0,d+120,319);
	    for(i=0;i<320;i++)
			  gImage_Dis(gImage_picture3, i,(d+120)*640);
		 	
		address_set(d+160,0,d+160,319);
	    for(i=0;i<320;i++)
			  gImage_Dis(gImage_picture3, i,(d+160)*640);

		address_set(d+200,0,d+200,319);
	    for(i=0;i<320;i++)
			  gImage_Dis(gImage_picture3,i,(d+200)*640);
	
		  Delay1(0xffff);
	}
	return gImage_picture3;
}
/*******************************************************************************
* ��������  : xiaoguo7
* ˵��      : ��������תȦ��ʾ
* ����      : ��Ч7
* ����      : ��
* ���÷�ʽ  : ��
*******************************************************************************/
const unsigned char *  XiaoGuo_7(void)
{
	int i; 
	int b,d,g;
 	LCD_WriteReg(0x0003, 0x1038); 
   	g=24;
	for(d=0;d<12;d++)
	{	
	  
		address_set(d*10,0,d*10+10,319);
	    for(i = d*3200; i < (3200+d*3200); i++)	  /*�ɺ�����ʾ*/	 
			 gImage_Dis(gImage_picture1, i,0);
	  
		for(b=0;b<230;b++)
	    {  
			address_set(10+b,310-10*d,10+b,320-10*d);	/*��������ʾ*/
			for(i=((310-10*d)+((10+b)*320));i<=((320-10*d)+320*(10+b));i++)	 
			  	gImage_Dis(gImage_picture1,i,0);
			
		}
		g--;
		address_set(g*10,0,g*10+10,319);  	/*��������*/
	    for(i = g*3200; i < (3200+g*3200); i++)	 
			  gImage_Dis(gImage_picture1,i,0);
			  
	   
 		for(b=0;b<230;b++)	    /*��������ʾ*/
	    {  
			address_set(10+b,10*d,10+b,10+10*d);
			for(i=(10*d+((10+b)*320));i<=((10+10*d)+320*(10+b));i++)	 
			  	gImage_Dis(gImage_picture1,i,0);
		}
	   	Delay1(0xafff);
	}
	return gImage_picture1;
}
/*******************************************************************************
* ��������  : xiaoguo8
* ˵��      : �м�����������
* ����      : ��Ч7
* ����      : ��
* ���÷�ʽ  : ��
*******************************************************************************/
const unsigned char *  XiaoGuo_8(void)
{
	int i,d; 
 	LCD_WriteReg(0x0003, 0x1038); 
   	for(d=0;d<119;d++)
	{
		address_set(120+d,0,120+d,319);
	    for(i=0;i<320;i++)		  /*���м���������ʾ*/
			gImage_Dis(gImage_picture2,i,(120+d)*640);
		 
		address_set(119-d,0,119-d,319);
	    for(i=0;i<320;i++)		/*���м���������ʾ*/
			  gImage_Dis(gImage_picture2,i,(120-d)*640);
		Delay1(0xff);	  	
	}		 
	return gImage_picture2;
}
/*******************************************************************************
* ��������  : xiaoguo9
* ˵��      : �������������ʾ
* ����      : ��Ч9
* ����      : ��
* ���÷�ʽ  : ��
*******************************************************************************/
const unsigned char * XiaoGuo_9(void)
{
	int i; 
	int b,d,g;
 	LCD_WriteReg(0x0003, 0x1038); 
   	g=12;
	for(d=12;d>=0;d--)
	{	
	  
		address_set(d*10,0,d*10+10,319);
	    for(i = d*3200; i < (3200+d*3200); i++)	  /*�ɺ�����ʾ*/	 
			 gImage_Dis(gImage_picture3, i,0);
	  
		for(b=0;b<230;b++)
	    {  
			address_set(10+b,310-10*d,10+b,320-10*d);	/*��������ʾ*/
			for(i=((310-10*d)+((10+b)*320));i<=((320-10*d)+320*(10+b));i++)	 
			  	gImage_Dis(gImage_picture3,i,0);		
		}
		g++;
		address_set(g*10,0,g*10+10,319);  	/*��������*/
	    for(i = g*3200; i < (3200+g*3200); i++)	 
			  gImage_Dis(gImage_picture3,i,0);
			    
 		for(b=0;b<230;b++)	    /*��������ʾ*/
	    {  
			address_set(10+b,10*d,10+b,10+10*d);
			for(i=(10*d+((10+b)*320));i<=((10+10*d)+320*(10+b));i++)	 
			  	gImage_Dis(gImage_picture3,i,0);
		}
	   	Delay1(0xafff);
	}
	return gImage_picture3;
}
/*******************************************************************************
* ��������  : xiaoguo10
* ˵��      : ����������ʾ
* ����      : ��Ч12
* ����      : ��
* ���÷�ʽ  : ��
*******************************************************************************/
const unsigned char * XiaoGuo_10(void)
{
	int i,d; 
 	LCD_WriteReg(0x0003, 0x1038); // set GRAM write direction and BGR=1.
		for(d=0;d<20;d++)
	{	
		address_set(110+d,145,110+d,175);
	    for(i = ((110+d)*320+145); i < ((110+d)*320+175); i++) 
			  gImage_Dis(gImage_picture1,i,0);		 
	}
	Delay1(0xafff);
	for(d=0;d<40;d++)
	{	
		address_set(100+d,130,100+d,190);
	    for(i = ((100+d)*320+130); i < ((100+d)*320+189); i++)
		  gImage_Dis(gImage_picture1,i,0);
	}
		Delay1(0xafff);
	for(d=0;d<80;d++)
	{	
		address_set(80+d,100,80+d,219);
	    for(i = ((80+d)*320+100); i < ((80+d)*320+219); i++)
		  gImage_Dis(gImage_picture1,i,0);
	}
	 Delay1(0xafff);
	for(d=0;d<120;d++)
	{	
		address_set(60+d,70,60+d,249);
	    for(i = ((60+d)*320+70); i < ((60+d)*320+249); i++)
		  gImage_Dis(gImage_picture1,i,0);
	}
	 Delay1(0xafff);
	for(d=0;d<160;d++)
	{	
		address_set(40+d,40,40+d,279);
	    for(i = ((40+d)*320+40); i < ((40+d)*320+279); i++)
		  gImage_Dis(gImage_picture1,i,0);
	}
	 Delay1(0xafff);
	for(d=0;d<200;d++)
	{	
		address_set(20+d,10,20+d,309);
	    for(i = ((20+d)*320+10); i < ((20+d)*320+309); i++)
		  gImage_Dis(gImage_picture1,i,0);
	}
	 Delay1(0xafff);
	for(d=0;d<240;d++)
	{	
		address_set(d,0,d,319);
	    for(i = d*320; i < (d*320+319); i++)
		  gImage_Dis(gImage_picture1,i,0);
	}
	return gImage_picture1; 
}
/*******************************************************************************
* ��������  : xiaoguo11
* ˵��      : ��5��СԲ
* ����      : ��Ч11
* ����      : ��
* ���÷�ʽ  : ��
*******************************************************************************/
const unsigned char *  XiaoGuo_11(void)
{
	int i;
	int bkcolor=0x001f; 
	LCD_WriteReg(0x0003, 0x1008); 
	for(i=1;i<60;i++)
	{ 
	if((i%10)==1)bkcolor=~bkcolor;
	LCD_DrawCircle(60, 80, i,bkcolor);
	LCD_DrawCircle(60, 80, i%10+1,Blue);			
	LCD_DrawCircle(60, 240, i,bkcolor);
	LCD_DrawCircle(60, 240, i%10+1,Blue);									 
    LCD_DrawCircle(120, 160, i,bkcolor);
	LCD_DrawCircle(120, 160, i%10+1,Blue);	 			 			 	
 	LCD_DrawCircle(180, 80, i,bkcolor);	
	LCD_DrawCircle(180, 80, i%10+1,Blue);	
	LCD_DrawCircle(180, 240, i,bkcolor);
	LCD_DrawCircle(180, 240, i%10+1,Blue);		
	}
	LCD_WriteReg(0x0003, 0x1038); 
	address_set(0,0,239,319);
   	for(i=0;i<153600/2;i++)
	{
		gImage_Dis(gImage_picture2,i,0);
		Delay1(0xf);
	}
	return gImage_picture2;
}
/*******************************************************************************
* ��������  : xiaoguo12
* ˵��      : ��������������ʾԲ
* ����      : ��Ч12
* ����      : ��
* ���÷�ʽ  : ��
*******************************************************************************/
const unsigned char *  XiaoGuo_12(void)
{
	int i;
	int bkcolor=0x001f; 
	LCD_WriteReg(0x0003, 0x1038); 
	for(i=1;i<140;i++)	   
	{  
		if((i%10)==1)bkcolor=~bkcolor;
	 	LCD_DrawCircle(120, 160, i,bkcolor);
		LCD_DrawCircle(120, 160, i%10+1,Blue);
	}
	address_set(0,0,239,319);
   	for(i=0;i<153600/2;i++)
	{
		gImage_Dis(gImage_picture3,i,0);
		Delay1(0xf);
	}
	return gImage_picture3;	
}
/*******************************************************************************
* ��������  : xiaoguo13
* ˵��      : ��ʾ�ض���ͼƬ����
* ����      : �����˵�
* ����      : ��
* ���÷�ʽ  : ��
*******************************************************************************/
void  XiaoGuo_13(const unsigned char gImage_p[])
{
	int i,d;
	LCD_WriteReg(0x0003, 0x1038); 
	for(d=0;d<77;d++)
	{
		address_set(d,24,d,159);
    		for(i=(d*320+24);i<(d*320+159);i++)
				gImage_Dis(gImage_p,i,0);
		
	}
}
