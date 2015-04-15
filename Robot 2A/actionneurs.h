#ifndef ACTIONNEURS_H
#define ACTIONNEURS_H

#define PERIMETRE_MAX   1500
#define PERIMETRE_BASE  1000    // ?
#define PERIMETRE_ADD_EMPILEUR_OUVERT       200 // ?

// Périmètre ajouté pendant l'ouverture
#define PERIMETRE_ADD_BRAS_OUVERTURE        500 // ?
// Périmètre ajouté en "position de repos" pour les différentes actions.
// Utilisé pour savoir si on peut ouvrir un autre actionneur en même temps.
#define PERIMETRE_ADD_BRAS_POSITION_NEUTRE  500 // ?
#define PERIMETRE_ADD_BRAS_POSITION_CLAPS   500 // ?
#define PERIMETRE_ADD_BRAS_POSITION_VERRE   500 // ?

// Empileur
// // Porte
int empileur_porte_ouvre();
int empileur_porte_ferme();
// // Monte-pieds
int empileur_monteur_descend();
int empileur_monteur_monte_un_pied();
int empileur_monteur_prend_une_ampoule();

// Bras latéraux
int bras_droit_ferme();
int bras_droit_position_clap();
int bras_droit_coince_verre();
int bras_droit_libere_verre();


int bras_gauche_ferme();
int bras_gauche_position_clap();
int bras_gauche_coince_verre();
int bras_gauche_libere_verre();


// Attrape-popcorns
int attrape_popcorns_tourne(int position);

#endif