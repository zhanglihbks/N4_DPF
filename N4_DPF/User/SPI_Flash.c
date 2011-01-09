#include "stm32f10x.h"
#include "SPI_Flash.h"
#include "stm32f10x_spi.h"

void SPI_Flash_Init(void);
unsigned int  SPI_Flash_ReadByte(unsigned char a);
unsigned int SPI_Flash_SendByte(unsigned char byte);
void FlashPageEarse(unsigned int  page);
void FlashPageRead(unsigned int  page,unsigned char *Data);
void FlashPageWrite(unsigned int  page,unsigned char *Data);
void FlashWaitBusy(void);
void AT45_RomTo_buf(unsigned char buffer,unsigned int page);
unsigned char AT45_buf_ToRam(unsigned char buffer,unsigned int start_address,unsigned int length);
unsigned char AT45_RamTo_buf(unsigned char buffer,unsigned int start_address,unsigned int length);	  
void AT45_buf_ToRom(unsigned char buffer,unsigned int page);
void AT45_page_earse(unsigned int page);


unsigned char AT45_buffer[528];

void FlashReadID(u8 *Data)
{

}

/*******************************************************************************
* Function Name  : SPI_FLASH_Init
* Description    : Initializes the peripherals used by the SPI FLASH driver.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_Flash_Init(void)
{
  SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
   
  /* Enable SPI1 GPIOB clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1 ,ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  /* Configure SPI1 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure PA.12 as Output push-pull, used as Flash Chip select */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Deselect the FLASH: Chip Select high */
  NotSelect_Flash();

  /* SPI1 configuration */ 
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);
  
  /* Enable SPI1  */
  SPI_Cmd(SPI1, ENABLE);   
}

/*******************************************************************************
* Function Name  : SPI_FLASH_ReadByte
* Description    : Reads a byte from the SPI Flash.
*                  This function must be used only if the Start_Read_Sequence
*                  function has been previously called.
* Input          : None
* Output         : None
* Return         : Byte Read from the SPI Flash.
*******************************************************************************/
u16 SPI_Flash_ReadByte(u8 a)
{
  return (SPI_Flash_SendByte(a));
}

/*******************************************************************************
* Function Name  : SPI_FLASH_SendByte
* Description    : Sends a byte through the SPI interface and return the byte 
*                  received from the SPI bus.
* Input          : byte : byte to send.
* Output         : None
* Return         : The value of the received byte.
*******************************************************************************/
u16 SPI_Flash_SendByte(u8 byte)
{
  /* Loop while DR register in not emplty */
  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
  //NotSelect_Flash();  while(1);
  /* Send byte through the SPI2 peripheral */
  SPI_I2S_SendData(SPI1, byte);

  /* Wait to receive a byte */
  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

  /* Return the byte read from the SPI bus */
  return SPI_I2S_ReceiveData(SPI1);
}

void FlashPageEarse(u16 page)
{	

}

void FlashPageRead(u16 page,u8 *Data)
{

}

void FlashPageWrite(u16 page,u8 *Data)		//写一整页，页范围0-4095
{
	
}

void FlashWaitBusy(void)
{
	
}

//将指定主存储器页的数据转入指定缓冲区
void AT45_RomTo_buf(unsigned char buffer,unsigned int page)
{ 

}

//读取指定缓冲区指定单元的数据，保存在DF_buffer[]数组中
/*
unsigned char AT45_buf_ToRam(unsigned char buffer,unsigned int start_address,unsigned int length)
{
	
}*/

//将DF_buffer[]数组中指定长度的数据写入指定缓冲区
/*
unsigned char AT45_RamTo_buf(unsigned char buffer,unsigned int start_address,unsigned int length)
{
	
}
*/

//将指定缓冲区中的数据写入主存储区的指定页
void AT45_buf_ToRom(unsigned char buffer,unsigned int page)
{
	
}

//擦除指定的主存储器页（地址范围0-4095）
/*
void AT45_page_earse(unsigned int page)
{

} */


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/

