#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "functions.h"
#include "blackjack.h"

/* Global */
int len = 52;
int deck_n[52] = {2,3,4,5,6,7,8,9,10,10,10,10,11,
                  2,3,4,5,6,7,8,9,10,10,10,10,11,
                  2,3,4,5,6,7,8,9,10,10,10,10,11,
                  2,3,4,5,6,7,8,9,10,10,10,10,11};

char deck_s[13][2] = {" 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9","10"," J"," Q"," K"," A"};
int dealt_i = 0;
int already_dealt = 0;
int dealt[52] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                 -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                 -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
                 -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

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
  // char str[128];

  /* Initialize two hands */
  hand dealer;
  dealer.id = DEALER;
  hand agent;
  agent.id = AGENT;
  /* Deal two hands */
  deck_reset();
  add_card(&agent);
  add_card(&agent);
  add_card(&dealer);
  add_card(&dealer);
  /* Check */
  printf("agent:[%d] %d, %s [%d] %d, %s\n",
         0, agent.cards[0].n, agent.cards[0].c, 1, agent.cards[1].n, agent.cards[1].c);


  /* End Program */
  // getch();
  // endwin();
  // return 0;
}




  /* Initialize deck */
  // int in_deck = 0;
  // int dealt[DECK_SIZE]; for(int i = 0; i < DECK_SIZE; i++) dealt[i] = -1;

  // /* Deal all 52 cards in random order */
  // for (int i = 0; i < DECK_SIZE; i++) {
  //   do { /* Deal a new unique card */
  //     in_deck = 0;
  //     dealt[i] = uniform_decision(DECK_SIZE);
  //     /* Check if card index has been dealt already, lol */
  //     for (int ii = 0; ii <= i; ii++) {
  //       if (dealt[ii] == dealt[i]) in_deck++;
  //     }
  //   } while(in_deck > 1);
  //   printf("i: %2d, card: %2d, index: %2d\n", i, deck_n[dealt[i]], dealt[i]);
  // }
