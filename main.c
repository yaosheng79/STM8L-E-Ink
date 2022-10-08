#include "stm8l15x.h"
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

void main(void)
{
  /* Initialize LEDs mounted on STM8L152X-EVAL board */
  GPIO_Init(LED_GPIO_PORT, LED_GPIO_PINS, GPIO_Mode_Out_PP_Low_Fast);

  while (1)
  {
    Power_On();
    Delay(0xFFFF);
    Power_Off();
    Delay(0xFFFF);
  }
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
