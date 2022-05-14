#ifndef INC_EASYBUT_H_
#define INC_EASYBUT_H_


/* Includes BEGIN */
#include "main.h"
/* Includes END */


#define PIN_QUANTITY 1

typedef enum ButtonStat
{
	BUT_PRESSED,
	BUT_NOTPRESSED
}butstat_t;

typedef struct ButtonPins
{
  GPIO_TypeDef *ButPort;
  uint16_t      ButPin;
  butstat_t		ButStat;
}but_pin_s;






/* PFP BEGIN */

HAL_StatusTypeDef EASYBUT_Init(uint8_t pin_num, GPIO_TypeDef *gpio_port, uint16_t gpio_pin);

uint8_t EASYBUT_ButtonStat(uint8_t butnum);
void EASYBUT_Handler(void);



/* PFP END */



#endif /* INC_EASYBUT_H_ */
