#include "EPD_213.h"

// LOW: idle, HIGH: busy
#define EPD_IS_BUSY  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3) == GPIO_Pin_3

#define EPD_RST_HIGH	GPIO_SetBits(GPIOC, GPIO_Pin_4)
#define EPD_RST_LOW	GPIO_ResetBits(GPIOC, GPIO_Pin_4)

#define EPD_DC_HIGH	GPIO_SetBits(GPIOC, GPIO_Pin_7)
#define EPD_DC_LOW	GPIO_ResetBits(GPIOC, GPIO_Pin_7)

#define SPI_CS_HIGH	GPIO_SetBits(GPIOE, GPIO_Pin_6)
#define SPI_CS_LOW	GPIO_ResetBits(GPIOE, GPIO_Pin_6)

#define SPI_SCK_HIGH	GPIO_SetBits(GPIOE, GPIO_Pin_7)
#define SPI_SCK_LOW	GPIO_ResetBits(GPIOE, GPIO_Pin_7)

#define SPI_MOSI_HIGH	GPIO_SetBits(GPIOD, GPIO_Pin_4)
#define SPI_MOSI_LOW	GPIO_ResetBits(GPIOD, GPIO_Pin_4)

// The phase length of LUT0~LUT4 is defined as TP[nX]
// 		n represents the Group number from 0 to 6
// 		X represents the sub-group number from A to D
// The range of TP[nX] is from 0 to 255.
// TP[nX] = 0 indicates phase skipped. 

// The range of RP[n] is from 0 to 255. 
// The repeat count of group is defined as RP[n], 
// 		which is used for the count of repeating TP[nA] ~ TP[nD]; 
// RP[n] = 0 indicates run time =1,
const uint8_t lut_full_update[]= {
	// 00: VSS (VCOM)	01: VSH1(WB) 15V	10: VSL(BW) -15V	11: VSH2(WB) 5V
	// Group 0 0x80: 10 00 00 00	BW __
	// Group 1 0x60: 01 10 00 00	WB BW
	// Group 2 0x40: 01 00 00 00	WB __
	0x80,0x60,0x40,0x00,0x00,0x00,0x00,			 //LUT0: BB:	 VS 0 ~7

	// Group 0 0x10: 00 01 00 00	__ WB
	// Group 1 0x60: 01 10 00 00	WB BW
	// Group 2 0x20: 00 10 00 00	BW __
	0x10,0x60,0x20,0x00,0x00,0x00,0x00,			 //LUT1: BW:	 VS 0 ~7

	// Group 0 0x80: 10 00 00 00	BW __
	// Group 1 0x60: 01 10 00 00	WB BW
	// Group 2 0x40: 01 00 00 00	WB __
	0x80,0x60,0x40,0x00,0x00,0x00,0x00,			 //LUT2: WB:	 VS 0 ~7

	// Group 0 0x10: 00 01 00 00	__ WB
	// Group 1 0x60: 01 10 00 00	WB BW
	// Group 2 0x20: 00 10 00 00	BW __
	0x10,0x60,0x20,0x00,0x00,0x00,0x00,			 //LUT3: WW:	 VS 0 ~7

	// 00: DCVCOM
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,			 //LUT4: VCOM:   VS 0 ~7

	0x03,0x03,0x00,0x00,0x02,					   // TP0A ~ TP0D, RP0
	0x09,0x09,0x00,0x00,0x02,					   // TP1A ~ TP1D, RP1
	0x03,0x03,0x00,0x00,0x02,					   // TP2A ~ TP2D, RP2
	0x00,0x00,0x00,0x00,0x00,					   // TP3A ~ TP3D, RP3
	0x00,0x00,0x00,0x00,0x00,					   // TP4A ~ TP4D, RP4
	0x00,0x00,0x00,0x00,0x00,					   // TP5A ~ TP5D, RP5
	0x00,0x00,0x00,0x00,0x00,					   // TP6A ~ TP6D, RP6

	// Command 0x03: Set Gate related driving voltage
	0x15,		// VGH at 19V(0x15) (POR is 0x19, 21V)
	// Command 0x04: Source Driving voltage Control 
	0x41,		// VSH1 at 15V(0x41)
	0xA8,		// VSH2 at 5V(0xA8)
	0x32,		// VSL at -15V(0x32)
	// Below 2 commands will give 50Hz Frame frequency under 48 dummy line pulse setting.
	// Command 0x3A: Set number of dummy line period (TGate)
	0x30,
	// Command 0x3B: Set Gate line width (TGate)
	0x0A,
};

