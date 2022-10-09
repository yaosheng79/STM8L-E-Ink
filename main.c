#include "stm8l15x.h"
#include "stdio.h"
#include "EPD_213.h"

const uint8_t IMAGE_DATA[] = {
/* 0X00,0X01,0X80,0X00,0XFA,0X00, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X38,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X0F,0X00,0X00,0X78,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0X80,0X00,0XF8,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,0XC0,0X03,0XF8,0X00,0X00,0X00,
0X00,0X00,0X00,0X01,0X00,0X00,0X00,0X00,0X01,0XFF,0XE0,0X1F,0XF8,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0XC0,0X00,0X00,0X00,0X03,0XFF,0X70,0X1F,0XF0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X7E,0X00,0X00,0X00,0X03,0XFF,0X78,0X38,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X3F,0X00,0X00,0X00,0X03,0XFF,0XF8,0XF0,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X0F,0XC0,0X00,0X00,0X03,0XF0,0XF8,0XC1,0XF8,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X03,0XF0,0X00,0X00,0X03,0XF3,0XF3,0X8F,0XFE,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X01,0XF8,0X00,0X00,0X03,0XFF,0XF3,0XBF,0XFF,0XC0,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X3E,0X00,0X00,0X03,0XFF,0XFA,0X7F,0XFF,0XF0,0X00,0X00,
0X00,0X0F,0X00,0X00,0X00,0X3F,0XE0,0X00,0X00,0XE7,0XFB,0XFF,0XFF,0XF0,0X00,0X00,
0X00,0X07,0X00,0X00,0X00,0X3F,0XF0,0X00,0X00,0XE7,0XFB,0XFF,0XFF,0XE0,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X1F,0XFC,0X00,0X00,0XFF,0XFB,0XFF,0XFF,0XE0,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X0F,0XFE,0X00,0X00,0X7F,0XFB,0XCF,0XFF,0XE0,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X03,0XFE,0X00,0X00,0X3F,0XF9,0XCF,0XFF,0XE0,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X01,0XFF,0X80,0X00,0X0F,0XF1,0XFF,0XFF,0XE0,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0XFF,0XC0,0X00,0X00,0X3D,0XEF,0XFF,0XE0,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X7F,0XE0,0X00,0X03,0XFF,0XF7,0XFF,0XC0,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X3F,0XE0,0X00,0X3F,0XFF,0XFF,0XFF,0X80,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X1F,0XE0,0X00,0X7E,0XFF,0XFF,0XFF,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X0F,0XE0,0X00,0X3E,0XFF,0XF1,0XFF,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X0F,0XE0,0X00,0X3F,0XFF,0XBF,0XFC,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X07,0XF0,0X00,0X3E,0X7F,0X3F,0XF8,0X38,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X07,0XF0,0X00,0X7E,0X7F,0XC0,0X00,0X7C,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X07,0XF0,0X00,0X7E,0X3F,0XC0,0X01,0XFE,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X07,0XF0,0X00,0X7F,0X1F,0XDF,0XFF,0XFF,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X03,0XF0,0X00,0X7F,0X87,0XEF,0XFF,0XFF,0X80,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X03,0XF0,0X00,0X7F,0XE3,0XF1,0XFF,0XFF,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X03,0XF0,0X01,0X87,0XFC,0X78,0XFE,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X03,0XF0,0X03,0X01,0XF8,0XFF,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X03,0XF0,0X0E,0X00,0X01,0XFF,0X80,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X03,0XF0,0X0C,0X00,0X03,0XFF,0X80,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X03,0XF0,0X1C,0X00,0X0F,0X98,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X03,0XF0,0X38,0X00,0X7F,0X9C,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X00,0X00,0X03,0XF0,0X30,0X00,0X3F,0XDC,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X07,0XFE,0X07,0XE0,0X30,0X00,0X1F,0XFE,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X0F,0XFF,0X87,0XF0,0X70,0X00,0X1F,0XFC,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X1F,0XFF,0XC7,0XF0,0X00,0X00,0X0F,0XFE,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X3F,0XFF,0XE7,0XE0,0X00,0X00,0X0F,0XF0,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X7F,0XFF,0XF3,0XE0,0X7F,0XFF,0XEF,0XE0,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0XFF,0X9F,0XFB,0XCF,0XFF,0XFF,0XC6,0X18,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X03,0XFF,0XCF,0XF9,0XDF,0XFF,0XFF,0XC0,0X08,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X0E,0XFF,0XDF,0XFD,0XFF,0XFF,0XFE,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0X01,0XF0,0XFF,0XFF,0XFD,0XFF,0XFE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0X03,0XF8,0XFF,0XFF,0XFD,0XFF,0XFC,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0X07,0XFC,0XFF,0XDF,0XFD,0XFF,0XF8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0X0F,0XFE,0XC7,0XDF,0XFD,0XFF,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0X3E,0X7F,0XF7,0XDF,0XFF,0XFE,0X30,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0X3E,0X7F,0XF7,0XDF,0XCF,0XF0,0X38,0X00,0X06,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0X7E,0X7F,0XFF,0XFF,0X9F,0XE0,0X38,0X00,0X1F,0XC0,0X00,0X00,0X00,0X00,
0X00,0X03,0X7F,0X1F,0XFF,0XFE,0X3E,0X00,0X3C,0X00,0X3B,0XE0,0X00,0X00,0X00,0X00,
0X00,0X03,0X7F,0X8F,0XFF,0XFE,0X7C,0X00,0X3C,0X00,0X3B,0XE0,0X00,0X00,0X00,0X00,
0X00,0X03,0X7F,0X87,0XFE,0X3F,0XF8,0X00,0X3C,0X00,0X7F,0XF0,0X00,0X00,0X00,0X00,
0X00,0X03,0X7F,0XA1,0XF8,0X1F,0XFC,0X00,0X1C,0X00,0X7C,0XF0,0X00,0X00,0X00,0X00,
0X00,0X03,0X3F,0XFF,0XF0,0X0F,0XFC,0X00,0X0C,0X00,0X7E,0X7C,0X00,0X00,0X00,0X00,
0X00,0X03,0X3F,0XFF,0XF0,0X0F,0XFE,0X00,0X0C,0X00,0X7F,0X3C,0X00,0X00,0X00,0X00,
0X00,0X03,0X1F,0XFF,0XF0,0X0F,0XFF,0X00,0X0C,0X00,0X3F,0X80,0X00,0X00,0X00,0X00,
0X00,0X03,0X0F,0XFF,0XF0,0X0E,0X7F,0X80,0X0C,0X00,0X3F,0XC0,0X00,0X00,0X00,0X00,
0X00,0X03,0X07,0XFF,0XF8,0X0E,0X3F,0XC0,0X0C,0X00,0X1F,0XF0,0X00,0X00,0X00,0X00,
0X00,0X03,0X03,0XFF,0XF8,0X1E,0X1F,0XE0,0X0C,0X00,0X0F,0XF0,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X3F,0XFE,0X3F,0X87,0XE0,0X3C,0X00,0X0F,0XBE,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X47,0XFF,0XFF,0XF0,0X60,0X3C,0X00,0X0F,0XBF,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X31,0XFF,0XFF,0XF8,0XE0,0X38,0X00,0X0F,0XBF,0X80,0X00,0X00,0X00,
0X00,0X03,0X06,0X11,0XFF,0XFD,0XFF,0XE0,0X38,0X00,0X0F,0X1F,0X80,0X00,0X00,0X00,
0X00,0X03,0X0E,0X13,0XFF,0XF9,0XFF,0XE0,0X30,0X00,0X0E,0X07,0X80,0X00,0X00,0X00,
0X00,0X03,0X3C,0XD7,0XFD,0XFD,0XFF,0XE0,0X30,0X00,0X1C,0XC7,0X80,0X00,0X00,0X00,
0X00,0X03,0X39,0XEF,0XFB,0XFF,0XFF,0XE0,0X30,0X00,0X3D,0XFF,0X80,0X00,0X00,0X00,
0X00,0X03,0X73,0XEF,0XFB,0XFF,0XFF,0XE0,0X60,0X00,0X3D,0XFF,0X80,0X00,0X00,0X00,
0X00,0X03,0X67,0XEF,0XFB,0XFF,0XFF,0XC0,0XC0,0X00,0X3F,0XFF,0X80,0X00,0X00,0X00,
0X00,0X03,0X8F,0XF7,0XE3,0XFF,0XFF,0X80,0XE0,0X00,0X1B,0XFF,0X80,0X00,0X00,0X00,
0X00,0X03,0X9F,0XF3,0XE1,0XFF,0XE0,0X01,0XC0,0X00,0X3B,0XFF,0XC0,0X00,0X00,0X00,
0X00,0X03,0X3F,0XF1,0XF9,0XFF,0XC0,0X03,0X80,0X00,0X7F,0XFF,0XE0,0X00,0X00,0X00,
0X00,0X03,0X7F,0XF1,0XFD,0XFF,0X80,0X07,0X00,0X00,0X1F,0XFF,0XF8,0X00,0X00,0X00,
0X00,0X03,0XFF,0XF1,0XFF,0XFF,0X80,0X0F,0X00,0X00,0X3F,0XFF,0XFC,0X00,0X00,0X00,
0X00,0X03,0XFF,0XE0,0XFF,0XFF,0X00,0X0E,0X00,0X00,0X3F,0XFF,0X9C,0X00,0X00,0X00,
0X00,0X03,0XFF,0X80,0X0F,0XFF,0X00,0X06,0X00,0X00,0X03,0XF6,0X7C,0X00,0X00,0X00,
0X00,0X03,0XFF,0X00,0X1F,0X7C,0X00,0XF8,0X00,0X00,0X09,0XF0,0X3C,0X00,0X00,0X00,
0X00,0X03,0XFE,0X00,0X3F,0X38,0X01,0XFC,0X00,0X00,0X1C,0XF8,0X1C,0X00,0X00,0X00,
0X00,0X03,0XFC,0X00,0XFF,0X90,0X03,0XFE,0X00,0X00,0X3D,0XFF,0X9C,0X00,0X00,0X00,
0X00,0X03,0XF8,0X00,0XFF,0XC0,0X0F,0XFF,0X00,0X00,0X73,0XFF,0XCC,0X00,0X00,0X00,
0X00,0X03,0XF0,0X00,0XFF,0XE0,0X0F,0XFF,0X00,0X00,0X61,0XFF,0XFC,0X60,0X00,0X00,
0X00,0X03,0XF0,0X01,0XFF,0XF0,0X1F,0XFF,0X00,0X00,0XC0,0XFF,0XFF,0XF0,0X00,0X00,
0X00,0X07,0XE0,0X01,0XFF,0XBF,0XFF,0XFF,0X80,0X00,0XE0,0X00,0X7F,0XF0,0X00,0X00,
0X00,0X03,0XC0,0X01,0XFF,0X3F,0XFF,0XFF,0X80,0X00,0XC0,0X00,0X3F,0XF8,0X00,0X00,
0X00,0X01,0X80,0X01,0XFE,0X7F,0XFF,0XFF,0X80,0X00,0X80,0X00,0X1F,0XFC,0X00,0X00,
0X00,0X07,0X00,0X00,0XFE,0X7F,0XFF,0XFF,0X80,0X00,0X80,0X00,0X0C,0XFC,0X00,0X00,
0X00,0X03,0X00,0X00,0XF0,0X7F,0XFF,0XFF,0X00,0X00,0X80,0X00,0X04,0X7C,0X00,0X00,
0X00,0X03,0X00,0X00,0X7E,0X3F,0XFF,0XFC,0X00,0X01,0X80,0X00,0X03,0XFC,0X00,0X00,
0X00,0X03,0X00,0X00,0X7E,0X3F,0XFF,0XFE,0X00,0X01,0X80,0X00,0X01,0XF0,0X00,0X00,
0X00,0X03,0X00,0X00,0X3F,0XDF,0XBF,0XFF,0X80,0X01,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X3F,0XCF,0XBF,0XFF,0XC0,0X01,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0X7F,0XCF,0XFF,0XFF,0XE0,0X01,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X00,0XFF,0XCF,0XCF,0XFF,0XC0,0X01,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0X00,0X1E,0XFF,0XEF,0XC7,0XFF,0XC0,0X01,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0X01,0XFC,0XFF,0XE7,0XF0,0X7F,0X80,0X03,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X07,0X07,0XC0,0XFF,0XF3,0XF8,0XFF,0X00,0X0F,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X03,0X0F,0X80,0X7F,0XF3,0XF9,0XFE,0X00,0X0E,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X1F,0X00,0X3F,0XF3,0XFB,0XFE,0X00,0X0C,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X38,0X00,0X03,0XF9,0XFB,0XF3,0XE0,0X18,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0XF0,0X00,0X3C,0XF9,0XFB,0XEF,0XF0,0X30,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0XC0,0X00,0X7D,0XF9,0XFB,0XCF,0XF0,0X70,0X00,0X00,0X18,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0XFF,0XF8,0XFB,0XCF,0XFC,0XC0,0X00,0X03,0XF8,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0XFF,0XFC,0XFB,0XFF,0XFC,0X00,0X00,0X07,0XF8,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0XFF,0XDE,0XFB,0XFF,0X7C,0X00,0X00,0X3F,0XFC,0X00,0X00,0X00,
0X00,0X01,0X00,0X00,0XFF,0XDE,0XF3,0XFF,0X3C,0X00,0X00,0X7F,0XFE,0X00,0X00,0X00,
0X00,0X01,0X00,0X00,0XFF,0XC2,0XF3,0XFF,0X1C,0X00,0X00,0XFF,0XFE,0X00,0X00,0X00,
0X00,0X01,0X00,0X00,0XFB,0XE3,0XFF,0XFF,0X3C,0X00,0X00,0XFF,0XFF,0X00,0X00,0X00,
0X00,0X01,0X00,0X00,0XF9,0XEF,0XFF,0XFE,0X3C,0X00,0X00,0XFF,0XFF,0X00,0X00,0X00,
0X00,0X01,0X00,0X00,0XFC,0XFF,0XFF,0XF9,0XFC,0X00,0X00,0XDC,0X7F,0X00,0X00,0X00,
0X00,0X01,0X00,0X01,0XFE,0X7F,0XFF,0XE3,0XFE,0X00,0X00,0XFF,0XBF,0X00,0X00,0X00,
0X00,0X01,0X00,0X01,0XFE,0X3F,0XFF,0XC7,0XFE,0X00,0X00,0XFF,0X9F,0X00,0X00,0X00,
0X00,0X01,0X00,0X03,0XFF,0X3F,0XFF,0XCF,0XFF,0X00,0X00,0XFF,0XBF,0X00,0X00,0X00,
0X00,0X01,0X00,0XFF,0XFF,0XCF,0XFF,0XFF,0XFF,0X80,0X00,0XFF,0XFE,0X00,0X00,0X00,
0X00,0X01,0X0F,0XE0,0X7F,0XFF,0X87,0XFF,0XFF,0X80,0X00,0XFF,0XC0,0X00,0X00,0X00,
0X00,0X01,0X1F,0X80,0X3F,0XFF,0X03,0XFF,0XCE,0X00,0X00,0XFF,0X00,0X00,0X00,0X00,
0X00,0X01,0XF0,0X00,0X0F,0XFE,0X01,0XFC,0X1E,0X00,0X00,0XF0,0X00,0X00,0X00,0X00,
0X00,0X01,0XE0,0X7F,0XC7,0XFC,0X01,0XFC,0X3E,0X00,0X00,0XC1,0XFF,0XE0,0X00,0X00,
0X00,0X01,0XC1,0XFF,0XF7,0XF8,0X01,0XFF,0XFC,0X00,0X01,0X8D,0XFF,0XF0,0X00,0X00,
0X00,0X01,0X87,0XFF,0XFB,0XFC,0X01,0XFF,0XF8,0X00,0X0F,0X1E,0XFF,0XF8,0X00,0X00,
0X00,0X01,0X3F,0X80,0X03,0XFC,0X01,0XFF,0XF0,0X00,0X0E,0X7E,0X7F,0XFE,0X00,0X00,
0X00,0X01,0XF8,0X00,0X07,0XFE,0X01,0XFF,0XE2,0X00,0X1E,0X7F,0X3F,0XFC,0X00,0X00,
0X00,0X01,0XE0,0XFF,0X9F,0XDF,0X03,0XFF,0XC6,0X60,0X1C,0XFF,0X8F,0XFE,0X00,0X00,
0X00,0X01,0X8F,0XC0,0XFF,0X3F,0XC7,0XEF,0XE3,0X78,0X3E,0X1F,0XCF,0XFF,0X00,0X00,
0X00,0X01,0XDF,0X80,0XFE,0X7F,0XEF,0XE7,0XF1,0XBC,0X7F,0X0F,0XCF,0XFF,0XC0,0X00,
0X00,0X01,0XFC,0X00,0XFD,0XFF,0XFF,0XE3,0XF1,0X9E,0X3F,0XC3,0XE7,0XFF,0X00,0X00,
0X00,0X01,0XF8,0X01,0XF1,0XF9,0XFF,0XF1,0XFD,0XCF,0X9F,0XE1,0XFF,0XFF,0X00,0X00,
0X00,0X01,0X80,0X01,0XF3,0XF1,0XFF,0XF9,0XFD,0XC1,0X9F,0XF8,0XFF,0XE0,0X00,0X00,
0X00,0X01,0X00,0X01,0XFF,0XE3,0XFD,0XFE,0XFF,0XC0,0X3F,0XF0,0X00,0X03,0X80,0X00,
0X00,0X01,0X00,0X00,0XFF,0XE3,0XFD,0XFF,0X7F,0XC0,0X7F,0XC0,0X00,0X07,0X80,0X00,
0X00,0X01,0X00,0X00,0XFF,0XE7,0XFC,0XFF,0X07,0X80,0XFF,0XCF,0XFF,0XFF,0X00,0X00,
0X00,0X01,0X00,0X00,0XFF,0XEF,0XCE,0X7F,0X07,0X00,0X7E,0X7F,0XFF,0XFE,0X00,0X00,
0X00,0X01,0X1F,0XFE,0XFF,0XFF,0XCE,0X7F,0X3E,0X00,0X3E,0X7F,0XFF,0XFC,0X00,0X00,
0X00,0X01,0XFF,0XFF,0XFF,0XF1,0XCE,0X3F,0X3E,0X00,0X3F,0XFC,0X07,0XF8,0X00,0X00,
0X00,0X01,0XFF,0XFF,0X3F,0XE1,0X8E,0X3F,0X3E,0X00,0X1F,0XFC,0X07,0XF0,0X00,0X00,
0X00,0X01,0XE0,0X00,0X0E,0X03,0X8E,0X3F,0X3E,0X00,0X0F,0XFF,0XF8,0X00,0X00,0X00,
0X00,0X01,0XFF,0XFF,0X87,0XFF,0X8E,0X3F,0X1E,0X00,0X04,0XFE,0X3E,0X00,0X00,0X00,
0X00,0X01,0XFF,0XFF,0XC7,0XFF,0X8F,0X3F,0XBE,0X00,0X00,0XFE,0X1E,0X00,0X00,0X00,
0X00,0X01,0XFF,0XFF,0XC7,0XFF,0X8F,0X9F,0XFE,0X00,0X00,0XFC,0X3F,0X80,0X00,0X00,
0X00,0X01,0X87,0XFF,0X8F,0XFF,0X8F,0X9F,0XFE,0X00,0X00,0X79,0XFF,0XC0,0X00,0X00,
0X00,0X01,0X00,0X06,0X3F,0XFF,0X8F,0XDF,0XFE,0X00,0X00,0X7F,0XFF,0XC0,0X00,0X00,
0X00,0X01,0X00,0X00,0X7F,0XFF,0X8F,0X8F,0XFC,0X00,0X00,0X1F,0XFF,0XE0,0X00,0X00,
0X00,0X01,0X80,0X00,0XFF,0XFF,0X8F,0X1F,0X00,0X00,0X00,0X0F,0XFF,0XF0,0X00,0X00,
0X00,0X01,0XC0,0X01,0XFF,0XFF,0X8E,0X3F,0X81,0X00,0X00,0X01,0XFF,0XE0,0X00,0X00,
0X00,0X01,0XE0,0X01,0XFF,0XFF,0X8E,0X7F,0XC3,0X80,0X00,0X00,0XFF,0X80,0X00,0X00,
0X00,0X01,0XF8,0X00,0XFF,0XF3,0X8E,0X7F,0XE7,0XC0,0X00,0X00,0X7F,0X00,0X00,0X00,
0X00,0X01,0XFF,0X80,0XFF,0XE7,0X8F,0XFF,0XC4,0XE0,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X87,0XE1,0XFF,0XDF,0X8F,0XFF,0XCE,0X1C,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0XF1,0XF8,0XFF,0XFF,0X8F,0XFF,0XCF,0XCF,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0XFE,0X1C,0XFF,0XBE,0X43,0XE0,0X1F,0XF3,0X80,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0XFF,0X06,0X7F,0X3E,0X63,0XC1,0X3F,0XF1,0XE0,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0XFF,0X83,0X3E,0X3C,0XF3,0X81,0X1F,0XF8,0XF0,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0XFF,0XE1,0X80,0X39,0XFF,0X00,0X07,0XFE,0X78,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0XFF,0XFE,0X60,0X1F,0XFE,0X1C,0X03,0XFF,0X1C,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X0F,0XFF,0X3C,0X1F,0XFE,0X60,0X01,0XFF,0X8E,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X01,0XFF,0X9E,0X0F,0XFF,0XC0,0X00,0X3F,0XC3,0X00,0X00,0X00,0X00,0X00,
0X00,0X01,0X00,0X7F,0XC3,0X8F,0XFD,0X80,0X00,0X3F,0XE3,0X80,0X00,0X00,0X00,0X00,
0X00,0X01,0X00,0X3F,0XE1,0XC7,0XFC,0X00,0X00,0X3F,0XF1,0XC0,0X00,0X00,0X00,0X00,
0X00,0X01,0X00,0X1F,0XF1,0XE3,0XF8,0X00,0X00,0X07,0XF0,0X60,0X00,0X00,0X00,0X00,
0X00,0X01,0X80,0X0F,0XF1,0XE1,0XF0,0X00,0X00,0X03,0XF8,0X30,0X00,0X00,0X00,0X00,
0X00,0X01,0X80,0X01,0XF8,0X30,0X00,0X00,0X00,0X01,0XFC,0X3C,0X00,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0XF8,0X18,0X00,0X00,0X00,0X00,0XFC,0X0E,0X00,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0XFC,0X0C,0X00,0X00,0X00,0X00,0XFE,0X0F,0X00,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X7C,0X0C,0X00,0X00,0X00,0X00,0X7E,0X07,0X80,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X7C,0X06,0X00,0X00,0X00,0X00,0X3F,0X03,0X80,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X7E,0X06,0X00,0X00,0X00,0X00,0X1F,0X81,0X80,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X1E,0X03,0X00,0X00,0X00,0X00,0X0F,0X80,0XC0,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X0E,0X01,0X00,0X00,0X00,0X00,0X07,0X80,0X60,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X0F,0X01,0X80,0X00,0X00,0X00,0X03,0XC0,0X30,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X07,0X81,0XC0,0X00,0X00,0X00,0X01,0XC0,0X38,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X07,0X81,0XC0,0X00,0X00,0X00,0X00,0XC0,0X18,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X07,0XC0,0XE0,0X00,0X00,0X00,0X00,0X40,0X08,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X03,0XC0,0XF0,0X00,0X00,0X00,0X00,0X00,0X04,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X03,0XC0,0X70,0X00,0X00,0X00,0X00,0X00,0X06,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X01,0XC0,0X70,0X00,0XF8,0X00,0X00,0X00,0X02,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X03,0XC0,0X30,0X00,0XFF,0XF0,0X00,0X00,0X07,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X03,0XC0,0X30,0X01,0XFF,0XF8,0X00,0X00,0X03,0X80,0X00,0X00,
0X00,0X01,0X80,0X00,0X01,0XC0,0X30,0X01,0XFF,0XFC,0X00,0X00,0X03,0X80,0X00,0X00,
0X00,0X01,0X80,0X00,0X01,0XC0,0X18,0X01,0XFF,0XFE,0X00,0X00,0X03,0X80,0X00,0X00,
0X00,0X01,0X80,0X00,0X01,0XC0,0X08,0X00,0XFF,0XFF,0X00,0X00,0X01,0XC0,0X00,0X00,
0X00,0X01,0X80,0X00,0X01,0XC0,0X08,0X00,0X67,0XFF,0X00,0X00,0X01,0XC0,0X00,0X00,
0X00,0X01,0X80,0X00,0X01,0XC0,0X08,0X00,0XFF,0XFF,0X00,0X00,0X00,0XC0,0X00,0X00,
0X00,0X01,0X80,0X00,0X01,0X80,0X08,0X03,0XFF,0XBF,0X80,0X00,0X00,0X40,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X07,0XFF,0X3F,0X80,0X00,0X00,0X40,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X03,0XFF,0XBF,0XC0,0X00,0X00,0X40,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X03,0XFF,0X3F,0XC0,0X00,0X00,0X40,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X03,0XF0,0X1F,0XC0,0X00,0X00,0X40,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X03,0XFF,0XCF,0XF0,0X00,0X00,0X40,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X01,0XFF,0XE7,0XFC,0X00,0X00,0XC0,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X01,0XFF,0XF3,0XFF,0XF0,0X01,0XC0,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X01,0XFF,0XF8,0XFF,0XF8,0X01,0X80,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X00,0X7F,0XFC,0X7F,0XFF,0X03,0X80,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X00,0X1F,0XFF,0X00,0X7F,0X83,0X80,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X00,0X3F,0XFF,0X80,0X1F,0XC7,0X80,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X00,0X3F,0XFF,0XFF,0XFF,0XC3,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X00,0X3F,0XFF,0XFF,0XFF,0XC4,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X00,0X3F,0XFF,0XFF,0XFF,0XC4,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X18,0X00,0X1F,0XFF,0XFF,0XFF,0XC4,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X38,0X00,0X0F,0XFF,0XFF,0XFF,0XC0,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X78,0X00,0X03,0XFF,0XFF,0XFF,0XC0,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0XF8,0X00,0X00,0X7F,0XFF,0XFF,0XFC,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X01,0XF8,0X00,0X00,0X3F,0XFF,0XFF,0XFC,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X38,0X00,0X00,0X3F,0XFF,0XF9,0XFC,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X18,0X00,0X00,0X3F,0XFF,0XF3,0XFC,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X00,0X00,0X3F,0XFF,0XE7,0XFC,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X08,0X00,0X00,0X3C,0XFC,0X1F,0XF8,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X00,0X8C,0X00,0X00,0X7E,0X00,0X7F,0X98,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0X79,0X8C,0X00,0X07,0XFF,0X0F,0XFF,0X9C,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X00,0XFC,0XC6,0X00,0X0F,0XFF,0X7F,0XFF,0X78,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X01,0XF8,0X46,0X00,0X0F,0XFF,0X7F,0XFE,0X78,0X00,0X00,0X00,
0X00,0X01,0X80,0X00,0X03,0XFC,0X07,0X00,0X0F,0XFF,0X7F,0XFE,0X78,0X00,0X00,0X00,
0X00,0X00,0X80,0X00,0X07,0XFE,0X07,0XC0,0X0F,0XFF,0X7F,0XFE,0X60,0X00,0X00,0X00,
0X00,0X00,0X80,0X00,0X07,0XF9,0XE7,0XE0,0X07,0XFF,0X7F,0XF8,0XC0,0X00,0X00,0X00,
0X00,0X00,0X80,0X00,0X03,0XE3,0XF3,0XF0,0X03,0XFF,0XFF,0XF1,0XC0,0X00,0X00,0X00,
0X00,0X00,0X80,0X00,0X7F,0XC3,0XF3,0X38,0X01,0XFF,0XFF,0XF1,0X80,0X00,0X00,0X00,
0X00,0X00,0X80,0X00,0XFF,0XDF,0XF3,0X1C,0X00,0X7F,0XFF,0XE3,0X80,0X00,0X00,0X00,
0X00,0X00,0X80,0X00,0XFF,0X9F,0XF3,0X8E,0X00,0X3F,0XFF,0XE7,0X80,0X00,0X00,0X00,
0X00,0X00,0X80,0X00,0XFE,0X33,0XFB,0XCF,0X00,0X1F,0XFF,0XCF,0X00,0X00,0X00,0X00,
0X00,0X00,0X80,0X01,0XFE,0X3F,0XF1,0XCF,0X00,0X0F,0XFF,0XCF,0X00,0X00,0X00,0X00,
0X00,0X00,0X80,0X00,0X0C,0X7F,0XCD,0XE3,0X80,0X0F,0XFF,0XDF,0X00,0X00,0X00,0X00,
0X00,0X00,0X80,0X01,0X01,0XFC,0X8E,0X7F,0X80,0X0F,0XFF,0X9F,0X00,0X00,0X00,0X00,
0X00,0X00,0X80,0X0F,0XF9,0XFC,0X1E,0X3F,0X80,0X0F,0XF3,0XBF,0X00,0X00,0X00,0X00,
0X00,0X00,0X80,0X0F,0XFD,0XFC,0X3E,0X3F,0X80,0X0F,0XE1,0XBF,0X00,0X00,0X00,0X00,
0X00,0X00,0X80,0X0F,0XFC,0XFC,0X3F,0X3F,0X80,0X0F,0XC1,0X3F,0X00,0X00,0X00,0X00,
0X00,0X00,0X80,0X1F,0XE5,0XF8,0X3B,0X9F,0X80,0X0F,0XC2,0X3F,0X80,0X00,0X00,0X00,
0X00,0X00,0X80,0X1F,0XCF,0XF0,0X33,0XDF,0XC0,0X03,0X9C,0X0F,0X80,0X00,0X00,0X00,
0X00,0X00,0X80,0X00,0X0E,0X00,0X39,0XD9,0XC0,0X00,0X38,0X63,0XC0,0X00,0X00,0X00,
0X00,0X00,0X80,0X0F,0XFE,0X00,0X0F,0XEE,0XF0,0X00,0XFF,0XF3,0XF0,0X00,0X00,0X00,
0X00,0X00,0X80,0X1F,0XFE,0X00,0X07,0XEE,0X78,0X01,0XFF,0XFF,0XF0,0X00,0X00,0X00,
0X00,0X00,0X00,0X1F,0XFE,0X00,0X07,0XEE,0X3C,0X01,0XFF,0XFF,0XF0,0X00,0X00,0X00,
0X00,0X00,0X00,0X1F,0XFE,0X00,0X07,0XEF,0X3C,0X01,0XFF,0XFF,0XF0,0X00,0X00,0X00,
0X00,0X00,0X00,0X1F,0X7C,0X00,0X00,0XEF,0XFC,0X01,0XFF,0XFF,0XF0,0X00,0X00,0X00,
0X00,0X00,0X00,0X1E,0X1C,0X00,0X00,0X6F,0XFC,0X01,0XFF,0XFF,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X33,0XFE,0X00,0XFF,0XFF,0XC0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XFE,0X00,0XFF,0XFF,0X80,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0XFE,0X00,0X3F,0XFF,0X80,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X07,0XFE,0X00,0X1F,0XFF,0X80,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XFC,0X00,0X03,0XFF,0X80,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XFE,0X00,0X03,0XFF,0X80,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X7E,0X00,0X03,0XFF,0X80,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X03,0XFF,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X01,0XFE,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X78,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X30,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

#ifdef _RAISONANCE_
#define PUTCHAR_PROTOTYPE int putchar (char c)
#define GETCHAR_PROTOTYPE int getchar (void)
#elif defined (_COSMIC_)
#define PUTCHAR_PROTOTYPE char putchar (char c)
#define GETCHAR_PROTOTYPE char getchar (void)
#else /* _IAR_ */
#define PUTCHAR_PROTOTYPE int putchar (int c)
#define GETCHAR_PROTOTYPE int getchar (void)
#endif /* _RAISONANCE_ */

#define LED_GPIO_PORT  GPIOG
#define LED_GPIO_PINS  GPIO_Pin_2

void Delay(__IO uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

// set PG2 to H to turn off U3, shut down Display and Flash
@inline void Power_Off(void)
{
	GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PINS);
}

@inline void Power_On(void)
{
	GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PINS);
}

