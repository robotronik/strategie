/*
int x_actuel = 300;
int y_actuel = 1000;

int x_futur, y_futur;

int found_path[20][2];
int found_path_length;

void manage_carto_system_errors() {

}
int find_path_to(int x, int y) {
    // On exécute l'algo
    int path_found = pathfinding(x_actuel, y_actuel, x, y);
    switch(path_found) {
        case -1: 
            debug(0, "Il y a eu une erreur dans l'algorithme, à débugger !\n");
            manage_carto_system_errors();
            return -1;
        case  0:
            debug(1, "Pas de chemin trouvé…\n");
            return  0;
    }
    x_futur = x;
    y_futur = y;

    // On récupère le chemin
    found_path_length = return_length_of_path_found();
    return_path_found(found_path);

    return 1; 
}


void affiche_chemin() {
    int i;
    for (i = 0; i < found_path_length; ++i)
        debug(3, "%d -- %d\n", found_path[i][0], found_path[i][1]);

}
void execute_chemin() {
    x_actuel = x_futur;
    y_actuel = y_futur;
}
*/