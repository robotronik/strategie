#ifndef ACTIONS_H
#define ACTIONS_H

typedef enum
{
	//déplacement
	XY,
	ALPHA,
	DELTA,
	THETA,

	//actions
	CLAP_OUVRE_D,
	CLAP_FERME_D,
	CLAP_OUVRE_G,
	CLAP_FERME_G,
	GOBELET_OUVRE_D,
	GOBELET_COINCE_D,
	GOBELET_LIBERE_D,
	GOBELET_OUVRE_G,
	GOBELET_COINCE_G,
	GOBELET_LIBERE_G,
	OUVRE_PORTE_EMPILEUR,
	FERME_PORTE_EMPILEUR,
	PREND_POP_CORN,
	VIDE_POP_CORN,

	FIN
} e_action_type;

void gestion_actions();
void set_asser_done();
void inverse_couleur();

#endif