//***************************************************************************
//  File........: nokia1100_lcd_lib.c
//  Author(s)...: Chiper
//  URL(s)......: http://digitalchip.ru/
//  Device(s)...: ATMega...
//  Compiler....: AVR-GCC
//  Description.: ������� LCD-����������� �� Nokia1100 � ������������ ���������
//  Data........: 28.03.12
//  Version.....: 2.1
//***************************************************************************
//  Notice: ��� ����������� �������� LCD-����������� ������ ���� ���������� �
//  ������ � ���� �� ����� �� ����������������
//***************************************************************************

#include "nokia1100_lcd_lib.h"
#include "nokia1100_lcd_font.h"	// ���������� ����� (����� �������� � ����������� ������)
#include <stdlib.h>

//******************************************************************************
// �������, �����������, ��������� ����������

// ������� ��� ������ � ������
#define ClearBit(reg, bit)       reg &= (~(1<<(bit)))
#define SetBit(reg, bit)         reg |= (1<<(bit))	
#define InvBit(reg, bit)         reg ^= 1<<bit	

//******************************************************************************
// ������������� �����������
void nlcd_Init(void)
{	
	// �������������� ���� �� ����� ��� ������ � LCD-������������
	DDR_LCD |= (1<<SCLK_LCD_PIN)|(1<<SDA_LCD_PIN)|(1<<CS_LCD_PIN)|(1<<RST_LCD_PIN);

	CS_LCD_RESET;
	RST_LCD_RESET;

	_delay_ms(5);            // ������� �� ����� 5�� ��� ��������� ����������(����� 5 �� ����� ����������)

	RST_LCD_SET;


	nlcd_SendByte(CMD_LCD_MODE,0xE2); // *** SOFTWARE RESET 

	nlcd_SendByte(CMD_LCD_MODE,0x3A); // *** Use internal oscillator
	nlcd_SendByte(CMD_LCD_MODE,0xEF); // *** FRAME FREQUENCY:
	nlcd_SendByte(CMD_LCD_MODE,0x04); // *** 80Hz
	nlcd_SendByte(CMD_LCD_MODE,0xD0); // *** 1:65 divider
	
	nlcd_SendByte(CMD_LCD_MODE,0x20); // ������ � ������� Vop 
	nlcd_SendByte(CMD_LCD_MODE,0x90);

	nlcd_SendByte(CMD_LCD_MODE,0xA4); // all on/normal display

	nlcd_SendByte(CMD_LCD_MODE,0x2F); // Power control set(charge pump on/off)
									  // ���������� �������������

	nlcd_SendByte(CMD_LCD_MODE,0x40); // set start row address = 0
	nlcd_SendByte(CMD_LCD_MODE,0xB0); // ���������� Y-����� = 0
	nlcd_SendByte(CMD_LCD_MODE,0x10); // ���������� X-�����, ������� 3 ����
	nlcd_SendByte(CMD_LCD_MODE,0x0);  // ���������� X-�����, ������� 4 ����

	nlcd_SendByte(CMD_LCD_MODE,0xC8); // mirror Y axis (about X axis)
	nlcd_SendByte(CMD_LCD_MODE,0xA1); // ������������� ����� �� �����������

	nlcd_SendByte(CMD_LCD_MODE,0xAC); // set initial row (R0) of the display
	nlcd_SendByte(CMD_LCD_MODE,0x07);

	//nlcd_SendByte(CMD_LCD_MODE,0xF9); //

	nlcd_SendByte(CMD_LCD_MODE,0xAF); // ����� ���/����

	nlcd_Clear(); // clear LCD
}

