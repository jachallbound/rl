#ifndef MONTE_CARLO_BLACKJACK_H
#define MONTE_CARLO_BLACKJACK_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "functions.h"
#include "blackjack.h"

/* Macros */
#define S0 10 /* 3D matrix dimension lengths */
#define S1 10
#define S2 2

/* Functions */
// void monte_carlo_blackjack(WINDOW* wnd, int pi, int* S, int episodes);
void monte_carlo_blackjack(double V[S0][S1][S2], int R[S0][S1][S2], int pi, int episodes);
void monte_carlo_play_hand(hand* hand0, int hit_threshold);

void zero_double_3d(double double_matrix[S0][S1][S2]);
void zero_int_3d(int int_matrix[S0][S1][S2]);

#endif /* MONTE_CARLO_BLACKJACK_H */