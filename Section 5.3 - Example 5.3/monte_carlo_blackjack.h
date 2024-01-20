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


/* Global */
extern int mc_debug;

/* Functions */
/* Mont carlo functions */
void monte_carlo_blackjack(double* Q, double* R, double* P, double* V, int episodes);
int monte_carlo_first_card_index(hand* h);

#endif /* MONTE_CARLO_BLACKJACK_H */