//******************************************************************************
// ������� ������
void nlcd_Clear(void)
{
	nlcd_SendByte(CMD_LCD_MODE,0x40); // Y = 0
	nlcd_SendByte(CMD_LCD_MODE,0xB0);
	nlcd_SendByte(CMD_LCD_MODE,0x10); // X = 0
	nlcd_SendByte(CMD_LCD_MODE,0x00);

	nlcd_xcurr=0; nlcd_ycurr=0;		  // ������������� � 0 ������� ���������� � �����������

	//nlcd_SendByte(CMD_LCD_MODE,0xAE); // disable display;
	
	for(unsigned int i=0;i<864;i++) nlcd_SendByte(DATA_LCD_MODE,0x00);
	
	//nlcd_SendByte(CMD_LCD_MODE,0x07);
	//nlcd_SendByte(CMD_LCD_MODE,0xAF); // enable display;
}


//******************************************************************************
// �������� ����� (������� ��� ������) �� LCD-����������
//  mode: CMD_LCD_MODE - �������� �������
//		  DATA_LCD_MODE - �������� ������
//  c: �������� ������������� �����
void nlcd_SendByte(char mode,unsigned char c)
{
    CS_LCD_RESET;
    SCLK_LCD_RESET;

	if (mode) 				// DATA_LCD_MODE
	{
		nlcd_memory[nlcd_xcurr][nlcd_ycurr] = c;	// ���������� ������ � ����������
	    
		nlcd_xcurr++;								// ��������� ���������� � �����������
		
		if (nlcd_xcurr>95)
		{
			nlcd_xcurr = 0;
			nlcd_ycurr++;
		}

		if (nlcd_ycurr>8) nlcd_ycurr = 0;			


		SDA_LCD_SET;								// �������� ����� � LCD-����������
	}
	 else SDA_LCD_RESET;	// CMD_LCD_MODE

    SCLK_LCD_SET;

    for(unsigned char i=0;i<8;i++)
    {
    	SCLK_LCD_RESET;

        if(c & 0x80) SDA_LCD_SET;
         else	     SDA_LCD_RESET;

        SCLK_LCD_SET;
        c <<= 1;

		//_delay_us(NLCD_MIN_DELAY);	// *****!!!!! 34 - ����������� ��������, ��� ������� �������� ��� LCD-����������
    }	

    CS_LCD_SET;
}

//******************************************************************************
// ����� ������� �� LCD-����� NOKIA 1100 � ������� �����
//  c: ��� �������
void nlcd_Putc(unsigned char c)
{
	if (c>127) c=c-64; 	// ��������� ������� �������� � ��������� CP1251 � ������ ������
						// �������� ������� ASCII (������� � ���� 0x80)
	
	for ( unsigned char i = 0; i < 5; i++ )
		 nlcd_SendByte(DATA_LCD_MODE,pgm_read_byte(&(nlcd_Font[c-32][i])));
    
	nlcd_SendByte(DATA_LCD_MODE,0x00); // ����� ����� ��������� �� ����������� � 1 �������
}

//******************************************************************************
// ����� �������� ������� �� LCD-����� NOKIA 1100 � ������� �����
//  c: ��� �������
void nlcd_PutcWide(unsigned char c)
{
	if (c>127) c=c-64; 	// ��������� ������� �������� � ��������� CP1251 � ������ ������
						// �������� ������� ASCII (������� � ���� 0x80)

	for ( unsigned char i = 0; i < 5; i++ )
	{
		unsigned char glyph = pgm_read_byte(&(nlcd_Font[c-32][i]));
	   	nlcd_SendByte(DATA_LCD_MODE,glyph);
	   	nlcd_SendByte(DATA_LCD_MODE,glyph);
    }
    
	nlcd_SendByte(DATA_LCD_MODE,0x00); // ����� ����� ��������� �� ����������� � 1 �������
//	nlcd_SendByte(DATA_LCD_MODE,0x00); // ����� ������� ��� �����
}

//******************************************************************************
// ����� ������ �������� �� LCD-����� NOKIA 1100 � ������� �����. ���� ������ �������
// �� ����� � ������� ������, �� ������� ����������� �� ��������� ������.
//  message: ��������� �� ������ ��������. 0x00 - ������� ����� ������.
void nlcd_Print(char * message)
{
	while (*message) nlcd_Putc(*message++); // ����� ������ ��������� �����
}

