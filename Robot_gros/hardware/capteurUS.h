#ifndef CAPTEUR_US_H
#define CAPTEUR_US_H

typedef struct {
    int value;
    int buffer;
    int bufferPos;
} capteurUSBuffer;

void adversaire_detecte_callback();
void init_capteurs_US();
void init_uart_capteur_US(int uart, int rcc, int nvic_irq);

#endif
