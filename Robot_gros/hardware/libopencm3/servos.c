#include <specific.h>

#define UART_SERVOS     USART2
#define RCC_UART_SERVOS RCC_USART2

void init_uart_servos() {
    // MUST enable the GPIO clock in ADDITION to the USART clock
    rcc_periph_clock_enable(RCC_GPIOD);

    // On utilise PD5 pour Tx, aucune pour Rx.
    gpio_mode_setup(GPIOD,
        GPIO_MODE_AF,
        GPIO_PUPD_PULLUP,
        GPIO5);

    // Actual Alternate function number (in this case 2) is part
    // depenedent, CHECK THE DATA SHEET for the right number to use.
    gpio_set_af(GPIOD, GPIO_AF7, GPIO5);


    // This then enables the clock to the USART1 peripheral which is
    // attached inside the chip to the APB1 bus. Different peripherals
    // attach to different buses, and even some UARTS are attached to
    // APB1 and some to APB2, again the data sheet is useful here.
    rcc_periph_clock_enable(RCC_UART_SERVOS);

    // Set up USART/UART parameters using the libopencm3 helper functions
    usart_set_baudrate(UART_SERVOS, 1000000);
    usart_set_databits(UART_SERVOS, 8);
    usart_set_stopbits(UART_SERVOS, USART_STOPBITS_1);
    usart_set_mode(UART_SERVOS, USART_MODE_TX);
    usart_set_parity(UART_SERVOS, USART_PARITY_NONE);
    usart_set_flow_control(UART_SERVOS, USART_FLOWCONTROL_NONE);
    usart_enable(UART_SERVOS);

    // Enable interrupts from the USART
    nvic_enable_irq(NVIC_USART2_IRQ);

    // Specifically enable recieve interrupts
    usart_enable_rx_interrupt(UART_SERVOS);

    // Pour que les servos aient le temps de s'initialiser
    delay_ms(550);
}

void send_servo(char * buff, uint8_t buff_len) {
    console_puts(UART_SERVOS, buff, buff_len);
    delay_ms(30);
}

void bras_gauche_set_angle(int angle) {
}


void bras_droit_set_angle(int angle) {
}


void porte_empileur_set_angle(int angle) {
}

void attrape_popcorns_set_angle(int angle) {
}


//init
void init_bras_gauche() {
}

void init_bras_droit() {
}

void init_porte_empileur() {
}

void init_attrape_popcorns() {
}
