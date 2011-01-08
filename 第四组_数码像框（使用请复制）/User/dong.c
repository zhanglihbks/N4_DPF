#include "lcd.h"
#include "stm32f10x_lib.h"
#include "dong.h"
	 
extern void address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);
extern void    LCD_WriteRAM(unsigned int val);
/***************延时函数*******************/
void  Delay1 (int nCount)
{
  for(; nCount != 0; nCount--);
}
 /************由下向上进入*****************/
void xiaoguo1(void)
{
	int i;
	unsigned int dd;

	LCD_WriteReg(0x0003, 0x1008); // set GRAM write direction and BGR=1.
	LCD_Clear(White);

	address_set(0,0,239,319);

    	for(i=153600/2;i>0;i--)
	{
	  	dd=(0x00|gImage_arm79[i*2+1])<<8;
		dd=dd|gImage_arm79[i*2];
		LCD_WriteRAM(dd);
		Delay1(0xf);
	}
	Delay1(0xfffff);
	Delay1(0xfffff);
	Delay1(0xfffff);
	Delay1(0xfffff);
}
	/**********在中心画圆***************/
void xiaoguo2(void)
{
	int i;
//	unsigned int dd;
	LCD_WriteReg(0x0003, 0x1008); // set GRAM write direction and BGR=1.
	for(i=1;i<40;i++)
	{
		LCD_DrawCircle(120, 160, i,Blue);	
	  	 	LCD_DrawCircle(120, 160, i+19,White);
					LCD_DrawCircle(120, 160, 5,Blue);
	}  
		for(i=1;i<80;i++)
	{	
	  LCD_DrawCircle(120, 160, i,Blue);
		LCD_DrawCircle(120, 160, i+19,White);				 
			LCD_DrawCircle(120, 160, 5,Blue);	 	
	}
		for(i=1;i<120;i++)
	{  
		LCD_DrawCircle(120, 160, i,Blue);	
	   		LCD_DrawCircle(120, 160, i+19,White);
				LCD_DrawCircle(120, 160, 5,Blue);	
				LCD_DrawCircle(120, 160, i+39,Blue);
	 				LCD_DrawCircle(120, 160, i+59,White);
	}	
}
/*************由外往内转圈显示****************/
void xiaoguo3(void)
{
	int i, d, b, g=24;
	unsigned int dd;
 	LCD_WriteReg(0x0003, 0x1038); // set GRAM write direction and BGR=1.
   	
	for(d=0;d<12;d++)
	{	
	   /*由横向显示*/
		 address_set(d*10,0,d*10+10,319);
	    for(i = d*3200; i < (3200+d*3200); i++)
		 {	 
			  dd=(0x00|gImage_1[2*i+1])<<8;
			  dd=dd|gImage_1[i*2];
			  LCD_WriteRAM(dd);
		  }	
		  	Delay1(0xaff);
	  /*右纵向显示*/
		  for(b=0;b<230;b++)
	    {  
		address_set(10+b,310-10*d,10+b,320-10*d);
		for(i=((310-10*d)+((10+b)*320));i<=((320-10*d)+320*(10+b));i++)
		 {	 
			  dd=(0x00|gImage_1[2*i+1])<<8;
			  dd=dd|gImage_1[i*2];
			  LCD_WriteRAM(dd);
			
		  }
		  	Delay1(0xaff);
		}
			Delay1(0xaff);
		/*由下向上*/
		g--;
		 address_set(g*10,0,g*10+10,319);
	    for(i = g*3200; i < (3200+g*3200); i++)
		 {	 
			  dd=(0x00|gImage_1[2*i+1])<<8;
			  dd=dd|gImage_1[i*2];
			  LCD_WriteRAM(dd);
			  
		  }
		  	Delay1(0xaff);
	    /*左纵向显示*/
 		for(b=0;b<230;b++)
	    {  
		address_set(10+b,10*d,10+b,10+10*d);
		for(i=(10*d+((10+b)*320));i<=((10+10*d)+320*(10+b));i++)
		 {	 
			  dd=(0x00|gImage_1[2*i+1])<<8;
			  dd=dd|gImage_1[i*2];
			  LCD_WriteRAM(dd);
			
		  }
		  	Delay1(0xaff);
		}
	   	Delay1(0xaff);
	}
	
	Delay1(0xaffff);
	Delay1(0xaffff);
	Delay1(0xaffff);
	Delay1(0xaffff); 
}
	/*百叶窗*/
void xiaoguo4(void)
{
	int d, i;
	unsigned int dd;
	LCD_WriteReg(0x0003, 0x1008); // set GRAM write direction and BGR=1.
	for(d=0;d<40;d++)
	{
	   
		address_set(d,0,d,319);
	    for(i=0;i<320;i++)
		 {
			  dd=(0x00|gImage_arm79[d*640+2*i+1])<<8;
			  dd=dd|gImage_arm79[d*640+i*2];
			  LCD_WriteRAM(dd);
		 
		  }	
		  	address_set(40+d,0,d+40,319);
	    for(i=0;i<320;i++)
		 {
			  dd=(0x00|gImage_arm79[(d+40)*640+2*i+1])<<8;
			  dd=dd|gImage_arm79[(d+40)*640+i*2];
			  LCD_WriteRAM(dd);
		 
		  }	
		address_set(d+80,0,d+80,319);
	    for(i=0;i<320;i++)
		 {
			  dd=(0x00|gImage_arm79[(d+80)*640+2*i+1])<<8;
			  dd=dd|gImage_arm79[(d+80)*640+i*2];
			  LCD_WriteRAM(dd);
		 
		  }	
		address_set(d+120,0,d+120,319);
	    for(i=0;i<320;i++)
		 {
			  dd=(0x00|gImage_arm79[(d+120)*640+2*i+1])<<8;
			  dd=dd|gImage_arm79[(d+120)*640+i*2];
			  LCD_WriteRAM(dd);
		 
		  }	
		   	address_set(d+160,0,d+160,319);
	    for(i=0;i<320;i++)
		 {
			  dd=(0x00|gImage_arm79[(d+160)*640+2*i+1])<<8;
			  dd=dd|gImage_arm79[(d+160)*640+i*2];
			  LCD_WriteRAM(dd);
		 
		  }	
		address_set(d+200,0,d+200,319);
	    for(i=0;i<320;i++)
		 {
			  dd=(0x00|gImage_arm79[(d+200)*640+2*i+1])<<8;
			  dd=dd|gImage_arm79[(d+200)*640+i*2];
			  LCD_WriteRAM(dd);
		 
		  }	
		  Delay1(0xffff);
	}

	Delay1(0xaffff);
	Delay1(0xaffff);
	Delay1(0xaffff);
	Delay1(0xaffff);
	Delay1(0xaffff);
}
	 /*右上角进入*/
