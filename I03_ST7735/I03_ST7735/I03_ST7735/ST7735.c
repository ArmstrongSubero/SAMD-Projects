/*
 * File:   ST7735.c
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Source file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This file contains source code for 
 *                      using the ST7735 display
 *
 * Modified From: None
 * 
 * Change History:
 *
 * Author                Rev     Date          Description
 * Armstrong Subero      1.0     25/05/2020    Initial Release
 *
 * Updated on August 05, 2020, 06:48 PM
 */ 

#include "sam.h"
#include "ST7735.h"
#include "delay.h"
#include "SPI.h"
#include <stdlib.h>

/*******************************************************************************
 * Description: Characters
 ******************************************************************************/
static const char Alpha1[] = {
                  0x00,0x00,0x00,0x00,0x00,  // 20 space
                  0x00,0x00,0x5f,0x00,0x00,  // 21 !
                  0x00,0x07,0x00,0x07,0x00,  // 22 "
                  0x14,0x7f,0x14,0x7f,0x14,  // 23 #
                  0x24,0x2a,0x7f,0x2a,0x12,  // 24 $
                  0x23,0x13,0x08,0x64,0x62,  // 25 %
                  0x36,0x49,0x55,0x22,0x50,  // 26 &
                  0x00,0x05,0x03,0x00,0x00,  // 27 '
                  0x00,0x1c,0x22,0x41,0x00,  // 28 (
                  0x00,0x41,0x22,0x1c,0x00,  // 29 )
                  0x14,0x08,0x3e,0x08,0x14,  // 2a *
                  0x08,0x08,0x3e,0x08,0x08,  // 2b +
                  0x00,0x50,0x30,0x00,0x00,  // 2c ,
                  0x08,0x08,0x08,0x08,0x08,  // 2d -
                  0x00,0x60,0x60,0x00,0x00,  // 2e .
                  0x20,0x10,0x08,0x04,0x02,  // 2f /
                  0x3e,0x51,0x49,0x45,0x3e,  // 30 0
                  0x00,0x42,0x7f,0x40,0x00,  // 31 1
                  0x42,0x61,0x51,0x49,0x46,  // 32 2
                  0x21,0x41,0x45,0x4b,0x31,  // 33 3
                  0x18,0x14,0x12,0x7f,0x10,  // 34 4
                  0x27,0x45,0x45,0x45,0x39,  // 35 5
                  0x3c,0x4a,0x49,0x49,0x30,  // 36 6
                  0x01,0x71,0x09,0x05,0x03,  // 37 7
                  0x36,0x49,0x49,0x49,0x36,  // 38 8
                  0x06,0x49,0x49,0x29,0x1e,  // 39 9
                  0x00,0x36,0x36,0x00,0x00,  // 3a :
                  0x00,0x56,0x36,0x00,0x00,  // 3b ;
                  0x08,0x14,0x22,0x41,0x00,  // 3c <
                  0x14,0x14,0x14,0x14,0x14,  // 3d =
                  0x00,0x41,0x22,0x14,0x08,  // 3e >
                  0x02,0x01,0x51,0x09,0x06,  // 3f ?
                  0x32,0x49,0x79,0x41,0x3e,  // 40 @
                  0x7e,0x11,0x11,0x11,0x7e,  // 41 A
                  0x7f,0x49,0x49,0x49,0x36,  // 42 B
                  0x3e,0x41,0x41,0x41,0x22,  // 43 C
                  0x7f,0x41,0x41,0x22,0x1c,  // 44 D
                  0x7f,0x49,0x49,0x49,0x41,  // 45 E
                  0x7f,0x09,0x09,0x09,0x01,  // 46 F
                  0x3e,0x41,0x49,0x49,0x7a,  // 47 G
                  0x7f,0x08,0x08,0x08,0x7f,  // 48 H
                  0x00,0x41,0x7f,0x41,0x00,  // 49 I
                  0x20,0x40,0x41,0x3f,0x01,  // 4a J
                  0x7f,0x08,0x14,0x22,0x41,  // 4b K
                  0x7f,0x40,0x40,0x40,0x40,  // 4c L
                  0x7f,0x02,0x0c,0x02,0x7f,  // 4d M
                  0x7f,0x04,0x08,0x10,0x7f,  // 4e N
                  0x3e,0x41,0x41,0x41,0x3e,  // 4f O
                  0x7f,0x09,0x09,0x09,0x06,  // 50 P
                  0x3e,0x41,0x51,0x21,0x5e}; // 51 Q

