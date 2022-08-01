/* Includes ------------------------------------------------------------------*/
#include "esp8266.h"
#include "stdio.h"
#include "usart.h"
/*8266-AT-CMD*/
uint8_t UART_CMD_AT[5] = "AT\r\n";
uint8_t UART_CMD_MODE[14] ="AT+CWMODE=2\r\n"; 
uint8_t UART_CMD_RST[9] ="AT+RST\r\n";
uint8_t UART_CMD_MUX[14] = "AT+CIPMUX=1\r\n";
uint8_t UART_CMD_SERVER[23] =" AT+CIPSERVER=1,8089\r\n";
extern uint8_t RxData;
uint8_t ESP8266_Init(void) 
{
	HAL_UART_Receive_IT(&huart1,&RxData,1);
	ESP8266_AT;
	HAL_Delay(1000);
	ESP8266_MODE;
	HAL_Delay(1000);
	ESP8266_RST;
	HAL_Delay(1000);
  ESP8266_MUX;
	HAL_Delay(1000);
  ESP8266_SERVER;
	HAL_Delay(1000);
	return  0;
}




