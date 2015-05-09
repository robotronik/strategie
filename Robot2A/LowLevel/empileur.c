#include "../../IO_pinout.h"
#include "../../../stm32f407/headers/GPIO.h"


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
	return !read_pin(IO4_PORT, IO4_PIN);
}

void init_moteur_empileur() {
	init_pin_mode(DIR_MOT1_PORT, DIR_MOT1_PIN, GPIO_MODE_OUTPUT, GPIO_NOLLUP);
	//TODO : init PWM_MOT1
}

void init_rupteur_pied() {
	init_pin_mode(IO4_PORT, IO4_PIN, GPIO_MODE_INPUT, GPIO_PULLUP);
}

void init_rupteur_moteur() {
	init_pin_mode(IO5_PORT, IO5_PIN, GPIO_MODE_INPUT, GPIO_PULLUP);
}