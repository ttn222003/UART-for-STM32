#include "UART_Lib.h"

/***** Low function *****/
void delay_us(uint32_t time)
{
	HAL_TIM_Base_Start(&htim1);
	__HAL_TIM_SET_COUNTER(&htim1,0);
	while(__HAL_TIM_GET_COUNTER(&htim1) < time);
	HAL_TIM_Base_Stop(&htim1);
}

void Set_Pin_As_Output()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void Set_Pin_As_Input()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
/*************************/

/***** High function *****/
/*
* desciption: send one byte 
* parameter: data you want to send
*/
void softUART_Transmitt_AByte(uint8_t data)
{
	Set_Pin_As_Output();
	// Start UART 
	HAL_GPIO_WritePin(UART_TX_PORT,UART_TX_PIN,GPIO_PIN_SET);
	HAL_GPIO_WritePin(UART_TX_PORT,UART_TX_PIN,GPIO_PIN_RESET);
	delay_us(93);
	// Send data with 6 bits
	for(uint8_t i = 0; i < 7; i++)
	{
		HAL_GPIO_WritePin(UART_TX_PORT,UART_TX_PIN,(GPIO_PinState)((data>>i)&0x01));
		delay_us(93);
	}
	HAL_GPIO_WritePin(UART_TX_PORT,UART_TX_PIN,GPIO_PIN_RESET);
	delay_us(93);
	// End UART 
	HAL_GPIO_WritePin(UART_TX_PORT,UART_TX_PIN,GPIO_PIN_SET);
}

/*
* desciption: send bytes 
* parameter: data you want to send
*/
void softUART_Transmitt(uint8_t* str)
{
	uint32_t i = 0;
	while(i < strlen((char*)str))
	{
		softUART_Transmitt_AByte(*(str + i));
		delay_us(500);
		i++;
	}
}

/*
* desciption: receive a byte 
* parameter: none
* return: the data you want to receive
*/
uint8_t softUART_Receive_AByte(void)
{
	uint8_t data_receive = 0x00;
	Set_Pin_As_Input();
	while(HAL_GPIO_ReadPin(UART_TX_PORT,UART_TX_PIN) == GPIO_PIN_SET);
	delay_us(93);
	for(uint8_t i = 0; i < 7; i++)
	{
		data_receive = data_receive | (HAL_GPIO_ReadPin(UART_TX_PORT,UART_TX_PIN) << i);
		delay_us(93);
	}
	while(HAL_GPIO_ReadPin(UART_TX_PORT,UART_TX_PIN) == GPIO_PIN_RESET);
	return data_receive;
}

/*
* desciption: receive bytes 
* parameter:
	@ received data: the data you want to receive
	@ length: length of the data
* return: the data you want to receive
*/
void softUART_Receive(uint8_t* data_receive, uint32_t length)
{
	uint32_t i = 0;
	while(i < (length - 1))
	{
		*(data_receive + i) = softUART_Receive_AByte();
		i++;
	}
	*(data_receive + i) = softUART_Receive_AByte();
}
/*******************************/
