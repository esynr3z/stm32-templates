//-- Includes ------------------------------------------------------------------
#include "retarget_conf.h"

//-- Functions -----------------------------------------------------------------
#ifdef USE_RETARGET
void retarget_init()
{
    // (1) Enable the peripheral clock of GPIO Port
    RETARGET_USART_GPIO_CLK_ENABLE();
    // Configure Tx Pin as : Alternate function, High Speed, Push pull, Pull up
    LL_GPIO_SetPinMode(RETARGET_USART_TX_GPIO_PORT, RETARGET_USART_TX_PIN, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(RETARGET_USART_TX_GPIO_PORT, RETARGET_USART_TX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RETARGET_USART_TX_GPIO_PORT, RETARGET_USART_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(RETARGET_USART_TX_GPIO_PORT, RETARGET_USART_TX_PIN, LL_GPIO_PULL_UP);
    // Configure Rx Pin as : Alternate function, High Speed, Push pull, Pull up
    LL_GPIO_SetPinMode(RETARGET_USART_RX_GPIO_PORT, RETARGET_USART_RX_PIN, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinSpeed(RETARGET_USART_RX_GPIO_PORT, RETARGET_USART_RX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinOutputType(RETARGET_USART_RX_GPIO_PORT, RETARGET_USART_RX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinPull(RETARGET_USART_RX_GPIO_PORT, RETARGET_USART_RX_PIN, LL_GPIO_PULL_UP);

    // (2) Enable USART peripheral clock and clock source
    RETARGET_USART_CLK_ENABLE();

    // (3) Configure USART functional parameters
    // TX/RX direction
    LL_USART_SetTransferDirection(RETARGET_USART, LL_USART_DIRECTION_TX_RX);
    // 8 data bit, 1 start bit, 1 stop bit, no parity
    LL_USART_ConfigCharacter(RETARGET_USART, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);
    // Set Baudrate using APB frequency
    LL_USART_SetBaudRate(RETARGET_USART, RETARGET_USART_CLK, RETARGET_BAUDRATE);

    // (4) Enable USART
    LL_USART_Enable(RETARGET_USART);
}

int retarget_get_char()
{
    while (!LL_USART_IsActiveFlag_RXNE(RETARGET_USART)) {
    }
    return (int)LL_USART_ReceiveData8(RETARGET_USART);
}

int retarget_put_char(int ch)
{
    while (!LL_USART_IsActiveFlag_TXE(RETARGET_USART)) {
    }
    LL_USART_TransmitData8(RETARGET_USART, ch);
    return 0;
}
#else
void retarget_init()
{
}

int retarget_get_char()
{
    return 0;
}

int retarget_put_char(int ch)
{
    (void)ch;
    return 0;
}
#endif // USE_RETARGET
