#ifndef SERVOS_H
#define SERVOS_H

void init_all_servo();


void bras_gauche_set_angle(int angle);
void bras_droit_set_angle(int angle);
void porte_empileur_set_angle(int angle);
void attrape_popcorns_set_angle(int angle);

#endif