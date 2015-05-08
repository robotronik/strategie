#include "../mapping/PWM.h"

void init_bras_gauche();
void init_bras_droit();
void init_porte_empileur();
void init_attrape_popcorns();

Servo_t servo_bras_gauche;
Servo_t servo_bras_droit;
Servo_t servo_porte_empileur;
Servo_t servo_attrape_popcorns;


void init_all_servo() {
    init_bras_gauche();
    init_bras_droit();
    init_porte_empileur();
    init_attrape_popcorns();
}


int bras_gauche_set_angle(int angle) {
    set_position_servo(angle, &servo_bras_gauche);
}


int bras_droit_set_angle(int angle) {
    set_position_servo(angle, &servo_bras_droit);
}


int porte_empileur_set_angle(int angle) {
    set_position_servo(angle, &servo_porte_empileur);
}

int attrape_popcorns_set_angle(int angle) {
    set_position_servo(angle, &servo_attrape_popcorns);
}


//init
void init_bras_gauche() {
    init_servo(&servo_bras_gauche, PWM2_PORT, PWM2_PIN);
}

void init_bras_droit() {
    init_servo(&servo_bras_droit, PWM1_PORT, PWM1_PIN);
}

void init_porte_empileur() {
    init_servo(&servo_porte_empileur, PWM4_PORT, PWM4_PIN);
}

void init_attrape_popcorns() {
    init_servo(&servo_attrape_popcorns, PWM3_PORT, PWM3_PIN);
}