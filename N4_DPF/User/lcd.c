/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : lcd.c
* Author             : MCD Application Team
* Version            : V1.1
* Date               : 11/26/2007
* Description        : This file includes the LCD driver for AM-240320LTNQW00H
*                      (LCD_HX8312) and AM-240320L8TNQW00H (LCD_ILI9320)
*                      Liquid Crystal Display Module of STM3210B-EVAL board.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include "fonts.h"
#include "lcd.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LCD_TYPE  0x9325

#define START_BYTE  0x70
#define SET_INDEX   0x00
#define READ_STATUS 0x01
#define WRITE_REG   0x02
#define READ_REG    0x03
#define WRITE_RAM   0x0022

#define LCD_Data_Addr    ((uint32_t)0x60020000)    
#define LCD_Reg_Addr     ((uint32_t)0x60000000)
/*---------------------------LCD marco commad-------------------------------*\
*硬件宏，移植的时候需要处理好
\*---------------------------LCD marco commad-------------------------------*/
#define  LCD_BUS    GPIOE->ODR
#define  LCD_nRST   GPIOE->BRR=GPIO_Pin_1
#define  LCD_nCS    GPIOD->BRR=GPIO_Pin_7
#define  LCD_nRS    GPIOD->BRR=GPIO_Pin_11
#define  LCD_nWR    GPIOD->BRR=GPIO_Pin_5
#define  LCD_nRD    GPIOD->BRR=GPIO_Pin_11

#define  LCD_RST    GPIOE->BSRR=GPIO_Pin_1
#define  LCD_CS     GPIOD->BSRR=GPIO_Pin_7
#define  LCD_RS     GPIOD->BSRR=GPIO_Pin_11
#define  LCD_WR     GPIOD->BSRR=GPIO_Pin_5
#define  LCD_RD     GPIOD->BSRR=GPIO_Pin_11

typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
extern const unsigned char gImage_arm79[];
extern const unsigned char gImage_arm_logo[] ;
/*---------------写数据到GRAM----------------*/
void    LCD_WriteRAM(unsigned int val)
{   
	*(volatile uint16_t *)(LCD_Data_Addr) = val; 	
}
/*---------------写索引寄存器----------------*/
void LCD_WriteIndex(unsigned int index)
{
	*(volatile uint16_t *)(LCD_Reg_Addr) = index;

}

/*******************************************************************************
* Function Name  : LCD_WriteReg
* Description    : Writes to the selected LCD register.
* Input          : - LCD_Reg: address of the selected register.
*                  - LCD_RegValue: value to write to the selected register.
* Output         : None
* Return         : None
*******************************************************************************/

void LCD_WriteReg(unsigned int LCD_Reg, unsigned int LCD_RegValue)
{
	//LCD_nCS;
	*(volatile uint16_t *) (LCD_Reg_Addr) = LCD_Reg;
	*(volatile uint16_t *) (LCD_Data_Addr) = LCD_RegValue;
	//LCD_CS;
}
/*---------------写数据准备-------------------*/
void LCD_WriteRAM_Prepare(void)   
{
	LCD_WriteIndex(WRITE_RAM);
}
/*---------------写数据完成-------------------*/
#define  LCD_WriteRAM_Ready() {LCD_CS;}

/*---------------------------LCD marco end-------------------------------*/


/* Private variables ---------------------------------------------------------*/
/* Global variables to set the written text color */
static  vu16 TextColor = 0x0000, BackColor = 0xFFFF;

/* Private function prototypes -----------------------------------------------*/
static  u32   StrLength(u8 *Str);
static  void  Delay    (u32 nCount);

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : LCD_Setup
* Description    : Setups the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void  Delay (u32 nCount)
{
  for(; nCount != 0; nCount--);
}
/*******************************************************************************
* Function Name  : StrLength
* Description    : Returns length of string.
* Input          : - Str: Character Pointer.
* Output         : None
* Return         : String length.
*******************************************************************************/
static u32 StrLength(u8 *Str)
{
  u32 Index = 0;

  /* Increment the Index unless the end of string */
  for(Index = 0; *Str != '\0'; Str++, Index++)
  {
  }

  return Index;
}

