#include <specific.h>
#include "../capteurUS.h"


// Les 2 capteurs
capteurUSBuffer capteur_front  = {.value = 255, .buffer = 0, .bufferPos = -1}; // UART5
capteurUSBuffer capteur_bottom = {.value = 255, .buffer = 0, .bufferPos = -1}; // UART8

int capteur_en_cours_de_reception = 0;


// 25.4 mm par inch
int getDistance_front() {
  return capteur_front.value * 25.4;
}

int getDistance_bottom() {
  return capteur_bottom.value * 25.4;
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
    init_uart_capteur_US(UART5, RCC_UART5, NVIC_UART5_IRQ);
    init_uart_capteur_US(UART8, RCC_UART8, NVIC_UART8_IRQ);

    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOD);
    rcc_periph_clock_enable(RCC_GPIOE);

    gpio_mode_setup(GPIOC, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO12);
    gpio_mode_setup(GPIOD, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2);
    gpio_set_af(GPIOC, GPIO_AF8, GPIO12);
    gpio_set_af(GPIOD, GPIO_AF8, GPIO2);

    gpio_mode_setup(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO0 | GPIO1);
    gpio_set_af(GPIOE, GPIO_AF8, GPIO0 | GPIO1);
}


// Retourne 0 si pas fini, autre si fini (-1 si erreur, sinon la distance)
int capteurRead(char c, capteurUSBuffer *capteur) {
    switch (capteur->bufferPos) {
    case -1:
        if (c == 'R') {
            capteur->bufferPos = 0;
            capteur->buffer = 0;
            return 0;
        } else {
            return 0;
        }
    case 3:
        if (c == '\r') { // Carriage return
            capteur->bufferPos = -1;
            capteur->value = capteur->buffer;
            if (capteur_en_cours_de_reception == 1)
                gpio_clear(GPIOC, GPIO10);
            return capteur->value;
        } else {
            capteur->bufferPos = -1;
            return -1;
        }
    case 2:
        if (capteur_en_cours_de_reception == 1)
            gpio_set(GPIOC, GPIO10);
    default:
        if (c >= '0' && c <= '9') {
            capteur->bufferPos++;
            capteur->buffer = capteur->buffer * 10 + (c-'0');
            return 0;
        } else {
            capteur->bufferPos = -1;
            return -1;
        }
    }
}

void uart5_isr(void) {
    if (USART_SR(UART5) & USART_SR_RXNE) {
        int readState = capteurRead(USART_DR(UART5), &capteur_front);
        if (readState != 0) {
            // On a fini de lire ce capteur, avec ou sans erreur, on s'en balek.
            // Yolo.
        }
    }
}

void uart8_isr(void) {
    if (USART_SR(UART8) & USART_SR_RXNE) {
        int readState = capteurRead(USART_DR(UART8), &capteur_bottom);
        if (readState != 0) {
            // On a fini de lire ce capteur, avec ou sans erreur, on s'en balek.
            // Yolo.
        }
    }
}

/*


// Attention, envoie sur le canal UART de l'asser ! uniquement en débug
void send_to_pc (capteurUSBuffer* capteur, char c) {
    char buffer[10];
    buffer[0] = ' ';
    buffer[1] = (capteur->value/1000) %10 + '0';
    buffer[2] = (capteur->value/100 ) %10 + '0';
    buffer[3] = (capteur->value/10  ) %10 + '0';
    buffer[4] = (capteur->value/1   ) %10 + '0';
    buffer[5] = ' ';
    buffer[6] = c;
    buffer[7] = ' ';
    console_puts(UART7, buffer, 8);
}
void send_to_pc_end() {
    char buffer[2];
    buffer[0] = '\r';
    console_puts(UART7, buffer, 1);
}
*/
