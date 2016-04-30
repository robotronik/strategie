#include <stdint.h>
// Pathfinding
#include "../../cartographie/cartographie.h"

// Actions, etc
#include <UART.h>
#include <alarms_and_delay.h>
#include "actions.h"
#include "actionneurs.h"
#include "reception_communication.h"
#include "hardware/common.h"
#include "hardware/capteurUS.h"
#include "hardware/empileur.h"


#include "xl_320.h"
#include "hardware/servos.h"


int called_test_led = 0;
void callback_test_led() {
    called_test_led = 1;
}

int mainTest() {

    /*
    // Blink the LEDs (PD12, PD13, PD14 and PD15) on the board.
    add_alarm(1400, callback_test_led);

    test_led();

    //add_alarm(false, 1500, callback_alarm);
    //add_alarm(false, 1000, callback_alarm);

    while(1) {
        if (called_test_led == 1) {
            //callback_test_led = 0;
            test_led();
        }
        for (int i = 0; i < 10000; ++i)
        {
            __asm__("nop");
        }
    }
    */

/*
    // UART test pour les servos
    init_all_servo();

    test_led();

    XL_320_socket_t my_socket1;
    init_socket(&my_socket1,&send_servo);
    XL_320_servo_t my_servo1;
    init_servo(&my_servo1,0x00,&my_socket1);


    disable_power_servo(&my_servo1, 1);
    set_control_mode_servo(&my_servo1, JOIN_MODE, 1);
    enable_power_servo(&my_servo1, 1);

    set_speed_servo(&my_servo1, 1023, 1);

    set_led_color_servo(&my_servo1,LED_BLUE,1);
    set_angle_servo(&my_servo1, 0, 1);
    delay_ms(1000);

    set_led_color_servo(&my_servo1,LED_YELLOW,1);
    set_angle_servo(&my_servo1, 60, 1);
    delay_ms(1000);

    disable_power_servo(&my_servo1, 1);
    set_control_mode_servo(&my_servo1, WHEEL_MODE, 1);
    enable_power_servo(&my_servo1, 1);

    set_led_color_servo(&my_servo1,LED_GREEN,1);
    set_speed_servo(&my_servo1, 123, 1);

    test_led();
*/


    // Test UART Asser
    init_uart_asser();
    test_led();
    //while(1)
    UART_send_message("auieauie", 8);


    /*pathfinding_init();

    int on_a_un_chemin;
    // Benchmark de la cartographie
    for (int i = 0; i < 20; ++i)
        on_a_un_chemin = pathfinding(500,1500,500,1501);

    if (on_a_un_chemin)
        HAL_GPIO_TogglePin(GPIOD, LED_VERTE);
    else
        HAL_GPIO_TogglePin(GPIOD, LED_ORANGE);

    for (int i = 0; i < return_length_of_path_found(); ++i) {
        HAL_GPIO_TogglePin(GPIOD, LED_BLEUE);
        delay_ms(500);
        HAL_GPIO_TogglePin(GPIOD, LED_BLEUE);
        delay_ms(500);
    }*/
    return 0;
}

void gestion_rupteurs() {
    /*if(rupteur_pied_empileur_is_pushed()) {
        descend_ascenseur();
        monte_pied();
    }*/
}

void gestion_communication() {
    if (read_asser_done())
        set_asser_done();
}

int mainStrategieRobot2A() {
    // Initialisation des différents machins
    init_reception_communication();

    init_actionneurs();


    if (read_color_button()) //on regarde notre couleur
        inverse_couleur(); //ici on change si on est en vert

    while(read_tirette()); // On attend la tirette

    // On met en route le timer 90 secondes
    //activate_EOM_timer();
    test_led();

    active_capteurUS_1();
    active_capteurUS_2();

    delay_ms(10);

    // Voilà, maintenant on peut s'amuser !



    while(1)
    {
        gestion_rupteurs();
        gestion_communication();

        gestion_actions();
    }

    return 0;
}

int main() {
    init_hardware();
    return mainTest();
    return mainStrategieRobot2A();
}
