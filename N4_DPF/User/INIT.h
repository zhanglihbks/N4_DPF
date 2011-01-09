#ifndef __INIT_H
#define __INIT_H
void SystemInit (void);
static void SetSysClock(void);
void FSMC_LCD_Init(void);
void NVIC_Configuration(void);
void EXTI_Config(void);
static void SetSysClock(void);
void SPI_Flash_Init(void);
#endif
