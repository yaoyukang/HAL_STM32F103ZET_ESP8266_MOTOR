#ifndef __motor_H
#define __motor_H

#define High 1 
#define Low  0

#define INA1(a) if(a)\
									HAL_GPIO_WritePin(INA1_GPIO_Port, INA1_Pin, GPIO_PIN_SET);\
								else \
									HAL_GPIO_WritePin(INA1_GPIO_Port, INA1_Pin, GPIO_PIN_RESET);
#define INB1(a) if(a)\
									HAL_GPIO_WritePin(INA1_GPIO_Port, INB1_Pin, GPIO_PIN_SET);\
								else \
									HAL_GPIO_WritePin(INA1_GPIO_Port, INB1_Pin, GPIO_PIN_RESET);
#define INA2(a) if(a)\
									HAL_GPIO_WritePin(INA1_GPIO_Port, INA2_Pin, GPIO_PIN_SET);\
								else \
									HAL_GPIO_WritePin(INA1_GPIO_Port, INA2_Pin, GPIO_PIN_RESET);
#define INB2(a) if(a)\
									HAL_GPIO_WritePin(INA1_GPIO_Port, INB2_Pin, GPIO_PIN_SET);\
								else \
									HAL_GPIO_WritePin(INA1_GPIO_Port, INB2_Pin, GPIO_PIN_RESET);
/*Function----------------------------------------------------------------------------*/						
void Motor1_stop(void);
void Motor1_forward(void);
void Motor1_backward(void);
void Motor2_stop(void);
void Motor2_forward(void);
void Motor2_backward(void);
void Motor_status(void);

								
							
#endif /*__ pinoutConfig_H */



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
