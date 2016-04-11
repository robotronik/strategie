#include "hardware_common.h"
#include "hardware/common.h"
#include "actions.h"
#include "actionneurs.h"
#include <string.h>
#include "../../common_code/communication/s2a.h"
#include "../../common_code/communication/text_emission.h"

static int cpt=0;
static int asser_done=1;
static int cpt_pause=0;

#define QTOUR 1571
#define DTOUR 3142

#define DELAI 1500
/*
static int milestones[40][3]=
{
	//{DELTA,0,0},
	{DELTA,500,0},
	//{PAUSE,2000,0},
	//{ARRET_CAPTEUR,0,0},
	{THETA,-1571,0},
	//{PAUSE,2000,0},
	{DELTA,740,0},
	//{PAUSE,2000,0},
	{THETA,0,0},
	//{PAUSE,2000,0},
	{CLAP_OUVRE_D,0,0},
	//{PAUSE,1000,0},
	{DELTA,250,0},
	//{PAUSE,2000,0},
	{THETA,1571,0},
	//{PAUSE,2000,0},
	{CLAP_FERME_D,0,0},
	//{PAUSE,1000,0},
	{FIN,0,0}
};*/

static int milestones[][3]= {
	//{DELTA, -25, 0},			{PAUSE, DELAI, 0},
	//{DESCEND_PIED_EMPILEUR, 0, 0},
	//{DELTA, 35, 0},			{PAUSE, DELAI, 0},
	//{MONTE_PIED_EMPILEUR, 0, 0},



	{DELTA, 600, 0}, 		{PAUSE, DELAI, 0},
	{ARRET_CAPTEUR, 0, 0},
	{ALPHA, QTOUR, 0}, 	{PAUSE, DELAI, 0},
	{DELTA, 470, 0}, 		{PAUSE, DELAI, 0},
	{ALPHA, QTOUR, 0}, 	{PAUSE, DELAI, 0},
	{DELTA, 740, 0}, 		{PAUSE, DELAI, 0},
	// On se cale sur le mur
	{DELTA,  180, 0}, 		{PAUSE, DELAI, 0},

	// On monte le pied
	//{DESCEND_PIED_EMPILEUR, 0, 0},
	//{MONTE_PIED_EMPILEUR, 0, 0},

	{DELTA, -85, 0}, 		{PAUSE, DELAI, 0},
	{ALPHA, -QTOUR, 0}, 		{PAUSE, DELAI, 0},
	// On se re-cale
	{DELTA, -160, 0}, 		{PAUSE, DELAI, 0},
	{DELTA, -140, 0}, 		{PAUSE, DELAI, 0},

	{DELTA, 443, 0}, 		{PAUSE, DELAI, 0},
	//{DELTA, -30, 0}, 		{PAUSE, DELAI, 0},
	{CLAP_OUVRE_G, 0, 0},
	{ALPHA, -QTOUR, 0}, 		{PAUSE, DELAI, 0},
	// On longe les claps
	{DELTA, 260, 0}, 		{PAUSE, DELAI, 0},
	{CLAP_FERME_G, 0, 0}, 	{PAUSE, DELAI, 0},

	{DELTA, 320, 0}, 		{PAUSE, DELAI, 0},
	{CLAP_OUVRE_G, 0, 0},	{PAUSE, DELAI, 0},

	{DELTA, 220, 0}, 		{PAUSE, DELAI, 0},
	{ALPHA, -QTOUR/2, 0}, 		{PAUSE, DELAI, 0},
	{DELTA, 150, 0}, 		{PAUSE, DELAI, 0},
	{ALPHA, QTOUR/2, 0}, 		{PAUSE, DELAI, 0},
	{CLAP_FERME_G, 0, 0}, 	{PAUSE, DELAI, 0},

	{DELTA, 200, 0}, 		{PAUSE, DELAI, 0},
	{ALPHA, -QTOUR, 0}, 		{PAUSE, DELAI, 0},
	{DELTA, -250, 0}, 		{PAUSE, DELAI, 0},
	{DELTA, -250, 0}, 		{PAUSE, DELAI, 0},

	// On a l'arrière dans la zone rouge
	{DESCEND_PIED_EMPILEUR, 0, 0},
	{OUVRE_PORTE_EMPILEUR, 0, 0}, 	{PAUSE, DELAI, 0},
	{DELTA, 220, 0}, 		{PAUSE, DELAI, 0},
	//{DELTA, 150, 0}, 		{PAUSE, DELAI, 0},
	//{FERME_PORTE_EMPILEUR, 0, 0}, 	{PAUSE, DELAI, 0},
	//{DELTA, -120, 0}, 		{PAUSE, DELAI, 0},
//*/

	{FIN,0,0}
};


void pause(int ms)
{
	//pour laisser la main pour le check des capteurs
	//(moche car en vrai le tps est plus grand du coup)
	delay_ms(1);
	cpt_pause++;
	if (cpt_pause==ms)
	{
		cpt++;
		cpt_pause=0;
	}
}