const uint8_t lut_partial_update[]= { //20 bytes
	// 00: DCVCOM
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,			 //LUT0: BB:	 VS 0 ~7
	// Group 0 0x80: 10 00 00 00	BW
	0x80,0x00,0x00,0x00,0x00,0x00,0x00,			 //LUT1: BW:	 VS 0 ~7
	// Group 0 0x40: 01 00 00 00	WB
	0x40,0x00,0x00,0x00,0x00,0x00,0x00,			 //LUT2: WB:	 VS 0 ~7
	// 00: DCVCOM
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,			 //LUT3: WW:	 VS 0 ~7
	// 00: DCVCOM
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,			 //LUT4: VCOM:   VS 0 ~7

	0x0A,0x00,0x00,0x00,0x00,					   // TP0A ~ TP0D, RP0
	0x00,0x00,0x00,0x00,0x00,					   // TP1A ~ TP1D, RP1
	0x00,0x00,0x00,0x00,0x00,					   // TP2A ~ TP2D, RP2
	0x00,0x00,0x00,0x00,0x00,					   // TP3A ~ TP3D, RP3
	0x00,0x00,0x00,0x00,0x00,					   // TP4A ~ TP4D, RP4
	0x00,0x00,0x00,0x00,0x00,					   // TP5A ~ TP5D, RP5
	0x00,0x00,0x00,0x00,0x00,					   // TP6A ~ TP6D, RP6

	// Command 0x03: Set Gate related driving voltage
	0x15,		// VGH at 19V(0x15) (POR is 0x19, 21V)
	// Command 0x04: Source Driving voltage Control 
	0x41,		// VSH1 at 15V(0x41)
	0xA8,		// VSH2 at 5V(0xA8)
	0x32,		// VSL at -15V(0x32)
	// Below 2 commands will give 50Hz Frame frequency under 48 dummy line pulse setting.
	// Command 0x3A: Set number of dummy line period (TGate)
	0x30,
	// Command 0x3B: Set Gate line width (TGate)
	0x0A,
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
	while (EPD_IS_BUSY)
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
		// _asm("nop"); // 16MHz nop = 62.5ns

		SPI_SCK_HIGH;
		// _asm("nop");
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
	// CS: PE6		SCK: PE7
	GPIO_Init(GPIOE, GPIO_Pin_6 | GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Fast);
	// BS1, RESET, D/C
	GPIO_Init(GPIOC, GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Fast);
	// MOSI
	GPIO_Init(GPIOD, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Fast);
	// BUSY: PC3	input
	GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_In_PU_No_IT);

	// PC2 low, 4pin SPI mode
	GPIO_ResetBits(GPIOC, GPIO_Pin_2);

	SPI_CS_HIGH;
	SPI_SCK_HIGH;

	// Sequence 1
	Epd_Reset();
	if (mode == EPD_FULL)
	{
		// comments below are based on ssd1675
		// Sequence 2
		WaitUntilIdle();
		SendCommand(0x12); // soft reset
		WaitUntilIdle();

		// Sequence 3
		SendCommand(0x74); // set analog block control
		SendData(0x54);	   // A[7:0]: 54h [POR]
		SendCommand(0x7E); // set digital block control
		SendData(0x3B);	   // A[7:0]: 3Bh [POR]

		SendCommand(0x01); // Driver output control
		SendData(0xF9);	   // 0xF9: (249+1)=250 Gate lines
		SendData(0x00);
		SendData(0x00);

		SendCommand(0x3A);			   // Set number of dummy line period (TGate)
		SendData(lut_full_update[74]); // 0x30 [POR]
		SendCommand(0x3B);			   // Set Gate line width (TGate)
		SendData(lut_full_update[75]); // 0x0A [POR]
		SendCommand(0x3C);			   // Border Waveform Control
		SendData(0x03);				   // 0x03: VBD Transition LUT3

		// Sequence 4
		SendCommand(0x11); // data entry mode
		SendData(0x03);	   // 01 ???Y increment, X increment

		SendCommand(0x44); // set Ram-X address start/end position
		SendData(0x00);	   // 0x00 increase to
		SendData(0x0F);	   // 0x0F-->(15+1)*8=128

		SendCommand(0x45); // set Ram-Y address start/end position
		SendData(0x00);	   // 0x00
		SendData(0x00);	   // increase to
		SendData(0xF9);	   // 0xF9-->(249+1)=250
		SendData(0x00);

		SendCommand(0x4E); // set RAM x address count to 0;
		SendData(0x00);
		SendCommand(0x4F); // set RAM y address count to 0;
		SendData(0x00);
		SendData(0x00);

		SendCommand(0x2C); // VCOM Voltagee, the smaller, the whiter
		SendData(0x50);	   // 0x50: -2V
		SendCommand(0x03); // Set Gate related driving voltage
		SendData(lut_full_update[70]);	// 0x15: 19V
		SendCommand(0x04); // Set Source output voltage magnitude
		SendData(lut_full_update[71]);	// 0x41: VSH1 at 15V
		SendData(lut_full_update[72]);	// 0xA8: VSH2 at 5V
		SendData(lut_full_update[73]);	// 0x32: VSL at -15V

		SendCommand(0x32);
		for (count = 0; count < 70; count++)
		{
			SendData(lut_full_update[count]);
		}

		WaitUntilIdle();
	}
	else
	{
		SendCommand(0x2C); // VCOM Voltage, the smaller, the whiter
		SendData(0x24);    // 0x24: -0.9V
		WaitUntilIdle();

		SendCommand(0x32);
		for (count = 0; count < 70; count++)
		{
			SendData(lut_partial_update[count]);
		}

		SendCommand(0x37); // Write OTP selection
		SendData(0x00);
		SendData(0x00);
		SendData(0x00);
		SendData(0x00);
		SendData(0x40);
		SendData(0x00);
		SendData(0x00);

		SendCommand(0x22); // Display Update Sequence Option
		SendData(0xC0);	   // 0xC0: (CLKEN=1, ANALOGEN=1) Enable Clock Signal, Enable ANALOG
		SendCommand(0x20); // Activate Display Update Sequence
		WaitUntilIdle();

		SendCommand(0x3C); // Border Waveform Control
		SendData(0x01);
	}
}

