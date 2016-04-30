#include <specific.h>

#define UART_SERVOS USART2

void init_all_servo() {
    // MUST enable the GPIO clock in ADDITION to the USART clock
    rcc_periph_clock_enable(RCC_GPIOD);

    // On utilise PD5 pour Tx, aucune pour Rx.
    gpio_mode_setup(GPIOD,
        GPIO_MODE_AF,
        GPIO_PUPD_NONE,
        GPIO5);

    // Actual Alternate function number (in this case 2) is part
    // depenedent, CHECK THE DATA SHEET for the right number to use.
    gpio_set_af(GPIOD, GPIO_AF7, GPIO5);


    // This then enables the clock to the USART1 peripheral which is
    // attached inside the chip to the APB1 bus. Different peripherals
    // attach to different buses, and even some UARTS are attached to
    // APB1 and some to APB2, again the data sheet is useful here.
    rcc_periph_clock_enable(RCC_USART2);

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
}



static void console_putc(char c) {
    uint32_t    reg;
    do {
        reg = USART_SR(UART_SERVOS);
    } while ((reg & USART_SR_TXE) == 0);
    USART_DR(UART_SERVOS) = (uint16_t) c & 0xff;
}

void send_servo(char * buff, uint8_t buff_len) {
    for (int i = 0; i < buff_len; ++i) {
        console_putc(*buff);
        buff++;
    }
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
