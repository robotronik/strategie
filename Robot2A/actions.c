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
	{DELTA,800,0},
	{THETA,-1571,0},
	{DELTA,800,0},
	{THETA,1571,0},
	{CLAP_OUVRE_G,0,0},
	{DELTA,200,0},
	{CLAP_FERME_D,0,0}, //
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
	char buff[33];
	int length;
	if (!asser_done)
		return;

	switch(milestones[cpt][0])
	{
		//déplacement
		case XY :
			//TODO
			break;
		case ALPHA :
			//TODO
			break;
		case DELTA :
			UART_send_message_asser("delta=800\n",strlen("delta=800\n"));
			//int2str(milestones[cpt][1],buff);
			//UART_send_message_asser(&buff, length);
			length=sprintf(buff,"%d",milestones[cpt][1]);
			//UART_send_message_asser(buff, length);
			UART_send_message_asser("alpha=",strlen("alpha="));
			UART_send_message_asser("0\n", 2);
			UART_send_message_asser("alpha_delta()\n",strlen("alpha_delta()\n"));
			Delay(10000);
			asser_done=0;
			break;
		case THETA :
			UART_send_message_asser("theta=\n",strlen("theta=\n"));
			//length=sprintf(buff,"%d",milestones[cpt][1]);
			//UART_send_message_asser(buff, length);
			UART_send_message_asser("theta()\n",strlen("theta()\n"));
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
			UART_send_message_asser("estop()\n",strlen("estop()\n"));
			Delay(3600000); //on attend une heur parce on sait jamais ;)
			break;
	}
	cpt++;
}

void set_asser_done()
{
	asser_done=1;
}