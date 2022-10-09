#include "EPD_213.h"

#define EPD_RST_HIGH    GPIO_SetBits(GPIOC, GPIO_Pin_4)
#define EPD_RST_LOW    GPIO_ResetBits(GPIOC, GPIO_Pin_4)

#define READ_BUSY  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3)

#define EPD_DC_HIGH    GPIO_SetBits(GPIOC, GPIO_Pin_7)
#define EPD_DC_LOW    GPIO_ResetBits(GPIOC, GPIO_Pin_7)

#define SPI_CS_HIGH    GPIO_SetBits(GPIOE, GPIO_Pin_6)
#define SPI_CS_LOW    GPIO_ResetBits(GPIOE, GPIO_Pin_6)

#define SPI_SCK_HIGH    GPIO_SetBits(GPIOE, GPIO_Pin_7)
#define SPI_SCK_LOW    GPIO_ResetBits(GPIOE, GPIO_Pin_7)

#define SPI_MOSI_HIGH    GPIO_SetBits(GPIOD, GPIO_Pin_4)
#define SPI_MOSI_LOW    GPIO_ResetBits(GPIOD, GPIO_Pin_4)

const uint8_t lut_full_update[]= {
    0x80,0x60,0x40,0x00,0x00,0x00,0x00,             //LUT0: BB:     VS 0 ~7
    0x10,0x60,0x20,0x00,0x00,0x00,0x00,             //LUT1: BW:     VS 0 ~7
    0x80,0x60,0x40,0x00,0x00,0x00,0x00,             //LUT2: WB:     VS 0 ~7
    0x10,0x60,0x20,0x00,0x00,0x00,0x00,             //LUT3: WW:     VS 0 ~7
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT4: VCOM:   VS 0 ~7

    0x03,0x03,0x00,0x00,0x02,                       // TP0 A~D RP0
    0x09,0x09,0x00,0x00,0x02,                       // TP1 A~D RP1
    0x03,0x03,0x00,0x00,0x02,                       // TP2 A~D RP2
    0x00,0x00,0x00,0x00,0x00,                       // TP3 A~D RP3
    0x00,0x00,0x00,0x00,0x00,                       // TP4 A~D RP4
    0x00,0x00,0x00,0x00,0x00,                       // TP5 A~D RP5
    0x00,0x00,0x00,0x00,0x00,                       // TP6 A~D RP6

    0x15,0x41,0xA8,0x32,0x30,0x0A,
};

const uint8_t lut_partial_update[]= { //20 bytes
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT0: BB:     VS 0 ~7
    0x80,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT1: BW:     VS 0 ~7
    0x40,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT2: WB:     VS 0 ~7
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT3: WW:     VS 0 ~7
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,             //LUT4: VCOM:   VS 0 ~7

    0x0A,0x00,0x00,0x00,0x00,                       // TP0 A~D RP0
    0x00,0x00,0x00,0x00,0x00,                       // TP1 A~D RP1
    0x00,0x00,0x00,0x00,0x00,                       // TP2 A~D RP2
    0x00,0x00,0x00,0x00,0x00,                       // TP3 A~D RP3
    0x00,0x00,0x00,0x00,0x00,                       // TP4 A~D RP4
    0x00,0x00,0x00,0x00,0x00,                       // TP5 A~D RP5
    0x00,0x00,0x00,0x00,0x00,                       // TP6 A~D RP6

    0x15,0x41,0xA8,0x32,0x30,0x0A,
};

static void delay(__IO uint16_t nCount)
{
	/* Decrement nCount value */
	while (nCount != 0)
	{
		nCount--;
	}
}

// 0: timeout	1: idle
uint8_t WaitUntilIdle(void)
{
	while (READ_BUSY == 0)
	{
		_asm("nop");
	}
}

void SpiTransfer(uint8_t txData)
{
	uint8_t i;
	SPI_CS_LOW;
	for (i = 0; i < 8; i++)
	{
		// send
		if (txData & 0x80)
		{
			SPI_MOSI_HIGH;
		}
		else
		{
			SPI_MOSI_LOW;
		}
		txData <<= 1;
		SPI_SCK_LOW;
		_asm("nop");
		_asm("nop"); // 16MHz delay 2*62.5 = 125ns

		SPI_SCK_HIGH;
		_asm("nop");
		_asm("nop");
	}
	SPI_CS_HIGH;
}

void SendCommand(uint8_t txData)
{
	EPD_DC_LOW;
	SpiTransfer(txData);
}

void SendData(uint8_t txData)
{
	EPD_DC_HIGH;
	SpiTransfer(txData);
}

void Epd_Reset(void)
{
	EPD_RST_HIGH;
    delay(0x2000);
    EPD_RST_LOW;
    delay(0x100);
    EPD_RST_HIGH;
    delay(0x2000);
}

