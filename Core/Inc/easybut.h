#ifndef INC_EASYBUT_H_
#define INC_EASYBUT_H_


/* Includes BEGIN */
#include "main.h"
/* Includes END */

/* Enumerations BEGIN */
typedef enum ButtonName
{
	/* SET BUTTON'S NAMES ↓: */
	/*_____________________*/
	BUT_SA2,
	BUT_SA1,
	BUT_WKUP,
	/*_____________________*/

	BUT_QUANTITY /* ← DON'T TOUCH IT! (uses to count buttons) */
}butname_t;
/* Enumerations END */


/****************************************************/

#define EASYBUT_DEBOUNCE_TIME 50 /* 50 ms, if call EASYBUT_Handler every 1 ms */
#define PIN_QUANTITY BUT_QUANTITY

/* Typedef BEGIN */
typedef enum ButtonStat
{
	BUT_PRESSED,
	BUT_NOTPRESSED
}butstat_t;

typedef enum ButtonRaw
{
	NowIsPressed,
	NowIsNotPressed
}butraw_t;

typedef struct ButtonPins
{
  GPIO_TypeDef *ButPort;
  uint16_t      ButPin;
  butstat_t		ButStat;
  butraw_t      ButRawStat;

  uint16_t		ButCounter;
  uint8_t		ButPrevStat;
}but_pin_s;

/* Typedef END */



/* Function Prototypes BEGIN */

void EASYBUT_InitButton(uint8_t pin_num, GPIO_TypeDef *gpio_port, uint16_t gpio_pin);
uint8_t EASYBUT_getButtonState(uint8_t butnum);
void EASYBUT_Handler(void);

/* Function Prototypes END */



#endif /* INC_EASYBUT_H_ */
