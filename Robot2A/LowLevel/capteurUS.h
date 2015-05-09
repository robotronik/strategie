#ifndef CAPTEUR_US_H
#define CAPTEUR_US_H

// Low-level pour initialiser les capteurs US
// Et pour récupérer les valeurs de distance

void init_capteurUS();

// En mm (?)
int capteurUS_get_distance();

#endif