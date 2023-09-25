#include "blackjack.h"

void deck_reset(void) {
  dealt_i = 0;
  already_dealt = 0;
  for(int i = 0; i < DECK_SIZE; i++) dealt[i] = -1;
  return;
}

card deal_card(void) {
  /* Deal new card that is still in deck */
  do {
    already_dealt = 0;
    dealt[dealt_i] = uniform_decision(DECK_SIZE);
    for (int i = 0; i <= dealt_i; i++) {
      if (dealt[i] == dealt[dealt_i]) already_dealt++;
    }
  } while(already_dealt > 1);
  /* Update deck */
  dealt_i++;
  /* Return dealt card */
  card c;
  c.n = deck_n[dealt[dealt_i]];
  strcpy(c.c, deck_s[c.n%13]);
  
  return c;
}

void add_card(hand* h) {
  h->cards[h->L++] = deal_card();
  if (h->L > 1) h->L = 0;
  return;
}

void calculate_hand_value(hand* h) {
  h->value = 0;
  for (int i = 0; i < h->L; i++) {
    h->value += h->cards[i].n; 
  }

  return;
}
