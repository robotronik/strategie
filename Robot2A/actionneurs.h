#ifndef ACTIONNEURS_H
#define ACTIONNEURS_H

typedef enum
{
	PORTE_EMPILEUR,
	BRAS_DROIT,
	BRAS_GAUCHE
} e_actionneur;

void init_actionneurs();


//etat
int something_is_open();
e_actionneur actionneur_ouvert();
int un_gobelet_est_saisi();

//empileur
	//porte
int ouvre_porte_empileur();
void ferme_porte_empileur();
	//ascenseur
void monte_pied();
void ascenseur_position_prise_balle();;
void descend_ascenseur();

//bras gauche
void bras_gauche_repos();
int bras_gauche_position_clap();
int bras_gauche_position_prise_gobelet();
int bras_gauche_coince_gobelet();
int bras_gauche_libere_gobelet();

//bras droit
void bras_droit_repos();
int bras_droit_position_clap();
int bras_droit_position_prise_gobelet();
int bras_droit_coince_gobelet();
int bras_droit_libere_gobelet();

//moulin
void prend_pop_corn();
void libere_pop_corn();

#endif