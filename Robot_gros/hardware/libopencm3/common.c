#include <specific.h>
#include <setup.h>
#include "leds.h"
#include "alarms_and_delay.h"
#include "common.h"

void init_hardware() {
    clock_setup();

    gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, GPIO0); // Bouton User
    gpio_mode_setup(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO2); // Tirette
    gpio_mode_setup(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO9); // Choix de couleur
    gpio_mode_setup(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_NONE,   GPIO10); //pin de retour de l'asservissement

    init_alarms_and_delay();
    init_leds();
    init_leds_debug();
    //init_RTC();

    //init_pwm_timer(TIM4, 1000);

    //init_UART_Asser(&UART_Asser);
    //init_EOM_timer();


    //init_sensor1();
    //init_sensor2();
}

int read_user_button() {
    return gpio_get(GPIOA, GPIO0);
}

int read_tirette() {
    return gpio_get(GPIOE, GPIO2);
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

void init_leds_debug(){
  rcc_periph_clock_enable(RCC_GPIOE);

  gpio_mode_setup(GPIOE, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO3 | GPIO4 | GPIO5 | GPIO6);
}

void set_leds(){
  gpio_set(GPIOE, GPIO3 | GPIO4 | GPIO5 | GPIO6);
}

void clear_leds(){
  gpio_clear(GPIOE, GPIO3 | GPIO4 | GPIO5 | GPIO6);
}

void set_ledBleue(){
  gpio_set(GPIOE, GPIO3);
}

void set_ledOrange(){
  gpio_set(GPIOE, GPIO5);
}

void set_ledVerte(){
  gpio_set(GPIOE, GPIO6);
}

void set_ledRouge(){
  gpio_set(GPIOE, GPIO4);
}

void clear_ledBleue(){
  gpio_clear(GPIOE, GPIO3);
}

void clear_ledOrange(){
  gpio_clear(GPIOE, GPIO5);
}

void clear_ledVerte(){
  gpio_clear(GPIOE, GPIO6);
}

void clear_ledRouge(){
  gpio_clear(GPIOE, GPIO4);
}
