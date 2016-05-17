#include <UART.h>
#include <alarms_and_delay.h>
#include "hardware/common.h"
#include "actions.h"
#include "actionneurs.h"
#include "reception_communication.h"
#include <string.h>
#include "../../common_code/communication/keys.h"
#include "../../common_code/communication/emission.h"

char buffer[40];

static int cpt=0;
//static int asser_done=1;
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



	{DELTA, 300, 0}, 	        {PAUSE, DELAI, 0}, 
	{ALPHA, -420, 0}, 	        {PAUSE, DELAI, 0},
	{DELTA, 200, 0}, 		{PAUSE, DELAI, 0},
	{ALPHA, 420, 0}, 		{PAUSE, DELAI, 0},
	{DELTA, 800, 0}, 		{PAUSE, DELAI, 0}, 
	{DELTA, -100, 0}, 		{PAUSE, DELAI, 0}, 
	{ALPHA, -QTOUR, 0}, 	{PAUSE, DELAI, 0}, 
	{DELTA, 650, 0}, 		{PAUSE, DELAI, 0}, 
	{ALPHA, -2094, 0}, 		{PAUSE, DELAI, 0}, 
	{DELTA, 800, 0}, 		{PAUSE, DELAI, 0}, 
	{ALPHA, -171, 0}, 		{PAUSE, DELAI, 0}, 
	{DELTA, 200, 0}, 		{PAUSE, DELAI, 0}, 



	// {ARRET_CAPTEUR, 0, 0},
	// {ALPHA, QTOUR, 0}, 	{PAUSE, DELAI, 0},
	// {DELTA, 470, 0}, 		{PAUSE, DELAI, 0},
	// {ALPHA, QTOUR, 0}, 	{PAUSE, DELAI, 0},
	// {DELTA, 740, 0}, 		{PAUSE, DELAI, 0},
	// // On se cale sur le mur
	// {DELTA,  180, 0}, 		{PAUSE, DELAI, 0},

	// // On monte le pied
	// //{DESCEND_PIED_EMPILEUR, 0, 0},
	// //{MONTE_PIED_EMPILEUR, 0, 0},

	// {DELTA, -85, 0}, 		{PAUSE, DELAI, 0},
	// {ALPHA, -QTOUR, 0}, 		{PAUSE, DELAI, 0},
	// // On se re-cale
	// {DELTA, -160, 0}, 		{PAUSE, DELAI, 0},
	// {DELTA, -140, 0}, 		{PAUSE, DELAI, 0},

	// {DELTA, 443, 0}, 		{PAUSE, DELAI, 0},
	// //{DELTA, -30, 0}, 		{PAUSE, DELAI, 0},
	// {CLAP_OUVRE_G, 0, 0},
	// {ALPHA, -QTOUR, 0}, 		{PAUSE, DELAI, 0},
	// // On longe les claps
	// {DELTA, 260, 0}, 		{PAUSE, DELAI, 0},
	// {CLAP_FERME_G, 0, 0}, 	{PAUSE, DELAI, 0},

	// {DELTA, 320, 0}, 		{PAUSE, DELAI, 0},
	// {CLAP_OUVRE_G, 0, 0},	{PAUSE, DELAI, 0},

	// {DELTA, 220, 0}, 		{PAUSE, DELAI, 0},
	// {ALPHA, -QTOUR/2, 0}, 		{PAUSE, DELAI, 0},
	// {DELTA, 150, 0}, 		{PAUSE, DELAI, 0},
	// {ALPHA, QTOUR/2, 0}, 		{PAUSE, DELAI, 0},
	// {CLAP_FERME_G, 0, 0}, 	{PAUSE, DELAI, 0},

	// {DELTA, 200, 0}, 		{PAUSE, DELAI, 0},
	// {ALPHA, -QTOUR, 0}, 		{PAUSE, DELAI, 0},
	// {DELTA, -250, 0}, 		{PAUSE, DELAI, 0},
	// {DELTA, -250, 0}, 		{PAUSE, DELAI, 0},

	// // On a l'arrière dans la zone rouge
	// {DESCEND_PIED_EMPILEUR, 0, 0},
	// {OUVRE_PORTE_EMPILEUR, 0, 0}, 	{PAUSE, DELAI, 0},
	// {DELTA, 220, 0}, 		{PAUSE, DELAI, 0},
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
  	  toggle_ledVerte();
	//char buff[33];
	//int length;
	if (get_asser_done_and_reset() == 0)
	{
		set_ledBleue();
		delay_ms(400);
		return;
	}
	else
	{
		//delay_ms(400);
    	clear_ledBleue();
	}

	switch(milestones[cpt][0])
	{
		//déplacement
		case XY :
			send_val(buffer, keys[VAL_X], milestones[cpt][1]);
			UART_send_message(buffer, 40);
			send_val(buffer, keys[VAL_Y], milestones[cpt][2]);
			UART_send_message(buffer, 40);
			send_cmd(buffer, keys[FCT_XY_ABSOLU]);
			UART_send_message(buffer, 40);
			//reset_asser_done();
			delay_ms(500); //le temps que l'asser remette la pin à 0
			//TODO
			break;
		case ALPHA :
			send_val(buffer, keys[VAL_ALPHA], milestones[cpt][1]);
			UART_send_message(buffer, 40);
			send_val(buffer, keys[VAL_DELTA], 0);
			UART_send_message(buffer, 40);
			send_cmd(buffer, keys[FCT_ALPHA_DELTA]);
			UART_send_message(buffer, 40);
			//reset_asser_done();
			delay_ms(500);
			//TODO
			break;

		case DELTA :
			send_val(buffer, keys[VAL_DELTA], milestones[cpt][1]);
			UART_send_message(buffer, 40);
			send_val(buffer, keys[VAL_ALPHA], 0);
			UART_send_message(buffer, 40);
			send_cmd(buffer, keys[FCT_ALPHA_DELTA]);
			UART_send_message(buffer, 40);
			//reset_asser_done();
			delay_ms(500);
			break;

		case THETA :
			send_val(buffer, keys[VAL_THETA], milestones[cpt][1]);
			UART_send_message(buffer, 40);
			send_cmd(buffer, keys[FCT_THETA]);
			UART_send_message(buffer, 40);
			//reset_asser_done();
			delay_ms(500);
			break;


		case FIN :
            send_cmd(buffer, keys[CMD_EMERGENCY_STOP]);
            while(1);
            break;

		case WAIT_ASSER :
	  		if(!asser_is_done()){
	    		cpt--;
	  		}
	  		break;

	  	case PAUSE :
		        pause(milestones[cpt][1]);
	  		break;


		//actions


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

		}
		i++;
	}
}


/* void set_asser_done() */
/* { */
/* 	asser_done=1; */
/* } */
