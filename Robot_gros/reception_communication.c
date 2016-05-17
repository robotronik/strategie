// Fonctions de l'asservissement

#include "reception_communication.h"
#include <debug.h>
#include <UART.h>

Reception_object values;


void init_reception_communication(){
    init_reception(&values, callbacks);
}

void gestion_communication() {
    char c;
    if (UART_getc(&c)) {
        lecture_message((char) c, &values);
    }
}

/* void reception_done() { */
/*     set_ledOrange(); */
/*     asser_done = 1; */
/* } */

/* void reset_asser_done() { */
/*     asser_done = 0; */
/* } */

/* int asser_is_done() { */
/*     return asser_done; */
/* } */

char buffer[40];

int received_theta,
    received_x,
    received_y;

void reception_set_x() {
    received_x = values.received_value;
}
void reception_set_y() {
    received_y = values.received_value;
}
void reception_set_theta() {
    received_theta = values.received_value;
}

// Est à 1 pour que la première action s'effectue.
int received_asser_done = 1;
void reception_done() {
    set_ledOrange();
    received_asser_done = 1;
}
int get_asser_done_and_reset() {
    if (received_asser_done ==1) {
        received_asser_done = 0;
        return 1;
    } else {
        return 0;
    }
}

int asser_is_done()
{
  return received_asser_done;
}

void reception_send_pos() {
}
void reception_quit() {
}


callback_t callbacks[KEYS_SIZE] = {
    //// Ces fonctions attendent une valeur entière
    [VAL_X]             = reception_set_x,
    [VAL_Y]             = reception_set_y,
    [VAL_ALPHA]         = NULL,
    [VAL_DELTA]         = NULL,
    [VAL_THETA]         = reception_set_theta,

    [VAL_KP_DELTA]      = NULL,
    [VAL_KD_DELTA]      = NULL,
    [VAL_KP_ALPHA]      = NULL,
    [VAL_KD_ALPHA]      = NULL,

    // Avant, on a un arg. Après, pas d'args.

    //// Ces commandes ne demandent pas d'argument

    // Fonctions : à appeler après avoir envoyé des valeurs pour "confirmer"
    [FCT_ALPHA_DELTA]   = NULL,
    [FCT_XY_RELATIF]    = NULL,
    [FCT_XY_ABSOLU]     = NULL,
    [FCT_THETA]         = NULL,

    [FCT_ADD]           = NULL,
    [FCT_CLEAR]         = NULL,
    [FCT_CHEMIN]        = NULL,

    [FCT_MODE_TENDU]    = NULL,
    [FCT_MODE_COURBE]   = NULL,

    [FCT_SET_POS]       = NULL,
    [FCT_SET_PID]       = NULL,


    [CMD_DONE]          = reception_done,
    [CMD_GET_POS]       = NULL,
    [CMD_SEND_POS]      = reception_send_pos,
    [CMD_QUIT]          = NULL, // TODO ?
    [CMD_HELP]          = NULL,

    [CMD_STOP]          = NULL,
    [CMD_EMERGENCY_STOP]= NULL,

};
