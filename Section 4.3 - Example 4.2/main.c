#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "ltqnorm.h"
#include "functions.h"
#include "mdp_car_rental.h"

/* Declarations */

/* Functions */

/* Macros */
#define STR_LEN 128
#define MAX_CARS 20
#define MAX_CARS_MOVE 5
#define R1 10 /* Return when a car is available to rent */
#define R0 0 /* Return when no car is available to rent */
#define RQ1 3 /* Expected rent requests at lot 1 */
#define RQ2 4 /* Expected rent requests at lot 2 */
#define RT1 3 /* Expected car returns at lot 1 */
#define RT2 2 /* Expected car returns at lot 2 */
#define G 0.9 /* gamma, discounted returns */

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

  /* Values and Arrays */
  int N = (MAX_CARS+1) * (MAX_CARS+1); /* number of states is (MAX_CARS+1)^2 */
  int K = MAX_CARS_MOVE*2 + 1; /* number of possible actions */
  int pi[N]; /* policy */
  pos S[N]; /* State space */
  double V[N]; randn(0, 1, V, N); /* State-value function */
  double v = 0, dV = 0;
  double E = 0.1;
  int r = 0; /* Reward */
  char str[STR_LEN];

  /* Initialize */
  for (int i = 0; i < N; i++) {
    /* Generate states, x is lot1, y is lot2 */
    S[i].x = i%MAX_CARS;
    S[i].y = i/MAX_CARS;

    /* Initialize policy to move 0 cars */
    pi[i] = 0;
  }

  /* Before training */
  int t = 0, T = 10; /* time steps */
  pos Sp; /* next state */
  int sp = 0; /* next state index */
  int n1 = 0, n2 = 0, nt1 = 0, nt2 = 0;
  double p = 0; /* poisson values */
  int policy_stable = 0; /* policy_stable count */
  do {
    do { /* Policy evalutation */
      dV = 0;
      for (int s = 0; s < N; s++) {
        nt1 = 0, nt2 = 0; /* Reset returned cars */
        v = V[s]; /* store old state-value */
        sp = s;
        for (t = 0; t < T; t++) { /* iterate time-steps here? */
          /* Probability of returned cars from yesterday */
          //p = pdfp(RT1, nt1)*pdfp(RT2, nt2);
          /* Update state: add moved cars from last night */
          Sp = car_policy(pi[sp]);
          /* Update state: add returned cars from previous day */
          Sp.x += nt1;
          Sp.y += nt2;
          /* Generate requested and returned cars */
          randp(RQ1, &n1, 1); /* requested cars today at lot 1 */
          randp(RQ2, &n2, 1); /* requested cars today at lot 2 */
          randp(RT1, &nt1, 1); /* returned cars today at lot 1 */
          randp(RT2, &nt2, 1); /* returned cars today at lot 2 */
          /* Calculate reward */
          r = 0;
          r += (S[sp].x - n1 >= 0 ? R1*n1 : R1*S[sp].x); /* Breaks if lot has negative cars, */
          r += (S[sp].y - n2 >= 0 ? R1*n2 : R1*S[sp].y); /* which shouldn't happen */
          sprintf(str, "x = %d, n1 = %d, y = %d, n2 = %d, r = %d\n", S[sp].x, n1, S[sp].y, n2, r);
          /* Update state: remove requested cars from today */
          Sp.x -= n1;
          Sp.y -= n2;
          /* New state */
          sp = next_state(S[sp], Sp);
          /* MDP: probability p = P(n1)*P(n2)*P(nt1)*P(nt2)*1/K ??? */
          p = pdfp(RQ1, n1)*pdfp(RQ2, n2); ///(double)K;
          /* Update state-value */
          V[s] = (r+G*V[sp]);

          move(0,0);
          winsnstr(wnd, str, 128);
          refresh();
        }
        dV = max(dV, fabs(v-V[s]));
        sprintf(str, "v = %0.2g, V[%d] = %0.2g, dV = %0.2g\n", v, s, V[s], dV);
        move(1,0);
        winsnstr(wnd, str, 128);
        refresh();
        getch();
      }
    } while (dV > E);
  } while (policy_stable < N);
  
  endwin();
  return 0;
}
