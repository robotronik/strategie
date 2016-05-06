#include <specific.h>

#define UART_ASSER UART7

void init_uart_asser() {
    rcc_periph_clock_enable(RCC_UART7);

    // Set up USART/UART parameters using the libopencm3 helper functions
    usart_set_baudrate      (UART7, 115200);
    usart_set_databits      (UART7, 8);
    usart_set_stopbits      (UART7, USART_STOPBITS_1);

    usart_set_mode          (UART7, USART_MODE_TX);
//    usart_set_mode(UART_ASSER, USART_MODE_TX_RX);

    usart_set_parity        (UART7, USART_PARITY_NONE);
    usart_set_flow_control  (UART8, USART_FLOWCONTROL_NONE);

    //USART_CR2(uart) |= (1 << 18);
    //usart_enable_data_inversion(uart);
    usart_enable            (UART7);

    // Enable interrupts from the USART
    nvic_enable_irq(NVIC_UART7_IRQ);
    usart_enable_rx_interrupt(UART7);

    rcc_periph_clock_enable(RCC_GPIOF);
    gpio_mode_setup(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO6);
    gpio_mode_setup(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO7);
    gpio_set_af(GPIOF, GPIO_AF8, GPIO6 | GPIO7);
}

void UART_send_message(char * buff, uint8_t buff_len) {
    console_puts(UART_ASSER, buff, buff_len);
}

#define RxBufferSize   128     // Arbitrary buffer size
char RxBuffer[RxBufferSize];
volatile int RxBufferWrite;      // Next place to store
volatile int RxBufferRead;      // Next place to read

void uart7_isr(void) {
    uint32_t    reg;
    int         i;
    do {
        reg = USART_SR(UART_ASSER);
        if (reg & USART_SR_RXNE) {
            RxBuffer[RxBufferWrite] = USART_DR(UART_ASSER);
            // Check for "overrun"
            i = (RxBufferWrite + 1) % RxBufferSize;
            if (i != RxBufferRead) {
                RxBufferWrite = i;
            }
        }
    } while ((reg & USART_SR_RXNE) != 0); // can read back-to-back interrupts
}

int UART_getc(unsigned char *c) {
    if (RxBufferRead != RxBufferWrite) {
        c = RxBuffer[RxBufferRead];
        RxBufferRead = (RxBufferRead + 1) % RxBufferSize;
        return true;
    }
    return false;
}
