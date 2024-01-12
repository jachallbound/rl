#include "monte_carlo_blackjack.h"

// void monte_carlo_blackjack(double V[S0][S1][S2], int R[S0][S1][S2], int pi, int episodes) {
void monte_carlo_blackjack(double Q[S0][S1][S2][A0], double P[S0][S1][S2], double R[S0][S1][S2][A0], int episodes) {
  /* Values */
  int reward = 0;
  int i0 = 0, i1 = 0, i2 = 0; /* state indices */
  blackjack_action a0 = HIT, a = HIT; /* actions */
  int agent_value_before_busting = 0;
  double Qa[2] = {0, 0};

  /* Initialize two hands */
  hand agent;
  agent.id = AGENT;

  hand dealer;
  dealer.id = DEALER;

  /* First-visit Monte Carlo */
  for (int i = 0; i < episodes; i++) {
    /* display progress */
    // printf("Episode: %d\n", i);

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
    i1 = dealer.cards[0].n - 1; /* Dealer state: convert card value to index 0-9 */

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
      /* Calculate state to choose policy */
      i0 = agent.value - 12; /* convert hand value to index 0-9 */
      i2 = hand_has_usable_ace(&agent); /* Check if Agent has usable ace */
      a = (blackjack_action)P[i0][i1][i2];
    }

    /* Decide winner */
    winner = hand_decide_winner(&agent, &dealer);

    /* Agent state, based off hand value before busting */
    i0 = hand_value_before_busting(&agent) - 12; /* convert hand value to index 0-9 */
    i2 = hand_has_usable_ace(&agent); /* check usable ace again, incase random `a` is STICK */

    /* Update action-state-value */
    Q[i0][i1][i2][a] += winner; /* summation of all rewards at this action-state */
    R[i0][i1][i2][a] ++; /* visits to this action-state */
    /* Choose action with higher value */
    Qa[0] = Q[i0][i1][i2][0]/R[i0][i1][i2][0]; /* averaged action-state value */
    Qa[1] = Q[i0][i1][i2][1]/R[i0][i1][i2][1]; /* there are only 2 possible actions */
    P[i0][i1][i2] = argmax(Qa, 2);
  }

  return;
}

void zero_double_3d(double double_matrix[S0][S1][S2]) {
  for (int s0 = 0; s0 < S0; s0++) {
    for (int s1 = 0; s1 < S1; s1++) {
      for (int s2 = 0; s2 < S2; s2++) {
        double_matrix[s0][s1][s2] = 0;
      }
    }
  }
  return;
}

void zero_double_4d(double double_matrix[S0][S1][S2][A0]) {
  for (int s0 = 0; s0 < S0; s0++) {
    for (int s1 = 0; s1 < S1; s1++) {
      for (int s2 = 0; s2 < S2; s2++) {
        for (int a0 = 0; a0 < A0; a0++) {
          double_matrix[s0][s1][s2][a0] = 0;
        }
      }
    }
  }
  return;
}

void zero_int_3d(int int_matrix[S0][S1][S2]) {
  for (int s0 = 0; s0 < S0; s0++) {
    for (int s1 = 0; s1 < S1; s1++) {
      for (int s2 = 0; s2 < S2; s2++) {
        int_matrix[s0][s1][s2] = 0;
      }
    }
  }
  return;
}

void zero_int_4d(int int_matrix[S0][S1][S2][A0]) {
  for (int s0 = 0; s0 < S0; s0++) {
    for (int s1 = 0; s1 < S1; s1++) {
      for (int s2 = 0; s2 < S2; s2++) {
        for (int a0 = 0; a0 < A0; a0++) {
          int_matrix[s0][s1][s2][a0] = 0;
        }
      }
    }
  }
  return;
}