void Epd_Init(const uint8_t mode)
{
	uint8_t count;
	// BUSY: PC3	input
	GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_In_PU_No_IT);
	// CS: PE6		SCK: PE7
	GPIO_Init(GPIOE, GPIO_Pin_6 | GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Fast);
	// BS1, RESET, D/C
	GPIO_Init(GPIOC, GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Fast);
	// MOSI
	GPIO_Init(GPIOD, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Fast);

	// PC2 low, 4pin SPI mode
	GPIO_ResetBits(GPIOC, GPIO_Pin_2);

	SPI_CS_HIGH;
	SPI_SCK_HIGH;

	Epd_Reset();
	if (mode == EPD_FULL)
	{
		WaitUntilIdle();
		SendCommand(0x12); // soft reset
		WaitUntilIdle();

		SendCommand(0x74); // set analog block control
		SendData(0x54);    // A[7:0]: 54h [POR]	
		SendCommand(0x7E); // set digital block control
		SendData(0x3B);    // A[7:0]: 3Bh [POR]

		SendCommand(0x01); // Driver output control
		SendData(0xF9);
		SendData(0x00);
		SendData(0x00);

		SendCommand(0x11); // data entry mode
		SendData(0x01);    // 01 –Y decrement, X increment, 

		SendCommand(0x44); // set Ram-X address start/end position
		SendData(0x00);
		SendData(0x0F);    // 0x0F-->(15+1)*8=128

		SendCommand(0x45); // set Ram-Y address start/end position
		SendData(0xF9);	   // 0xF9-->(249+1)=250
		SendData(0x00);
		SendData(0x00);
		SendData(0x00);

		SendCommand(0x3C); // BorderWavefrom
		SendData(0x03);

		SendCommand(0x2C); // VCOM Voltage
		SendData(0x55);	   //

		SendCommand(0x03);
		SendData(lut_full_update[70]);

		SendCommand(0x04); //
		SendData(lut_full_update[71]);
		SendData(lut_full_update[72]);
		SendData(lut_full_update[73]);

		SendCommand(0x3A); // Dummy Line
		SendData(lut_full_update[74]);
		SendCommand(0x3B); // Gate time
		SendData(lut_full_update[75]);

		SendCommand(0x32);
		for (count = 0; count < 70; count++)
		{
			SendData(lut_full_update[count]);
		}

		SendCommand(0x4E); // set RAM x address count to 0;
		SendData(0x00);
		SendCommand(0x4F); // set RAM y address count to 0XF9;
		SendData(0xF9);
		SendData(0x00);
		WaitUntilIdle();
	}
	else
	{
		SendCommand(0x2C); // VCOM Voltage
		SendData(0x26);

		WaitUntilIdle();

		SendCommand(0x32);
		for (count = 0; count < 70; count++)
		{
			SendData(lut_partial_update[count]);
		}

		SendCommand(0x37);
		SendData(0x00);
		SendData(0x00);
		SendData(0x00);
		SendData(0x00);
		SendData(0x40);
		SendData(0x00);
		SendData(0x00);

		SendCommand(0x22);
		SendData(0xC0);

		SendCommand(0x20);
		WaitUntilIdle();

		SendCommand(0x3C); // BorderWavefrom
		SendData(0x01);
	}
}

void Epd_Clear(void)
{
	unsigned int w, i, j;
	w = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1);
	SendCommand(0x24);
	for (j = 0; j < EPD_HEIGHT; j++)
	{
		for (i = 0; i < w; i++)
		{
			if (((j >> 4) << 4) == j)
				SendData(0xff);
			else
				SendData(0xfe);
		}
	}

	// DISPLAY REFRESH
	SendCommand(0x22);
	SendData(0xC7);
	SendCommand(0x20);
	WaitUntilIdle();
}

void Epd_Display(const uint8_t* frame_buffer)
{
		unsigned int i, j;
    unsigned int w = (EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1);
    unsigned int h = EPD_HEIGHT;

    if (frame_buffer != 0) {
        SendCommand(0x24);
				for (j = 0; j < h; j++) {
						for (i = 0; i < w; i++) {
								SendData(*(frame_buffer + i + j * w));
						}
				}
    }

    //DISPLAY REFRESH
    SendCommand(0x22);
    SendData(0xC7);
    SendCommand(0x20);
    WaitUntilIdle();
}

/**
 *  @brief: After this command is transmitted, the chip would enter the
 *          deep-sleep mode to save power.
 *          The deep sleep mode would return to standby by hardware reset.
 *          The only one parameter is a check code, the command would be
 *          executed if check code = 0xA5.
 *          You can use Epd::Init() to awaken
 */
void Epd_Sleep(void)
{
    SendCommand(0x10); //enter deep sleep
    SendData(0x01);
    delay(0x2000);

    EPD_RST_LOW;
}