void LCD_Setup(void)
{
/* Configure the LCD Control pins --------------------------------------------*/
	LCD_CtrlLinesConfig();
	GPIO_ResetBits(GPIOC, GPIO_Pin_1);
    Delay(0x5FFFF);					   
    GPIO_SetBits(GPIOC, GPIO_Pin_1 );		 	 
	Delay(0x5FFFF);	
	  //************* Start Initial Sequence **********//
	LCD_WriteReg(0x00E3, 0x3008); // Set u16ernal timing
	LCD_WriteReg(0x00E7, 0x0012); // Set u16ernal timing
	LCD_WriteReg(0x00EF, 0x1231); // Set u16ernal timing
	LCD_WriteReg(0x0001, 0x0100); // set SS and SM bit
	LCD_WriteReg(0x0002, 0x0700); // set 1 line inversion
	LCD_WriteReg(0x0003, 0x1038); // set GRAM write direction and BGR=1.
	LCD_WriteReg(0x0004, 0x0000); // Resize register
	LCD_WriteReg(0x0008, 0x020E); // set the back porch and front porch
	LCD_WriteReg(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
	LCD_WriteReg(0x000A, 0x0000); // FMARK function
	LCD_WriteReg(0x000C, 0x0000); // RGB u16erface setting
	LCD_WriteReg(0x000D, 0x0000); // Frame marker Position
	LCD_WriteReg(0x000F, 0x0000); // RGB u16erface polarity
	//*************Power On sequence ****************//
	LCD_WriteReg(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WriteReg(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
	LCD_WriteReg(0x0012, 0x0000); // VREG1OUT voltage
	LCD_WriteReg(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
	Delay(0XAFFFF); // Dis-charge capacitor power voltage
	LCD_WriteReg(0x0010, 0x1290); // SAP, BT[3:0], AP, DSTB, SLP, STB
	LCD_WriteReg(0x0011, 0x0221); // R11h=0x0221 at VCI=3.3V, DC1[2:0], DC0[2:0], VC[2:0]
	Delay(0XAFFFF); // Delay 50ms
	LCD_WriteReg(0x0012, 0x001A); // External reference voltage= Vci;
	Delay(0XAFFFF); // Delay 50ms
	LCD_WriteReg(0x0013, 0x1600); // R13=0F00 when R12=009E;VDV[4:0] for VCOM amplitude
	LCD_WriteReg(0x0029, 0x0022); // R29=0019 when R12=009E;VCM[5:0] for VCOMH
	LCD_WriteReg(0x002B, 0x000A); // Frame Rate 
	Delay(0XAFFFF); // Delay 50ms
	LCD_WriteReg(0x0020, 0x0000); // GRAM horizontal Address
	LCD_WriteReg(0x0021, 0x0000); // GRAM Vertical Address
	// ----------- Adjust the Gamma Curve ----------//
	LCD_WriteReg(0x0030, 0x0000);
	LCD_WriteReg(0x0031, 0x0302);
	LCD_WriteReg(0x0032, 0x0202);
	LCD_WriteReg(0x0035, 0x0103);
	LCD_WriteReg(0x0036, 0x080C);
	LCD_WriteReg(0x0037, 0x0505);
	LCD_WriteReg(0x0038, 0x0504);
	LCD_WriteReg(0x0039, 0x0707);
	LCD_WriteReg(0x003C, 0x0301);
	LCD_WriteReg(0x003D, 0x1008);
	//------------------ Set GRAM area ---------------//
	LCD_WriteReg(0x0050, 0x0000); // Horizontal GRAM Start Address
	LCD_WriteReg(0x0051, 0x00EF); // Horizontal GRAM End Address
	LCD_WriteReg(0x0052, 0x0000); // Vertical GRAM Start Address
	LCD_WriteReg(0x0053, 0x013F); // Vertical GRAM Start Address
	LCD_WriteReg(0x0060, 0x2700); // Gate Scan Line
	LCD_WriteReg(0x0061, 0x0001); // NDL,VLE, REV
	LCD_WriteReg(0x006A, 0x0000); // set scrolling line
	//-------------- Partial Display Control ---------//
	LCD_WriteReg(0x0080, 0x0000);
	LCD_WriteReg(0x0081, 0x0000);
	LCD_WriteReg(0x0082, 0x0000);
	LCD_WriteReg(0x0083, 0x0000);
	LCD_WriteReg(0x0084, 0x0000);
	LCD_WriteReg(0x0085, 0x0000);
	//-------------- Panel Control -------------------//
	LCD_WriteReg(0x0090, 0x0010);
	LCD_WriteReg(0x0092, 0x0600);
	LCD_WriteReg(0x0093, 0x0003);
	LCD_WriteReg(0x0095, 0x0110);
	LCD_WriteReg(0x0097, 0x0000);
	LCD_WriteReg(0x0098, 0x0000);
	LCD_WriteReg(0x0007, 0x0133); // 262K color and display ON
}

/*******************************************************************************
* Function Name  : LCD_SetTextColor
* Description    : Sets the Text color.
* Input          : - Color: specifies the Text color code RGB(5-6-5).
* Output         : - TextColor: Text color global variable used by LCD_DrawChar
*                  and LCD_DrawPicture functions.
* Return         : None
*******************************************************************************/
void LCD_SetTextColor(vu16 Color)
{
  TextColor = Color;
}

/*******************************************************************************
* Function Name  : LCD_SetBackColor
* Description    : Sets the Background color.
* Input          : - Color: specifies the Background color code RGB(5-6-5).
* Output         : - BackColor: Background color global variable used by
*                  LCD_DrawChar and LCD_DrawPicture functions.
* Return         : None
*******************************************************************************/
void LCD_SetBackColor(vu16 Color)
{
  BackColor = Color;
}

/*******************************************************************************
* Function Name  : LCD_ClearLine
* Description    : Clears the selected line.
* Input          : - Line: the Line to be cleared.
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_ClearLine(u8 Line)
{
  LCD_DisplayStringLine(Line, "                    ");
}

/*******************************************************************************
* Function Name  : LCD_Clear
* Description    : Clears the hole LCD.
* Input          : Color: the color of the background.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_Clear(u16 Color)
{
  u32 index = 0;

  LCD_SetCursor(0x00, 0x013F);

    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

  for(index = 0; index < 76800; index++)
  {
    LCD_WriteRAM(Color);
  }
  LCD_WriteRAM_Ready();
}

/*******************************************************************************
* Function Name  : LCD_SetCursor
* Description    : Sets the cursor position.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetCursor(u8 Xpos, u16 Ypos)
{
    LCD_WriteReg(0x0020, Xpos);
    LCD_WriteReg(0x0021, Ypos);
}

/*******************************************************************************
* Function Name  : LCD_DrawChar
* Description    : Draws a character on LCD.
* Input          : - Xpos: the Line where to display the character shape.
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
*                  - Ypos: start column address.
*                  - c: pointer to the character data.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawChar(u8 Xpos, u16 Ypos, uc16 *c)
{
  u32 index = 0, i = 0;
  u8 Yaddress = 0;

  Yaddress = Ypos;

  LCD_SetCursor(Xpos, Yaddress);

  for(index = 0; index < 24; index++)
  {
    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
    for(i = 0; i < 16; i++)
    {
      if((c[index] & (1 << i)) == 0x00)
      {
        LCD_WriteRAM(BackColor);
      }
      else
      {
        LCD_WriteRAM(TextColor);
      }
    }
    LCD_WriteRAM_Ready();
    Yaddress++;
    LCD_SetCursor(Xpos, Yaddress);
  }  
}
/*******************************************************************************
* Function Name  : LCD_DisplayChar
* Description    : Displays one character (16dots width, 24dots height).
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
*                  - Column: start column address.
*                  - Ascii: character ascii code, must be between 0x20 and 0x7E.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayChar(u8 Line, u16 Column, u8 Ascii)
{
  Ascii -= 32;
//  LCD_DrawChar(Line, Column, &ASCII_Table[Ascii * 24]);
}

/*******************************************************************************
* Function Name  : LCD_DisplayStringLine
* Description    : Displays a maximum of 20 char on the LCD.
* Input          : - Line: the Line where to display the character shape .
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
*                  - *ptr: pointer to string to display on LCD.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayStringLine(u8 Line, u8 *ptr)
{
  u32 i = 0;
  u16 refcolumn = 0;

  /* Send the string character by character on lCD */
  while ((*ptr != 0) & (i < 15))
  {
    /* Display one character on LCD */
    LCD_DisplayChar(refcolumn, Line, *ptr);
    /* Decrement the column position by 16 */
    refcolumn+= 16;
    /* Point on the next character */
    ptr++;
    /* Increment the character counter */
    i++;
  }
}

/*******************************************************************************
* Function Name  : LCD_DisplayString
* Description    : Displays a maximum of 200 char on the LCD.
* Input          : - Line: the starting Line where to display the character shape.
*                    This parameter can be one of the following values:
*                       - Linex: where x can be 0..9
*                  - *ptr: pointer to string to display on LCD.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayString(u8 Line, u8 *ptr)
{
  u32 i = 0, column = 0, index = 0, spaceindex = 0;
  u16 refcolumn = 319;
  u32 length = 0;

  /* Get the string length */
  length = StrLength(ptr);
  if(length > 200)
  {
    /* Set the Cursor position */
    LCD_SetCursor(Line, 0x013F);
    /* Clear the Selected Line */
    LCD_ClearLine(Line);
    LCD_DisplayStringLine(Line, "   String too long  ");
  }
  else
  {
    /* Set the Cursor position */
    LCD_SetCursor(Line, 0x013F);
    /* Clear the Selected Line */
//    LCD_ClearLine(Line);

    while(length--)
    {
      if(index == 20)
      {
        if(*ptr == 0x20)
        {
          ptr++;
        }
        else
        {
          for(i = 0; i < spaceindex; i++)
          {
            LCD_DisplayChar(Line, column, ' ');
            column -= 16;
          }
          ptr -= (spaceindex - 1);
          length += (spaceindex - 1);
        }
        Line += 24;
        /* Clear the Selected Line */
//        LCD_ClearLine(Line);
        refcolumn = 319;
        index = 0;
      }
      /* Display one character on LCD */
      LCD_DisplayChar(Line, refcolumn, *ptr);

      /* Increment character number in one line */
      index++;

      /* Decrement the column position by 16 */
      refcolumn -= 16;
      /* Point on the next character */
      ptr++;
      /* Increment the number of character after the last space */
      spaceindex++;
      if(*ptr == 0x20)
      {
        spaceindex = 0;
        column = refcolumn - 16;
      }
    }
  }
}
/*******************************************************************************
* Function Name  : LCD_SetDisplayWindow
* Description    : Sets a display window
* Input          : - Xpos: specifies the X buttom left position.
*                  - Ypos: specifies the Y buttom left position.
*                  - Height: display window height.
*                  - Width: display window width.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_SetDisplayWindow(u8 Xpos, u16 Ypos, u8 Width, u16 Height)
{
 
      LCD_WriteReg(0x0050, Xpos);
      LCD_WriteReg(0x0051, (Xpos+Width-1));

      LCD_WriteReg(0x0052, Ypos);
      LCD_WriteReg(0x0053,(Ypos + Height-1));
      
      LCD_SetCursor(Xpos, Ypos);
}

/*******************************************************************************
* Function Name  : LCD_WindowModeDisable
* Description    : Disables LCD Window mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WindowModeDisable(void)
{
    LCD_SetDisplayWindow(0, 0, 239, 319);
}
/*******************************************************************************
* Function Name  : LCD_DrawLine
* Description    : Displays a line.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
*                  - Length: line length.
*                  - Direction: line direction.
*                    This parameter can be one of the following values: Vertical
*                    or Horizontal.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawLine(u8 Xpos, u16 Ypos, u16 Length, u8 Direction)
{
  u32 i = 0;

  LCD_SetCursor(Xpos, Ypos);

  if(Direction == Horizontal)
  {

    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */
     
    for(i = 0; i < Length; i++)
    {
      LCD_WriteRAM(TextColor);
    }
    
    LCD_WriteRAM_Ready();
  }
  else
  {
   for(i = 0; i < Length; i++)
    {
      LCD_WriteRAMWord(TextColor);
      
      Ypos++;
      
      LCD_SetCursor(Xpos, Ypos);
    }
  }
}

