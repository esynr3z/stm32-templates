//-- Define to prevent recursive inclusion -------------------------------------
#ifndef __MAIN_H
#define __MAIN_H

//-- Includes ------------------------------------------------------------------
#include <stdint.h>
#include "stm32f1xx_conf.h"
#include "stm32f1xx_it.h"
#include "stm32f1xx_hal_conf.h"
#include "retarget_conf.h"

//-- Exported constants --------------------------------------------------------
#define LED_PIN                           LL_GPIO_PIN_13
#define LED_GPIO_PORT                     GPIOC
#define LED_GPIO_CLK_ENABLE()             LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC)

//-- Exported variables --------------------------------------------------------
extern uint32_t APB1Clock;
extern uint32_t APB2Clock;

//-- Exported functions --------------------------------------------------------
// TIM2 update interrupt processing
void TimerUpdate_Callback(void);

#endif // __MAIN_H
