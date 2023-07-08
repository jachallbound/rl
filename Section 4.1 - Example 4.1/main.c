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
  srand(time(NULL));

  /*** BEGIN CURSES ***/
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
  double v[N], V[N]; /* State-value functions */
  double Va[K]; for(size_t i = 0; i < K; i++) Va[i] = 0; /* state-value for each action */

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
  }

  /* State-value function */
  randn(0, 1, V, N); /* Initialize V with random values */
  V[0] = 0; /* Terminal states are 0 */
  V[N-1] = 0;

  /************/
  /* Training */
  /************/
  double dv = 0; /* delta V, return increase */
  double E = 0.5; /* theta, threshold of return increase */
  double g = 0.7; /* gamma, discounted return */
  double Vsum = 0; /* sum of policy for each state */
  char str[STR_LEN]; /* string for displaying messages */

  /* Training loop */
  while(1) {
    char c = getch();
    if (c == 'q') break; /* Quit */

    else { /* Start training */
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
          for (size_t a = 0; a < K; a++) { /* Loop over next states (actions) */
            size_t sn = next_state_gw(S[s], A[a]); /* Calculate next state */
            /* MDP dynamics: pi(a|s) = 0.25 (equiprobable), p(sn,r|s,a) = 1.0 */
            Vsum += 0.25*(R[sn] + g*V[sn]);
          }
          V[s] = Vsum;
          dv = (dv > fabs(v[s] - V[s]) ? dv : fabs(v[s] - V[s])); /* Update state-value improvement */
          /* Print value in grid */
          move_gridworld(S[s]);
          sprintf(str, "%0.2g", V[s]);
          winsnstr(wnd, str, STR_LEN);
        }
        getch();
      } while(dv > E); /* Break when update less than margin */
      move((H-1)*H_scale,(W)*W_scale);
      winsnstr(wnd, "  Done evaluating\n", STR_LEN);
      getch();

      /* Test policy for every state */
      size_t a = 0, ss = 0;
      for (size_t s = 1; s < (N-1); s++) {
        /* Display in gridworld */
        move((H-1)*H_scale,(W)*W_scale);
        sprintf(str, "  Starting in state: %zu\n", s);
        winsnstr(wnd, str, STR_LEN);
        move((H-1)*H_scale+3,(W)*W_scale);
        sprintf(str, "\n");
        winsnstr(wnd, str, STR_LEN);

        ss = s;
        move_gridworld(S[ss]); /* move cursor */
        getch();

        do { /* take actions until in 0 or N-1 */
          for (a = 0; a < K; a++) { /* greedy search for best action */
            Va[a] = V[next_state_gw(S[ss], A[a])];
          }
          a = argmax(Va, K);
          ss = next_state_gw(S[ss], A[a]); /* choose argmax a */
          
          /* Display in gridworld */
          move((H-1)*H_scale+1,(W)*W_scale);
          sprintf(str, "  State: %zu, V[a=%d] = %0.2g, V[a=%d] = %0.2g, V[a=%d] = %0.2g, V[a=%d] = %0.2g\n",
                  ss, 0, Va[0], 1, Va[1], 2, Va[2], 3, Va[3]);
          winsnstr(wnd, str, STR_LEN);
          move((H-1)*H_scale+2,(W)*W_scale);
          sprintf(str, "  Took action: %zu\n", a);
          winsnstr(wnd, str, STR_LEN);
          move_gridworld(S[ss]); /* move cursor */
          getch();
        } while (ss != 0 && ss != N-1);
        /* Display in gridworld */
        move((H-1)*H_scale+3,(W)*W_scale);
        sprintf(str, "  Reached terminal position: %zu!\n", ss);
        winsnstr(wnd, str, STR_LEN);
        move_gridworld(S[ss]);
        getch();
      }
      move((H-1)*H_scale-2,(W)*W_scale);
      sprintf(str, "  PRESS ANY BUTTON TO QUIT\n");
      winsnstr(wnd, str, STR_LEN);
      getch();
      break;
    }
  }

  endwin();
  return 0;
}