//******************************************************************************
// ����� ������ �������� �� LCD-����� NOKIA 1100 � ������� ����� �� ����������� ������.
// ���� ������ ������� �� ����� � ������� ������, �� ������� ����������� �� ��������� ������.
//  message: ��������� �� ������ �������� � ����������� ������. 0x00 - ������� ����� ������.
void nlcd_PrintF(unsigned char * message)
{
	unsigned char data;
	while (data=pgm_read_byte(message), data)
	{ 
    	nlcd_Putc(data);
		message++;
    }
}


//******************************************************************************
// ����� ������ �������� ������� ������ �� LCD-����� NOKIA 1100 � ������� �����
// �� ����������� ������. ���� ������ ������� �� ����� � ������� ������, �� �������
// ����������� �� ��������� ������.
//  message: ��������� �� ������ �������� � ����������� ������. 0x00 - ������� ����� ������.
void nlcd_PrintWide(unsigned char * message)
{
	while (*message) nlcd_PutcWide(*message++);  // ����� ������ ��������� �����
}


//******************************************************************************
// ������������� ������ � ����������� ���������. ������ ���������� � ������� 
// ����� ����. �� ����������� 16 ���������, �� ��������� - 8
//  x: 0..15
//  y: 0..7    
void nlcd_GotoXY(char x,char y)
{
	x=x*6;	// ��������� �� ���������� � ����������� � ����������� � ��������

	nlcd_xcurr=x;
	nlcd_ycurr=y;

	nlcd_SendByte(CMD_LCD_MODE,(0xB0|(y&0x0F)));      // ��������� ������ �� Y: 0100 yyyy         
    nlcd_SendByte(CMD_LCD_MODE,(0x00|(x&0x0F)));      // ��������� ������ �� X: 0000 xxxx - ���� (x3 x2 x1 x0)
    nlcd_SendByte(CMD_LCD_MODE,(0x10|((x>>4)&0x07))); // ��������� ������ �� X: 0010 0xxx - ���� (x6 x5 x4)

}

//******************************************************************************
// ������������� ����� �������� ����� ������. ������ �� ������ �� ����������, ������ �������������
//  mode: INV_MODE_ON ��� INV_MODE_OFF
void nlcd_Inverse(unsigned char mode)
{
	if (mode) nlcd_SendByte(CMD_LCD_MODE,0xA6);
	 else nlcd_SendByte(CMD_LCD_MODE,0xA7);
}


//******************************************************************************
// ������������� ������ � ��������. ������ ���������� � ������� 
// ����� ����. �� ����������� 96 ��������, �� ��������� - 65
//  x: 0..95
//  y: 0..64
void nlcd_GotoXY_pix(char x,char y)
{
	nlcd_xcurr=x;
	nlcd_ycurr=y/8;

	nlcd_SendByte(CMD_LCD_MODE,(0xB0|(nlcd_ycurr&0x0F)));      // ��������� ������ �� Y: 0100 yyyy         
    nlcd_SendByte(CMD_LCD_MODE,(0x00|(x&0x0F)));      // ��������� ������ �� X: 0000 xxxx - ���� (x3 x2 x1 x0)
    nlcd_SendByte(CMD_LCD_MODE,(0x10|((x>>4)&0x07))); // ��������� ������ �� X: 0010 0xxx - ���� (x6 x5 x4)
}


//******************************************************************************
// ����� ����� �� LCD-����� NOKIA 1100
//  x: 0..95  ���������� �� ����������� (������ �� �������� ������ ����)
//	y: 0..64  ���������� �� ���������
//	pixel_mode: PIXEL_ON  - ��� ��������� ��������
//				PIXEL_OFF - ��� ���������� �������
//				PIXEL_INV - ��� �������� �������
void nlcd_Pixel(unsigned char x,unsigned char y, unsigned char pixel_mode)
{
	unsigned char temp;

	nlcd_GotoXY_pix(x,y);        
	temp=nlcd_memory[nlcd_xcurr][nlcd_ycurr];

	switch(pixel_mode)
	{
    	case PIXEL_ON:
        	SetBit(temp, y%8);			// �������� ������
			break;
    	case PIXEL_OFF:
     		ClearBit(temp, y%8);		// ��������� ������
			break;
    	case PIXEL_INV:
     		InvBit(temp, y%8);			// ����������� ������
			break;
	}
	
	nlcd_memory[nlcd_xcurr][nlcd_ycurr] = temp; // �������� ���� � ����������
	nlcd_SendByte(DATA_LCD_MODE,temp); // �������� ���� � ����������
}