static const char Alpha2[] = {
                  0x7f,0x09,0x19,0x29,0x46,
                  0x46,0x49,0x49,0x49,0x31,  // 53 S
                  0x01,0x01,0x7f,0x01,0x01,  // 54 T
                  0x3f,0x40,0x40,0x40,0x3f,  // 55 U
                  0x1f,0x20,0x40,0x20,0x1f,  // 56 V
                  0x3f,0x40,0x38,0x40,0x3f,  // 57 W
                  0x63,0x14,0x08,0x14,0x63,  // 58 X
                  0x07,0x08,0x70,0x08,0x07,  // 59 Y
                  0x61,0x51,0x49,0x45,0x43,  // 5a Z
                  0x00,0x7f,0x41,0x41,0x00,  // 5b [
                  0x02,0x04,0x08,0x10,0x20,  // 5c 55
                  0x00,0x41,0x41,0x7f,0x00,  // 5d ]
                  0x04,0x02,0x01,0x02,0x04,  // 5e ^
                  0x40,0x40,0x40,0x40,0x40,  // 5f _
                  0x00,0x01,0x02,0x04,0x00,  // 60 `
                  0x20,0x54,0x54,0x54,0x78,  // 61 a
                  0x7f,0x48,0x44,0x44,0x38,  // 62 b
                  0x38,0x44,0x44,0x44,0x20,  // 63 c
                  0x38,0x44,0x44,0x48,0x7f,  // 64 d
                  0x38,0x54,0x54,0x54,0x18,  // 65 e
                  0x08,0x7e,0x09,0x01,0x02,  // 66 f
                  0x0c,0x52,0x52,0x52,0x3e,  // 67 g
                  0x7f,0x08,0x04,0x04,0x78,  // 68 h
                  0x00,0x44,0x7d,0x40,0x00,  // 69 i
                  0x20,0x40,0x44,0x3d,0x00,  // 6a j
                  0x7f,0x10,0x28,0x44,0x00,  // 6b k
                  0x00,0x41,0x7f,0x40,0x00,  // 6c l
                  0x7c,0x04,0x18,0x04,0x78,  // 6d m
                  0x7c,0x08,0x04,0x04,0x78,  // 6e n
                  0x38,0x44,0x44,0x44,0x38,  // 6f o
                  0x7c,0x14,0x14,0x14,0x08,  // 70 p
                  0x08,0x14,0x14,0x18,0x7c,  // 71 q
                  0x7c,0x08,0x04,0x04,0x08,  // 72 r
                  0x48,0x54,0x54,0x54,0x20,  // 73 s
                  0x04,0x3f,0x44,0x40,0x20,  // 74 t
                  0x3c,0x40,0x40,0x20,0x7c,  // 75 u
                  0x1c,0x20,0x40,0x20,0x1c,  // 76 v
                  0x3c,0x40,0x30,0x40,0x3c,  // 77 w
                  0x44,0x28,0x10,0x28,0x44,  // 78 x
                  0x0c,0x50,0x50,0x50,0x3c,  // 79 y
                  0x44,0x64,0x54,0x4c,0x44,  // 7a z
                  0x00,0x08,0x36,0x41,0x00,  // 7b {
                  0x00,0x00,0x7f,0x00,0x00,  // 7c |
                  0x00,0x41,0x36,0x08,0x00,  // 7d }
                  0x10,0x08,0x08,0x10,0x08,  // 7e ~
                  0x78,0x46,0x41,0x46,0x78}; // 7f &brvbar;
                  
                  
/*******************************************************************************
* Function: ST7735_WriteCommand(int i)
*
* Returns: Nothing
*
* Description: Writes command to LCD
*******************************************************************************/
void ST7735_WriteCommand(int i)
{
  // set RS low
  REG_PORT_OUTCLR0 = DC_PIN_MASK;
  //ST7735_RS = 0;

  // set CS low
  REG_PORT_OUTCLR0 = CS_PIN_MASK;
  //ST7735_CS = 0;

  // Write Data
  spiSend(i);
  //SPI1_Write(i);

  // set CS high
  REG_PORT_OUTSET0 = CS_PIN_MASK;
  //ST7735_CS = 1;
}

