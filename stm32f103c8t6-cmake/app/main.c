//-- Includes ------------------------------------------------------------------
#include "main.h"

//-- Global variables ----------------------------------------------------------
uint32_t APB1Clock = HSI_VALUE;
uint32_t APB2Clock = HSI_VALUE;

//-- Periph init ---------------------------------------------------------------
void sysclk_init(void)
{
    // Set FLASH latency
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_2);

    // Enable HSE oscillator
    LL_RCC_HSE_Enable();
    while (LL_RCC_HSE_IsReady() != 1) {
    };

    // Main PLL configuration and activation
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE_DIV_1, LL_RCC_PLL_MUL_9);
    LL_RCC_PLL_Enable();
    while (LL_RCC_PLL_IsReady() != 1) {
    };

    // Sysclk activation on the main PLL
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
    };

    // Update CMSIS variable
    SystemCoreClockUpdate();

    // Set APB1 & APB2 prescaler
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);
    APB1Clock = SystemCoreClock / 2;
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
    APB2Clock = SystemCoreClock / 1;
}

void gpio_init(void)
{
    LED_GPIO_CLK_ENABLE();
    LL_GPIO_SetPinMode(LED_GPIO_PORT, LED_PIN, LL_GPIO_MODE_OUTPUT);
}

void tim_init(void)
{
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

    // Set the pre-scaler value to have TIM2 counter clock equal to 10 kHz from PCLK1
    LL_TIM_SetPrescaler(TIM2, __LL_TIM_CALC_PSC(APB1Clock, 10000));

    // Set the auto-reload value to have an initial update event frequency of 4 Hz
    LL_TIM_SetAutoReload(TIM2, __LL_TIM_CALC_ARR(APB1Clock, LL_TIM_GetPrescaler(TIM2), 4));

    // Enable the update interrupt
    LL_TIM_EnableIT_UPDATE(TIM2);
    NVIC_SetPriority(TIM2_IRQn, 0);
    NVIC_EnableIRQ(TIM2_IRQn);

    // Enable counter
    LL_TIM_EnableCounter(TIM2);

    // Force update generation
    LL_TIM_GenerateEvent_UPDATE(TIM2);
}

void mco_init(void)
{
    // MCO Clock Enable
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);

    // Configure the MCO pin in alternate function mode
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_HIGH);

    // Configure MCO
    LL_RCC_ConfigMCO(LL_RCC_MCO1SOURCE_SYSCLK);
}

void periph_init()
{
    // Configure the system clock to 72 MHz
    mco_init();
    sysclk_init();
    // Configure retarget
    retarget_init();
    // Configure GPIO and TIM for LED
    gpio_init();
    tim_init();
}

//-- Application ---------------------------------------------------------------
int main(void)
{
    periph_init();
    printf("Hello from STM32F103 running on %d Hz!\n", (int)SystemCoreClock);

    while (1) {
    }
}

void TimerUpdate_Callback(void)
{
    LL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN);
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
    printf("Wrong parameters value: file %s on line %d", file, (int)line);
    while (1) {
    }
}
#endif
