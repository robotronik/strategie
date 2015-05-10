
#include <stdio.h>
#include <stdlib.h>

#include "../../cartographie/cartographie.h"
#include "../../common_code/uart_emission.h"
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

s_PWM moteur_empileur;
Servo_t servo_porte_empileur;

int mainStrategie() {
    init_actionneurs();
    test_led();

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
    while(1)
    {
        if (rupteur_pied_empileur_is_pushed()) {
            descend_ascenseur();
            Delay(100);
            monte_pied();
        }
    }

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
