#ifndef MONTE_CARLO_BLACKJACK_H
#define MONTE_CARLO_BLACKJACK_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "functions.h"
#include "blackjack.h"
#include "volk_arrays.h"


/* Functions */
/* Mont carlo functions */
void monte_carlo_blackjack(double* Q, double* R, double* P, double* V, int episodes);
int monte_carlo_first_card_index(hand* h);

#if 0
/* 4d static array functions */
void zero_double_3d(double double_matrix[S0][S1][S2]);
void zero_double_4d(double double_matrix[S0][S1][S2][A0]);
void zero_int_3d(int int_matrix[S0][S1][S2]);
void zero_int_4d(int int_matrix[S0][S1][S2][A0]);
#endif

#endif /* MONTE_CARLO_BLACKJACK_H */
