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

char* deck_s[13] = {" 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9","10"," J"," Q"," K"," A"};
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
  WINDOW* wnd = initscr(); /* curses call to initialize window */
  cbreak(); /* curses call to set no waiting for Enter key */
  noecho(); /* curses call to set no echoing */
  clear(); /* curses call to clear screen, send cursor to position (0,0) */
  refresh(); /* curses call to implement all changes since last refresh */
  curs_set(0); /* display cursor or not */
  char str[128];
  char c;

  /* Initialize two hands */
  hand dealer;
  dealer.id = DEALER;
  hand agent;
  agent.id = AGENT;
  do {
    /* Reset values */
    curses_reset_screen(wnd);
    int who_won = 0;
    /* Deal two hands */
    /* Agent */
    deck_reset(); /* Reset deck */
    hand_add_card(&agent); /* Deal 1st card */
    hand_add_card(&agent); /* Deal 2nd card */
    hand_calculate_value(&agent); /* Calculate value of hand */
    /* Dealer */
    hand_add_card(&dealer); /* Deal 1st card */
    /* Print hands to screen */
    curses_update_hands(wnd, &agent, &dealer);
    /* Get input and make decision */
    do {
      c = getch();
      /* Type 'h' to hit */
      if (c == 'h') {
        hand_add_card(&agent);
        hand_calculate_value(&agent);
        curses_update_hands(wnd, &agent, &dealer);
      }
    } while (c == 'h'); /* Type anything else to stay */
    /* Deal second card to dealer */
    hand_add_card(&dealer);
    /* Check who won */
    if (agent.value > dealer.value) who_won = 1;
    /* Display results */
    curses_end_game(wnd, who_won);
  } while (c != 'q');


  /* End Program */
  getch();
  endwin();
  return 0;
}



//   /* Check hands */
//   printf("agent:  %s, %s; value %d\n", /* Check after dealing 2nd card */
//          agent.cards[0].c, agent.cards[1].c, agent.value);
//   printf("dealer: %s, %s; value %d\n", /* Check after dealing 2nd card */
//          dealer.cards[0].c, dealer.cards[1].c, dealer.value);

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