void uart_init(void)
{
  /* Enable usart clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_USART3, ENABLE);
  /*TXD PG1*/
  GPIO_Init(GPIOG, GPIO_Pin_1, GPIO_Mode_Out_PP_High_Fast);
  /*RXD PG0*/
  GPIO_Init(GPIOG, GPIO_Pin_0, GPIO_Mode_In_PU_No_IT);
  /* Reset */
  USART_DeInit(USART3);

  /* 115200 N 8 1 */
  USART_Init(USART3, 115200, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, 
             (USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));

  USART_SendData8(USART3, '\r');
  while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
}

void main(void)
{
  /* Initialize LEDs mounted on STM8L152X-EVAL board */
  GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Fast);

  /*High speed internal clock prescaler: 1*/
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);

  /* EVAL COM (USARTx) configuration -----------------------------------------*/
  /* USART configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Receive and transmit enabled
        - USART Clock disabled
  */
  uart_init();

  /* Output a message on Hyperterminal using printf function */
  printf("\n\rSTARTED\n\r");

  Power_On();
  Epd_Init(EPD_FULL);
	//Epd_Clear();
  Epd_Display(IMAGE_DATA);
	//Delay(0xFFFF);
  Epd_Sleep();
  Power_Off();
  while (1)
  {
		printf("Hello!\r\n");
		Delay(0xFFFF);
  }
}

/**
  * @brief Retargets the C library printf function to the USART.
  * @param[in] c Character to send
  * @retval char Character sent
  * @par Required preconditions:
  * - None
  */
PUTCHAR_PROTOTYPE
{
  /* Write a character to the USART */
  USART_SendData8(USART3, c);
  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);

  return (c);
}
/**
  * @brief Retargets the C library scanf function to the USART.
  * @param[in] None
  * @retval char Character to Read
  * @par Required preconditions:
  * - None
  */
GETCHAR_PROTOTYPE
{
  int c = 0;
  /* Loop until the Read data register flag is SET */
  while (USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
	c = USART_ReceiveData8(USART3);
	return (c);
}


#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {}
}

#endif
