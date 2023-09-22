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
  char str[STR_LEN];

  /* Values and Arrays */
  int N = 99; /* number of states: 1-99 */
  int sweep = 0; /* number of sweeps */
  double V[N+2]; randn(0, 1, V, N); /* value function */
  V[0] = 0; V[N+1] = 1;
  int pi[N+2]; for (int i = 0; i < N+2; i++) pi[i] = 0; /* policy */

  double v = 0, dV = 0;
  double E = 1E-4;

  do { /* Value Iteration */
    /* Formuoli */
    dV = 0;
    for (int s = 1; s < N+1; s++) {
      v = V[s];
      V[s] = mdp(wnd, s, V, pi);
      dV = max(dV, fabs(v-V[s]));
    }

    /* Display */
    sprintf(str, "sweep: %2d, dV = %2.2f\n", sweep++, dV);
    move(1,0);
    winsnstr(wnd, str, 128);
    refresh();
  } while(dV > E);

  /* Print policy to file */
  FILE* f = fopen("policy.dat", "w");
  for (int s = 0; s < N+2; s++) {
    fprintf(f, "%d %d\n", s, pi[s]);
  }
  fclose(f);

  /* End Program */
  getch();
  endwin();
  return 0;
}
