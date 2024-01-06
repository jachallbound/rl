#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#include "functions.h"
#include "blackjack.h"
#include "monte_carlo_blackjack.h"

/* Macros */
#define TRAIN_AGENT_OR_PLAY_BLACKJACK 1 /* 1: train agent, 0: play blackjack */

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
int agent_wins = 0;
int dealer_wins = 0;

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
  // // char str[128];
  // // char c;
  // endwin();


  /* Policy: hit for hand value < 20 */
  int pi = 20;

  /* number of states: S[0] agent's starting hand, S[1] dealer's showing card, S[2] usable ace */
  int S[3] = {S0, S1, S2};
  int episodes = 10000; /* number of episodes */

  /* 1: train agent as described in Example 5.1 */
  #if TRAIN_AGENT_OR_PLAY_BLACKJACK

  /* Initialize states */
  int S_total = S[0]*S[1]*S[2];
  double V[S[0]][S[1]][S[2]]; //randn(0, 1, V, S_total); /* state values */
  int    R[S[0]][S[1]][S[2]]; /* return count for averaging */
  
  monte_carlo_blackjack(V, R, pi, episodes);

  /* Check V */
  int iii = 0;
  FILE* f = fopen("V.dat", "w");
  for (int i = 0; i < S0; i++) {
    for (int ii = 0; ii < S1; ii++) {
      fprintf(f, "%2.5f ", V[i][ii][iii]/R[i][ii][iii]);
    }
    fprintf(f, "\n");
  }
  fclose(f);


  /* 0: play blackjack */
  #else
  hand agent;
  agent.id = AGENT;
  hand dealer;
  dealer.id = DEALER;
  do {
    /* Reset values */
    curses_reset_screen(wnd);
    hand_reset(&agent);
    hand_reset(&dealer);
    player winner = DEALER;
    deck_reset(); /* Reset deck */
    /* Deal two hands */
    hand_add_card(&agent);
    hand_add_card(&agent);
    hand_add_card(&dealer);
    curses_update_hands(wnd, &agent, &dealer);
    /* Get input and make decision to hit or stay */
    do {
      c = getch();
      /* Type 'h' to hit */
      if (c == 'h') {
        if (hand_add_card(&agent)) goto end_hand;
        // if (hand_calculate_value(&agent)) goto end_hand;
        curses_update_hands(wnd, &agent, &dealer);
      }
    } while (c == 'h'); /* Type anything else to stay */
    /* Deal second card to dealer */
    hand_add_card(&dealer);
    hand_calculate_value(&dealer);
    hand_dealer_decision(&dealer);
    /* Check who won */
    end_hand:
    curses_update_hands(wnd, &agent, &dealer);
    winner = hand_decide_winner(&agent, &dealer);
    /* Display results */
    curses_end_game(winner);
    getch();
  } while (c != 'q');

  #endif /* TRAIN_AGENT_OR_PLAY_BLACKJACK */

  /* End Program */
  // getch();
  // endwin();
  return 0;
}
