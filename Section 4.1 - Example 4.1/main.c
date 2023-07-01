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
#define STR_LEN 128

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
  size_t N = H*W; /* Number of states */
  size_t K = 4; /* Number of actions */
  pos S[N]; /* States, as x,y positions */
  pos A[K]; /* Posible actions, how x,y will change */
  double R[N]; /* Rewards */
  double pi[N][K]; /* Stochastic policy */
  size_t pi_A[K]; /* policy improvement */
  double Hs[N][K]; /* Policy preferences */
  double v[N], V[N]; /* State-value functions */
  double q[N][K]; /* Action-value function */

  /*******************/
  /* Initializations */
  /*******************/
  /* Set of states saved to array */
  for (size_t i = 0; i < N; i++) {
    S[i].x = i%W; /* Translate index to grid coordinates */
    S[i].y = i/H;
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
    /* Initialize arrays */
    v[i] = 0;
    V[i] = 0;

    for (size_t ii = 0; ii < K; ii++) {
      pi[i][ii] = 0.25;
      q[i][ii] = 0;
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
  double E = 0.1; /* theta, threshold of return increase */
  double g = 0.7; /* gamma, discounted return */
  double Vsum = 0; /* sum of policy for each state */
  bool policy_stable = true; /* decision for policy improvement */
  char str[STR_LEN]; /* string for displaying messages */
  size_t a_new = 0;

  /* Training loop */
  while(1) {
    char c = getch();
    if (c == 'q') break; /* Quit */

    else { /* Start training */
      do {
        /* Policy Evaluation */
        do {
          /* Redraw gridworld */
          clear();
          draw_gridworld(S, N);
          move(0,(W)*W_scale+4);
          winsnstr(wnd, "0 = UP, 1 = DOWN, 2 = RIGHT, 3 = LEFT", STR_LEN);
          move((H-1)*H_scale,(W)*W_scale);

          dv = 0; /* Reset evaluation */
          for (size_t s = 1; s < (N-1); s++) { /* Loop over all states */
            /* Update V(s) */
            v[s] = V[s]; /* Store old state-value: v <- V(s) */
            Vsum = 0;
            for (size_t a = 0; a < K; a++) {
              size_t sn = next_state_gw(S[s], A[a]); /* Calculate index of next state */
              q[s][a] = pi[s][a]*(R[s] + g*V[sn]); /* MDP dynamics: p(sn,r|s,pi(s)) */
              Vsum += q[s][a]; /* state-value is sum of action-values? */
            }
            V[s] = Vsum; /* V(s) <- MDP dynamics */
            dv = (dv > fabs(v[s] - V[s]) ? dv : fabs(v[s] - V[s])); /* Update state-value improvement */

            /* Print value in grid */
            move_gridworld(S[s]);
            sprintf(str, "%0.2g", V[s]);
            winsnstr(wnd, str, STR_LEN);
          }
        } while(dv > E); /* Break when update less than margin */
        move((H-1)*H_scale,(W)*W_scale);
        winsnstr(wnd, "  Done evaluating\n", STR_LEN);
        getch();

        /* Policy Improvement */
        policy_stable = true;
        for (size_t s = 1; s < (N-1); s++) {
          size_t a_old = argmax(pi[s], K);
          /* Update policy */
          softmax(pi[s], q[s], K);
          /* Get a_new from updated policy */
          a_new = argmax(pi[s], K);
          /* Check policy */
          policy_stable = ((policy_stable && (a_old == a_new)) ? true : false);

          /* Display results */
          move((H-1)*H_scale,(W)*W_scale);
          sprintf(str, "   q[%zu][%d] = %0.2g,  q[%zu][%d] = %0.2g,  q[%zu][%d] = %0.2g,  q[%zu][%d] = %0.2g\n",
                  s, 0, q[s][0], s, 1, q[s][1], s, 2, q[s][2], s, 3, q[s][3]);
          winsnstr(wnd, str, STR_LEN);

          move((H-1)*H_scale+1,(W)*W_scale);
          sprintf(str, "   p[%zu][%d] = %0.2g,  p[%zu][%d] = %0.2g,  p[%zu][%d] = %0.2g,  p[%zu][%d] = %0.2g\n",
                  s, 0, pi[s][0], s, 1, pi[s][1], s, 2, pi[s][2], s, 3, pi[s][3]);
          winsnstr(wnd, str, STR_LEN);

          move((H-1)*H_scale+2,(W)*W_scale);
          sprintf(str, "   Policy stable? %d\n", policy_stable);
          winsnstr(wnd, str, STR_LEN);

          move_gridworld(S[s]);
          getch();
        }
        
      } while (!policy_stable);
      
      break;
    }
  }

  endwin();
  return 0;
}


            
            // /* Action probability, of previous H */
            // softmax(pi, H, K);

            // /* Pick previous action, based on previous H */
            // A = (t > 0 ? random_decision(pi, K) : (size_t)rand()%K);

            // /* Generate reward of previous action */
            // randn(q[A], 1, &R, 1);

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