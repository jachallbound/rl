#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "data_structures.h"
#include "ltqnorm.h"
#include "functions.h"
#include "mdp.h"

/* Declarations */

/* Functions */

/* Macros */

/* Main */
int main (void) {
  /* Set random seed */
  srand(time(NULL));

  /*** BEGIN CURSES ***/
  WINDOW* wnd = initscr(); /* curses call to initialize window */
  cbreak(); /* curses call to set no waiting for Enter key */
  noecho(); /* curses call to set no echoing */
  clear(); /* curses call to clear screen, send cursor to position (0,0) */
  refresh(); /* curses call to implement all changes since last refresh */
  curs_set(0); /* display cursor or not */

  /* Values and Arrays */
  int N = 99; /* number of states: 1-99 */
  int K = N+1; /* max number of actions: 0-99 */
  double V[N]; randn(0, 0.1, V, N); /* value function */
  char str[STR_LEN];

  /* Policy iteration */
  double v = 0, dV = 0;
  double E = 0.1;

  for (int s = 1; s < N+1; s++) {
    /* Formuoli */
    v = V[s-1];
    V[s-1] = mdp(s, V);

    /* Display */
    sprintf(str, "v = %4.1f, V[%3d] = %4.1f, \tdV = %4.1f\n", v, s, V[s], dV);
    move(0,0);
    winsnstr(wnd, str, 128);
    refresh();
    getch();
  }

  /* End Program */
  endwin();
  return 0;
}
