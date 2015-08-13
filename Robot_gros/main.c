
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../cartographie/cartographie.h"
//#include "../../common_code/uart_emission.h"
#include "../../common_code/debug.h"
#include "actionneurs.h"
//#include "utilities.h"
#include "LowLevel/empileur.h"
#include "../mapping/PWM_pinout.h"

//test pwm
#include "../mapping/IO_pinout.h"
#include "../mapping/PWM_pinout.h"
#include "../../hardware/stm32f407/headers/GPIO.h"
#include "../../hardware/stm32f407/headers/PWM.h"
#include "utilities.h"
#include "LowLevel/capteurUS.h"

//test servo
//#include "../../mapping/PWM_pinout.h"
#include "../../hardware/stm32f407/headers/servo.h"

//test uart
#include "../../hardware/stm32f407/headers/UART.h"

#include "actions.h"

s_PWM moteur_empileur;
Servo_t servo_porte_empileur;
int arret_capteur=0;


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}


void gestion_rupteurs() {
    /*if(rupteur_pied_empileur_is_pushed()) {
        descend_ascenseur();
        monte_pied();
    }
    */

}

void gestion_communication()
{
    if (!read_pin(IO7_PORT, IO7_PIN))
    {
        set_asser_done();
    }
    //set_asser_done();
}

int mainStrategie() {
    //init_EOM_timer();
    init_actionneurs();
    init_RTC();
    init_sensor1();
    activate_sensor1();
    init_sensor2();
    activate_sensor2();
    //demarre_alarme_90secondes();

    init_UART_Asser(&UART_Asser);
    init_pin_mode(IO6_PORT, IO6_PIN, GPIO_MODE_INPUT, GPIO_PULLUP); //init du changement de couleur
    init_pin_mode(IO7_PORT, IO7_PIN, GPIO_MODE_INPUT, GPIO_NOPULL); //pin de retour de l'asservissement
    // Init tirette
    Delay(10);

    if (read_pin(IO6_PORT, IO6_PIN)) //on regarde notre couleur
        inverse_couleur(); //ici on change si on est en vert

    init_pin_mode(IO1_PORT, IO1_PIN, GPIO_MODE_INPUT, GPIO_PULLUP);
    while(read_pin(IO1_PORT, IO1_PIN));
    //activate_EOM_timer();

    while(1)
    {
        //if (!arret_capteur)
        //    gestion_capteurs();
        gestion_rupteurs();
        gestion_communication();

        gestion_actions();
        //HAL_GPIO_TogglePin(GPIOD, LED_VERTE);
        //Delay(300);

    }

    /*//test de l'uart asser
    init_UART_Asser(&UART_Asser);
    Delay(10);
    char* message1 ="x=0\n";
    UART_send_message_asser(message1, strlen(message1));
    char* message2 ="y=2000\n";
    UART_send_message_asser(message2, strlen(message2));
    char* message3 ="xy_absolu()\n";
    UART_send_message_asser(message3, strlen(message3));
    Delay(100);
    while(1);*/

    //test de l'uart_asser
    //init_UART_Asser(&UART_Asser);
    /*while(1)
    {
        //send_word(&UART_Asser,"I'm alive");
        //UART_send_message("I'm alive");
        Delay(100);
    }*/
    //test du bras droit
    /*while(1) {
        bras_droit_position_clap();
        Delay(1000);
        bras_droit_repos();
        Delay(1000);
    }*/
    /*while(1) {
        bras_droit_position_prise_gobelet();
        Delay(1000);
        bras_droit_coince_gobelet();
        Delay(1000);
    }*/

    //test du bras gauche
    /*while(1) {
        bras_gauche_position_clap();
        Delay(1000);
        bras_gauche_repos();
        Delay(1000);
    }*/
    /*while(1) {
        bras_gauche_position_prise_gobelet();
        Delay(1000);
        bras_gauche_coince_gobelet();
        Delay(1000);
    }*/

    //test du moulin
    /*while(1)
    {
        prend_pop_corn();
        Delay(1000);
        libere_pop_corn();
        Delay(1000);
    }*/

    //test de l'empileur
    /*while(1)
    {
        if (rupteur_pied_empileur_is_pushed()) {
            descend_ascenseur();
            Delay(100);
            monte_pied();
        }
    }*/

    /*x_futur = x_actuel;
    y_futur = y_actuel;
    pathfinding_init();
    nouvel_obstacle_rond(1500, 1200, 200);
    if(find_path_to(2700,4000)) {
        affiche_chemin();
        execute_chemin();
    }
    // Si on force un chemin qui a été déterminé comme impossible,
    // il n'est PAS exécuté ! :)
    execute_chemin();

    if(find_path_to( 300,1600)) {
        affiche_chemin();
        execute_chemin();
    }

    if(find_path_to(2700,1600)) {
        affiche_chemin();
        execute_chemin();
    }*/
    return 0;
}