/*******************************************************************************
* Function: ST7735_WriteData(int i)
*
* Returns: Nothing
*
* Description: Writes data to LCD
*******************************************************************************/
void ST7735_WriteData(int i)
{
   // set RS low
   REG_PORT_OUTSET0 = DC_PIN_MASK;
  //ST7735_RS = 1;

  // set CS low
  REG_PORT_OUTCLR0 = CS_PIN_MASK;
  //ST7735_CS = 0;

  // Write Data
  spiSend(i);
  //SPI1_Write(i);

  // set CS high
  REG_PORT_OUTSET0 = CS_PIN_MASK;
  //ST7735_CS = 1;
}

/*******************************************************************************
* Function: void ST7735_Init(void)
*
* Returns: Nothing
*
* Description: Initalizes LCD
*******************************************************************************/
void ST7735_Init(void)
{
	    REG_PORT_OUTSET0 = RST_PIN_MASK;
        //ST7735_RESET = 1;
        delay_us(500);
		
		REG_PORT_OUTCLR0 = RST_PIN_MASK;
        //ST7735_RESET = 0;
        delay_us(500);
		
		REG_PORT_OUTSET0 = RST_PIN_MASK;
        //ST7735_RESET = 1;
        delay_us(500);

        REG_PORT_OUTCLR0 = CS_PIN_MASK;
        //ST7735_CS = 0;

        ST7735_WriteCommand(ST7735_SWRESET); // software reset
        delay_us(150);

        ST7735_WriteCommand(ST7735_SLPOUT);  // out of sleep mode
        delay_us(500);

        ST7735_WriteCommand(ST7735_COLMOD);  // set color mode
        ST7735_WriteData(0x05);        // 16-bit color
        delay_us(10);

        ST7735_WriteCommand(ST7735_FRMCTR1);  // frame rate control - normal mode
        ST7735_WriteData(0x01);  // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
        ST7735_WriteData(0x2C);
        ST7735_WriteData(0x2D);

        ST7735_WriteCommand(ST7735_FRMCTR2);  // frame rate control - idle mode
        ST7735_WriteData(0x01);  // frame rate = fosc / (1 x 2 + 40) * (LINE + 2C + 2D)
        ST7735_WriteData(0x2C);
        ST7735_WriteData(0x2D);

        ST7735_WriteCommand(ST7735_FRMCTR3);  // frame rate control - partial mode
        ST7735_WriteData(0x01); // dot inversion mode
        ST7735_WriteData(0x2C);
        ST7735_WriteData(0x2D);
        ST7735_WriteData(0x01); // line inversion mode
        ST7735_WriteData(0x2C);
        ST7735_WriteData(0x2D);

        ST7735_WriteCommand(ST7735_INVCTR);  // display inversion control
        ST7735_WriteData(0x07);  // no inversion

        ST7735_WriteCommand(ST7735_PWCTR1);  // power control
        ST7735_WriteData(0xA2);
        ST7735_WriteData(0x02);      // -4.6V
        ST7735_WriteData(0x84);      // AUTO mode

        ST7735_WriteCommand(ST7735_PWCTR2);  // power control
        ST7735_WriteData(0xC5);      // VGH25 = 2.4C VGSEL = -10 VGH = 3 * AVDD

        ST7735_WriteCommand(ST7735_PWCTR3);  // power control
        ST7735_WriteData(0x0A);      // Opamp current small
        ST7735_WriteData(0x00);      // Boost frequency

        ST7735_WriteCommand(ST7735_PWCTR4);  // power control
        ST7735_WriteData(0x8A);      // BCLK/2, Opamp current small & Medium low
        ST7735_WriteData(0x2A);

        ST7735_WriteCommand(ST7735_PWCTR5);  // power control
        ST7735_WriteData(0x8A);
        ST7735_WriteData(0xEE);

        ST7735_WriteCommand(ST7735_VMCTR1);  // power control
        ST7735_WriteData(0x0E);

        ST7735_WriteCommand(ST7735_INVOFF);    // don't invert display

        ST7735_WriteCommand(ST7735_MADCTL);  // memory access control (directions)
        
        // normal R G B order
        madctl = 0xC0;
        ST7735_WriteData(madctl);  // row address/col address, bottom to top refresh

        ST7735_WriteCommand(ST7735_COLMOD);  // set color mode
        ST7735_WriteData(0x05);        // 16-bit color

        ST7735_WriteCommand(ST7735_CASET);  // column addr set
        ST7735_WriteData(0x00);
        ST7735_WriteData(0x00);   // XSTART = 0
        ST7735_WriteData(0x00);
        ST7735_WriteData(0x7F);   // XEND = 127

        ST7735_WriteCommand(ST7735_RASET);  // row addr set
        ST7735_WriteData(0x00);
        ST7735_WriteData(0x00);    // XSTART = 0
        ST7735_WriteData(0x00);
        ST7735_WriteData(0x9F);    // XEND = 159

        ST7735_WriteCommand(ST7735_GMCTRP1);
        ST7735_WriteData(0x0f);
        ST7735_WriteData(0x1a);
        ST7735_WriteData(0x0f);
        ST7735_WriteData(0x18);
        ST7735_WriteData(0x2f);
        ST7735_WriteData(0x28);
        ST7735_WriteData(0x20);
        ST7735_WriteData(0x22);
        ST7735_WriteData(0x1f);
        ST7735_WriteData(0x1b);
        ST7735_WriteData(0x23);
        ST7735_WriteData(0x37);
        ST7735_WriteData(0x00);
        ST7735_WriteData(0x07);
        ST7735_WriteData(0x02);
        ST7735_WriteData(0x10);
        ST7735_WriteCommand(ST7735_GMCTRN1);
        ST7735_WriteData(0x0f);
        ST7735_WriteData(0x1b);
        ST7735_WriteData(0x0f);
        ST7735_WriteData(0x17);
        ST7735_WriteData(0x33);
        ST7735_WriteData(0x2c);
        ST7735_WriteData(0x29);
        ST7735_WriteData(0x2e);
        ST7735_WriteData(0x30);
        ST7735_WriteData(0x30);
        ST7735_WriteData(0x39);
        ST7735_WriteData(0x3f);
        ST7735_WriteData(0x00);
        ST7735_WriteData(0x07);
        ST7735_WriteData(0x03);
        ST7735_WriteData(0x10);

        ST7735_WriteCommand(0xF6); //Disable ram power save mode
        ST7735_WriteData(0x00);

        ST7735_WriteCommand(ST7735_DISPON);
        delay_us(100);

        ST7735_WriteCommand(ST7735_NORON);  // normal display on
        delay_us(10);

        REG_PORT_OUTSET0 = CS_PIN_MASK;
        //ST7735_CS = 1;
}

