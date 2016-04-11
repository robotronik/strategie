#include "specific.h"


void init_hardware() {
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_GPIOD);
    rcc_periph_clock_enable(RCC_GPIOE);

    gpio_mode_setup(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO4); // Tirette
    gpio_mode_setup(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO9); // Choix de couleur
    gpio_mode_setup(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_NONE,   GPIO10); //pin de retour de l'asservissement

    /* Set GPIO12-15 (in GPIO port D) to 'output push-pull' for leds. */
    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT,
            GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);

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

void led_verte_on() {
    gpio_set(GPIOD, GPIO12 | GPIO14);
}
void led_verte_off() {
    gpio_clear(GPIOD, GPIO12 | GPIO14);

}

void set_all_led() {

}
void test_led() {

}

void delay_ms() {

}
