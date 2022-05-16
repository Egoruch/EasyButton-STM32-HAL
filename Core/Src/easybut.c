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
uint8_t EASYBUT_getPinState(but_pin_s *bp) {
	if (HAL_GPIO_ReadPin(bp->ButPort, bp->ButPin) == GPIO_PIN_RESET) {
		bp->ButRawStat = NowIsPressed;

		return 1;
	} else {
		bp->ButRawStat = NowIsNotPressed;

		return 0;
	}
}

/**
 * @brief  Store previous pin's state
 * @param  pointer to structure
 * @param  current pin's state
 * @retval None
 */
void EASYBUT_setPrevState(but_pin_s *bp, uint8_t state) {
	bp->ButPrevStat = state;
}

/**
 * @brief  Return previous pin's state
 * @param  pointer to structure
 * @retval true - was pressed, false - was not pressed
 */
uint8_t EASYBUT_getPrevState(but_pin_s *bp) {
	return bp->ButPrevStat;
}

/**
 * @brief  Store previous pin's state
 * @param  pointer to structure
 * @retval None
 */
void EASYBUT_setButPressed(but_pin_s *bp) {
	bp->ButStat = BUT_PRESSED;
}


void EASYBUT_setButNotPressed(but_pin_s *bp) {
	bp->ButStat = BUT_NOTPRESSED;
}

/**
 * @brief  Return button's counter value
 * @param  pointer to structure
 * @param  counter value
 * @retval None
 */
void EASYBUT_setCounter(but_pin_s *bp, uint8_t cnt) {
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
 * @brief  Check structure press flasg and reset if, if it true
 * @param  pointer to structure
 * @retval true if pressed, false if not pressed
 */
uint8_t EASYBUT_getStatData(but_pin_s *bp) {
	if (bp->ButStat == BUT_PRESSED) {
		bp->ButStat = BUT_NOTPRESSED;

		return 1;
	} else {
		return 0;
	}
}

/**
 * @brief  Return handled button state (without bouncing)
 * @param  None
 * @retval true - pressed, false - not pressed
 */
uint8_t EASYBUT_getButtonState(butname_t butname) {
	if (EASYBUT_getStatData(&ButPin[butname])) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * @brief  Check button, call it every 1ms
 * @param  None
 * @retval None
 */
void EASYBUT_Handler(void) {

	for (uint8_t i = 0; i < PIN_QUANTITY; i++) {
		uint8_t curstate = EASYBUT_getPinState(&ButPin[i]); // read gpio raw value

		if (curstate != EASYBUT_getPrevState(&ButPin[i])) {

			uint16_t counter = EASYBUT_getCounter(&ButPin[i]);

			if (counter < EASYBUT_DEBOUNCE_TIME) {
				counter++;
			}

			if (counter >= EASYBUT_DEBOUNCE_TIME) {

				EASYBUT_setPrevState(&ButPin[i], curstate);

				/* If the button still pressed (not released), tell main so */
				if (EASYBUT_getPinState(&ButPin[i]) != 0) {
					EASYBUT_setButPressed(&ButPin[i]);
					EASYBUT_setCounter(&ButPin[i], 0);
				}
			}

			EASYBUT_setCounter(&ButPin[i], counter);

		} else {

			EASYBUT_setButNotPressed(&ButPin[i]);
			EASYBUT_setCounter(&ButPin[i], 0);
		}

//		ButPin[i]->ButPin

	}

}
