#include "blackjack.h"

void deck_reset(void) {
  dealt_i = 0;
  already_dealt = 0;
  for(int i = 0; i < DECK_SIZE; i++) dealt[i] = -1;
  return;
}

card card_deal(void) {
  /* Deal new card that is still in deck */
  do {
    already_dealt = 0;
    dealt[dealt_i] = uniform_decision(DECK_SIZE);
    for (int i = 0; i <= dealt_i; i++) {
      if (dealt[i] == dealt[dealt_i]) already_dealt++;
    }
  } while(already_dealt > 1);

  /* Return dealt card */
  card c;
  c.n = deck_n[dealt[dealt_i]];
  strcpy(c.c, deck_s[dealt[dealt_i]%13]);
  
  /* Update deck */
  if (dealt_i++ > DECK_SIZE) deck_reset();
  return c;
}

void hand_add_card(hand* h) {
  if (h->L > HAND_SIZE) h->L = 0;
  h->cards[h->L++] = card_deal();
  return;
}

void hand_calculate_value(hand* h) {
  h->value = 0; /* Reset */
  if (h->L > 0) { /* Loop through entire hand */
    /* Add all card values */
    for (int i = 0; i < h->L; i++) h->value += h->cards[i].n;
    /* If hand is over 21, check for any aces and change them to 1 */
    if (h->value > 21) {
      for (int i = 0; i < h->L; i++) {
        if (h->cards[i].n == 11) h->value -= 10;
        if (h->value <= 21) break;
      }
    }
    if (h->value > 21) h->bust = 1;
    else h->bust = 0;
  }
  return;
}

void hand_reset(hand* h) {
  h->L = 0;
}

void curses_reset_screen(WINDOW* wnd) {
  /* Screen:
  0        10        20        30        40        50
  123456789012345678901234567890123456789012345678901234567890
  Player:  Cards:              Value:    Outcome:
  Agent
  Dealer
  
  */
  move(0,0);
  winsnstr(wnd, "Player:  Cards:              Value:    Outcome:\n", 128);
  move(1,0);
  winsnstr(wnd, "Agent                                          \n", 128);
  move(2,0);
  winsnstr(wnd, "Dealer                                         \n", 128);


  refresh();
  return;
}

void curses_update_hands(WINDOW* wnd, hand* agent, hand* dealer) {
  return;
}

void curses_end_game(WINDOW* wnd, int who_won) {
  return;
}