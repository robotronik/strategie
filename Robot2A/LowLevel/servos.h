#ifndef SERVOS_H
#define SERVOS_H

void init_all_servo();


int bras_gauche_set_angle(int angle);
int bras_droit_set_angle(int angle);
int porte_empileur_set_angle(int angle);
int attrape_popcorns_set_angle(int angle);

#endif