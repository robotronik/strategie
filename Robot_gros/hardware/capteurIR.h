#ifndef CAPTEUR_IR_H
#define CAPTEUR_IR_H

// Low-level pour initialiser les capteurs US
// Et pour récupérer les valeurs de distance

void init_capteurIR();

// En mm (?)
int capteurIR_get_distance();

#endif