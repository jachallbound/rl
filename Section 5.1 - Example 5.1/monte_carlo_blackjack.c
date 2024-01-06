#include "monte_carlo_blackjack.h"

void monte_carlo_blackjack(double V[S0][S1][S2], int R[S0][S1][S2], int pi, int episodes) {
  /*** S MUST BE 3 ELEMENT ARRAY ***/

  /* Values */
  int reward = 0;
  int i0 = 0, i1 = 0, i2 = 0;
      int agent_value_before_busting = 0;

  /* Initialize two hands */
  hand agent;
  agent.id = AGENT;

  hand dealer;
  dealer.id = DEALER;

  /* First-visit Monte Carlo */
  for (int i = 0; i < episodes; i++) {
    /* display progress */
    printf("Episode: %d\n", i);

    /* Reset values */
    hand_reset(&agent);
    hand_reset(&dealer);
    player winner = DEALER;
    deck_reset(); /* Reset deck */

    /* Deal two hands */
    hand_add_card(&agent);
    hand_add_card(&agent);
    hand_calculate_value(&agent);

    hand_add_card(&dealer);
    hand_add_card(&dealer);
    hand_calculate_value(&dealer);

    /* Agent and Dealer play until they decide to stick */
    monte_carlo_play_hand(&agent, pi);
    monte_carlo_play_hand(&dealer, 17);

    /* Decide winner */
    winner = hand_decide_winner(&agent, &dealer);
    switch (winner) {
      case DEALER:
        reward = -1;
        break;
      case DRAW:
        reward = 0;
        break;
      case AGENT:
        reward = 1;
        break;
    }

    /* Convert values to states */
    i0 = 0; /* zero axis, agent state */
    i1 = 0; /* first axis, dealer state */
    i2 = 0; /* second axis, usable ace boolean */

    /* Agent state, based off hand value before busting */
    if (agent.bust) { /* Agent busted, get value when hitting busted */
      agent_value_before_busting = agent.value - agent.cards[agent.L-1].n;
    } else { /* Agent did not bust, get full hand value */
      agent_value_before_busting = agent.value;
    }
    /* Only update state-value when first two cards > 11 */
    if (agent_value_before_busting > 11) { /* This will always be true */
      i0 = agent_value_before_busting - 12; /* convert hand value to index 0-9 */
      i1 = dealer.cards[0].n - 1; /* convert card value to index 0-9 */

      /* Check if Agent has usable ace */
      for (int c = 0; c < agent.L; c++) {
        /* card value will only ever be 1 when it is a usable ace */
        if (agent.cards[c].n == 1) {
          i2 = 1;
          break;
        }
      }

      /* Update state-value */
      V[i0][i1][i2] += reward; /* summation of all rewards at this state */
      R[i0][i1][i2] ++; /* visits to this state */
    }
  }


  return;
}

void monte_carlo_play_hand(hand* h, int hit_threshold) {
  blackjack_action action = HIT;
  int hits = 0;
  do {
    if (h->value < hit_threshold) {
      action = HIT;
      hand_add_card(h);
      printf("HIT: h->value = %d, hit_threshold = %d\n", h->value, hit_threshold);
      if (++hits > 10) exit(1);
    } else {
      action = STICK;
      printf("STICK\n");
    }
    hand_calculate_value(h);
  } while(action != STICK);
  return;
}


//     /* Get input and make decision to hit or stay */
//     do {
//       c = getch();
//       /* Type 'h' to hit */
//       if (c == 'h') {
//         if (hand_add_card(&agent)) goto end_hand;
//         // if (hand_calculate_value(&agent)) goto end_hand;
//         curses_update_hands(wnd, &agent, &dealer);
//       }
//     } while (c == 'h'); /* Type anything else to stay */
//     /* Deal second card to dealer */
//     hand_add_card(&dealer);
//     hand_calculate_value(&dealer);
//     hand_dealer_decision(&dealer);
//     /* Check who won */
//     end_hand:
//     curses_update_hands(wnd, &agent, &dealer);
//     winner = hand_decide_winner(&agent, &dealer);
//     /* Display results */
//     curses_end_game