/*******************************************************************************
* Function: void ST7735_test()
*
* Returns: Nothing
*
* Description: Tests the LCD
*******************************************************************************/
void ST7735_test(){
    int x;
    ST7735_fillScreen(colWhite);


    for (x = 0; x <= 500; x += 50){
        ST7735_drawCircle(60, (SCREEN_WIDTH/2) + 15 , 42, colMagenta);
        ST7735_writeInteger(25,  SCREEN_WIDTH/2, x, colCyan, 2);
        ST7735_drawString(1, 1, "Reading", colMediumOrchid, 3);
        delay_ms(1000);
        ST7735_writeInteger(25,  SCREEN_WIDTH/2, x, colWhite, 2);
        if (x >= 500){
            break;
        }
    }
}

/*******************************************************************************
* Function: void ST7735_writeInteger(int x, int y, int v, unsigned int colour, int size)
*
* Returns: Nothing
*
* Description: Writes and integer to the LCD
*******************************************************************************/
void ST7735_writeInteger(int x, int y, int v, unsigned int colour, int size)
{
     unsigned char buf[8];
     
     ST7735_drawString(x, y, itoa(v, buf, 10), colour, size);

}

/*******************************************************************************
********************************************************************************
 Functions hereafter copied from Adafruit Library with Modifications
********************************************************************************
*******************************************************************************/
void setAddrWindow(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1)
{
        ST7735_WriteCommand(ST7735_CASET);  // column addr set
        ST7735_WriteData(0x00);
        ST7735_WriteData(x0+0);   // XSTART
        ST7735_WriteData(0x00);
        ST7735_WriteData(x1+0);   // XEND

        ST7735_WriteCommand(ST7735_RASET);  // row addr set
        ST7735_WriteData(0x00);
        ST7735_WriteData(y0+0);    // YSTART
        ST7735_WriteData(0x00);
        ST7735_WriteData(y1+0);    // YEND

        ST7735_WriteCommand(ST7735_RAMWR);  // write to RAM
}

