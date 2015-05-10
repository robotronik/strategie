#include "../../mapping/IO_pinout.h"
#include "../../mapping/PWM_pinout.h"
#include "../../../stm32f407/headers/GPIO.h"
#include "../../../stm32f407/headers/PWM.h"
#include "utilities.h"

// Low-level pour la gestion du moteur de l'empileur

s_PWM moteur_empileur;

void init_moteur_empileur();
void init_rupteur_pied();
void init_rupteur_moteur();

void init_empileur()
{
	init_rupteur_pied();
	init_rupteur_moteur();
	init_moteur_empileur();
}

void set_PWM_moteur_empileur(uint32_t pwm, int direction) {
	//on indique la direction
	write_pin(DIR_MOT1_PORT, DIR_MOT1_PIN, direction);
	//on indique le pwm
	start_PWM(&moteur_empileur, pwm);
}

void stop_moteur_empileur()
{
	stop_PWM(&moteur_empileur);
}

int rupteur_moteur_empileur_is_pushed() {
	return !read_pin(IO4_PORT, IO4_PIN);
}

int rupteur_pied_empileur_is_pushed() {
	int retour = read_pin(IO5_PORT, IO5_PIN);
	return !retour;
}

void init_moteur_empileur() {
	init_pin_mode(DIR_MOT1_PORT, DIR_MOT1_PIN, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL);
	init_pwm(&moteur_empileur, PWM_MOT1_PORT, PWM_MOT1_PIN);
	stop_moteur_empileur();
}

void init_rupteur_pied() {
	init_pin_mode(IO4_PORT, IO4_PIN, GPIO_MODE_INPUT, GPIO_PULLUP);
}

void init_rupteur_moteur() {
	init_pin_mode(IO5_PORT, IO5_PIN, GPIO_MODE_INPUT, GPIO_PULLUP);
}
