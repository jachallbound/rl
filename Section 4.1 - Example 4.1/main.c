#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "ltqnorm.h"
#include "functions.h"

/* Declarations */
/* Structures */
typedef struct pos {
  int x;
  int y;
} pos;

/* Functions */
void draw(char c);
void draw_gridworld(pos* S, size_t N);

/* Macros */


/* Main */
int main (void) {
  /* Set random seed */
  srand(time(NULL));

  /*** CURSES ***/
  WINDOW* wnd = initscr(); /* curses call to initialize window */
  cbreak(); /* curses call to set no waiting for Enter key */
  noecho(); /* curses call to set no echoing */
  clear(); /* curses call to clear screen, send cursor to position (0,0) */
  refresh(); /* curses call to implement all changes since last refresh */
  /*** END CURSES ***/

  /* Arrays */
  size_t N = 16; /* Number of states */
  size_t K = 4; /* Number of actions */
  pos S[N]; /* States, as x,y positions */
  double R[N]; /* Rewards */
  double pi[N][K]; /* Stochastic policy */
  double H[N][K]; /* Policy preferences */
  double v[N], V[N]; /* State-value functions */

  /* Initializations */
  /* Set of states saved to array */
  for (size_t i = 0; i < N; i++) {
    S[i].x = i%K; /* Translate index to grid coordinates */
    S[i].y = i/K;
  }
  /* Draw gridworld from array of states */
  draw_gridworld(S, N);

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
  int s = (rand()%(N-3))+1; /* Random first state, 1-14 */
  int sp = s; /* Next state */
  int a = rand()%3; /* Random first action */

  /************/
  /* Training */
  /************/
  double dv = 0; /* delta V, return increase */
  double E = 0.1; /* epsilon, threshold of return increase */
  double g = 0.7; /* gamma, discounted return */

  while(1) {
    char c = getch();
    if (c == 'q') break; /* Quit */
    else { /* Start training */
      /* Policy Evaluation */
      dv = 0;
      do {
        for (size_t i = 1; i < (N-1); i++) {
          v[i] = V[i];
          V[i] = (R[s] + g*V[sp]); /* MDP dynamics equation */
          dv = (dv > fabs(v[i] - V[i]) ? dv : fabs(v[i] - V[i]));
        }
      } while(dv > E);
    }
  }

  endwin();
  return 0;
}

/* Functions */
void draw(char c) {
  delch();
  insch(c);
  return;
}

void draw_gridworld(pos* S, size_t N) {
  /* Draw gridworld from array of states */
  for (size_t i = 0; i < N; i++) {
    if (i < 10) {
      move(S[i].y, S[i].x*3+1);
      draw(48+i);
    } else {
      move(S[i].y, S[i].x*3);
      draw(48+1);
      move(S[i].y, S[i].x*3+1);
      draw(48+i-10);
    }
    refresh();
  }
  move(3,12);
  return;
}
