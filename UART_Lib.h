#ifndef __UART_LIB_H__
#define __UART_LIB_H__
#include "main.h"
#include "string.h"

extern TIM_HandleTypeDef htim1;

/***** Define Port and Pin here *****/
#define UART_TX_PORT	GPIOA
#define UART_TX_PIN		GPIO_PIN_1
/************************************/

/*	Warning!!!
This UART just uses one wire to transmitt and receive.
That means in a mean time you just can use to transmitt or receive, can't use both of them
*/

// Set the prescaler in CubeMx equal to APB timer clock you use
// This UART is used for 9600 baud
// None parity 
void delay_us(uint32_t time);
void softUART_Transmitt_AByte(uint8_t data);
void softUART_Transmitt(uint8_t* str);
uint8_t softUART_Receive_AByte(void);
void softUART_Receive(uint8_t* data_receive, uint32_t length);
#endif
