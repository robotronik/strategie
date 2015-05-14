#include "capteurUS.h"
// Low-level pour initialiser les capteurs US
// Et pour récupérer les valeurs de distance

static int valeurs_capteur1[10] =
{LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100};
static int somme_capteur1 = 10*(LIMIT_RANGE+100);
static int pos_in_valeurs_capteur1 = 0;
void nouvelle_valeur_captee_capteur1(int valeur) {
    somme_capteur1 -= valeurs_capteur1[pos_in_valeurs_capteur1];
    valeurs_capteur1[pos_in_valeurs_capteur1] = valeur;
    somme_capteur1 += valeur;
    pos_in_valeurs_capteur1 = (pos_in_valeurs_capteur1 + 1)%10;
}
int get_moyenne_capteur1() {
    return somme_capteur1/10;
}

static int valeurs_capteur2[10] =
{LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100,
 LIMIT_RANGE+100};
static int somme_capteur2 = 10*(LIMIT_RANGE+100);
static int pos_in_valeurs_capteur2 = 0;
void nouvelle_valeur_captee_capteur2(int valeur) {
    somme_capteur2 -= valeurs_capteur2[pos_in_valeurs_capteur2];
    valeurs_capteur2[pos_in_valeurs_capteur2] = valeur;
    somme_capteur2 += valeur;
    pos_in_valeurs_capteur2 = (pos_in_valeurs_capteur2 + 1)%10;
}
int get_moyenne_capteur2() {
    return somme_capteur2/10;
}
