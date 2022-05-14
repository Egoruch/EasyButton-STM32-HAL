#include "easybut.h"


but_pin_s ButPin[PIN_QUANTITY];


/* brief: Choose GPIO for button
 *
 */
HAL_StatusTypeDef EASYBUT_Init(uint8_t pin_num, GPIO_TypeDef *gpio_port, uint16_t gpio_pin)
{
	if(pin_num>=PIN_QUANTITY){
		return HAL_ERROR;
	}

	ButPin[pin_num].ButPort=gpio_port;
	ButPin[pin_num].ButPin=gpio_pin;

	return HAL_OK;
}

uint8_t EASYBUT_GPIO_Check(but_pin_s *bp)
{
	if(HAL_GPIO_ReadPin(bp->ButPort, bp->ButPin) == GPIO_PIN_RESET) // PRESSED
	{
		bp->ButStat = BUT_PRESSED;

		return 1;
	}else
	{
		bp->ButStat = BUT_NOTPRESSED;

		return 0;
	}
}

uint8_t EASYBUT_Data_Check(but_pin_s *bp)
{
	if(bp->ButStat == BUT_PRESSED)
	{
		bp->ButStat = BUT_NOTPRESSED;

		return 1;
	}else
	{
		return 0;
	}
}

uint8_t EASYBUT_ButtonStat(uint8_t butnum)
{

	if(EASYBUT_Data_Check(&ButPin[butnum]))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*
 * @brief: Call it every 1ms
 * retval: no
 */
void EASYBUT_Handler(void)
{

	for(uint8_t i = 0; i < PIN_QUANTITY; i++)
	{

		EASYBUT_GPIO_Check(&ButPin[i]);

//		ButPin[i]->ButPin

	}

}
