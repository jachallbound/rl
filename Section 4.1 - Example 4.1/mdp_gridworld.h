#ifndef MDP_GRIDWORLD_H
#define MDP_GRIDWORLD_H

#include <stdlib.h>
#include <curses.h>

/* Macros */
#define H 4
#define W 4
#define H_scale 3
#define W_scale 7

/* Data Structures */
typedef struct pos {
    int x;
    int y;
} pos;

/* Calculate next state (for a gridworld) */
size_t next_state_gw(pos Ss, pos Aa);

/* Draw gridworld in curses */
void draw(char c);
void draw_gridworld(pos* S, size_t N);
void move_gridworld(pos Ss);

#endif /* MDP_GRIDWORLD_H */
