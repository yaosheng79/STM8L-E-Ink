#include "EInk.h"

#define EINK_RST_HIGH    GPIO_SetBits(GPIOC, GPIO_Pin_4)
#define EINK_RST_LOW    GPIO_ResetBits(GPIOC, GPIO_Pin_4)

#define READ_BUSY  GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_3)

#define EINK_DC_HIGH    GPIO_SetBits(GPIOC, GPIO_Pin_7)
#define EINK_DC_LOW    GPIO_ResetBits(GPIOC, GPIO_Pin_7)

#define SPI_CS_HIGH    GPIO_SetBits(GPIOE, GPIO_Pin_6)
#define SPI_CS_LOW    GPIO_ResetBits(GPIOE, GPIO_Pin_6)

#define SPI_SCK_HIGH    GPIO_SetBits(GPIOE, GPIO_Pin_7)
#define SPI_SCK_LOW    GPIO_ResetBits(GPIOE, GPIO_Pin_7)

#define SPI_MOSI_HIGH    GPIO_SetBits(GPIOD, GPIO_Pin_4)
#define SPI_MOSI_LOW    GPIO_ResetBits(GPIOD, GPIO_Pin_4)


static void delay(__IO uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

uint8_t EInk_READ_BUSY(void)
{
	uint8_t ret = 1;
	uint16_t timeout = 0xffff;
	while(READ_BUSY == 0)
	{
		timeout--;
		if (0 == timeout)
		{
			ret = 0;
			break;
		}
	}
	return ret;
}

void EInk_SPI_WriteByte(uint8_t txData)
{
	uint8_t i;
	// uint8_t rxData = 0;

	for(i = 0; i < 8; i++)
	{
		// send
		if(txData & 0x80){
			SPI_MOSI_HIGH;
		}else{
			SPI_MOSI_LOW;
		}
		txData <<= 1;
		SPI_SCK_LOW;
		_asm("nop");_asm("nop");	// 16MHzdelay 2*62.5 = 125ns

		SPI_SCK_HIGH;
		_asm("nop");_asm("nop");
	}
}

void EInk_Write_Command(uint8_t txData)
{
	SPI_CS_HIGH;
	SPI_CS_LOW;
	EINK_DC_LOW;
	EInk_SPI_WriteByte(txData);
	SPI_CS_HIGH;
}

void EInk_Write_Data(uint8_t txData)
{
	SPI_CS_HIGH;
	SPI_CS_LOW;
	EINK_DC_HIGH;
	EInk_SPI_WriteByte(txData);
	SPI_CS_HIGH;
}

void EInk_HW_Init(const uint8_t full_refresh)
{
	// BUSY: PC3	input
	GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_In_PU_No_IT);
	// CS: PE6		SCK: PE7
  GPIO_Init(GPIOE, GPIO_Pin_6 | GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Fast);
	// BS1, RESET, D/C
  GPIO_Init(GPIOC, GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Fast);
	// MOSI
  GPIO_Init(GPIOD, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Fast);

	SPI_CS_HIGH;
	SPI_SCK_HIGH;

	// PC2 low, 4pin SPI mode
	GPIO_ResetBits(GPIOC, GPIO_Pin_2);
	
	// reset
	EINK_RST_LOW;
	delay(0xFFFF);
	EINK_RST_HIGH;
	delay(0xFFFF);
	
	EInk_READ_BUSY();
	EInk_Write_Command(0x12);	// soft reset
	EInk_READ_BUSY();
	
	
	EInk_Write_Command(0x01); //Driver output control      
	EInk_Write_Data(0x2B);
	EInk_Write_Data(0x01);
	EInk_Write_Data(0x00);

	EInk_Write_Command(0x11); //data entry mode       
	EInk_Write_Data(0x03);		//Y increment, X increment

	EInk_Write_Command(0x44); //set Ram-X address start/end position   
	EInk_Write_Data(0x00);		//0x00-->0
	EInk_Write_Data(0x31);    //0x31-->(49+1)*8=400

	EInk_Write_Command(0x45); //set Ram-Y address start/end position          
	EInk_Write_Data(0x00);   	
	EInk_Write_Data(0x00);
	EInk_Write_Data(0x2B);		//0x012B-->(299+1)=300
	EInk_Write_Data(0x01); 

	EInk_Write_Command(0x3C); //BorderWavefrom
	EInk_Write_Data(0x01);	

    EInk_Write_Command(0x18); //Temperature Sensor Selection
	EInk_Write_Data(0x80);	  //Internal temperature sensor
	
    EInk_Write_Command(0x22); 
	if(full_refresh)
		EInk_Write_Data(0xB1);	// full screen refresh LUT
	else
		EInk_Write_Data(0xB9);	//µ÷ÓÃ¾ÖË¢LUT   
	EInk_Write_Command(0x20); 
	EInk_READ_BUSY(); 	

	EInk_Write_Command(0x4E);   // set RAM x address count
	EInk_Write_Data(0x00);
	EInk_Write_Command(0x4F);   // set RAM y address count
	EInk_Write_Data(0x00);
	EInk_Write_Data(0x00);
	EInk_READ_BUSY();
}
