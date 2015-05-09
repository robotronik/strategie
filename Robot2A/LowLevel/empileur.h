#ifndef EMPILEUR_H
#define EMPILEUR_H

// Low-level pour la gestion du moteur de l'empileur

void init_empileur();

void set_PWM_moteur_empileur(float pwm, int direction);
int rupteur_empileur_is_pushed();


#endif