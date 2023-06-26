#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "ltqnorm.h"
#include "functions.h"
#include "mdp_gridworld.h"

/* Declarations */

/* Functions */

/* Macros */


/* Main */
int main (void) {
  /* Set random seed */
  WINDOW* wnd = initscr(); /* curses call to initialize window */
  cbreak(); /* curses call to set no waiting for Enter key */
  noecho(); /* curses call to set no echoing */
  clear(); /* curses call to clear screen, send cursor to position (0,0) */
  refresh(); /* curses call to implement all changes since last refresh */
  /*** END CURSES ***/

  /* Arrays */
  size_t h = 4, w = 4; /* height and width of gridworld */
  size_t N = h*w; /* Number of states */
  size_t K = 4; /* Number of actions */
  pos S[N]; /* States, as x,y positions */
  pos A[K]; /* Posible actions, how x,y will change */
  double R[N]; /* Rewards */
  double pi[N][K]; /* Stochastic policy */
  double H[N][K]; /* Policy preferences */
  double v[N], V[N]; /* State-value functions */

  /* Initializations */
  /* Set of states saved to array */
  for (size_t i = 0; i < N; i++) {
    S[i].x = i%w; /* Translate index to grid coordinates */
    S[i].y = i/h;
  }
  /* Draw gridworld from array of states */
  draw_gridworld(S, N);

  /* Actions */
  /* Actions: 0 = up, 1 = down, 2 = right, 3 = left */
  A[0].x = 0; A[0].y = -1;
  A[1].x = 0; A[1].y = 1;
  A[2].x = 1; A[2].y = 0;
  A[3].x = -1; A[3].y = 0;

  /* Rewards */
  for (size_t i = 1; i < (N-1); i++) R[i] = -1;
  R[0] = 0;
  R[N-1] = 0;

  /* Policy, start equiprobable */
  /* Policy: 0 = up, 1 = down, 2 = right, 3 = left */
  for (size_t i = 0; i < N; i++) {
    for (size_t ii = 0; ii < K; ii++) {
      pi[i][ii] = 0.25;
      H[i][ii] = 0;
    }
  }

  /* State-value function */
  randn(0, 1, V, N); /* Initialize V with random values */
  V[0] = 0; /* Terminal states are 0 */
  V[N-1] = 0;

  /* First state and action (needed?) */
  //int s = (rand()%(N-3))+1; /* Random first state, 1-14 */
  int sp = 0; /* Next state */
  //int a = rand()%3; /* Random first action */

  /************/
  /* Training */
  /************/
  double dv = 0; /* delta V, return increase */
  double E = 0.1; /* epsilon, threshold of return increase */
  double g = 0.7; /* gamma, discounted return */
  double evaluation = 0; /* sum of policy for each state */
  double mdp = 0; /* mdp dynamics summation */

  /* Testing variables */
  size_t ss = 12;
  int a = 1;

  /* Training loop */
  while(1) {
    char c = getch();
    if (c == 'q') break; /* Quit */
    else if (c == ' ') {
      /* Code testing */
      move_gridworld(S[ss]);
      refresh();
      c = getch();
      ss = next_state_gw(S[ss], A[a], h, w);
      move_gridworld(S[ss]);
      refresh();
    }
    else { /* Start training */
      /* Policy Evaluation */
      dv = 0;
      do {
        for (size_t s = 1; s < (N-1); s++) {
          /* Calculate summations */
          evaluation = 0;
          for (size_t a = 0; a < K; a++) {
            mdp = mdp_dynamics_gw(s, a, S, A, R, h, w);
            evaluation += pi[s][a];
          }
          v[s] = V[s]; /* Store old state-value */
          V[s] = (R[s] + g*V[sp]); /* MDP dynamics equation */
          dv = (dv > fabs(v[s] - V[s]) ? dv : fabs(v[s] - V[s])); /* Update state-value improvement */
        }
      } while(dv > E); /* Break when update less than margin */
    }
  }

  endwin();
  return 0;
}
