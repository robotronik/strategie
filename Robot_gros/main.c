
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

int mainTest() {
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


int mainStrategieRobot2A() {
    // Initialisation des différents machins
    init_hardware();

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
    return mainStrategieRobot2A();
    //return mainTest();
}
