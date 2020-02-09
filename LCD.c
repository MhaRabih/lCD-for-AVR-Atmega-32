/*
 * LCD.C
 *
 *  Created on: Aug 23, 2019
 *      Author: maha_
 */
#include "avr/io.h"
#include "utlis.h"
#include "stdtypes.h"
#include <util/delay.h>
#define CLEAR_SCREEN LDC_WriteCmd (0b00000001)
#define MOVE_CURSOR  LDC_WriteCmd (0b00011111)
#define ENTARY_MODE_SET  LDC_WriteCmd (0b00000111)
#define PRINT_MAHA  LCD_WriteData ('M');\
    		     	LCD_WriteData ('a');\
    		     	LCD_WriteData ('h');\
    		    	LCD_WriteData ('a')
#define PRINT_maha  LCD_WriteData (2);\
    		     	LCD_WriteData (1);\
    		     	LCD_WriteData (0)

void LCD_WriteData (u8);
void LDC_WriteCmd (u8);
void GotoXY (u8,u8);
void LCD_u8Init(void);
void Move_Word (void);
void Move_Word_Sin (void);
void Write_Number (u8);
void Print_BinNum (u8);
void Print_HexNum (u8);
int main (void)
{
	u8 sw=0,lastsw;
	DDRD=0x00;
	PORTD=0xff;
	LCD_u8Init();
	lastsw=PIND;
	CLEAR_SCREEN ;
    while(1)
    {
    	sw =PIND;
   		CLEAR_SCREEN ;
   		GotoXY(0,0);
   		LCD_WriteData('D');
   		LCD_WriteData('E');
   		LCD_WriteData('C');
   		LCD_WriteData(':');
        Write_Number (sw);
        lastsw=sw;
       GotoXY(0,1);
   		LCD_WriteData('B');
   		LCD_WriteData('I');
   		LCD_WriteData('N');
   		LCD_WriteData(':');
   		Print_BinNum (sw);
   		GotoXY(8,0);
   		LCD_WriteData('H');
   		LCD_WriteData('E');
   		LCD_WriteData('X');
   		LCD_WriteData(':');
   		Print_HexNum (sw);
   		while(PIND==lastsw);


  }

}
void LDC_WriteCmd (u8 u8cmd)
{
	Clr_Bit(PORTA,0); //clr RS cmd mode
	Clr_Bit(PORTA,1); //write mode
	PORTB = u8cmd ;
	Set_Bit(PORTA,2); //set enable pin
	_delay_ms(2);
	Clr_Bit(PORTA,2);//clr enable pin

}

void LCD_WriteData(u8 u8data)
{
	Set_Bit(PORTA,0); //set RS data mode
	Clr_Bit(PORTA,1); //write mode
	PORTB = u8data ;
	Set_Bit(PORTA,2); //set enable pin
	_delay_ms(2);
	Clr_Bit(PORTA,2);//clr enable pin

}
void LCD_u8Init(void)
{
	DDRA=0xff;
	DDRB=0xff;
	_delay_ms(30);
	LDC_WriteCmd (0b00111100);
	_delay_ms(1);
	LDC_WriteCmd (0b00001111);
	_delay_ms(1);
	CLEAR_SCREEN ;
	_delay_ms(2);
	LDC_WriteCmd (0b00000110);
}
void GotoXY (u8 x ,u8 y)
{
	if (y==0)
	{
		LDC_WriteCmd (0b10000000+x);
	}
	else if (y==1)
	{
		LDC_WriteCmd (0b11000000+x);
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

void Move_Word (void)
{
	u8 i,j ;
	for(i=0,j=1;i<=12;i++)
     {

	     GotoXY(i,j);
         PRINT_maha;
   	     _delay_ms(500);
   	     CLEAR_SCREEN ;
   	     GotoXY((i+6),j);
     }
}
void Move_Word_Sin (void)
{
	u8 i,j ;
	for(i=0,j=1;i<=12;i++)
 	{
    	  GotoXY(i,j);
    	  PRINT_MAHA;
          j=(j*(-1))+1;
          GotoXY((i+3),(j));
          PRINT_maha;
          _delay_ms(500);
    	  CLEAR_SCREEN ;
    	  GotoXY((i+6),j);

 	}
}

void Print_BinNum (u8 num)
	{
	   u8 i=1,arr[9]={0,0,0,0,0,0,0,0,0,0},mod;
	   mod=num;
	   do
	   {
		  mod=num%2;
		  num=num/2;
		  arr[i]=mod;
		  i++;
	    }while(num!=0);
	     for(i=8;i>0;i--)
			   {
				   LCD_WriteData (arr[i]+'0');
			   }
	}
void Print_HexNum (u8 num)
	{
	   u8 i=1,arr[3]={0,0,0},mod,j,a;
	   mod=num;

	   do
	   {
		  mod=num%16;
		  num=num/16;
		  arr[i]=mod;
		  i++;
	    }while(num!=0);
	     for(i=2;i>0;i--)
			   {
	    	      if (arr[i]<10)
				   LCD_WriteData (arr[i]+'0');
	    	      else if (arr[i]==10)
	    	       LCD_WriteData ('A');
	    	      else if (arr[i]==11)
	    	       LCD_WriteData ('B');
	    	      else if (arr[i]==12)
	    	       LCD_WriteData ('C');
	    	      else if (arr[i]==13)
	    	        LCD_WriteData ('D');
	    	      else if (arr[i]==14)
	    	      	LCD_WriteData ('E');
	    	      else if (arr[i]==15)
	    	      	LCD_WriteData ('F');


			   }

	}
/* maha arabic
      LCD_WriteData  (0b01000000);
	LCD_WriteData (0b00000000);
	LCD_WriteData (0b00000000);
	LCD_WriteData (0b00000000);
	LCD_WriteData (0b00000000);
	LCD_WriteData (0b00000110);
	LCD_WriteData (0b00111001);
	LCD_WriteData (0b00000110);
    LCD_WriteData (0b00000000);
	LCD_WriteData (0b00000000);
	LCD_WriteData (0b00000000);
	LCD_WriteData (0b00000000);
	LCD_WriteData (0b00000100);
	LCD_WriteData (0b00001010);
	LCD_WriteData (0b00011111);
	LCD_WriteData (0b00001010);
	LCD_WriteData (0b00000100);
	LCD_WriteData (0b00000000);
	LCD_WriteData (0b00001000);
	LCD_WriteData (0b00001000);
	LCD_WriteData (0b00001000);
	LCD_WriteData (0b00001000);
	LCD_WriteData (0b00001111);
	LCD_WriteData (0b00000000);
    LCD_WriteData (0b00000000);*/
