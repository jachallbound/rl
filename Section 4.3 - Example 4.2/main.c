#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "data_structures.h"
#include "ltqnorm.h"
#include "functions.h"
#include "mdp_car_rental.h"

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
  int N = (MAX_CARS+1) * (MAX_CARS+1); /* number of states is (MAX_CARS+1)^2 */
  int K = MAX_CARS_MOVE*2 + 1; /* number of possible actions */
  int pi[N]; /* policy */
  int old_a; /* actions */
  pos S[N]; /* State space */
  double V[N]; randn(0, 1, V, N); /* State-value function */
  double Vk[K]; /* state-value used in policy improvement */
  double v = 0, dV = 0;
  double E = .1;
  // int r = 0; /* Reward */
  char str[STR_LEN];

  /* Initialize */
  for (int i = 0; i < N; i++) {
    /* Generate states, x is lot1, y is lot2 */
    S[i].x = i%MAX_CARS;
    S[i].y = i/MAX_CARS;

    /* Initialize to 0 */
    pi[i] = 0;
    Vk[i] = 0;
  }

  /* Before training */
  int s = 0; //, sp = 0; /* next state index */
  int policy_stable = 0; /* policy_stable count */
  do {
    do { /* Policy evaluation */
      dV = 0;
      for (s = 0; s < N; s++) {
        /* Formuoli */
        v = V[s]; /* store old state-value */
        V[s] = mdp_car_rental(S[s], pi[s], V);
        dV = max(dV, fabs(v-V[s]));

        /* Display */
        sprintf(str, "v = %4.1f, V[%3d] = %4.1f, \tdV = %4.1f\n", v, s, V[s], dV);
        move(0,0);
        winsnstr(wnd, str, 128);
        refresh();
      }
    } while (dV > E);
    /* Policy improvement */
    /* Formuoli */
    policy_stable = 0;
    for (s = 0; s < N; s++) {
      old_a = pi[s];
      for (int a = 0; a < K; a++) {
        Vk[a] = mdp_car_rental(S[s], a - MAX_CARS_MOVE, V);
        /* Display */
        sprintf(str, "Vk[%3d] = %4.1f\n", a-MAX_CARS_MOVE, Vk[a]);
        move(0,0);
        winsnstr(wnd, str, 128);
        refresh();
      }
      pi[s] = argmax(Vk, K) - MAX_CARS_MOVE;
      if(old_a == pi[s]) policy_stable++; /* Increment policy_stable */

      /* Display */
      sprintf(str, "Testing policy: p[%3d] = %3d, old action = %3d\n", s, pi[s], old_a);
      move(1,0);
      winsnstr(wnd, str, 128);
      refresh();
    }

    /* Display */
    sprintf(str, "Policies stable = %3d/%3d\n", policy_stable, N);
    move(2,0);
    winsnstr(wnd, str, 128);
    refresh();
  } while (policy_stable < N); /* All policies are stable when policy_stable == N */
  
  /* Policy improvement finished */
  sprintf(str, "Policy stabilized! (saved to file 'car_rental_policy.dat')\n");
  move(3,0);
  winsnstr(wnd, str, 128);
  getch();

  /* Save to file */
  FILE* f = fopen("car_rental_policy.dat", "w");
  for (int x = 0; x <= MAX_CARS; x++) {
    for (int y = 0; y <= MAX_CARS; y++) {
      fprintf(f, "%d ", pi[y*MAX_CARS + x]);
    }
    fprintf(f, "\n");
  }
  fclose(f);

  endwin();
  return 0;
}
