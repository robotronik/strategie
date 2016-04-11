#include "specific.h"
// Mapping. Useful for direct pinout access
#include "../../../mapping/IO_pinout.h"
#include "../../../mapping/PWM_pinout.h"



void init_hardware() {
    init_RTC();

    init_pin_mode(IO1_PORT, IO1_PIN, GPIO_MODE_INPUT, GPIO_PULLUP); // Tirette
    init_pin_mode(IO6_PORT, IO6_PIN, GPIO_MODE_INPUT, GPIO_PULLUP); // Choix de couleur
    init_pin_mode(IO7_PORT, IO7_PIN, GPIO_MODE_INPUT, GPIO_NOPULL); //pin de retour de l'asservissement

    init_UART_Asser(&UART_Asser);
    //init_EOM_timer();


    init_sensor1();
    init_sensor2();
}


int read_tirette() {
    return read_pin(IO1_PORT, IO1_PIN);
}

int read_color_button() {
    return read_pin(IO6_PORT, IO6_PIN);
}

int read_asser_done() {
    return !read_pin(IO7_PORT, IO7_PIN);
}

void active_capteurUS_1() {
    activate_sensor1();
}

void active_capteurUS_2() {
    activate_sensor2();
}

void arret_capteurs() {
    HAL_NVIC_DisableIRQ(TIM5_IRQn);
}

void led_verte_on() {
    HAL_GPIO_WritePin(GPIOD, LED_VERTE, GPIO_PIN_RESET);
}
void led_verte_off() {
    HAL_GPIO_WritePin(GPIOD, LED_VERTE, GPIO_PIN_SET);
}
