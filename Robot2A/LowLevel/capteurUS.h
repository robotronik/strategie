#ifndef CAPTEUR_US_H
#define CAPTEUR_US_H


#define LIMIT_RANGE 250

// Low-level pour initialiser les capteurs US
// Et pour récupérer les valeurs de distance

void nouvelle_valeur_captee_capteur1(int valeur);
int get_moyenne_capteur1();

void nouvelle_valeur_captee_capteur2(int valeur);
int get_moyenne_capteur2();

#endif