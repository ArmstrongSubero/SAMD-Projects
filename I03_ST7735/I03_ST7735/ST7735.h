/*
 * File:   ST7735.h
 * Author: Armstrong Subero
 * Processor: SAMD21G18A @ 48MHz, 3.3v
 * Program: Header file for application
 * Compiler: ARM-GCC (v6.3.1, Atmel Studio 7.0)
 * Program Version 1.0
 * Program Description: This header file provides functions for using 
 *                      the ST7735 Display
 * Modified From: None
 * 
 * Change History:
 *
 * Author             Rev     Date          Description
 * Armstrong Subero   1.0     26/05/2020    Initial Release.
 * 
 * Updated on August 05, 2020, 06:35 PM
 */ 


#ifndef ST7735_H_
#define ST7735_H_

#define F_CPU 48000000UL

#define RESET 0x200      /* PA09 reset */
#define DC    0x100      /* PA08 register select */

// DC IO Pin definition
#define DC_PORT            PORTA
#define DC_PIN_NUMBER      (08ul)
#define DC_PIN_MASK        PORT_PA08

// CS
#define CS_PORT            PORTA
#define CS_PIN_NUMBER      (22ul)
#define CS_PIN_MASK        PORT_PA22

// RST
#define RST_PORT            PORTA
#define RST_PIN_NUMBER      (09ul)
#define RST_PIN_MASK        PORT_PA09


unsigned char colorB;
char madctl;
unsigned int dx, dy;
int err;
int ystep;

#define swap(a, b) { int t = a; a = b; b = t; }

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 160

#define ST7735_NOP 0x0
#define ST7735_SWRESET 0x01
#define ST7735_RDDID 0x04
#define ST7735_RDDST 0x09

#define ST7735_SLPIN  0x10
#define ST7735_SLPOUT  0x11
#define ST7735_PTLON  0x12
#define ST7735_NORON  0x13

#define ST7735_INVOFF 0x20
#define ST7735_INVON 0x21
#define ST7735_DISPOFF 0x28
#define ST7735_DISPON 0x29
#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_RAMRD 0x2E

#define ST7735_COLMOD 0x3A
#define ST7735_MADCTL 0x36


#define ST7735_FRMCTR1 0xB1
#define ST7735_FRMCTR2 0xB2
#define ST7735_FRMCTR3 0xB3
#define ST7735_INVCTR 0xB4
#define ST7735_DISSET5 0xB6

#define ST7735_PWCTR1 0xC0
#define ST7735_PWCTR2 0xC1
#define ST7735_PWCTR3 0xC2
#define ST7735_PWCTR4 0xC3
#define ST7735_PWCTR5 0xC4
#define ST7735_VMCTR1 0xC5

#define ST7735_RDID1 0xDA
#define ST7735_RDID2 0xDB
#define ST7735_RDID3 0xDC
#define ST7735_RDID4 0xDD

#define ST7735_PWCTR6 0xFC

#define ST7735_GMCTRP1 0xE0
#define ST7735_GMCTRN1 0xE1

// macro to convert to RGB888 (24-bit value) to RGB565(12-bit, 4096 color)
#define RGB565(r,g,b) ((((r>>3)<<11) | ((g>>2)<<5) | (b>>3)))

