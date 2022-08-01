#ifndef __DATA_H
#define __DATA_H
#include "main.h"


uint16_t CaculateCRC(uint8_t *Data,uint16_t len);
void RS485_Send_analysis(void);
void RS485_Rx_analysis(void);
int strToint(uint8_t* str);
uint8_t* Transform_16(int num);
void Esp8266_analysis(void);

void Delta_status(void);
void Speed_status(void);
void All_status(void);


#endif
