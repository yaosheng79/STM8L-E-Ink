#include "stm8l15x.h"
#include "stdio.h"

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

	/*打开串口*/
  // USART_Cmd(USART3, ENABLE);

  USART_SendData8(USART3, '\r');
  /*用于检查串口UART1是否发送完成,完成时，TC中断标志置位，退出轮询等待*/
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

  while (1)
  {
    Power_On();
    Delay(0xFFFF);
    Power_Off();
    Delay(0xFFFF);
		printf("Hello!\r\n");
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
