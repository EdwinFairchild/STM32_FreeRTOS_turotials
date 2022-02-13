#include "main_app.h"


void main_app(void)
{

	uint32_t counter= 0;
	while(1)
	{
		printMsg("Hello %d\r\n", counter++);
	}
}

void printMsg(char *msg, ...)
{
	char buff[50];
	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);

	for (int i = 0; i < strlen(buff); i++)
	{
		USART2->DR = buff[i];
		while (!(USART2->SR & USART_SR_TXE))
			;
	}

	while (!(USART2->SR & USART_SR_TC))
		;
}

static void blinkLed(void)
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
