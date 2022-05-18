#include "easybut.h"

but_pin_s ButPin[PIN_QUANTITY];

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
 * @brief  Store previous pin's state
 * @param  pointer to structure
 * @retval None
 */
void EASYBUT_setShortPress(but_pin_s *bp) {
	bp->ButStat = BUT_SHORT_PRESS;
}

void EASYBUT_setLongPress(but_pin_s *bp) {
	bp->ButStat = BUT_LONG_PRESS;
}

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
 * @retval short/long/no press
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
 * @brief  Check button, call it every 1ms
 * @param  None
 * @retval None
 */
void EASYBUT_Handler(void) {

	for (uint8_t i = 0; i < PIN_QUANTITY; i++) {


		if(EASYBUT_getPinState(&ButPin[i]) == NowIsPressed){
			ButPin[i].ButStat = BUT_DOWN;
		}

		if (EASYBUT_getPinState(&ButPin[i]) != EASYBUT_getPrevState(&ButPin[i])) {

			uint16_t counter = EASYBUT_getCounter(&ButPin[i]);

			if (counter <= EASYBUT_SHORT_PRESS+1) {
				counter++;
			}

/************* SHORT PRESS *****************/
			if (counter >= EASYBUT_SHORT_PRESS && counter < EASYBUT_LONG_PRESS) {

				EASYBUT_setPrevState(&ButPin[i], EASYBUT_getPinState(&ButPin[i]));

				if (EASYBUT_getPinState(&ButPin[i]) == NowIsPressed) { /* If still pressed */

					EASYBUT_setShortPress(&ButPin[i]); // Set SHORT press flag

					ButPin[i].ButLongFlag = 1; // Allow to count
				}
			}
/*****************************************/

			EASYBUT_setCounter(&ButPin[i], counter);

		} else {

				if(EASYBUT_getPinState(&ButPin[i]) == NowIsPressed && ButPin[i].ButLongFlag){ /* Still pressed and flag short_press was setter */

					volatile uint16_t counter = EASYBUT_getCounter(&ButPin[i]);

					if (counter <= EASYBUT_LONG_PRESS+1) {
						counter++;
					}

			/************* LONG PRESS *****************/
						if (counter >= EASYBUT_LONG_PRESS) {

							ButPin[i].ButLongFlag = 0;

							if (EASYBUT_getPinState(&ButPin[i]) == NowIsPressed) { /* If still pressed */

								EASYBUT_setLongPress(&ButPin[i]); // Set LONG press flag

								counter = 0;
							}
						}
			/*****************************************/

						EASYBUT_setCounter(&ButPin[i], counter);


				}
				if(EASYBUT_getPinState(&ButPin[i]) == NowIsNotPressed){ /* Released */
					ButPin[i].ButLongFlag = 0;
					EASYBUT_setNotPress(&ButPin[i]);
					EASYBUT_setCounter(&ButPin[i], 0);
				}




		}
	}

}