#define colAliceBlue RGB565(240,248,255)
#define colAntiqueWhite RGB565(250,235,215)
#define colAqua RGB565( 0,255,255)
#define colAquamarine RGB565(127,255,212)
#define colAzure RGB565(240,255,255)
#define colBeige RGB565(245,245,220)
#define colBisque RGB565(255,228,196)
#define colBlack RGB565( 0, 0, 0)
#define colBlanchedAlmond RGB565(255,255,205)
#define colBlue RGB565( 0, 0,255)
#define colBlueViolet RGB565(138, 43,226)
#define colBrown RGB565(165, 42, 42)
#define colBurlywood RGB565(222,184,135)
#define colCadetBlue RGB565( 95,158,160)
#define colChartreuse RGB565(127,255, 0)
#define colChocolate RGB565(210,105, 30)
#define colCoral RGB565(255,127, 80)
#define colCornflowerBlue RGB565(100,149,237)
#define colCornsilk RGB565(255,248,220)
#define colCrimson RGB565(220, 20, 60)
#define colCyan RGB565( 0,255,255)
#define colDarkBlue RGB565( 0, 0,139)
#define colDarkCyan RGB565( 0,139,139)
#define colDarkGoldenRod RGB565(184,134, 11)
#define colDarkGray RGB565(169,169,169)
#define colDarkGreen RGB565( 0,100, 0)
#define colDarkKhaki RGB565(189,183,107)
#define colDarkMagenta RGB565(139, 0,139)
#define colDarkOliveGreen RGB565( 85,107, 47)
#define colDarkOrange RGB565(255,140, 0)
#define colDarkOrchid RGB565(153, 50,204)
#define colDarkRed RGB565(139, 0, 0)
#define colDarkSalmon RGB565(233,150,122)
#define colDarkSeaGreen RGB565(143,188,143)
#define colDarkSlateBlue RGB565( 72, 61,139)
#define colDarkSlateGray RGB565( 47, 79, 79)
#define colDarkTurquoise RGB565( 0,206,209)
#define colDarkViolet RGB565(148, 0,211)
#define colDeepPink RGB565(255, 20,147)
#define colDeepSkyBlue RGB565( 0,191,255)
#define colDimGray RGB565(105,105,105)
#define colDodgerBlue RGB565( 30,144,255)
#define colFireBrick RGB565(178, 34, 34)
#define colFloralWhite RGB565(255,250,240)
#define colForestGreen RGB565( 34,139, 34)
#define colFuchsia RGB565(255, 0,255)
#define colGainsboro RGB565(220,220,220)
#define colGhostWhite RGB565(248,248,255)
#define colGold RGB565(255,215, 0)
#define colGoldenRod RGB565(218,165, 32)
#define colGray RGB565(127,127,127)
#define colGreen RGB565( 0,128, 0)
#define colGreenYellow RGB565(173,255, 47)
#define colHoneyDew RGB565(240,255,240)
#define colHotPink RGB565(255,105,180)
#define colIndianRed RGB565(205, 92, 92)
#define colIndigo RGB565( 75, 0,130)
#define colIvory RGB565(255,255,240)
#define colKhaki RGB565(240,230,140)
#define colLavender RGB565(230,230,250)
#define colLavenderBlush RGB565(255,240,245)
#define colLawngreen RGB565(124,252, 0)
#define colLemonChiffon RGB565(255,250,205)
#define colLightBlue RGB565(173,216,230)
#define colLightCoral RGB565(240,128,128)
#define colLightCyan RGB565(224,255,255)
#define colLightGoldenRodYellow RGB565(250,250,210)
#define colLightGreen RGB565(144,238,144)
#define colLightGrey RGB565(211,211,211)
#define colLightPink RGB565(255,182,193)
#define colLightSalmon RGB565(255,160,122)
#define colLightSeaGreen RGB565( 32,178,170)
#define colLightSkyBlue RGB565(135,206,250)
#define colLightSlateGray RGB565(119,136,153)
#define colLightSteelBlue RGB565(176,196,222)
#define colLightYellow RGB565(255,255,224)
#define colLime RGB565( 0,255, 0)
#define colLimeGreen RGB565( 50,205, 50)
#define colLinen RGB565(250,240,230)
#define colMagenta RGB565(255, 0,255)
#define colMaroon RGB565(128, 0, 0)
#define colMediumAquamarine RGB565(102,205,170)
#define colMediumBlue RGB565( 0, 0,205)
#define colMediumOrchid RGB565(186, 85,211)
#define colMediumPurple RGB565(147,112,219)
#define colMediumSeaGreen RGB565( 60,179,113)
#define colMediumSlateBlue RGB565(123,104,238)
#define colMediumSpringGreen RGB565( 0,250,154)
#define colMediumTurquoise RGB565( 72,209,204)
#define colMediumVioletRed RGB565(199, 21,133)
#define colMidnightBlue RGB565( 25, 25,112)
#define colMintCream RGB565(245,255,250)
#define colMistyRose RGB565(255,228,225)
#define colMoccasin RGB565(255,228,181)
#define colNavajoWhite RGB565(255,222,173)
#define colNavy RGB565( 0, 0,128)
#define colNavyblue RGB565(159,175,223)
#define colOldLace RGB565(253,245,230)
#define colOlive RGB565(128,128, 0)
#define colOliveDrab RGB565(107,142, 35)
#define colOrange RGB565(255,165, 0)
#define colOrangeRed RGB565(255, 69, 0)
#define colOrchid RGB565(218,112,214)
#define colPaleGoldenRod RGB565(238,232,170)
#define colPaleGreen RGB565(152,251,152)
#define colPaleTurquoise RGB565(175,238,238)
#define colPaleVioletRed RGB565(219,112,147)
#define colPapayaWhip RGB565(255,239,213)
#define colPeachPuff RGB565(255,218,185)
#define colPeru RGB565(205,133, 63)
#define colPink RGB565(255,192,203)
#define colPlum RGB565(221,160,221)
#define colPowderBlue RGB565(176,224,230)
#define colPurple RGB565(128, 0,128)
#define colRed RGB565(255, 0, 0)
#define colRosyBrown RGB565(188,143,143)
#define colRoyalBlue RGB565( 65,105,225)
#define colSaddleBrown RGB565(139, 69, 19)
#define colSalmon RGB565(250,128,114)
#define colSandyBrown RGB565(244,164, 96)
#define colSeaGreen RGB565( 46,139, 87)
#define colSeaShell RGB565(255,245,238)
#define colSienna RGB565(160, 82, 45)
#define colSilver RGB565(192,192,192)
#define colSkyBlue RGB565(135,206,235)
#define colSlateBlue RGB565(106, 90,205)
#define colSlateGray RGB565(112,128,144)
#define colSnow RGB565(255,250,250)
#define colSpringGreen RGB565( 0,255,127)
#define colSteelBlue RGB565( 70,130,180)
#define colTan RGB565(210,180,140)
#define colTeal RGB565( 0,128,128)
#define colThistle RGB565(216,191,216)
#define colTomato RGB565(255, 99, 71)
#define colTurquoise RGB565( 64,224,208)
#define colViolet RGB565(238,130,238)
#define colWheat RGB565(245,222,179)
#define colWhite RGB565(255,255,255)
#define colWhiteSmoke RGB565(245,245,245)
#define colYellow RGB565(255,255, 0)
#define colYellowGreen RGB565(139,205, 50)

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void ST7735_WriteCommand(int i);
void ST7735_WriteData(int i);
void ST7735_Init(void);
void ST7735_drawPixel(unsigned char x, unsigned char y, unsigned int color) ;
void ST7735_fillScreen(unsigned int color);
void setAddrWindow(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1);
void ST7735_pushColor(unsigned int color);
void ST7735_drawChar(unsigned char x, unsigned char y, char c, unsigned int color, unsigned char size);
void ST7735_drawString(unsigned char x, unsigned char y, char *c, unsigned int color, unsigned char size);
void ST7735_fillCircle(unsigned char x0, unsigned char y0, unsigned char r, unsigned int color);
void ST7735_drawCircle(unsigned char x0, unsigned char y0, unsigned char r, unsigned int color);
void ST7735_setRotation(unsigned char m);
void ST7735_drawRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned int color);
void ST7735_fillRect(unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned int color);
void ST7735_drawVerticalLine(unsigned char x, unsigned char y, unsigned char length, unsigned int color);
void ST7735_drawHorizontalLine(unsigned char x, unsigned char y, unsigned char length, unsigned int color);
void ST7735_drawFastLine(unsigned char x, unsigned char y, unsigned char length, unsigned int color, unsigned char rotflag);
void ST7735_drawLine(int x0, int y0, int x1, int y1, unsigned int color);
void ST7735_writeInteger(int x, int y, int v, unsigned int colour, int size);
void ST7735_test();


#endif /* ST7735_H_ */