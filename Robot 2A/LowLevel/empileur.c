// Low-level pour la gestion du moteur de l'empileur

void init_moteur_empileur();
void init_rupteur_pied();
void init_rupteur_moteur();

void init_empileur()
{
	init_moteur_empileur();
	init_rupteur_pied();
	init_rupteur_moteur();
}

void set_PWM_moteur_empileur(float pwm, int direction) {

}

int rupteur_empileur_is_pushed() {
	return 1;
}

void init_moteur_empileur() {

}

void init_rupteur_pied() {

}

void init_rupteur_moteur() {

}