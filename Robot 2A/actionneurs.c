#include "actionneurs.h"
#include "/LowLevel/empileur.h"
#include "/LowLevel/empileur.h"

int perimetre_actuel = PERIMETRE_BASE;

//init
void init_actionneurs()
{
    init_all_servo();
    init_empileur();
}

// Empileur
// // Porte
int empileur_porte_ouverte = 0;
int empileur_porte_ouvre() {
    if (!empileur_porte_ouverte
        && (perimetre_actuel+PERIMETRE_ADD_EMPILEUR_OUVERT)<PERIMETRE_MAX ) {
        // On ouvre l'empileur
        perimetre_actuel += PERIMETRE_ADD_EMPILEUR_OUVERT;
        empileur_porte_ouverte = 1;
        return 0;
    }
    return 1;
}
int empileur_porte_ferme() {
    // On ferme l'empileur
    if (empileur_porte_ouverte) {
        perimetre_actuel -= PERIMETRE_ADD_EMPILEUR_OUVERT;
        empileur_porte_ouverte = 0;
        return 0;
    }
    return 1;
}
// // Monte-pieds
int empileur_monteur_descend() {
    return 1;
}
int empileur_monteur_monte_un_pied() {
    return 1;
}
int empileur_monteur_prend_une_ampoule() {
    return 1;
}


// Bras latéraux
int bras_droit_position = 0;
int bras_droit_ferme() {
    return 1;
}
int bras_droit_position_clap() {
    return 1;
}
int bras_droit_coince_verre() {
    return 1;
}
int bras_droit_libere_verre() {
    return 1;
}


int bras_gauche_position = 0;
int bras_gauche_ferme() {
    return 1;
}
int bras_gauche_position_clap() {
    return 1;
}
int bras_gauche_coince_verre() {
    return 1;
}
int bras_gauche_libere_verre() {
    return 1;
}


// Attrape-popcorns
int attrape_popcorns_tourne(int position) {
    return 1;
}
