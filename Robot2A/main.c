
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../cartographie/cartographie.h"
//#include "../../common_code/uart_emission.h"
#include "../../common_code/debug.h"
#include "actionneurs.h"
#include "utilities.h"
#include "LowLevel/empileur.h"
#include "../mapping/PWM_pinout.h"

//test pwm
#include "../mapping/IO_pinout.h"
#include "../mapping/PWM_pinout.h"
#include "../../stm32f407/headers/GPIO.h"
#include "../../stm32f407/headers/PWM.h"
#include "utilities.h"

//test servo
//#include "../../mapping/PWM_pinout.h"
#include "../../stm32f407/headers/servo.h"

//test uart
#include "../../stm32f407/headers/UART.h"

#include "actions.h"

s_PWM moteur_empileur;
Servo_t servo_porte_empileur;

void gestion_capteurs()
{
    //TODO

}
void gestion_rupteurs()
{
    //TODO
}

void gestion_communication()
{
    set_asser_done();
}

int mainStrategie() {
    init_actionneurs();
    init_RTC();
        test_led();
    //demarre_alarme_90secondes();

    init_UART_Asser(&UART_Asser);
    Delay(10);
    inverse_couleur();

    char* auie;
    while(1)
    {
        gestion_capteurs();
        gestion_rupteurs();
        gestion_communication();
        gestion_actions();
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
