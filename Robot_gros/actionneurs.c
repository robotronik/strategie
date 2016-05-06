#include "actionneurs.h"
#include "hardware/servos.h"
#include <alarms_and_delay.h>

void init_protection_perimetre();
void init_position_actionneurs();


//================================= INIT ====================================//

void init_actionneurs()
{
    init_all_servo();
    init_protection_perimetre();
    init_position_actionneurs();
    /*descend_ascenseur();
    delay_ms(10);
    monte_pied();*/

}

void init_protection_perimetre()
{
 
}

void init_position_actionneurs()
{

}
