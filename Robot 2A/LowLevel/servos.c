Servo_t servo_bras_gauche;
Servo_t servo_bras_droit;
Servo_t servo_porte_empileur;
Servo_t servo_attrape_popcorns;

void init_bras_gauche() {
    //TODO : Donner les bonnes valeurs
    init_servo(&servo_bras_gauche, GPIOA, 0);
}
int bras_gauche_set_angle(int angle) {
    set_position_servo(angle, &servo_bras_gauche);
}

void init_bras_droit() {
    //TODO : Donner les bonnes valeurs
    init_servo(&servo_bras_droit, GPIOA, 0);
}
int bras_droit_set_angle(int angle) {
    set_position_servo(angle, &servo_bras_droit);
}

void init_porte_empileur() {
    //TODO : Donner les bonnes valeurs
    init_servo(&servo_porte_empileur, GPIOA, 0);
}
int porte_empileur_set_angle(int angle) {
    set_position_servo(angle, &servo_porte_empileur);
}

void init_attrape_popcorns() {
    //TODO : Donner les bonnes valeurs
    init_servo(&servo_attrape_popcorns, GPIOA, 0);
}
int attrape_popcorns_set_angle(int angle) {
    set_position_servo(angle, &servo_attrape_popcorns);
}
