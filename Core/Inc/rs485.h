#ifndef __RS485_H
#define __RS485_H
#include "main.h"
#include "gpio.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//RS485��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2017/4/14
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
#define RS485_TX_EN    HAL_GPIO_WritePin(RS485_TX_EN_GPIO_Port, RS485_TX_EN_Pin, GPIO_PIN_SET)  //����ģʽ
#define RS485_RX_EN    HAL_GPIO_WritePin(RS485_TX_EN_GPIO_Port, RS485_TX_EN_Pin, GPIO_PIN_RESET)  //����ģʽ

extern uint8_t RS485_RX_BUF[64]; 		//���ջ���,���64���ֽ�
extern uint8_t RS485_RX_CNT;   			//���յ������ݳ���


void RS485_Init(void);
void RS485_Send_Data(uint8_t *buf,uint8_t len);
void RS485_Receive_Data(uint8_t *buf,uint8_t *len);	
 void Delta_status(void);

#endif
