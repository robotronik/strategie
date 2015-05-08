#ifndef SERVOS_H
#define SERVOS_H

void init_bras_gauche();
int bras_gauche_set_angle(int angle);

void init_bras_droit();
int bras_droit_set_angle(int angle);

void init_porte_empileur();
int porte_empileur_set_angle(int angle);

void init_attrape_popcorns();
int attrape_popcorns_set_angle(int angle);

#endif