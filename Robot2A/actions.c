#include "actions.h"
#include "actionneurs.h"
#include "../../stm32f407/headers/UART.h"
#include "utilities.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../common_code/communication/s2a.h"
#include "../../common_code/communication/text_emission.h"

static int cpt=0;
static int asser_done=1;

static int milestones[40][3]=
{
	{DELTA,500,0},
	{THETA,-1571,0},
	{DELTA,740,0},
	{THETA,0,0},
	{CLAP_OUVRE_D,0,0},
	{DELTA,250,0},
	{THETA,1571,0},
	{CLAP_FERME_D,0,0},
	{FIN,0,0}
};

void inverse_couleur()
{
	int i=0;
	while(milestones[i][0]!=FIN)
	{
		switch(milestones[i][1])
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
			case FIN :
				break;
		}
		i++;
	}
}

void gestion_actions()
{
	//char buff[33];
	//int length;
	if (!asser_done)
		return;

	switch(milestones[cpt][0])
	{
		//déplacement
		case XY :
			send_val(s2a_keys[S2A_KEY_X], milestones[cpt][1]);
			send_val(s2a_keys[S2A_KEY_Y], milestones[cpt][1]);
			send_fonction(s2a_keys[S2A_FCT_XY_ABSOLU]);
			Delay(2000);
			//TODO
			break;
		case ALPHA :
			send_val(s2a_keys[S2A_KEY_ALPHA], milestones[cpt][1]);
			send_val(s2a_keys[S2A_KEY_DELTA], 0);
			send_fonction(s2a_keys[S2A_FCT_ALPHA_DELTA]);
			Delay(2000);
			//TODO
			break;

		case DELTA :
			send_val(s2a_keys[S2A_KEY_DELTA], milestones[cpt][1]);
			send_val(s2a_keys[S2A_KEY_ALPHA], 0);
			send_fonction(s2a_keys[S2A_FCT_ALPHA_DELTA]);
			Delay(2000);
			asser_done=0;
			break;
			
		case THETA :
			send_val(s2a_keys[S2A_KEY_THETA], milestones[cpt][1]);
			send_fonction(s2a_keys[S2A_FCT_THETA]);
			Delay(2000);
			asser_done=0;
			break;

		//actions
		case CLAP_OUVRE_D :
			bras_droit_position_clap();
			Delay(1000); //a voir
			break;
		case CLAP_FERME_D :
			bras_droit_repos();
			Delay(1000); //a voir
			break;
		case CLAP_OUVRE_G :
			bras_gauche_position_clap();
			Delay(1000); //a voir
			break;
		case CLAP_FERME_G :
			bras_gauche_repos();
			Delay(1000); //a voir
			break;
		case GOBELET_OUVRE_D :
			bras_droit_position_prise_gobelet();
			Delay(1000); //a voir
			break;
		case GOBELET_COINCE_D :
			bras_droit_coince_gobelet();
			Delay(1000); //a voir
			break;
		case GOBELET_LIBERE_D :
			bras_droit_libere_gobelet();
			Delay(1000); //a voir
			break;
		case GOBELET_OUVRE_G :
			bras_gauche_position_prise_gobelet();
			Delay(1000); //a voir
			break;
		case GOBELET_COINCE_G :
			bras_gauche_coince_gobelet();
			Delay(1000); //a voir
			break;
		case GOBELET_LIBERE_G :
			bras_gauche_libere_gobelet();
			Delay(1000); //a voir
			break;
		case OUVRE_PORTE_EMPILEUR :
			ouvre_porte_empileur();
			Delay(1000); //a voir
			break;
		case FERME_PORTE_EMPILEUR :
			ferme_porte_empileur();
			Delay(1000); //a voir
			break;
		case PREND_POP_CORN :
			prend_pop_corn();
			Delay(1000); //a voir
			break;
		case VIDE_POP_CORN :
			libere_pop_corn();
			Delay(1000); //a voir
			break;

		case FIN :
			cpt--;
			send_cmd(s2a_keys[S2A_CMD_EMERGENCY_STOP]);
			Delay(3600000); //on attend une heure parce on sait jamais ;)
			break;

	}
	cpt++;
}


void set_asser_done()
{
	asser_done=1;
}