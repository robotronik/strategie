#include "actionneurs.h"
#include "Calibration/Servos/reglage_servos.h"
#include "LowLevel/empileur.h"
#include "LowLevel/empileur.h"


int porte_empileur_is_open = 0;
int bras_droit_is_risen = 0;
int bras_gauche_is_risen = 0;

//init
void init_actionneurs()
{
    init_all_servo();
    init_empileur();
    init_protection_perimetre();
}

int something_is_open()
{
    retour= porte_empileur_is_open||bras_gauche_is_risen||bras_gauche_is_risen;
    return retour;
}

//empileur
int ouvre_porte_empileur()
{
    if(something_is_open())
        return 1;
    porte_empileur_is_open=1;
    porte_empileur_set_angle(ANGLE_OUVERTURE_PORTE);
    return 0;

}

void ferme_porte_empileur()
{
    porte_empileur_set_angle(ANGLE_FERMETURE_PORTE);
    porte_empileur_is_open=0;
}

//bras gauche
void bras_gauche_repos()
{
    bras_gauche_set_angle(ANGLE_REPOS_BRAS_GAUCHE);
    bras_gauche_is_risen=0;
}

int bras_gauche_position_clap()
{
    if(porte_empileur_is_open || bras_droit_is_risen)
        return 1;
    bras_gauche_is_risen=1;
    bras_gauche_set_angle(ANGLE_CLAP_BRAS_DROIT);
    return 0;
}

int bras_gauche_position_prise_gobelet()
{
     if(porte_empileur_is_open || bras_droit_is_risen)
        return 1;
    bras_gauche_is_risen=1;
    bras_gauche_set_angle(ANGLE_GOBELET_LIBRE_BRAS_GAUCHE);
    return 0;   
}

int bras_gauche_coince_gobelet()
{
     if(porte_empileur_is_open || bras_droit_is_risen)
        return 1;
    bras_gauche_is_risen=1;
    bras_gauche_set_angle(ANGLE_GOBELET_COINCE_BRAS_GAUCHE);
    /*wait();
    bras_gauche_set_angle(ANGLE_GOBELET_LIBRE_BRAS_GAUCHE);
    wait();
    bras_gauche_set_angle(ANGLE_GOBELET_COINCE_BRAS_GAUCHE);*/
    return 0;   
}

int bras_gauche_libere_gobelet()
{
     if(porte_empileur_is_open || bras_droit_is_risen)
        return 1;
    bras_gauche_is_risen=1;
    bras_gauche_set_angle(ANGLE_GOBELET_LIBRE_BRAS_GAUCHE);
    return 0; 
}

//bras droit
void bras_droit_repos()
{
    bras_droit_set_angle(ANGLE_REPOS_BRAS_DROIT);
    bras_droit_is_risen=0;
}

int bras_droit_position_clap()
{
    if(porte_empileur_is_open || bras_gauche_is_risen)
        return 1;
    bras_droit_is_risen=1;
    bras_droit_set_angle(ANGLE_CLAP_BRAS_DROIT);
    return 0;
}

int bras_droit_position_prise_gobelet()
{
     if(porte_empileur_is_open || bras_gauche_is_risen)
        return 1;
    bras_droit_is_risen=1;
    bras_droit_set_angle(ANGLE_GOBELET_LIBRE_BRAS_DROIT);
    return 0;   
}

int bras_droit_coince_gobelet()
{
     if(porte_empileur_is_open || bras_gauche_is_risen)
        return 1;
    bras_droit_is_risen=1;
    bras_droit_set_angle(ANGLE_GOBELET_COINCE_BRAS_DROIT);
    /*wait();
    bras_droit_set_angle(ANGLE_GOBELET_LIBRE_BRAS_DROIT);
    wait();
    bras_droit_set_angle(ANGLE_GOBELET_COINCE_BRAS_DROIT);*/
    return 0;   
}

int bras_droit_libere_gobelet()
{
     if(porte_empileur_is_open || bras_gauche_is_risen)
        return 1;
    bras_droit_is_risen=1;
    bras_droit_set_angle(ANGLE_GOBELET_LIBRE_BRAS_DROIT);
    return 0; 
}

//init
void init_protection_perimetre()
{
    int porte_empileur_is_open=0;
    int bras_droit_is_risen=0;
    int bras_gauche_is_risen=0;
}