void ST7735_pushColor(unsigned int color)
{
	   REG_PORT_OUTSET0 = DC_PIN_MASK;
       // ST7735_RS = 1;
	   
	   REG_PORT_OUTCLR0 = CS_PIN_MASK;
       // ST7735_CS = 0;
	   
	   spiSend(color >> 8);
	   spiSend(color);
	   
	   REG_PORT_OUTSET0 = CS_PIN_MASK;
        //SPI1_Write(color >> 8);
        //SPI1_Write(color);
        //ST7735_CS = 1;
}

 void ST7735_drawPixel(unsigned char x, unsigned char y, unsigned int color)
{
        setAddrWindow(x, y, x+1, y+1);

        REG_PORT_OUTSET0 = DC_PIN_MASK;
		REG_PORT_OUTCLR0 = CS_PIN_MASK;
      //  ST7735_RS = 1;
       // ST7735_CS = 0;

        spiSend(color >> 8);
		spiSend(color);
       // SPI1_Write(color >> 8);
       // SPI1_Write(color);

        REG_PORT_OUTSET0 = CS_PIN_MASK;
        //ST7735_CS = 1;
}

void ST7735_fillScreen(unsigned int color)
{
        unsigned char x;
        unsigned char y;

        setAddrWindow(0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);

        // setup for data
		REG_PORT_OUTSET0 = DC_PIN_MASK;
		REG_PORT_OUTCLR0 = CS_PIN_MASK;
        //ST7735_RS = 1;
        //ST7735_CS = 0;

        colorB = color >> 8;

        for (x=0; x < SCREEN_WIDTH; x++) {
                for (y=0; y < SCREEN_HEIGHT; y++) {
					    spiSend(colorB);
						spiSend(color);
                        //SPI1_Write(colorB);
                        //SPI1_Write(color);
                }
        }

        REG_PORT_OUTSET0 = CS_PIN_MASK;
        //ST7735_CS = 1;
}

 void ST7735_drawChar(unsigned char x, unsigned char y, char c, unsigned int color, unsigned char size)
{
        unsigned char i, j;

        unsigned char letter = c < 0x52 ? c - 0x20 : c - 0x52;
        for (i =0; i<5; i++ ) {
                unsigned char line = c < 0x52 ? Alpha1[letter*5+i] : Alpha2[letter*5+i];

                for (j = 0; j<8; j++) {
                        if (line & 0x1) {
                                if (size == 1) // default size
                                ST7735_drawPixel(x+i, y+j, color);
                                else {  // big size
                                        ST7735_fillRect(x+i*size, y+j*size, size, size, color);
                                }
                        }
                        line >>= 1;
                }
        }
}

void ST7735_drawString(unsigned char x, unsigned char y, char *c, unsigned int color, unsigned char size)
{
        while (c[0] != 0) {
                ST7735_drawChar(x, y, c[0], color, size);
                x += size*6;
                c++;
                if (x + 5 >= SCREEN_WIDTH) {
                        y += 10;
                        x = 0;
                }
        }
}


// fill a circle
void ST7735_fillCircle(unsigned char x0, unsigned char y0, unsigned char r, unsigned int color) {
        int f = 1 - r;
        int ddF_x = 1;
        int ddF_y = -2 * r;
        int x = 0;
        int y = r;

        ST7735_drawVerticalLine(x0, y0-r, 2*r+1, color);

        while (x<y) {
                if (f >= 0) {
                        y--;
                        ddF_y += 2;
                        f += ddF_y;
                }
                x++;
                ddF_x += 2;
                f += ddF_x;

                ST7735_drawVerticalLine(x0+x, y0-y, 2*y+1, color);
                ST7735_drawVerticalLine(x0-x, y0-y, 2*y+1, color);
                ST7735_drawVerticalLine(x0+y, y0-x, 2*x+1, color);
                ST7735_drawVerticalLine(x0-y, y0-x, 2*x+1, color);
        }
}

// draw a circle outline
void ST7735_drawCircle(unsigned char x0, unsigned char y0, unsigned char r, unsigned int color) {
        int f = 1 - r;
        int ddF_x = 1;
        int ddF_y = -2 * r;
        int x = 0;
        int y = r;

        ST7735_drawPixel(x0, y0+r, color);
        ST7735_drawPixel(x0, y0-r, color);
        ST7735_drawPixel(x0+r, y0, color);
        ST7735_drawPixel(x0-r, y0, color);

        while (x<y) {
                if (f >= 0) {
                        y--;
                        ddF_y += 2;
                        f += ddF_y;
                }
                x++;
                ddF_x += 2;
                f += ddF_x;

                ST7735_drawPixel(x0 + x, y0 + y, color);
                ST7735_drawPixel(x0 - x, y0 + y, color);
                ST7735_drawPixel(x0 + x, y0 - y, color);
                ST7735_drawPixel(x0 - x, y0 - y, color);

                ST7735_drawPixel(x0 + y, y0 + x, color);
                ST7735_drawPixel(x0 - y, y0 + x, color);
                ST7735_drawPixel(x0 + y, y0 - x, color);
                ST7735_drawPixel(x0 - y, y0 - x, color);

        }
}

