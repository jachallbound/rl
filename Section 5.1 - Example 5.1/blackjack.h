#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <stdlib.h>
#include <string.h>
#include "functions.h"

/* Macros */
#define DECK_SIZE 52
#define UNIQUE_CARDS 13

/* Structures */
/* 52 card deck, suit doesn't matter in blackjack */
extern int len;
extern int deck_n[52];

extern char deck_s[13][2];
extern int dealt_i;
extern int already_dealt;
extern int dealt[52];

typedef struct card {
  int n;
  char c[2];
} card;

typedef enum player {
  DEALER,
  AGENT,
  USER
} player;

typedef struct hand {
  card cards[2];
  int L;
  int value;
  player id;
} hand;

/* Functions */
void deck_reset(void);
card deal_card(void);
void add_card(hand* h);
void calculate_hand_value(hand* h);

#endif /* BLACKJACK_H */
