#ifndef RETARGET_CONF_H
#define RETARGET_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

//-- Includes ------------------------------------------------------------------
#include "main.h"
#include <stdio.h>

//-- Defines -------------------------------------------------------------------

#ifdef USE_RETARGET
#define RETARGET_USART USART1
#define RETARGET_USART_CLK_ENABLE() LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1)

#define RETARGET_USART_GPIO_CLK_ENABLE() LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA)
#define RETARGET_USART_TX_PIN LL_GPIO_PIN_9
#define RETARGET_USART_TX_GPIO_PORT GPIOA
#define RETARGET_USART_RX_PIN LL_GPIO_PIN_10
#define RETARGET_USART_RX_GPIO_PORT GPIOA
#define RETARGET_USART_CLK APB2Clock

#ifndef RETARGET_BAUDRATE
#define RETARGET_BAUDRATE 115200
#endif
#else
#define printf(...) ((void)0)
#endif // USE_RETARGET

//-- Functions -----------------------------------------------------------------
void retarget_init(void);
int retarget_get_char(void);
int retarget_put_char(int ch);

#ifdef __cplusplus
}
#endif

#endif // RETARGET_CONF_H