unsigned char ST7735_getRotation() 
{
        return madctl;
}

void ST7735_setRotation(unsigned char m)
{
        madctl = m;
        ST7735_WriteCommand(ST7735_MADCTL);  // memory access control (directions)
        ST7735_WriteData(madctl);  // row address/col address, bottom to top refresh
}

// draw a rectangle
void ST7735_drawRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h,
unsigned int color)
{
        // smarter version
        ST7735_drawHorizontalLine(x, y, w, color);
        ST7735_drawHorizontalLine(x, y+h-1, w, color);
        ST7735_drawVerticalLine(x, y, h, color);
        ST7735_drawVerticalLine(x+w-1, y, h, color);
}

void ST7735_fillRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h,
unsigned int color)
 {
        // smarter version

        setAddrWindow(x, y, x+w-1, y+h-1);

        // setup for data
		REG_PORT_OUTSET0 = DC_PIN_MASK;
		REG_PORT_OUTCLR0 = CS_PIN_MASK;
        //ST7735_RS = 1;
       // ST7735_CS = 0;

        colorB = color >> 8;
        for (x=0; x < w; x++) {
                for (y=0; y < h; y++) {
					    spiSend(colorB);
						spiSend(color);
                        //SPI1_Write(colorB);
                        //SPI1_Write(color);
                }
        }

        REG_PORT_OUTSET0 = CS_PIN_MASK;
       //ST7735_CS = 1;
}

void ST7735_drawVerticalLine(unsigned char x, unsigned char y, unsigned char length, unsigned int color)
{
        if (x >= SCREEN_WIDTH) return;
        if (y+length >= SCREEN_HEIGHT) length = SCREEN_HEIGHT-y-1;

        ST7735_drawFastLine(x,y,length,color,1);
}

void ST7735_drawHorizontalLine(unsigned char x, unsigned char y, unsigned char length, unsigned int color)
{
        if (y >= SCREEN_HEIGHT) return;
        if (x+length >= SCREEN_WIDTH) length = SCREEN_WIDTH-x-1;

        ST7735_drawFastLine(x,y,length,color,0);
}

void ST7735_drawFastLine(unsigned char x, unsigned char y, unsigned char length,
unsigned int color, unsigned char rotflag)
{
        if (rotflag) {
                setAddrWindow(x, y, x, y+length);
        } else {
                setAddrWindow(x, y, x+length, y+1);
        }
        // setup for data
		REG_PORT_OUTSET0 = DC_PIN_MASK;
		REG_PORT_OUTCLR0 = CS_PIN_MASK;
        //ST7735_RS = 1;
        //ST7735_CS = 0;

        colorB = color >> 8;
        while (length--) {
			    spiSend(colorB);
				spiSend(color);
                //SPI1_Write(colorB);
                //SPI1_Write(color);
        }
		REG_PORT_OUTSET0 = CS_PIN_MASK;
        //ST7735_CS = 1;
}

int abs(int val)
{
        return (val > 0) ? val : -val;
}

// bresenham's algorithm - thx wikpedia
void ST7735_drawLine(int x0, int y0, int x1, int y1,
unsigned int color) {
        unsigned int steep = abs(y1 - y0) > abs(x1 - x0);
        if (steep) {
                swap(x0, y0);
                swap(x1, y1);
        }

        if (x0 > x1) {
                swap(x0, x1);
                swap(y0, y1);
        }


        dx = x1 - x0;
        dy = abs(y1 - y0);

        err = dx / 2;
        ystep;

        if (y0 < y1) {
                ystep = 1;
        } else {
                ystep = -1;}

        for (; x0<=x1; x0++) {
                if (steep) {
                        ST7735_drawPixel(y0, x0, color);
                } else {
                        ST7735_drawPixel(x0, y0, color);
                }
                err -= dy;
                if (err < 0) {
                        y0 += ystep;
                        err += dx;
                }
        }
}
