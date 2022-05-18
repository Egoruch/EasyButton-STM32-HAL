# EasyButton-STM32-HAL

Simple library to handle buttons with convenient usage pin's labels (set in Cube) and HAL.
![Config pin as input and set gpio label](/Images/easybutton_library.svg)
# How to use?

 1. Add *easybutton.c* to **Src** and *easybutton.h* to **Inc**
![add .c and h. file](/Images/src_inc_add.png)
 2. Configure required pin as **GPIO_Input** (left click) and set **label** (right click). Must be pull-upped and short on ground!
![Config pin as input and set gpio label](/Images/gpio_input_user_label.png)
I have three pins for three buttons:
![Configured pins for buttons](/Images/three_buttons_cube.png)
 3. Include *easybut.h* in **main.c**:
```
 /* USER CODE BEGIN Includes */
#include "easybut.h"
/* USER CODE END Includes */
```
 4. Open *easybut.h* (right clock -> Open Decralation) and write down unique button's names.
```
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
   ```
 5. Initialize buttons
```
  /* USER CODE BEGIN 2 */
  EASYBUT_InitButton(BUT_SA1, SA1_BUT_GPIO_Port, SA1_BUT_Pin);
  EASYBUT_InitButton(BUT_SA2, SA2_BUT_GPIO_Port, SA2_BUT_Pin);
  EASYBUT_InitButton(BUT_WKUP, WKUP_GPIO_Port, WKUP_Pin);
  /* USER CODE END 2 */
  ```
   6. Call **EASYBUT_Handler()** every *1 ms* (e.g. in timer's interrupt or FreeRTOS task).
```
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
        if(htim->Instance == TIM9)
 {
	EASYBUT_Handler();
 }
}
```
   7.  Poll button state and execute requirement code, if it return 1.
```
if(EASYBUT_getButtonState(BUT_SA2, BUT_SHORT_PRESS))
{
	HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}
```
# Working demonstrating

# TODO
 - [x] Short press, long press
 - [ ]  Polarity choose
 - [ ] Very long press