/*******************************************************************************
* Function Name  : LCD_DrawRect
* Description    : Displays a rectangle.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
*                  - Height: display rectangle height.
*                  - Width: display rectangle width.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawRect(u8 Xpos, u16 Ypos, u8 Width, u16 Height)
{
  LCD_DrawLine(Xpos, Ypos, Width, Horizontal);
  LCD_DrawLine(Xpos, (Ypos + Height), Width, Horizontal);

  LCD_DrawLine(Xpos, Ypos, Height, Vertical);
  LCD_DrawLine((Xpos+Width-1) ,Ypos, Height, Vertical);
}

/*******************************************************************************
* Function Name  : LCD_DrawRect
* Description    : Displays a rectangle.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
*                  - Height: display rectangle height.
*                  - Width: display rectangle width.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawRectFill(u8 Xpos, u16 Ypos, u8 Width, u16 Height,u16 fill){
  u8 j;
  LCD_SetDisplayWindow(Xpos,Ypos,Width,Height);

  LCD_WriteRAM_Prepare();
   for(Height=Height;Height>0;Height--)
     for(j=Width;j>0;j--)
        LCD_WriteRAM(fill);
  LCD_WriteRAM_Ready();
  LCD_WindowModeDisable();
}

/*******************************************************************************
* Function Name  : LCD_DrawCircle
* Description    : Displays a circle.
* Input          : - Xpos: specifies the X position.
*                  - Ypos: specifies the Y position.
*                  - Height: display rectangle height.
*                  - Width: display rectangle width.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawCircle(u8 Xpos, u16 Ypos, u16 Radius, int a)
{
  s32  D;/* Decision Variable */
  u32  CurX;/* Current X Value */
  u32  CurY;/* Current Y Value */

  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;

  while (CurX <= CurY)
  {
    LCD_SetCursor(Xpos + CurX, Ypos + CurY);
 
      LCD_WriteRAMWord(a);

 
    LCD_SetCursor(Xpos + CurX, Ypos - CurY);

      LCD_WriteRAMWord(a);

    LCD_SetCursor(Xpos - CurX, Ypos + CurY);

      LCD_WriteRAMWord(a);

    LCD_SetCursor(Xpos - CurX, Ypos - CurY);

      LCD_WriteRAMWord(a);

    LCD_SetCursor(Xpos + CurY, Ypos + CurX);
    
    
      LCD_WriteRAMWord(a);

    LCD_SetCursor(Xpos + CurY, Ypos - CurX);

      LCD_WriteRAMWord(a);
  

    LCD_SetCursor(Xpos - CurY, Ypos + CurX);

      LCD_WriteRAMWord(a);

    LCD_SetCursor(Xpos - CurY, Ypos - CurX);

      LCD_WriteRAMWord(a);

    if (D < 0)
    {
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }
}

