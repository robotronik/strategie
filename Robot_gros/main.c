#include <stdint.h>
#include <string.h>
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


#include "hardware/xl_320.h"
#include "hardware/servos.h"

extern capteurUSBuffer capteur_front,  capteur_bottom;


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
/*

    // Test UART Asser
    init_uart_asser();
    test_led();
    //while(1)
    UART_send_message("auieauie", 8);

*/


    // Test Capteurs
    init_capteurs_US();

    init_uart_asser();
    //init_serial_test_capteurs();

    while(1){
        if(capteur_front.value > 8){
            set_ledVerte();
        }
        else{
            clear_ledVerte();
        }
        //send_to_pc(&capteur_front, 'f');

        if(capteur_bottom.value > 8){
            set_ledOrange();
        }
        else{
            clear_ledOrange();
        }
        //send_to_pc(&capteur_bottom, 'b');

        delay_ms(50);
        UART_send_message("qsdf", 4);
        //send_to_pc_end();
    }


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

int asser_locked = 0;
void gestion_capteursUS() {
    if (capteur_front.value  < 10
     || capteur_bottom.value < 10
        ) {
        set_ledOrange();
        if (asser_locked == 0) {
            asser_locked = 1;   // Anti-spam
            char buffer[40];
            send_cmd(buffer, keys[CMD_LOCK]); //ajouter anti-spam (ici on envoie sans arret)
            UART_send_message(buffer, strlen(buffer));
        }
    } else {
        clear_ledOrange();
        if (asser_locked == 1) {
            asser_locked = 0;   // Anti-spam
            char buffer[40];
            send_cmd(buffer, keys[CMD_UNLOCK]); //ajouter anti-spam (ici on envoie sans arret)
            UART_send_message(buffer, strlen(buffer));
        }
    }
}


void gestion_communication() {
    char c;
    if (UART_getc(&c)) {
        reception_communication((char) c);
    }
}

// Callbacks d'alarme
int match_fini = 0;
void alarme_fin_match() {
    match_fini = 1;
}

int mainStrategieRobot2A() {
    // Initialisation des capteurs
    init_capteurs_US();

    // Initialisation de la réception
    init_reception_communication();
    init_uart_asser();

    // à décomenter si on est en vert
    // inverse_couleur(); //ici on change si on est en vert

    while(read_tirette()); // On attend la tirette
    // Voilà, maintenant on peut s'amuser !

    //add_alarm(85000, alarme_fin_match, false);

    // Mouvement robot
    char buffer[1000];


    // Ça, c'est pour être sûr que le bus uart est réinitialisé du côté
    // de l'asservissement, pour que la lecture se fasse bien
    UART_send_message("\n", 1);


    // Servos et positions d'actionneurs
    init_uart_servos();
    init_servos();
    set_position_portes(0);

    clear_ledBleue();
    while(1)
    {
        // toggle_ledVerte();
        // gestion_capteursUS();
        // toggle_all_led();

        if (match_fini == 1) {
            send_cmd(buffer, keys[CMD_EMERGENCY_STOP]);
            while(1);
        }

        gestion_communication();

        gestion_actions();

        delay_ms(100);
    }
    while(1);
    return 0;
}

int main() {
    init_hardware();
    // return mainTest();
    return mainStrategieRobot2A();
}
