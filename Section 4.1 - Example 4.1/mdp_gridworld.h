#ifndef MDP_GRIDWORLD_H
#define MDP_GRIDWORLD_H

#include <stdlib.h>
#include <curses.h>

/* Data Structures */
typedef struct pos {
    int x;
    int y;
} pos;

/* Markov Decision Process (for a gridworld) */
double mdp_dynamics_gw(size_t s, size_t a, pos* S, pos* A, double* R, size_t h, size_t w);
size_t next_state_gw(pos Ss, pos Aa, size_t h, size_t w);

/* Draw gridworld in curses */
void draw(char c);
void draw_gridworld(pos* S, size_t N);
void move_gridworld(pos Ss);

#endif /* MDP_GRIDWORLD_H */
