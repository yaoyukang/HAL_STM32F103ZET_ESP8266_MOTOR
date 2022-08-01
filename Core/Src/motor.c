/* Includes ------------------------------------------------------------------*/
#include "motor.h"
#include "gpio.h"
#include "main.h"
/*----------------------------------------------------------------------------*/
uint8_t Motor_flag =0;

void Motor1_stop(void)
{
	INA1(Low);
	INB1(Low);
}
 
void Motor1_forward(void) 
{
	INA1(Low);
	INB1(High);
}

void Motor1_backward(void)
{

	INA1(High);
	INB1(Low);
}
void Motor2_stop(void)
{
	INA2(Low);
	INB2(Low);
}
 
void Motor2_forward(void)
{
	INA2(Low);
	INB2(High);
}

void Motor2_backward(void)
{

	INA2(High);
	INB2(Low);
}
void Motor_status(void)
{
	switch(Motor_flag)
	{
		case '0':
			HAL_Delay(1);
		  break;
		case  '1'://前进
			Motor1_forward();
			Motor2_forward();
			break;
		case  '2'://后退
			Motor1_backward();
		  Motor2_backward();
			break;
		case  '3'://左转		
			Motor1_stop();
			Motor2_forward();
			break;
		case  '4'://右转
			Motor2_stop();//s
			Motor1_forward();
			break;
		case  '5'://停止
			Motor1_stop();
			Motor2_stop();
			break;	
		default:

		break;			
	
	}

}
/*----------------------------------------------------------------------------*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
