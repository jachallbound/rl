#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "functions.h"

/* Macros */
#define DECK_SIZE 52
#define HAND_SIZE 10
#define UNIQUE_CARDS 13

/* Structures */
/* 52 card deck, suit doesn't matter in blackjack */
extern int len;
extern int deck_n[52];

extern char* deck_s[13];
extern int dealt_i;
extern int already_dealt;
extern int dealt[52];

typedef enum player {
  DEALER,
  AGENT,
  USER
} player;

typedef struct card {
  int n;
  char c[2];
} card;

typedef struct hand {
  card cards[HAND_SIZE];
  int L;
  int value;
  int bust;
  player id;
} hand;

/* Functions */
void deck_reset(void);
card card_deal(void);
void hand_add_card(hand* h);
void hand_calculate_value(hand* h);
void hand_reset(hand* h);
void curses_reset_screen(WINDOW* wnd);
void curses_update_hands(WINDOW* wnd, hand* agent, hand* dealer);
void curses_end_game(WINDOW* wnd, int who_won);

#endif /* BLACKJACK_H */
