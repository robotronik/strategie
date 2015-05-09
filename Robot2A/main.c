
#include <stdio.h>
#include <stdlib.h>

#include "../../cartographie/cartographie.h"
#include "../../common_code/uart_emission.h"
#include "../../common_code/debug.h"
#include "utilities.h"

int mainStrategie() {
    init();
    init_GPIO_LED();
    test_led();
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