void Epd_Clear(void)
{
	uint16_t w, i, j;
	w = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1);
	SendCommand(0x24);		// Write RAM (BW)
	for (j = 0; j < EPD_HEIGHT; j++)
	{
		for (i = 0; i < w; i++)
		{
			SendData(0xff);
		}
	}

	// DISPLAY REFRESH
	SendCommand(0x22);
	SendData(0xC7);		// Enable Clock Signal, Enable ANALOG, DISPLAY, Disable ANALOG, Disable OSC
	SendCommand(0x20);	// Activate Display Update Sequence
	WaitUntilIdle();
}

// Setting the display window
void Epd_SetWindows(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
    SendCommand(0x44); // SET_RAM_X_ADDRESS_START_END_POSITION
    SendData((Xstart>>3) & 0xFF);
    SendData((Xend>>3) & 0xFF);
	
    SendCommand(0x45); // SET_RAM_Y_ADDRESS_START_END_POSITION
    SendData(Ystart & 0xFF);
    SendData((Ystart >> 8) & 0xFF);
    SendData(Yend & 0xFF);
    SendData((Yend >> 8) & 0xFF);
}

// Set Cursor
void Epd_SetCursor(uint16_t Xstart, uint16_t Ystart)
{
    SendCommand(0x4E); // SET_RAM_X_ADDRESS_COUNTER
    SendData(Xstart & 0xFF);

    SendCommand(0x4F); // SET_RAM_Y_ADDRESS_COUNTER
    SendData(Ystart & 0xFF);
    SendData((Ystart >> 8) & 0xFF);
}

