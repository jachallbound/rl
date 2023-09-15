#ifndef MDP_CAR_RENTAL_H
#define MDP_CAR_RENTAL_H

#include <stdlib.h>
#include <math.h>
#include <curses.h>

#include "data_structures.h"
#include "functions.h"

/* Macros */
#define H 20
#define W 20
#define H_scale 1
#define W_scale 1

/* Data Structures */
typedef struct pos {
    int x;
    int y;
} pos;

/* MDP */
double mdp_car_rental(pos Ss, int a, double* V);
pos car_policy(int a);
int next_state(pos Ss, pos Aa);

/* Draw in curses */
void draw(char c);
void move_pos(pos Ss);

#endif /* MDP_CAR_RENTAL_H */