//******************************************************************************
// ����� ����� �� LCD-����� NOKIA 1100
//  x1, x2: 0..95  ���������� �� ����������� (������ �� �������� ������ ����)
//	y1, y2: 0..64  ���������� �� ���������
//	pixel_mode: PIXEL_ON  - ��� ��������� ��������
//				PIXEL_OFF - ��� ���������� �������
//				PIXEL_INV - ��� �������� �������
void nlcd_Line (unsigned char x1,unsigned char y1, unsigned char x2,unsigned char y2, unsigned char pixel_mode)
{
	int dy, dx;
	signed char addx = 1, addy = 1;
	signed int 	P, diff;

	unsigned char i = 0;
   
	dx = abs((signed char)(x2 - x1));
	dy = abs((signed char)(y2 - y1));

	if(x1 > x2)	addx = -1;
	if(y1 > y2)	addy = -1;

	if(dx >= dy)
	{
		dy *= 2;
		P = dy - dx;

		diff = P - dx;

		for(; i<=dx; ++i)
		{
			nlcd_Pixel(x1, y1, pixel_mode);

			if(P < 0)
			{
				P  += dy;
				x1 += addx;
			}
			else
			{
				P  += diff;
				x1 += addx;
				y1 += addy;
			}
		}
	}
	else
	{
		dx *= 2;
		P = dx - dy;
		diff = P - dy;

		for(; i<=dy; ++i)
		{
			nlcd_Pixel(x1, y1, pixel_mode);

			if(P < 0)
			{
				P  += dx;
				y1 += addy;
			}
			else
			{
				P  += diff;
				x1 += addx;
				y1 += addy;
			}
		}
	}
}



//******************************************************************************
// ����� ���������� �� LCD-����� NOKIA 1100
//  x: 0..95  ���������� ������ ���������� (������ �� �������� ������ ����)
//	y: 0..64  ���������� �� ���������
//  radius:   ������ ����������
//  fill:		FILL_OFF  - ��� ������� ����������
//				FILL_ON	  - � ��������
//	pixel_mode: PIXEL_ON  - ��� ��������� ��������
//				PIXEL_OFF - ��� ���������� �������
//				PIXEL_INV - ��� �������� �������

void nlcd_Circle(unsigned char x, unsigned char y, unsigned char radius, unsigned char fill, unsigned char pixel_mode)
{
	signed char  a, b, P;

	a = 0;
	b = radius;
	P = 1 - radius;

	do
	{
		if(fill)
		{
			nlcd_Line(x-a, y+b, x+a, y+b, pixel_mode);
			nlcd_Line(x-a, y-b, x+a, y-b, pixel_mode);
			nlcd_Line(x-b, y+a, x+b, y+a, pixel_mode);
			nlcd_Line(x-b, y-a, x+b, y-a, pixel_mode);
		}
		else
		{
			nlcd_Pixel(a+x, b+y, pixel_mode);
			nlcd_Pixel(b+x, a+y, pixel_mode);
			nlcd_Pixel(x-a, b+y, pixel_mode);
			nlcd_Pixel(x-b, a+y, pixel_mode);
			nlcd_Pixel(b+x, y-a, pixel_mode);
			nlcd_Pixel(a+x, y-b, pixel_mode);
			nlcd_Pixel(x-a, y-b, pixel_mode);
			nlcd_Pixel(x-b, y-a, pixel_mode);
		}

		if(P < 0) P += 3 + 2 * a++;
			else P += 5 + 2 * (a++ - b--);
	} while(a <= b);
}



