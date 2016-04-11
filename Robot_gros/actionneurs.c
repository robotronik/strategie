#include "hardware_common.h"

#include "actionneurs.h"
#include "Calibration/reglages_servos.h"
#include "Calibration/reglages_ascenseur.h"
#include "Calibration/reglages_moulin.h"
#include "hardware/empileur.h"
#include "hardware/servos.h"

void init_protection_perimetre();
void init_position_actionneurs();

static int porte_empileur_is_open = 0;
static int bras_droit_is_risen = 0;
static int bras_gauche_is_risen = 0;
static int gobelet_saisi = 0;
static int ascenseur_en_position_balle=0;


//================================= INIT ====================================//

void init_actionneurs()
{
    init_all_servo();
    init_empileur();
    init_protection_perimetre();
    init_position_actionneurs();
    /*descend_ascenseur();
    delay_ms(10);
    monte_pied();*/

}


//================================= ETAT ====================================//

int something_is_open()
{
    //return porte_empileur_is_open||bras_gauche_is_risen||bras_gauche_is_risen;
    return 0;
}

e_actionneur actionneur_ouvert()
{
    if (porte_empileur_is_open)
        return PORTE_EMPILEUR;
    if (bras_droit_is_risen)
        return BRAS_DROIT;
    if (bras_gauche_is_risen)
        return BRAS_GAUCHE;
    return NOTHING;
}

int un_gobelet_est_saisi()
{
    return gobelet_saisi;
}

//=============================== EMPILEUR ==================================//

//porte
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

//ascenseur
void stop_ascenseur()
{
    //set_PWM_moteur_empileur(1,1);
    stop_moteur_empileur();
}

void monte_pied()
{
    set_PWM_moteur_empileur(PWM_MOTEUR,DIR_MONTEE);
    if(ascenseur_en_position_balle) {
        delay_ms(TPS_MONTEE_PIED-TPS_MONTEE_BALLE);
    }
    else {
        delay_ms(TPS_MONTEE_PIED);
    }
    stop_ascenseur();
    ascenseur_en_position_balle=0;
}

void ascenseur_position_prise_balle()
{
    descend_ascenseur();
    set_PWM_moteur_empileur(PWM_MOTEUR,DIR_MONTEE);
    delay_ms(TPS_MONTEE_BALLE);
    stop_ascenseur();
    ascenseur_en_position_balle=1;

}

void descend_ascenseur()
{
    set_PWM_moteur_empileur(PWM_MOTEUR,DIR_DESCENTE);
    while(!rupteur_moteur_empileur_is_pushed());
    stop_ascenseur();
    ascenseur_en_position_balle=0;
}

//============================== BRAS GAUCHE ================================//

void bras_gauche_repos()
{
    bras_gauche_set_angle(ANGLE_REPOS_BRAS_GAUCHE);
    bras_gauche_is_risen=0;
}

int bras_gauche_position_clap()
{
    //if(porte_empileur_is_open || bras_droit_is_risen)
    //    return 1;
    bras_gauche_is_risen=1;
    bras_gauche_set_angle(ANGLE_CLAP_BRAS_GAUCHE);
    return 0;
}

int bras_gauche_position_prise_gobelet()
{
    //if(porte_empileur_is_open || bras_droit_is_risen)
    //    return 1;
    bras_gauche_is_risen=1;
    bras_gauche_set_angle(ANGLE_GOBELET_LIBRE_BRAS_GAUCHE);
    return 0;
}

int bras_gauche_coince_gobelet()
{
    //if(porte_empileur_is_open || bras_droit_is_risen)
    //    return 1;
    bras_gauche_is_risen=1;
    bras_gauche_set_angle(ANGLE_GOBELET_COINCE_BRAS_GAUCHE);
    gobelet_saisi=1;
    /*wait();
    bras_gauche_set_angle(ANGLE_GOBELET_LIBRE_BRAS_GAUCHE);
    wait();
    bras_gauche_set_angle(ANGLE_GOBELET_COINCE_BRAS_GAUCHE);*/
    return 0;
}

int bras_gauche_libere_gobelet()
{
    //if(porte_empileur_is_open || bras_droit_is_risen)
    //    return 1;
    bras_gauche_is_risen=1;
    bras_gauche_set_angle(ANGLE_GOBELET_LIBRE_BRAS_GAUCHE);
    gobelet_saisi=0;
    return 0;
}

//============================== BRAS DROIT =================================//

void bras_droit_repos()
{
    bras_droit_set_angle(ANGLE_REPOS_BRAS_DROIT);
    bras_droit_is_risen=0;
}

int bras_droit_position_clap()
{
    //if(porte_empileur_is_open || bras_gauche_is_risen)
    //    return 1;
    bras_droit_is_risen=1;
    bras_droit_set_angle(ANGLE_CLAP_BRAS_DROIT);
    return 0;
}

int bras_droit_position_prise_gobelet()
{
    //if(porte_empileur_is_open || bras_gauche_is_risen)
    //    return 1;
    bras_droit_is_risen=1;
    bras_droit_set_angle(ANGLE_GOBELET_LIBRE_BRAS_DROIT);
    return 0;
}

int bras_droit_coince_gobelet()
{
    //if(porte_empileur_is_open || bras_gauche_is_risen)
    //    return 1;
    bras_droit_is_risen=1;
    bras_droit_set_angle(ANGLE_GOBELET_COINCE_BRAS_DROIT);
    gobelet_saisi=1;
    /*wait();
    bras_droit_set_angle(ANGLE_GOBELET_LIBRE_BRAS_DROIT);
    wait();
    bras_droit_set_angle(ANGLE_GOBELET_COINCE_BRAS_DROIT);*/
    return 0;
}

int bras_droit_libere_gobelet()
{
    //if(porte_empileur_is_open || bras_gauche_is_risen)
    //    return 1;
    bras_droit_is_risen=1;
    bras_droit_set_angle(ANGLE_GOBELET_LIBRE_BRAS_DROIT);
    gobelet_saisi=0;
    return 0;
}

//================================ MOULIN ===================================//

void moulin_position_repos()
{
    attrape_popcorns_set_angle(ANGLE_REPOS_MOULIN);
}

void prend_pop_corn()
{
    /*int i;
    for(i=ANGLE_REPOS_MOULIN,i<ANGLE_VIDE_POP_CORN,i++)
    {
        attrape_popcorns_set_angle(i);
        //wait(SLOW_PREND_POP_CORN);
    }*/
    attrape_popcorns_set_angle(ANGLE_PREND_POP_CORN);
}

void libere_pop_corn()
{
    int i;
    for(i=ANGLE_REPOS_MOULIN;i>ANGLE_VIDE_POP_CORN;i--)
    {
        attrape_popcorns_set_angle(i);
        delay_ms(SLOW_VIDE_POP_CORN);
    }
    attrape_popcorns_set_angle(ANGLE_VIDE_POP_CORN);
    //wait éventuel
    //moulin_position_repos();
}

//============================= INIT INTERNE ================================//

void init_protection_perimetre()
{
    porte_empileur_is_open=0;
    bras_droit_is_risen=0;
    bras_gauche_is_risen=0;
}

void init_position_actionneurs()
{
    moulin_position_repos();
    bras_droit_repos();
    bras_gauche_repos();
    ferme_porte_empileur();
}
