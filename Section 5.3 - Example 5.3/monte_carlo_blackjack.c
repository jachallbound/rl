#include "monte_carlo_blackjack.h"

// void monte_carlo_blackjack(double V[S0][S1][S2], int R[S0][S1][S2], int pi, int episodes) {
void monte_carlo_blackjack(double* Q, double* R, double* P, double* V, int episodes) {
  /* Values */
  int i0 = 0, i1 = 0, i2 = 0; /* state indices */
  int Qa_argmax = 0;
  blackjack_action a = HIT; /* actions */
  double Qa[2] = {0, 0};

  /* Initialize two hands */
  hand agent;
  agent.id = AGENT;

  hand dealer;
  dealer.id = DEALER;

  /* First-visit Monte Carlo */
  for (int i = 0; i < episodes; i++) {
    /* display progress */
    if (mc_debug) if (i%1000 == 0) printf("Episode: %4d | \n", i);

    /* Reset values */
    hand_reset(&agent);
    hand_reset(&dealer);
    player winner = DRAW;
    deck_reset(); /* Reset deck */

    /* Deal two hands */
    hand_add_card(&agent);
    hand_add_card(&agent);
    hand_calculate_value(&agent);

    hand_add_card(&dealer);
    hand_add_card(&dealer);
    hand_calculate_value(&dealer);

    /* Dealer play until he decides to stick */
    hand_dealer_plays(&dealer);
    i1 = monte_carlo_first_card_index(&dealer); /* Dealer state: convert card value to index 0-9 */

    /* Monte Carlo Exploring Starts */
    /* Hit until agent.value > 12 */
    while (agent.value < 12) {
      hand_add_card(&agent);
      hand_calculate_value(&agent);
    }

    /* Random first action */
    a = (blackjack_action)uniform_decision(1); /* uniform decision between 0 and 1 */
    while (a == HIT) {
      hand_add_card(&agent); /* deal a card */
      hand_calculate_value(&agent); /* calculate new hand value */
      /* If agent has busted, break */
      if (agent.bust) break;
      else { /* agent has not busted yet */
        /* Calculate state to choose policy */
        i0 = agent.value - 12; /* convert hand value to index 0-9 */
        i2 = hand_has_usable_ace(&agent); /* Check if Agent has usable ace */
        /* Get action from policy */
        a = (blackjack_action)get_volk_3d(P, i0, i1, i2, S0*S1*S2);
      }
    }

    /* Decide winner */
    winner = hand_decide_winner(&agent, &dealer);

    /* Agent state, based off hand value before busting */
    i0 = hand_value_before_busting(&agent) - 12; /* convert hand value to index 0-9 */
    i2 = hand_has_usable_ace(&agent); /* check usable ace again, incase random `a` is STICK */

    /* Update action-state-value */
    set_volk_4d(Q, get_volk_4d(Q, i0, i1, i2, (int)a, S0*S1*S2*A0) + (double)winner, /* add to itself */
                i0, i1, i2, (int)a, S0*S1*S2*A0); /* summation of all rewards at this action-state */
    set_volk_4d(R, get_volk_4d(R, i0, i1, i2, (int)a, S0*S1*S2*A0) + 1.0f, /* increment by 1 */
                i0, i1, i2, (int)a, S0*S1*S2*A0); /* visits to this action-state */
    /* Choose action with higher value */
    /* Qa: averaged action-state value */
    Qa[0] = get_volk_4d(Q, i0, i1, i2, 0, S0*S1*S2*A0) / get_volk_4d(R, i0, i1, i2, 0, S0*S1*S2*A0);
    Qa[1] = get_volk_4d(Q, i0, i1, i2, 1, S0*S1*S2*A0) / get_volk_4d(R, i0, i1, i2, 1, S0*S1*S2*A0);
    Qa_argmax = argmax(Qa, 2);

    /* policy is argmax of both actions at current action state */
    set_volk_3d(P, (double)Qa_argmax, i0, i1, i2, S0*S1*S2);

    /* state value is action-state value at argmax of both actions */
    set_volk_3d(V, Qa[Qa_argmax], i0, i1, i2, S0*S1*S2);
  }

  return;
}

int monte_carlo_first_card_index(hand* h) {
  /* Return index of 1st dealt card. Correct for ace */
  /* Subtract 1 for all cards except ace which is always index 0 */
  return (h->cards[0].n != 1 && h->cards[0].n != 11) ? h->cards[0].n - 1 : 0;
}