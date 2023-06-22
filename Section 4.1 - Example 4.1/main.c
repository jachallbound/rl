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

  /*** CURSES PREAMBLE ***/
  WINDOW* wnd = initscr(); /* curses call to initialize window */
  cbreak(); /* curses call to set no waiting for Enter key */
  noecho(); /* curses call to set no echoing */
  clear(); /* curses call to clear screen, send cursor to position (0,0) */
  refresh(); /* curses call to implement all changes since last refresh */
  /*** END CURSES PREAMBLE ***/

  /* Initializations */
  /* Set of states saved to array */
  size_t N = 16;
  pos S[N];
  for (size_t i = 0; i < N; i++) {
    S[i].x = i%4; /* Translate index to grid coordinates */
    S[i].y = i/4;
  }
  /* Draw gridworld from array of states */
  draw_gridworld(S, N);

  /* Policy, start equiprobable */
  /* Policy: 0 = up, 1 = down, 2 = right, 3 = left */
  double pi[N][4];
  for (size_t i = 0; i < N; i++)
    for (size_t ii = 0; ii < 4; ii++)
      pi[i][ii] = 0.25;

  /* Loop: begin training or quit */
  while(1) {
    char c = getch();
    if (c == 'q') break; /* Quit */
    else { /* Start training */
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
