/* Includes ------------------------------------------------------------------*/
#include "data_processing.h"
#include "Legacy/stm32_hal_legacy.h" //timset 
#include "stdio.h"
#include "usart.h"
#include "string.h"
#include "rs485.h"
#include "motor.h"
#include "tim.h"


uint8_t Esp8266_flag_rx = 0;
uint8_t Esp8266_flag_cnt = 1;
uint8_t RS485_flag_rx = 0;
uint8_t RS485_flag_cnt = 1;

uint8_t Rx485;
uint16_t RS485_buf[64];
uint8_t RxData;
uint8_t strDeal[64] ;//8266
uint8_t strDeal485[20];//485
uint8_t cmd1  = 'K';
uint8_t cmd_ok[3] = "OK";

uint8_t Speed_flag = 0;
uint8_t Delta_flag = 0;
uint8_t Do_flag = 0;
//01-10-00-08-00-05-0A-00-00-00-00-ED-40-00-00-01-00-1F-12
//(0,0,-480)
uint8_t point1[] = {0x01, 0x10, 0x00, 0x08, 0x00, 0x05, 0x0A, 0x00, 0x00, 0x00, 0x00, 0xED, 0x40, 0x00, 0x00, 0x01, 0x00, 0x1F, 0x12};
//01-10-00-08-00-05-0A-03-84-00-00-EA-20-00-00-01-00-3D-A4
//(90,0,-560)
uint8_t point2[] = {0x01, 0x10, 0x00, 0x08, 0x00, 0x05, 0x0A, 0x03, 0x84, 0x00, 0x00, 0xEA, 0x20, 0x00, 0x00, 0x01, 0x00, 0x3D, 0xA4};
//01-10-00-08-00-05-0A-FC-7C-00-00-EA-20-00-00-01-00-6B-93
//(-90,0,-560)
uint8_t point3[] = {0x01, 0x10, 0x00, 0x08, 0x00, 0x05, 0x0A, 0xFC, 0x7C, 0x00, 0x00, 0xEA, 0x20, 0x00, 0x00, 0x01, 0x00, 0x6B, 0x93};
//(270,0,-560)
//01-10-00-08-00-05-0A-0A-8C-00-00-EA-20-00-00-01-00-8A-4B
uint8_t point4[] = {0x01, 0x10, 0x00, 0x08, 0x00, 0x05, 0x0A, 0x0A, 0x8C, 0x00, 0x00, 0xEA, 0x20, 0x00, 0x00, 0x01, 0x00, 0x8A, 0x4B};
//(-270,0,-560)
//01-10-00-08-00-05-0A-F5-74-00-00-EA-20-00-00-01-00-DC-7C
uint8_t point5[] = {0x01, 0x10, 0x00, 0x08, 0x00, 0x05, 0x0A, 0xF5, 0x74, 0x00, 0x00, 0xEA, 0x20, 0x00, 0x00, 0x01, 0x00, 0xDC, 0x7C};

//485
uint8_t rx  = 'Z';
extern uint8_t Motor_flag;
extern uint8_t Delta_flag;

/*--------------------------------补码-----------------------------------------*/
uint8_t* Transform_16(int num)
{
    int i;
    char s[17] = {0};
    static uint8_t reNum[4];
    for(i = 0; i < 16; i++)
    {
        s[i] = (0x01 & (num >> (15 - i))) ? '1' : '0' ;
    }
    for(int j = 0; j < 4; j++)
    {
        reNum[j] = (s[j * 4] - '0') * 8 + (s[j * 4 + 1] - '0') * 4 + (s[j * 4 + 2] - '0') * 2 + (s[j * 4 + 3] - '0') * 1;
        switch(reNum[j])
        {
            case 10 :
                reNum[j] = 'A';
                break;
            case 11 :
                reNum[j] = 'B';
                break;
            case 12 :
                reNum[j] = 'C';
                break;
            case 13 :
                reNum[j] = 'D';
                break;
            case 14 :
                reNum[j] = 'E';
                break;
            case 15 :
                reNum[j] = 'F';
                break;
            default:
                reNum[j] = reNum[j] + '0';
                break;
        }
    }
    return reNum;
}
/*--------------------------------CRC16-----------------------------------------*/
uint16_t CaculateCRC(uint8_t *Data, uint16_t len)
{
    uint16_t n, i;
    uint16_t crc = 0xffff;
    for (n = 0; n < len; n++)
    {
        crc = crc ^ Data[n];
        for (i = 0; i < 8; i++)
        {
            if((crc & 1) == 1)
            {
                crc = crc >> 1;
                crc = crc ^ 0xA001;
            }
            else
            {
                crc = crc >> 1;
            }
        }
    }
    return(crc);
}
/*---------------------------------Delta control-------------------------------------------------------*/
void Delta_status(void)
{
    switch(Delta_flag)
    {
        case '0':
            //
            HAL_Delay(100);
            break;
        case '1':
            RS485_Send_Data(point2, sizeof(point2));
            break;
        case '2':
            RS485_Send_Data(point3, sizeof(point3));
            break;
        case '3':
            RS485_Send_Data(point4, sizeof(point4));
            break;
        case '4':
            RS485_Send_Data(point5, sizeof(point5));
            break;
        case '5':
            break;
        default:
            break;
    }
    HAL_Delay(300);
    RS485_Send_Data(point1, sizeof(point1));
    HAL_Delay(100);
}
/*---------------------------------Speed control-------------------------------------------------------*/
void Speed_status(void)
{
    switch(Speed_flag)
    {
        case '0':
            HAL_Delay(1);
            break;
        case '1':
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 300);
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, 300);
            break;
        case '2':
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 400);
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, 400);
            break;
        case '3':
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 600);
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, 600);
            break;
        case '4':
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 800);
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, 800);
            break;
        case '5':
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, 998);
            __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_2, 998);
            break;
    }
}
/*--------------------------------8266  Data processing-----------------------------------------*/
void Esp8266_analysis(void)
{
    Motor_flag = strDeal[1];
    Delta_flag = strDeal[2];
    Speed_flag = strDeal[3];
    Do_flag = 1;
}
void All_status(void)
{
    if(Do_flag == 1)
    {
        Motor_status();		//快速刷新状态
        Speed_status();
        Delta_status();
        Do_flag = 0;
    }
}


/*--通信协议--*/
/*
N000END 控制电机
N-100,-500,-10END
*/
/*---------------------------------------------------------------------*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /*esp8266*/
    if(huart == &huart1)
    {
        if(RxData == ':' && Esp8266_flag_rx == 0)
        {
            strDeal[0] = 'N';
            Esp8266_flag_rx = 1;
        }
        else if(Esp8266_flag_rx == 1 && strDeal[0] == 'N')
        {
            strDeal[Esp8266_flag_cnt] = RxData;
            Esp8266_flag_cnt++;
            if(Esp8266_flag_cnt == 7 && strDeal[6] == 'D') //N 123 END
            {
                Esp8266_flag_rx = 0;
                Esp8266_flag_cnt = 1;
                Esp8266_analysis();
            }
            if(Esp8266_flag_cnt > 7)
            {
                Esp8266_flag_rx = 0;
                Esp8266_flag_cnt = 1;
                memset(strDeal, 0, sizeof(strDeal));//无效数据 - 清零
            }
        }
    }
}





