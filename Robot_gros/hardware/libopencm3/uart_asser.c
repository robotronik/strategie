#include <specific.h>

#define UART_ASSER      USART1
#define RCC_UART_ASSER  RCC_USART1

void init_uart_asser() {
    // This then enables the clock to the USART1 peripheral which is
    // attached inside the chip to the APB1 bus. Different peripherals
    // attach to different buses, and even some UARTS are attached to
    // APB1 and some to APB2, again the data sheet is useful here.
    rcc_periph_clock_enable(RCC_UART_ASSER);
    // MUST enable the GPIO clock in ADDITION to the USART clock
    rcc_periph_clock_enable(RCC_GPIOA);

    // On utilise PD5 pour Tx, aucune pour Rx.
    gpio_mode_setup(GPIOB,
        GPIO_MODE_AF,
        GPIO_PUPD_NONE,
        GPIO9 | GPIO10);

    // Actual Alternate function number (in this case 7) is part
    // depenedent, CHECK THE DATA SHEET for the right number to use.
    gpio_set_af(GPIOA, GPIO_AF7, GPIO9 | GPIO10);

    // Set up USART/UART parameters using the libopencm3 helper functions
    usart_set_baudrate(UART_ASSER, 115200);
    usart_set_databits(UART_ASSER, 8);
    usart_set_stopbits(UART_ASSER, USART_STOPBITS_1);
    usart_set_mode(UART_ASSER, USART_MODE_TX_RX);
    usart_set_parity(UART_ASSER, USART_PARITY_NONE);
    usart_set_flow_control(UART_ASSER, USART_FLOWCONTROL_NONE);
    usart_enable(UART_ASSER);

    // Enable interrupts from the USART
    nvic_enable_irq(NVIC_USART2_IRQ);

    // Specifically enable recieve interrupts
    usart_enable_rx_interrupt(UART_ASSER);
}

void UART_send_message(char * buff, uint8_t buff_len) {
    console_puts(UART_ASSER, buff, buff_len);
}

