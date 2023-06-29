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
  int Sn[N]; /* Number of possible next states give current state */
  pos A[K]; /* Posible actions, how x,y will change */
  double R[N]; /* Rewards */
  double pi[N][K]; /* Stochastic policy */
  double H[N][K]; /* Policy preferences */
  double v[N], V[N]; /* State-value functions */

  /*******************/
  /* Initializations */
  /*******************/
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

  /************/
  /* Training */
  /************/
  double dv = 0; /* delta V, return increase */
  double E = 0.1; /* epsilon, threshold of return increase */
  double g = 0.7; /* gamma, discounted return */
  double Vsum = 0; /* sum of policy for each state */
  double mdp = 0; /* mdp dynamics summation */
  size_t sn = 0; /* next-state */
  bool policy_stable = true; /* decision for policy improvement */
  char str[64]; /* string for displaying messages */

  /* Training loop */
  while(1) {
    char c = getch();
    if (c == 'q') break; /* Quit */

    else { /* Start training */
      /* Policy Evaluation */
      do {
        clear();
        draw_gridworld(S, N);
        dv = 0; /* Reset evaluation */
        for (size_t s = 1; s < (N-1); s++) {
          /* Calculate summations */
          v[s] = V[s]; /* Store old state-value: v <- V(s) */
          Vsum = 0;
          for (size_t a = 0; a < K; a++) {
            size_t sn = next_state_gw(S[s], A[a], h, w); /* Possible next states */
            Vsum += pi[s][a]*(R[sn] + g*V[sn]); /* MDP dynamics: p(sn,r|s,pi(a)) */
          }
          V[s] = Vsum; /* V(s) <- MDP dynamics */
          dv = (dv > fabs(v[s] - V[s]) ? dv : fabs(v[s] - V[s])); /* Update state-value improvement */
          /* Print status */
          sprintf(str, " fabs(v[%zu] - V[%zu]) = %0.2g, dv = %0.2g\n", s, s, fabs(v[s] - V[s]), dv);
          winsnstr(wnd, str, 64);
          /* Print value in grid */
          move_gridworld(S[s]);
          sprintf(str, "%0.2g", V[s]);
          winsnstr(wnd, str, 64);
          move(6,28);
          getch();
        }
      } while(dv > E); /* Break when update less than margin */
      winsnstr(wnd, " Done evaluating\n", 64);
      getch();
      break;

      /* Policy Improvement */
      // do {
      //   for (size_t s = 1; s < (N-1); s++) {

      //   }
      // } while (!policy_stable);
    }
  }

  endwin();
  return 0;
}

          // sprintf(str, "v[s] = %0.2g, V[s] = %0.2g\n", v[s], V[s]);
          // winsnstr(wnd, str, 64);
          // getch();

          // mdp = mdp_dynamics_gw(s, a, S, A, R, h, w);
          // V[s] = (R[s] + g*V[sn]); /* MDP dynamics equation */
/* Code Testing */

  // /* Testing variables */
  // size_t ss = 3;
  // int aa = 1;
    // else if (c == ' ') {
    //   /* Code testing */
    //   move_gridworld(S[ss]);
    //   refresh();
    //   c = getch();
    //   ss = next_state_gw(S[ss], A[aa], h, w);
    //   move_gridworld(S[ss]);
    //   refresh();
    // }