/*******************************************************************************
* Function Name  : LCD_DrawMonoPict
* Description    : Displays a monocolor picture.
* Input          : - Pict: pointer to the picture array.
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DrawMonoPict(uc8 *Pict)
{
  u32 index = 0, i = 0;

  //LCD_SetCursor(0, 0);

    LCD_WriteRAM_Prepare(); /* Prepare to write GRAM */

  for(index = 0; index < (6040); index++)
  {
    for(i = 0; i < 8; i++)
    {
      if((Pict[index] & (1 << i)) == 0x00) {
        LCD_WriteRAM(BackColor);
      }
      else {
        LCD_WriteRAM(TextColor);
      }
    }
  }
  LCD_WriteRAM_Ready();
}




/*******************************************************************************
* Function Name  : LCD_WriteRAMWord
* Description    : Writes 1 word to the LCD RAM.
* Input          : - RGB_Code: the pixel color in RGB mode (5-6-5).
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_WriteRAMWord(u16 RGB_Code)
{
  LCD_WriteRAM_Prepare();

  LCD_WriteRAM(RGB_Code);
  
  LCD_WriteRAM_Ready();
}

/*******************************************************************************
* Function Name  : LCD_PowerOn
* Description    : Power on the LCD.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_PowerOn(void)
{

}

/*******************************************************************************
* Function Name  : LCD_DisplayOn
* Description    : Enables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOn(void)
{

}

/*******************************************************************************
* Function Name  : LCD_DisplayOff
* Description    : Disables the Display.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_DisplayOff(void)
{

}											

/*******************************************************************************
* Function Name  : LCD_CtrlLinesConfig
* Description    : Configures LCD control lines in Output Push-Pull mode.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_CtrlLinesConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
                         RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO , ENABLE); 

   GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  //GPIO_SetBits(GPIOB, GPIO_Pin_6);		

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 |GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  
  						 
/*===========GPIO For the LCD_Bus========================*/	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
  								GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
  								GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

