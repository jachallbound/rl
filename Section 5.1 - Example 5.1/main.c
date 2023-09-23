#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "functions.h"
#include "blackjack.h"

/* Declarations */

/* Functions */

/* Macros */

/* Main */
int main (void) {
  /* Set random seed */
  srand(time(NULL));

  /*** BEGIN CURSES ***/
  // WINDOW* wnd = initscr(); /* curses call to initialize window */
  // cbreak(); /* curses call to set no waiting for Enter key */
  // noecho(); /* curses call to set no echoing */
  // clear(); /* curses call to clear screen, send cursor to position (0,0) */
  // refresh(); /* curses call to implement all changes since last refresh */
  // curs_set(0); /* display cursor or not */
  // char str[STR_LEN];

  /* Initialize deck */
  int in_deck = 0;
  int dealt[DECK_SIZE]; for(int i = 0; i < DECK_SIZE; i++) dealt[i] = -1;

  /* Deal all 52 cards in random order */
  for (int i = 0; i < DECK_SIZE; i++) {
    do { /* Deal a new unique card */
      in_deck = 0;
      dealt[i] = uniform_decision(DECK_SIZE);
      /* Check if dealt index has been dealt already, lol */
      for (int ii = 0; ii <= i; ii++) {
        if (dealt[ii] == dealt[i]) in_deck++;
      }
    } while(in_deck > 1);
    printf("i: %2d, card: %2d, index: %2d\n", i, deck_n[dealt[i]], dealt[i]);
  }

  /* Deal two hands */
  


  /* End Program */
  // getch();
  // endwin();
  return 0;
}
