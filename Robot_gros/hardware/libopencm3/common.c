#include "specific.h"

#include "leds.h"
#include "alarms_and_delay.h"

void init_hardware() {
    clock_setup();


    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOD);
    rcc_periph_clock_enable(RCC_GPIOE);

    gpio_mode_setup(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO4); // Tirette
    gpio_mode_setup(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO9); // Choix de couleur
    gpio_mode_setup(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_NONE,   GPIO10); //pin de retour de l'asservissement

    init_alarms_and_delay();
    init_leds();

    //init_UART_Asser(&UART_Asser);
    //init_EOM_timer();


    //init_sensor1();
    //init_sensor2();
}


int read_tirette() {
    return gpio_get(GPIOE, GPIO4);
}

int read_color_button() {
    return gpio_get(GPIOE, GPIO9);
}

int read_asser_done() {
    return !gpio_get(GPIOE, GPIO10);
}

void active_capteurUS_1() {
  //  activate_sensor1();
}

void active_capteurUS_2() {
  //  activate_sensor2();
}

void arret_capteurs() {
  //  HAL_NVIC_DisableIRQ(TIM5_IRQn);
}
