#include ../mapping/PWM.h

Servo_t servo_bras_gauche;
Servo_t servo_bras_droit;
Servo_t servo_porte_empileur;
Servo_t servo_attrape_popcorns;

void init_bras_gauche() {
    //TODO : Donner les bonnes valeurs
    init_servo(&servo_bras_gauche, PWM2_PORT, PWM2_PIN);
}
int bras_gauche_set_angle(int angle) {
    set_position_servo(angle, &servo_bras_gauche);
}

void init_bras_droit() {
    //TODO : Donner les bonnes valeurs
    init_servo(&servo_bras_droit, PWM1_PORT, PWM1_PIN);
}
int bras_droit_set_angle(int angle) {
    set_position_servo(angle, &servo_bras_droit);
}

void init_porte_empileur() {
    //TODO : Donner les bonnes valeurs
    init_servo(&servo_porte_empileur, PWM4_PORT, PWM4_PIN);
}
int porte_empileur_set_angle(int angle) {
    set_position_servo(angle, &servo_porte_empileur);
}

void init_attrape_popcorns() {
    //TODO : Donner les bonnes valeurs
    init_servo(&servo_attrape_popcorns, PWM3_PORT, PWM3_PIN);
}
int attrape_popcorns_set_angle(int angle) {
    set_position_servo(angle, &servo_attrape_popcorns);
}
