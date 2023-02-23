#include "easybut.h"

but_pin_s ButPin[BUT_QUANTITY];

/**
 * @brief  Set GPIO and name for button
 * @param  button name from enum (defined in .h file)
 * @param  GPIO_TypeDef - GPIO port (defined by label in Cube)
 * @param  GPIO_Pin - GPIO pin (defined by label in Cube)
 * @retval None
 */
void EASYBUT_InitButton(butname_t but_name, GPIO_TypeDef *gpio_port, uint16_t gpio_pin) {
	/* Check the parameters */
	assert_param(IS_GPIO_PIN(GPIO_Pin));
	assert_param(IS_GPIO_PIN_ACTION(PinState));

	ButPin[but_name].ButPort = gpio_port;
	ButPin[but_name].ButPin = gpio_pin;
}

/**
 * @brief  Return current pin state
 * @param  pointer to structure
 * @retval true - pressed, false - not pressed
 */
butraw_t EASYBUT_getPinState(but_pin_s *bp) {
	if (HAL_GPIO_ReadPin(bp->ButPort, bp->ButPin) == GPIO_PIN_RESET) {
		bp->ButRawStat = NowIsPressed;

		return NowIsPressed;
	} else {
		bp->ButRawStat = NowIsNotPressed;

		return NowIsNotPressed;
	}
}

/**
 * @brief  Store previous pin's state
 * @param  pointer to structure
 * @param  current pin's state
 * @retval None
 */
void EASYBUT_setPrevState(but_pin_s *bp, butraw_t state) {
	bp->ButPrevStat = state;
}

/**
 * @brief  Return previous pin's state
 * @param  pointer to structure
 * @retval true - was pressed, false - was not pressed
 */
butraw_t EASYBUT_getPrevState(but_pin_s *bp) {
	return bp->ButPrevStat;
}

/**
 * @brief  Store previous pin state to short pressed
 * @param  pointer to structure
 * @retval None
 */
void EASYBUT_setShortPress(but_pin_s *bp) {
	bp->ButStat = BUT_SHORT_PRESS;
}

/**
 * @brief  Store previous pin state to long pressed
 * @param  pointer to structure
 * @retval None
 */
void EASYBUT_setLongPress(but_pin_s *bp) {
	bp->ButStat = BUT_LONG_PRESS;
}

/**
 * @brief  Store previous pin state to not pressed
 * @param  pointer to structure
 * @retval None
 */
void EASYBUT_setNotPress(but_pin_s *bp) {
	bp->ButStat = BUT_NOT_PRESSED;
}

/**
 * @brief  Return button's counter value
 * @param  pointer to structure
 * @param  counter value
 * @retval None
 */
void EASYBUT_setCounter(but_pin_s *bp, uint16_t cnt) {
	bp->ButCounter = cnt;
}

/**
 * @brief  Return button's counter value
 * @param  pointer to structure
 * @retval Counter value (from structure)
 */
uint16_t EASYBUT_getCounter(but_pin_s *bp) {
	return bp->ButCounter;
}

/**
 * @brief  Return handled button state (without bouncing)
 * @param  pointer to structure
 * @retval Previous button state
 */
uint8_t EASYBUT_getPrevStat(but_pin_s *bp) {
	if (bp->ButPrevStat) {
		bp->ButPrevStat = 0;

		return 1;
	} else {
		return 0;
	}
}

/**
 * @brief  Check structure status flag
 * @param  pointer to structure
 * @retval short/long/no press
 */
butstat_t EASYBUT_getStatData(but_pin_s *bp) {

	return bp->ButStat;
}

/**
 * @brief  Return handled button state (without bouncing)
 * @param  None
 * @retval pressed/short/long/no press
 */
uint8_t EASYBUT_getButtonState(butname_t butname, butstat_t butstat) {

	if(EASYBUT_getStatData(&ButPin[butname]) == BUT_SHORT_PRESS && (butstat == BUT_SHORT_PRESS)){

		ButPin[butname].ButStat = BUT_POLLED; /* Avoid repeat action */
		return 1;
	}

	if(EASYBUT_getStatData(&ButPin[butname]) == BUT_LONG_PRESS && (butstat == BUT_LONG_PRESS)){
		ButPin[butname].ButStat = BUT_POLLED; /* Avoid repeat action */
		return 1;
	}

	if(EASYBUT_getStatData(&ButPin[butname]) == BUT_DOWN && (butstat == BUT_DOWN)){
		return 1;
	}

	return 0;
}

/**
 * @brief  Check button state, call it every 1ms
 * @param  None
 * @retval None
 */
void
EASYBUT_Handler (void)
{

  for (butname_t but_i = 0; but_i < BUT_QUANTITY; but_i++)
    {

      /* Poll buttons for fast reaction*/
      if(EASYBUT_getStatData(&ButPin[but_i]) != BUT_LONG_PRESS){


      if (EASYBUT_getPinState(&ButPin[but_i]) == NowIsPressed)
	{
	  ButPin[but_i].ButStat = BUT_DOWN;
	}
      else
	{
	  ButPin[but_i].ButStat = BUT_NOT_PRESSED;
	}


      }

      butraw_t cur_state = EASYBUT_getPinState (&ButPin[but_i]);
      butraw_t prev_state = EASYBUT_getPrevState (&ButPin[but_i]);
      uint16_t counter = EASYBUT_getCounter (&ButPin[but_i]);



      /************* SHORT PRESS *****************/
      if (counter >= EASYBUT_SHORT_PRESS && counter < EASYBUT_LONG_PRESS)
	{
	  if(EASYBUT_getPinState(&ButPin[but_i]) == NowIsNotPressed){ // If buttons released
	      counter = 0; /* Nullify counter */
	      EASYBUT_setShortPress(&ButPin[but_i]); // Set SHORT press flag
	  }
	}
      /*****************************************/

      /************* LONG PRESS *****************/
      if (counter >=  EASYBUT_LONG_PRESS)
	{
	  if((EASYBUT_getPinState(&ButPin[but_i]) == NowIsPressed) && (prev_state == NowIsNotPressed)){ // If buttons still pressed
	      EASYBUT_setLongPress(&ButPin[but_i]); // Set LONG press flag
	      EASYBUT_setPrevState(&ButPin[but_i], NowIsPressed);


	  }
	  if((EASYBUT_getPinState(&ButPin[but_i]) == NowIsNotPressed) && (prev_state == NowIsPressed)){ // If buttons released
	      counter = 0; /* Nullify counter */

	      EASYBUT_setPrevState(&ButPin[but_i], NowIsNotPressed);

	      /* Released after long press */
//	      EASYBUT_setLongPress(&ButPin[but_i]); // Set LONG press flag
	  }

	}
      /*****************************************/

      if ((cur_state == NowIsPressed) && (prev_state == NowIsNotPressed)){

	  if (counter < EASYBUT_LONG_PRESS){
	      counter++;
	    }
	}

      EASYBUT_setCounter (&ButPin[but_i], counter);

    }

}
