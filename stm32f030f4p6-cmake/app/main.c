
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32f0xx.h"
#include "system_stm32f0xx.h"

/* Defines -------------------------------------------------------------------*/
#define DEBUG_LED_PORT  GPIOA
#define DEBUG_LED_PIN   4
#define DEBUG_LED_SET   DEBUG_LED_PORT->BSRR = 1<<DEBUG_LED_PIN
#define DEBUG_LED_CLR   DEBUG_LED_PORT->BRR = 1<<DEBUG_LED_PIN

/* Functions prototypes ------------------------------------------------------*/
void debug_led_init();

/* Functions -----------------------------------------------------------------*/
void PeriphInit()
{
    debug_led_init();
}

int main()
{
    PeriphInit();

    while(1)
    {
        DEBUG_LED_SET;
        for(volatile uint32_t i=0;i<1000000;i++);
        DEBUG_LED_CLR;
        for(volatile uint32_t i=0;i<1000000;i++);
    }
    return 0;
}

/* DEBUG LED */
void debug_led_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // Configure PA4 in output pushpull mode
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(DEBUG_LED_PORT, &GPIO_InitStructure);
}

void assert_failed(uint8_t* file, uint32_t line)
{
    while(1);
}