//******************************************************************************
// ����� ���������� �� LCD-����� NOKIA 1100
//  x1, x2: 0..95  ���������� �� ����������� (������ �� �������� ������ ����)
//	y1, y2: 0..64  ���������� �� ���������
//	pixel_mode: PIXEL_ON  - ��� ��������� ��������
//				PIXEL_OFF - ��� ���������� �������
//				PIXEL_INV - ��� �������� �������
void nlcd_Rect (unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char fill, unsigned char pixel_mode)
{
	if(fill)
	{			// � ��������
		unsigned char  i, xmin, xmax, ymin, ymax;

		if(x1 < x2) { xmin = x1; xmax = x2; }	// ���������� ����������� � ������������ ���������� �� X
		 else { xmin = x2; xmax = x1; }

		if(y1 < y2) { ymin = y1; ymax = y2; }	// ���������� ����������� � ������������ ���������� �� Y
		 else { ymin = y2; ymax = y1; }

		for(; xmin <= xmax; ++xmin)
		{
			for(i=ymin; i<=ymax; ++i) nlcd_Pixel(xmin, i, pixel_mode);
		}
	}
	else		// ��� �������
	{
		nlcd_Line(x1, y1, x2, y1, pixel_mode);		// ������ ������� ��������������
		nlcd_Line(x1, y2, x2, y2, pixel_mode);
		nlcd_Line(x1, y1+1, x1, y2-1, pixel_mode);
		nlcd_Line(x2, y1+1, x2, y2-1, pixel_mode);
	}
}


//******************************************************************************
// ����� �������� �� LCD-����� NOKIA 1100
//  x: 0..95  ���������� �������� ������ ���� �� ����������� (������ �� �������� ������ ���� ������)
//	y: 0..64  ���������� �������� ������ ���� �� ���������
//  picture: ��������� �� ������ � ����������� ���������, ������ 2 ����� ��������� ��������������
//			 ������ �������� �� ����������� � ��������� 
void nlcd_Pict  (unsigned char x, unsigned char y, unsigned char * picture)
{
	unsigned char pict_width = pgm_read_byte(&picture[0]);  // ������ ������� � ��������  
	unsigned char pict_height = pgm_read_byte(&picture[1]); // ������ ������� � ��������
	unsigned char pict_height_bank=pict_height / 8+((pict_height%8)>0?1:0); // ������ ������� � ������
	unsigned char y_pos_in_bank = y/8 + ((y%8)>0?1:0);		// ������� �� y � ������ (������� �� 8 ����.)

	int adr = 2; // ������ �������� ����� � ������� � ���������

	for (unsigned char i=0; i< pict_height_bank; i++)
	{ // ������ ��������� (�� ������)

		if (i<((NLCD_Y_RES/8)+1)) // �� �������� �������� �� ��������� ������
		{
			//���������������� �� ����� ������
			nlcd_xcurr=x;
			nlcd_ycurr=y + i;

			nlcd_SendByte(CMD_LCD_MODE,(0xB0|((y_pos_in_bank+i)&0x0F))); // ��������� ������ �� Y: 0100 yyyy         
    		nlcd_SendByte(CMD_LCD_MODE,(0x00|(x&0x0F)));      // ��������� ������ �� X: 0000 xxxx - ���� (x3 x2 x1 x0)
    		nlcd_SendByte(CMD_LCD_MODE,(0x10|((x>>4)&0x07))); // ��������� ������ �� X: 0010 0xxx - ���� (x6 x5 x4)

			//����� ������
			for ( unsigned char j = 0; j < pict_width; j++ )
			{
				if ((x+j) < NLCD_X_RES) nlcd_SendByte(DATA_LCD_MODE,pgm_read_byte(&(picture[adr]))); // �� �������� �������� �� ��������� ������
				adr++;
			}
		}
	}
}

