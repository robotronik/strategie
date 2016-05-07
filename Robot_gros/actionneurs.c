#include "actionneurs.h"
#include "hardware/servos.h"
#include "xl_320.h"
#include <alarms_and_delay.h>

void init_protection_perimetre();
void init_position_actionneurs();


//================================= INIT ====================================//

void init_actionneurs()
{
    //init_all_servo();
    //init_protection_perimetre();
    //init_position_actionneurs();
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



//================================= SERVOS ===================================//
XL_320_socket_t socket_servos;

XL_320_servo_t servo_porte_gauche;
XL_320_servo_t servo_porte_droite;
XL_320_group_t portes;

XL_320_servo_t servo_peche_plexy_gauche;
XL_320_servo_t servo_peche_plexy_droite;
XL_320_group_t group_peche_plexy;

XL_320_servo_t servo_peche_aimants_gauche;
XL_320_servo_t servo_peche_aimants_droite;
XL_320_group_t group_peche_aimants;


void init_servos() {
    init_socket(&socket_servos,&send_servo);
    init_servo(&servo_porte_gauche,0x02,&socket_servos);
    init_servo(&servo_porte_droite,0x01,&socket_servos);
    init_group(&portes);
    add_servo_to_group(&servo_porte_gauche, &portes);
    add_servo_to_group(&servo_porte_gauche, &portes);


    init_servo(&servo_peche_plexy_gauche,0x03,&socket_servos);
    init_servo(&servo_peche_plexy_droite,0x04,&socket_servos);
    init_group(&group_peche_plexy);
    add_servo_to_group(&servo_peche_plexy_gauche, &group_peche_plexy);
    add_servo_to_group(&servo_peche_plexy_droite, &group_peche_plexy);

    init_servo(&servo_peche_aimants_gauche,0x05,&socket_servos);
    init_servo(&servo_peche_aimants_droite,0x06,&socket_servos);
    init_group(&group_peche_aimants);
    add_servo_to_group(&servo_peche_aimants_gauche, &group_peche_aimants);
    add_servo_to_group(&servo_peche_aimants_droite, &group_peche_aimants);

    //set_baud_rate(3);
    //delay_ms(1000);

    set_control_mode_servo  (&servo_porte_gauche, JOIN_MODE, 1);
    set_speed_servo         (&servo_porte_gauche, 80, 1);
    enable_power_servo      (&servo_porte_gauche, 1);
    set_led_color_servo     (&servo_porte_gauche, servo_porte_gauche.ID,0);

    set_control_mode_servo  (&servo_porte_droite, JOIN_MODE, 1);
    set_speed_servo         (&servo_porte_droite, 80, 1);
    enable_power_servo      (&servo_porte_droite, 1);
    set_led_color_servo     (&servo_porte_droite, servo_porte_droite.ID,0);

    set_control_mode_servo  (&servo_peche_plexy_gauche, JOIN_MODE, 1);
    set_speed_servo         (&servo_peche_plexy_gauche, 80, 1);
    enable_power_servo      (&servo_peche_plexy_gauche, 1);
    set_led_color_servo     (&servo_peche_plexy_gauche, servo_peche_plexy_gauche.ID,0);

    set_control_mode_servo  (&servo_peche_plexy_droite, JOIN_MODE, 1);
    set_speed_servo         (&servo_peche_plexy_droite, 80, 1);
    enable_power_servo      (&servo_peche_plexy_droite, 1);
    set_led_color_servo     (&servo_peche_plexy_droite, servo_peche_plexy_droite.ID,0);

    set_control_mode_servo  (&servo_peche_aimants_gauche, JOIN_MODE, 1);
    set_speed_servo         (&servo_peche_aimants_gauche, 80, 1);
    enable_power_servo      (&servo_peche_aimants_gauche, 1);
    set_led_color_servo     (&servo_peche_aimants_gauche, servo_peche_aimants_gauche.ID,0);

    set_control_mode_servo  (&servo_peche_aimants_gauche, JOIN_MODE, 1);
    set_speed_servo         (&servo_peche_aimants_gauche, 80, 1);
    enable_power_servo      (&servo_peche_aimants_gauche, 1);
    set_led_color_servo     (&servo_peche_aimants_gauche, servo_peche_aimants_gauche.ID,0);

    set_control_mode_servo  (&servo_peche_aimants_droite, JOIN_MODE, 1);
    set_speed_servo         (&servo_peche_aimants_droite, 80, 1);
    enable_power_servo      (&servo_peche_aimants_droite, 1);
    set_led_color_servo     (&servo_peche_aimants_droite, servo_peche_aimants_droite.ID,0);

    launch_previous_action(&socket_servos.group);
}


#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) < (y) ? (y) : (x))

void set_baud_rate(int baudrate) {
    send_data_servo(&servo_peche_plexy_droite, BAUDRATE, baudrate, 1);
    send_data_servo(&servo_peche_plexy_gauche, BAUDRATE, baudrate, 1);
    send_data_servo(&servo_peche_aimants_droite, BAUDRATE, baudrate, 1);
    send_data_servo(&servo_peche_aimants_gauche, BAUDRATE, baudrate, 1);
    send_data_servo(&servo_porte_droite, BAUDRATE, baudrate, 1);
    send_data_servo(&servo_porte_gauche, BAUDRATE, baudrate, 1);
}

void set_position_porte_gauche(int position) {
    set_angle_servo(&servo_porte_gauche, 830-position, 1);

}
void set_position_porte_droite(int position) {
    set_angle_servo(&servo_porte_droite, 210+position, 1);

}

void set_position_portes(int position) {
    position = min(max(0, position), 400);
    set_position_porte_gauche(position);
    set_position_porte_droite(position);
}


void set_position_peche_plexy(int position) {
    position = min(max(0, position), 350);
    set_angle_servo(&servo_peche_plexy_gauche, 820-position, 0);
    set_angle_servo(&servo_peche_plexy_droite, 190+position, 0);
    launch_previous_action(&group_peche_plexy);
}

void set_position_peche_aimants(int position) {
    position = min(max(0, position), 210);
    set_angle_servo(&servo_peche_aimants_gauche, 210-position, 0);
    set_angle_servo(&servo_peche_aimants_droite, 510+position, 0);
    launch_previous_action(&group_peche_aimants);
}


// 200, 200 fonctionnent bien pour lâcher les poissons
// 200, 200 fonctionnent bien pour lâcher les poissons