void xiaoguo5(void)
{
	int i, b, d;
	unsigned int dd;
	LCD_WriteReg(0x0003, 0x1008); // set GRAM write direction and BGR=1.
	for(d=0;d<24;d++)
	{	
	   /*由横向显示*/
		 address_set(d*10,0,d*10+10,319);
	    for(i = d*3200; i < (3200+d*3200); i++)
		 {	 
			  dd=(0x00|gImage_1[2*i+1])<<8;
			  dd=dd|gImage_1[i*2];
			  LCD_WriteRAM(dd);
			 
		  }	
		  
	 	 /*右纵向显示*/
		  for(b=0;b<230;b++)
	    {  
		address_set(10+b,310-10*d,10+b,320-10*d);
		for(i=((310-10*d)+((10+b)*320));i<=((320-10*d)+320*(10+b));i++)
		 {	 
			  dd=(0x00|gImage_1[2*i+1])<<8;
			  dd=dd|gImage_1[i*2];
			  LCD_WriteRAM(dd);
			
		  }
		  	
		} 
		Delay1(0xaff);
		Delay1(0xaffff);
	}
	Delay1(0xaffff);
	Delay1(0xaffff);
	Delay1(0xaffff);
	Delay1(0xaffff);
}
/*************由右向左进入*************/
void xiaoguo6(void)
{	
	int i;
	unsigned int dd;
	LCD_WriteReg(0x0003, 0x1020); // set GRAM write direction and BGR=1.
//	LCD_Clear(White);
	address_set(0,0,239,319);

	for(i=153600/2;i>0;i--)
	{
		dd=(0x00|gImage_picture1[i*2+1])<<8;
		dd=dd|gImage_picture1[i*2];
		LCD_WriteRAM(dd);
		Delay1(0xf);
	}
	Delay1(0xfffff);
	Delay1(0xfffff);
	Delay1(0xfffff);
	Delay1(0xfffff);
}
/************中间进入******************/
void xiaoguo7(void)
{
	int i, d;
	unsigned int dd; 
 	LCD_WriteReg(0x0003, 0x1038); // set GRAM write direction and BGR=1.
   	for(d=0;d<119;d++)
	{
	   /*由中间往下面显示*/
		address_set(120+d,0,120+d,319);
	    for(i=0;i<320;i++)
		 {
			  dd=(0x00|gImage_1[(120+d)*640+2*i+1])<<8;
			  dd=dd|gImage_1[(120+d)*640+i*2];
			  LCD_WriteRAM(dd);
		 
		  }
		/*由中间往上面显示*/
		address_set(119-d,0,119-d,319);
	    for(i=0;i<320;i++)
		 {
			  dd=(0x00|gImage_1[(120-d)*640+2*i+1])<<8;
			  dd=dd|gImage_1[(120-d)*640+i*2];
			  LCD_WriteRAM(dd);
		  }
	Delay1(0xf);	  	
	}		 
	Delay1(0xaffff);
	Delay1(0xaffff);
	Delay1(0xaffff);
	Delay1(0xaffff);
	Delay1(0xaffff);
}
	/*画4个小圆*/
void xiaoguo9(void)
{
	int i;
	for(i=1;i<20;i++)
	{
	LCD_DrawCircle(60, 80, i,Blue);	
	   	LCD_DrawCircle(60, 80, i+10,White);
			LCD_DrawCircle(60, 80, i+20,Blue);	
		
	 LCD_DrawCircle(60, 240, i,Blue);
		LCD_DrawCircle(60, 240, i+10,White);
			LCD_DrawCircle(60, 240, i+20,Blue);					 
			 	
 	LCD_DrawCircle(180, 80, i,Blue);	
	   	LCD_DrawCircle(180, 80, i+10,White);
			LCD_DrawCircle(180, 80, i+20,Blue);
	
	LCD_DrawCircle(180, 240, i,Blue);	
	   	LCD_DrawCircle(180, 240, i+10,White);
			LCD_DrawCircle(180, 240, i+20,Blue);		
	}  
}
/******************由左向右进入*****************/
void xiaoguo8(void)
{
    int i;
	unsigned int dd;
	LCD_WriteReg(0x0003, 0x1010); // set GRAM write direction and BGR=1.
	address_set(0,0,239,319);
    for(i=153600/2;i>0;i--)
    {
	  dd=(0x00|gImage_picture1[i*2+1])<<8;
	  dd=dd|gImage_picture1[i*2];
	  LCD_WriteRAM(dd);
	  Delay1(0xf);
	}
	Delay1(0xfffff);
	Delay1(0xfffff);
	Delay1(0xfffff);
	Delay1(0xfffff);
}
