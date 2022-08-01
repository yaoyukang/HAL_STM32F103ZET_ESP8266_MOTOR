#ifndef __RS485_H
#define __RS485_H
#include "main.h"
#include "gpio.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//RS485驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2017/4/14
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
#define RS485_TX_EN    HAL_GPIO_WritePin(RS485_TX_EN_GPIO_Port, RS485_TX_EN_Pin, GPIO_PIN_SET)  //发送模式
#define RS485_RX_EN    HAL_GPIO_WritePin(RS485_TX_EN_GPIO_Port, RS485_TX_EN_Pin, GPIO_PIN_RESET)  //接收模式

extern uint8_t RS485_RX_BUF[64]; 		//接收缓冲,最大64个字节
extern uint8_t RS485_RX_CNT;   			//接收到的数据长度


void RS485_Init(void);
void RS485_Send_Data(uint8_t *buf,uint8_t len);
void RS485_Receive_Data(uint8_t *buf,uint8_t *len);	
 void Delta_status(void);

#endif
