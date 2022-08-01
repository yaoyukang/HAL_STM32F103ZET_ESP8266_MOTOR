#ifndef __ESP8266_H
#define __ESP8266_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"


/* define---------------------------------------------------------------------*/

#define ESP8266_AT HAL_UART_Transmit(&huart1, UART_CMD_AT, sizeof(UART_CMD_AT),0xffff)
#define ESP8266_MODE HAL_UART_Transmit(&huart1, UART_CMD_MODE, sizeof(UART_CMD_MODE),0xffff)
#define ESP8266_RST	HAL_UART_Transmit(&huart1, UART_CMD_RST, sizeof(UART_CMD_RST),0xffff)
#define ESP8266_MUX HAL_UART_Transmit(&huart1, UART_CMD_MUX, sizeof(UART_CMD_MUX),0xffff)
#define ESP8266_SERVER HAL_UART_Transmit(&huart1, UART_CMD_SERVER, sizeof(UART_CMD_SERVER),0xffff)

uint8_t ESP8266_Init(void);
uint8_t Send_cmd(uint8_t* cmd);

#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
