#include "main_app.h"

//prototypes
static void blinkLed(void);
void printMsg(char *msg, ...);
static void hello_task(void *pvParameters);
static void led_task(void *pvParameters);
void main_app(void)
{
	int8_t status; 
	uint32_t counter= 0;
	//led task
	status = xTaskCreate(led_task, "LED", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
	if (status == -1)
		printMsg("error creating LED task task\n");

	//hello task
	status = xTaskCreate(hello_task, "Hello", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);
		if (status == -1)
			printMsg("error creating LED task task\n");
	//should never return from here
	vTaskStartScheduler();	

	while(1)
	{
		printMsg("Hello %d\r\n", counter++);
	}
}

static void hello_task(void *pvParameters)
{
	uint32_t counter = 0;
	while (1)
	{
		printMsg("hello %d \r\n", counter++);
		vTaskDelay(1000);
	}
}

static void led_task(void *pvParameters)
{
	//setup

	while (1)
	{
		blinkLed();
		printMsg("led\r\n");
		vTaskDelay(500);
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
		blinkLed();
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
