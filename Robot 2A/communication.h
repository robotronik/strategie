#ifndef COMMUNICATION_H
#define COMMUNICATION_H

// Ce fichier définit une interface avec l'UART, afin de simplifier les choses.

// Une fonction de réception
void get_asser_done();

// Les fonctions permettant de donner à l'asser une liste de points…
void asser_begin_passage_sequence();	// Utile ?
void asser_send_passage_point(int x, int y);
void asser_finish_passage_sequence();
// … Et de l'exécuter.
void asser_execute_passage_sequence();

void asser_match_end();
void asser_emergency_stop();
void set_max_speed(int v);	// Valeur arbitraire. Je sais, c'est pas encore implémenté.

// Utile pour le callage sur les parois.
void set_real_position(int x, int y, int millirads);

#endif
