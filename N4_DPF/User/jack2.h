#ifndef	__JACK2_H
#define __JACK2_H
#include "stm32f10x_type.h"

void HomePage_Disp(void);
void DispHanZi_32(unsigned int x,unsigned int y,unsigned char const *tab_p,
								unsigned int charColor,unsigned int bkColor);
void DispHanZi_24(unsigned int x,unsigned int y,unsigned char const *tab_p,
								unsigned int charColor,unsigned int bkColor);
void SetPoint(u16 x,u16 y,u16 point);
void Draw_Bottom(unsigned char mod);
unsigned char XuanZhongXianShi(unsigned char index_old,unsigned char index_new);
void Draw_Menu(void);
void ChuPing_IT(void);
void ZuoJian_IT(void);
void YouJian_IT(void);
void DispChinese(unsigned int x,unsigned int y,unsigned char z,unsigned int charColor,unsigned int bkColor);
#endif




