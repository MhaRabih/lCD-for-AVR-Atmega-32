/*
 * Key_Pad.c
 *
 *  Created on: Aug 24, 2019
 *      Author: maha_
 */
#include "avr/io.h"
#include "stdtypes.h"
#include "utlis.h"
#include <util/delay.h>
#define CLEAN_SCREEN LCD_WriteCmd (0b00000001);
void Key_int(void);
u8 u8Key_Get_Sw(void);
void LCD_WriteData (u8);
void LCD_WriteCmd (u8);
void LCD_u8Init(void);
void Write_Number (u8 num);
void GotoXY (u8,u8);
int main(void)
{
	LCD_u8Init();
	Key_int();
	u8 keynum ;
	//LCD_WriteData ('m');
	Clr_Bit(DDRA,5);
	while(1)
	{

		keynum =  u8Key_Get_Sw();

if (Get_Bit(PINA,5)==1)
{
	CLEAN_SCREEN;

}
else
 {
		if (keynum>0)
		{
			//CLEAN_SCREEN;
			if(keynum<10)
			{

				LCD_WriteData(keynum-1+'0');
			}
		else
			{
			Write_Number (keynum-1);
			}
		}
     }
 }
}
void LCD_WriteCmd (u8 u8cmd)
{
	Clr_Bit(PORTA,1); //clr RS cmd mode
	Clr_Bit(PORTA,2); //write mode
	PORTB = u8cmd ;
	Set_Bit(PORTA,3); //set enable pin
	_delay_ms(2);
	Clr_Bit(PORTA,3);//clr enable pin

}
void LCD_WriteData(u8 u8data)
{
	Set_Bit(PORTA,1); //set RS data mode
	Clr_Bit(PORTA,2); //write mode
	PORTB = u8data ;
	Set_Bit(PORTA,3); //set enable pin
	_delay_ms(2);
	Clr_Bit(PORTA,3);//clr enable pin

}
void LCD_u8Init(void)
{
	DDRA=0xff;
	DDRB=0xff;
	_delay_ms(30);
	LCD_WriteCmd (0b00111100);
	_delay_ms(1);
	LCD_WriteCmd (0b00001111);
	_delay_ms(1);
	LCD_WriteCmd (0b00000001);
	_delay_ms(2);
	LCD_WriteCmd (0b00000110);
}
void GotoXY (u8 x ,u8 y)
{
	if (y==0)
	{
		LCD_WriteCmd (0b10000000+x);
	}
	else if (y==1)
	{
		LCD_WriteCmd (0b11000000+x);
	}

}

void Write_Number (u8 num)
	{
		   u8 i=1,j,arr[4],mod;
		   mod=num;
		   do
		   {
	           mod=num%10;
	          num=num/10;
	           arr[i]=mod;
	           i++;
             }while(num!=0);
     for(j=i-1;j>0;j--)
	 {
			   LCD_WriteData (arr[j]+'0');
	}
	}


void Key_int(void)
{
	DDRC=0x0f;
	PORTC=0xff;
}
u8 u8Key_Get_Sw(void)
{
	u8 u8Return = 0 ;
	u8 u8RowNo,u8ColNo;
	for(u8ColNo=0;u8ColNo<=3;u8ColNo++)
	{
		Clr_Bit(PORTC,u8ColNo);
		for(u8RowNo=0;u8RowNo<=3;u8RowNo++)
		{
			if (!Get_Bit(PINC,(u8RowNo+4)))
			{
				u8Return=(u8RowNo*4)+u8ColNo+1;
				while(!(Get_Bit(PINC,(u8RowNo+4))));
			}

		}
		Set_Bit(PORTC,u8ColNo);
	}

	return u8Return;
}
