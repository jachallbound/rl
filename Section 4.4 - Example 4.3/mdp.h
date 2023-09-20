#ifndef MDP_H
#define MDP_H

#include <stdlib.h>
#include <math.h>
#include <curses.h>

#include "data_structures.h"
#include "functions.h"

/* Macros */

/* MDP */
double mdp(int s, double* V);

/* Draw in curses */
void draw(char c);

#endif /* MDP_H */