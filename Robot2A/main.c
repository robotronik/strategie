// Mapping. Useful for direct pinout access
#include "../mapping/IO_pinout.h"

// Actions, etc
#include "actions.h"
#include "actionneurs.h"
#include "LowLevel/empileur.h"

// Cartographie
#include "../../cartographie/cartographie.h"

// In stm32f407 repository
#include "UART.h"
#include "GPIO.h"

void gestion_rupteurs() {
    /*if(rupteur_pied_empileur_is_pushed()) {
        descend_ascenseur();
        monte_pied();
    }*/
}

void gestion_communication() {
    if (!read_pin(IO7_PORT, IO7_PIN))
        set_asser_done();
}

int mainStrategie() {
    //return mainStrategieRobot2A();
    return mainTest();
}

int mainTest() {
    pathfinding_init();

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
        Delay(500);
        HAL_GPIO_TogglePin(GPIOD, LED_BLEUE);
        Delay(500);

    }
}


int mainStrategieRobot2A() {
    // Initialisation des différents machins
    init_actionneurs();

    init_UART_Asser(&UART_Asser);
    //init_EOM_timer();

    init_pin_mode(IO1_PORT, IO1_PIN, GPIO_MODE_INPUT, GPIO_PULLUP); // Tirette
    init_pin_mode(IO6_PORT, IO6_PIN, GPIO_MODE_INPUT, GPIO_PULLUP); // Choix de couleur
    init_pin_mode(IO7_PORT, IO7_PIN, GPIO_MODE_INPUT, GPIO_NOPULL); //pin de retour de l'asservissement

    init_sensor1();
    init_sensor2();

    init_RTC();

    if (read_pin(IO6_PORT, IO6_PIN)) //on regarde notre couleur
        inverse_couleur(); //ici on change si on est en vert

    while(read_pin(IO1_PORT, IO1_PIN)); // On attend la tirette

    // On met en route le timer 90 secondes
    //activate_EOM_timer();
    test_led();

    activate_sensor1();
    activate_sensor2();

    Delay(10);

    // Voilà, maintenant on peut s'amuser !



    while(1)
    {
        gestion_rupteurs();
        gestion_communication();

        gestion_actions();
    }

    return 0;
}