void gestion_actions()
{
	//char buff[33];
	//int length;
	if (!asser_done)
	{
		led_verte_off();
		return;
	}
	else
	{
		led_verte_on();
	}

	switch(milestones[cpt][0])
	{
		//déplacement
		case XY :
			send_val(s2a_keys[S2A_KEY_X], milestones[cpt][1]);
			send_val(s2a_keys[S2A_KEY_Y], milestones[cpt][2]);
			send_fonction(s2a_keys[S2A_FCT_XY_ABSOLU]);
			asser_done=0;
			delay_ms(500); //le temps que l'asser remette la pin à 0
			//TODO
			break;
		case ALPHA :
			send_val(s2a_keys[S2A_KEY_ALPHA], milestones[cpt][1]);
			send_val(s2a_keys[S2A_KEY_DELTA], 0);
			send_fonction(s2a_keys[S2A_FCT_ALPHA_DELTA]);
			asser_done=0;
			delay_ms(500);
			//TODO
			break;

		case DELTA :
			send_val(s2a_keys[S2A_KEY_DELTA], milestones[cpt][1]);
			send_val(s2a_keys[S2A_KEY_ALPHA], 0);
			send_fonction(s2a_keys[S2A_FCT_ALPHA_DELTA]);
			asser_done=0;
			delay_ms(500);
			break;

		case THETA :
			send_val(s2a_keys[S2A_KEY_THETA], milestones[cpt][1]);
			send_fonction(s2a_keys[S2A_FCT_THETA]);
			asser_done=0;
			delay_ms(500);
			break;

		//actions
		case CLAP_OUVRE_D :
			bras_droit_position_clap();
			break;
		case CLAP_FERME_D :
			bras_droit_repos();
			break;
		case CLAP_OUVRE_G :
			bras_gauche_position_clap();
			break;
		case CLAP_FERME_G :
			bras_gauche_repos();
			break;
		case GOBELET_OUVRE_D :
			bras_droit_position_prise_gobelet();
			break;
		case GOBELET_COINCE_D :
			bras_droit_coince_gobelet();
			break;
		case GOBELET_LIBERE_D :
			bras_droit_libere_gobelet();
			break;
		case GOBELET_OUVRE_G :
			bras_gauche_position_prise_gobelet();
			break;
		case GOBELET_COINCE_G :
			bras_gauche_coince_gobelet();
			break;
		case GOBELET_LIBERE_G :
			bras_gauche_libere_gobelet();
			break;
		case OUVRE_PORTE_EMPILEUR :
			//descend_ascenseur();
			ouvre_porte_empileur();
			break;
		case FERME_PORTE_EMPILEUR :
			ferme_porte_empileur();
			break;
		case DESCEND_PIED_EMPILEUR :
		    descend_ascenseur();
		    break;
	    case MONTE_PIED_EMPILEUR :
    	    monte_pied();
    	    break;
		case PREND_POP_CORN :
			prend_pop_corn();
			break;
		case VIDE_POP_CORN :
			libere_pop_corn();
			break;
		case PAUSE :
			pause(milestones[cpt][1]); //a voir
			cpt--;
			break;
		case ARRET_CAPTEUR :
			//set_arret_capteur(1);
			arret_capteurs();
			set_all_led();
			break;
		case FIN :
			cpt--;
			send_cmd(s2a_keys[S2A_CMD_STOP]);
			delay_ms(3600000); //on attend une heure parce on sait jamais ;)
			break;

	}
	cpt++;
}


void inverse_couleur()
{
	int i=0;
	while(milestones[i][0]!=FIN)
	{
		//milestones[i][0]=milestones_vert[i][0];
		//milestones[i][1]=milestones_vert[i][1];
		//milestones[i][2]=milestones_vert[i][2];
		switch(milestones[i][0])
		{
			case XY :
				//on inverse les valeurs pour x
				//(l'axe des Y coupe la table en deux, on est dessus au départ)
				milestones[i][1]=-milestones[i][1];
				break;
			case ALPHA :
				//on inverse le sens de rotation
				milestones[i][1]=-milestones[i][1];
				break;
			case DELTA :
				//rien à faire
				break;
			case THETA :
				//on inverse le sens de rotation
				milestones[i][1]=-milestones[i][1];
				break;
			//surement moyen de faire ça plus propre
			case CLAP_OUVRE_D :
				milestones[i][0]=CLAP_OUVRE_G;
				break;
			case CLAP_FERME_D :
				milestones[i][0]=CLAP_FERME_G;
				break;
			case CLAP_OUVRE_G :
				milestones[i][0]=CLAP_OUVRE_D;
				break;
			case CLAP_FERME_G :
				milestones[i][0]=CLAP_FERME_D;
				break;
			case GOBELET_OUVRE_D :
				milestones[i][0]=GOBELET_OUVRE_G;
				break;
			case GOBELET_COINCE_D :
				milestones[i][0]=GOBELET_COINCE_G;
				break;
			case GOBELET_LIBERE_D :
				milestones[i][0]=GOBELET_LIBERE_G;
				break;
			case GOBELET_OUVRE_G :
				milestones[i][0]=GOBELET_OUVRE_D;
				break;
			case GOBELET_COINCE_G :
				milestones[i][0]=GOBELET_COINCE_D;
				break;
			case GOBELET_LIBERE_G :
				milestones[i][0]=GOBELET_LIBERE_D;
				break;

			//rien à faire pour le reste
			case OUVRE_PORTE_EMPILEUR :
				break;
			case FERME_PORTE_EMPILEUR :
				break;
			case PREND_POP_CORN :
				break;
			case VIDE_POP_CORN :
				break;

			case DEMARRE_CAPTEUR:
				break;

			case ARRET_CAPTEUR :
				break;

			case FIN :
				break;
		}
		i++;
	}
}

void set_asser_done()
{
	asser_done=1;
}