/*===========GPIO For the LCD_RESET=======================*/
/**	
 *	PC1 -> LCD_RESET
 */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

/*===========GPIO For the Control========================*/
/**	
 *	PD13 -> Light
 *	PD4	-> OE	,	PD5	-> WE 
 *	PD7	-> CS	,	PD11 -> RS 
 */	

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 |GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	 
  GPIO_Init(GPIOD, &GPIO_InitStructure); 

/*===========GPIO For the LED ========================*/
/**
 *	LED1 -> PB8	,	LED2 -> PB9 , LED3 -> PE0 , LED4 -> PE1
 */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOE, &GPIO_InitStructure);	
/*===========Please Set LED-back-Light ========================*/
/**
 *	Light_LED -> PD13
 */

  GPIO_SetBits(GPIOD, GPIO_Pin_13);		//打开背光LED

  
}


/**
 * LCD地址设置
 *
 */

void address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
    LCD_WriteReg(0x0020,x1);//设置X坐标位置
    LCD_WriteReg(0x0021,y1);//设置Y坐标位置
    LCD_WriteReg(0x0050,x1);   //开始X
	LCD_WriteReg(0x0052,y1);	  //开始Y
    LCD_WriteReg(0x0051,x2);  //结束X
	LCD_WriteReg(0x0053,y2);  //结束Y
    LCD_WriteRAM_Prepare();
}


/**
 * LCD测试
 *
 */


void test(void)
{
}

void test2(void)
{

}
void test1(void)
{


}
/****************************************************************************
* 名    称：void ili9320_DrawPicture(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic)
* 功    能：在指定座标范围显示一副图片
* 入口参数：StartX     行起始座标
*           StartY     列起始座标
*           EndX       行结束座标
*           EndY       列结束座标
            pic        图片头指针
* 出口参数：无
* 说    明：图片取模格式为水平扫描，16位颜色模式
* 调用方法：ili9320_DrawPicture(0,0,100,100,(u16*)demo);
****************************************************************************/
void ili9320_DrawPicture(u8 StartX,u16 StartY,u8 EndX,u16 EndY,uc8 *pic)
{
  unsigned int  i;
  unsigned int dd;
  LCD_SetDisplayWindow(StartX, StartY, EndX, EndY);
	    			
  for (i=0;i<(EndX*EndY);i++) 
  {
  	 dd=(0x00|pic[i*2+1])<<8;
     dd=dd|pic[i*2];
     LCD_WriteRAM(dd);
   }
}

/*---------------------------------E N D--------------------------------------*/