void Epd_Display(const uint8_t *frame_buffer)
{
	uint16_t i, j;
	uint8_t w = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1);

	if (frame_buffer != 0)
	{
		SendCommand(0x24);		// Write RAM (BW)
		for (j = 0; j < EPD_HEIGHT; j++)
		{
			for (i = 0; i < w; i++)
			{
				SendData(*(frame_buffer + i + j * w));
			}
		}
	}

	// DISPLAY REFRESH
	SendCommand(0x22);
	SendData(0xC7);		// Enable Clock Signal, Enable ANALOG, DISPLAY, Disable ANALOG, Disable OSC
	SendCommand(0x20);
	WaitUntilIdle();
}

void Epd_DisplayPartBaseImage(const uint8_t *frame_buffer)
{
	uint16_t i, j;
	uint8_t w = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1);

	if (frame_buffer != 0)
	{
		SendCommand(0x24);	// Write RAM (BW)
		for (j = 0; j < EPD_HEIGHT; j++)
		{
			for (i = 0; i < w; i++)
			{
				SendData(*(frame_buffer + i + j * w));
			}
		}

		SendCommand(0x26);	// Write RAM (RED)
		for (j = 0; j < EPD_HEIGHT; j++)
		{
			for (i = 0; i < w; i++)
			{
				SendData(*(frame_buffer + i + j * w));
			}
		}
	}

	// DISPLAY REFRESH
	SendCommand(0x22);
	SendData(0xC7);		// Enable Clock Signal, Enable ANALOG, DISPLAY, Disable ANALOG, Disable OSC
	SendCommand(0x20);
	WaitUntilIdle();
}

void Epd_DisplayPart(const uint8_t *frame_buffer)
{
	uint8_t w = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1);
	uint16_t i, j;

	if (frame_buffer != 0)
	{
		SendCommand(0x24);
		for (j = 0; j < EPD_HEIGHT; j++)
		{
			for (i = 0; i < w; i++)
			{
				SendData(*(frame_buffer + i + j * w));
			}
		}
	}

	// DISPLAY REFRESH
	SendCommand(0x22);
	SendData(0x0C);
	SendCommand(0x20);
	WaitUntilIdle();
}

void Epd_ClearPart(void)
{
	uint16_t i, j;
	uint8_t w;
	w = (EPD_WIDTH % 8 == 0) ? (EPD_WIDTH / 8) : (EPD_WIDTH / 8 + 1);
	SendCommand(0x24);	// Write RAM (BW)
	for (j = 0; j < EPD_HEIGHT; j++)
	{
		for (i = 0; i < w; i++)
		{
			SendData(0xff);
		}
	}

	// DISPLAY REFRESH
	SendCommand(0x22);
	SendData(0x0C);
	SendCommand(0x20);
	WaitUntilIdle();
}

/**
 *  @brief: After this command is transmitted, the chip would enter the
 *		  deep-sleep mode to save power.
 *		  The deep sleep mode would return to standby by hardware reset.
 *		  The only one parameter is a check code, the command would be
 *		  executed if check code = 0xA5.
 *		  You can use Epd::Init() to awaken
 */
void Epd_Sleep(void)
{
	// Deep Sleep Mode 1: Retain RAM data but cannot access the RAM
	// Deep Sleep Mode 2: Cannot retain RAM data
	SendCommand(0x10); // Deep Sleep mode
	SendData(0x01);	   // Enter Deep Sleep Mode 1
	delay(0x2000);
	EPD_RST_LOW;

	// To Exit Deep Sleep mode, User required to send HWRESET to the driver
}
