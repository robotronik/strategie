#include <specific.h>

typedef struct {
    int value;
    int buffer;
    int bufferPos;
} capteurUSBuffer;

capteurUSBuffer capteur1 = {.value = 255, .buffer = 0, .bufferPos = -1};
capteurUSBuffer capteur2 = {.value = 255, .buffer = 0, .bufferPos = -1};
capteurUSBuffer capteur3 = {.value = 255, .buffer = 0, .bufferPos = -1};
capteurUSBuffer capteur4 = {.value = 255, .buffer = 0, .bufferPos = -1};


// 25.4 mm par inch
int capteurUS1_get_distance() { return capteur1.value * 25.4;
}


void test_uart_capteur1() {
    if (capteur1.value == 255)
        return;
    char buffer[6];
    buffer[0] = 'A';
    buffer[1] = (capteurUS1_get_distance()/1000) %10 + '0';
    buffer[2] = (capteurUS1_get_distance()/100 ) %10 + '0';
    buffer[3] = (capteurUS1_get_distance()/10  ) %10 + '0';
    buffer[4] = (capteurUS1_get_distance()/1   ) %10 + '0';
    buffer[5] = '\n';
    buffer[6] = '\r';
    console_puts(UART4, buffer, 7);
}

int capteurUS2_get_distance() { return capteur2.value * 25.4;
}
int capteurUS3_get_distance() { return capteur3.value * 25.4;
}
int capteurUS4_get_distance() { return capteur4.value * 25.4;
}

void init_uart_capteur_US(int uart, int rcc, int nvic_irq) {
    rcc_periph_clock_enable(rcc);

    // Set up USART/UART parameters using the libopencm3 helper functions
    usart_set_baudrate      (uart, 9600);
    usart_set_databits      (uart, 8);
    usart_set_stopbits      (uart, USART_STOPBITS_1);
    usart_set_mode          (uart, USART_MODE_TX_RX);
    usart_set_parity        (uart, USART_PARITY_NONE);
    usart_set_flow_control  (uart, USART_FLOWCONTROL_NONE);

    //USART_CR2(uart) |= (1 << 18);
    //usart_enable_data_inversion(uart);
    usart_enable            (uart);

    // Enable interrupts from the USART
    nvic_enable_irq(nvic_irq);
    usart_enable_rx_interrupt(uart);
}

void init_capteurs_US() {
    init_uart_capteur_US(UART4, RCC_UART4, NVIC_UART4_IRQ);

    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO10 | GPIO11);
    gpio_set_af(GPIOC, GPIO_AF8, GPIO10 | GPIO11);


    init_uart_capteur_US(UART5, RCC_UART5, NVIC_UART5_IRQ);

    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOD);
    gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO12);
    gpio_mode_setup(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
    gpio_set_af(GPIOC, GPIO_AF8, GPIO12);
    gpio_set_af(GPIOD, GPIO_AF8, GPIO2);


    init_uart_capteur_US(UART7, RCC_UART7, NVIC_UART7_IRQ);

    rcc_periph_clock_enable(RCC_GPIOF);
    gpio_mode_setup(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO7 | GPIO6);
    gpio_set_af(GPIOF, GPIO_AF8, GPIO7 | GPIO6);


    init_uart_capteur_US(UART8, RCC_UART8, NVIC_UART8_IRQ);

    rcc_periph_clock_enable(RCC_GPIOE);
    gpio_mode_setup(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO1 | GPIO0);
    gpio_set_af(GPIOE, GPIO_AF8, GPIO1 | GPIO0);
}

void capteurRead(char c, capteurUSBuffer *capteur) {
    switch (capteur->bufferPos) {
    case -1:
        if (c == 'R') {
            capteur->bufferPos = 0;
            capteur->buffer = 0;
        }
        break;
    case 3:
        if (c == '\r') { // Carriage return
            capteur->bufferPos = -1;
            capteur->value = capteur->buffer;
        } else
            capteur->bufferPos = -1;
        break;
    default:
        if (c >= '0' && c <= '9') {
            capteur->bufferPos++;
            capteur->buffer = capteur->buffer * 10 + (c-'0');
        } else
            capteur->bufferPos = -1;
        break;
    }
}


void common_usart_isr(uint32_t usart, capteurUSBuffer *capteur) {
    if (USART_SR(usart) & USART_SR_RXNE)
        capteurRead(USART_DR(usart), capteur);
}

// Individual ISR's for the serial ports just redirect
void uart4_isr(void) {
    common_usart_isr(UART4, &capteur1);
}
void uart5_isr(void) {
    common_usart_isr(UART5, &capteur2);
}
void uart7_isr(void) {
    common_usart_isr(UART7, &capteur3);
}
void uart8_isr(void) {
    common_usart_isr(UART8, &capteur4);
}
