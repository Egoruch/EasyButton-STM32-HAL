#ifndef INC_EASYBUT_H_
#define INC_EASYBUT_H_


/* Includes BEGIN */
#include "main.h"
/* Includes END */

///* Enumerations BEGIN */


/* E X A M P L E */
//typedef enum ButtonName
//{
//	/* SET BUTTON'S NAMES ↓: */
//	/*_____________________*/
//	BUT_SA2,
//	BUT_SA1,
//	BUT_WKUP,
//	/*_____________________*/
//
//	BUT_QUANTITY /* ← DON'T TOUCH IT! (uses to count buttons) */
//}butname_t;


///* Enumerations END */


/****************************************************/

/* Default values, dont't touch it */
#define EASYBUT_SHORT_PRESS 50 /* 50 ms, if call EASYBUT_Handler every 1 ms */
#define EASYBUT_LONG_PRESS 500 /* ms */


/* Typedef BEGIN */
typedef enum ButtonStat
{
	BUT_NOT_PRESSED = 0, // don't modify that, because default value is 0
	BUT_SHORT_PRESS,
	BUT_SHORT_AFTER_PRESS,
	BUT_LONG_PRESS,
	BUT_LONG_AFTER_PRESS,
	BUT_DOWN,
	BUT_POLLED
}butstat_t;

typedef enum ButtonRaw
{
	NowIsNotPressed,
	NowIsPressed
}butraw_t;

typedef struct ButtonPins
{
  GPIO_TypeDef *ButPort;
  uint16_t      ButPin;
  butstat_t	ButStat;
  butraw_t      ButRawStat;

  uint16_t		ButCounter;
  butraw_t		ButPrevStat;
  uint8_t		ButLongFlag;
}but_pin_s;


typedef struct ButtonData
{
  uint32_t ButLongPress_ms;
  uint32_t ButShortPress_ms;
}but_data_s;

/* Typedef END */



/* Function Prototypes BEGIN */

void EASYBUT_InitButton(uint8_t pin_num, GPIO_TypeDef *gpio_port, uint16_t gpio_pin);
uint8_t EASYBUT_getButtonState(butname_t butname, butstat_t butstat);
void EASYBUT_Handler(void);

/* Function Prototypes END */



#endif /* INC_EASYBUT_H_ */
