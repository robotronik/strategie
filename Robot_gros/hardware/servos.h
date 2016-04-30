#ifndef SERVOS_H
#define SERVOS_H

#include <stdint.h>

void init_all_servo();
void send_servo(char * buff, uint8_t buff_len);


void bras_gauche_set_angle(int angle);
void bras_droit_set_angle(int angle);
void porte_empileur_set_angle(int angle);
void attrape_popcorns_set_angle(int angle);

#endif
