#include "mdp.h"

/* Curses */
void draw(char c) {
  delch();
  insch(c);
  return;
}

double mdp(int s, double* V) {
  double Vs = 0, Va = 0; /* state values */
  /* Loop through all actions */
  for (int a = 0; a < min(s, 100-s); a++) {
    if (s+a > 100 || s-a < 0) { /* error */
      fprintf(stderr, "State out of range: %d or %d", s+a, s-a);
      exit(1);
    }
    /* MDP */
    Va = PH*((s+a == 100 ? 1 : 0) + G*(s+a == 100 ? 1 : V[s+a])); /* value if heads won */
    Va += (1-PH)*(G*(s-a == 0 ? 0 : V[s-a])); /* value if heads lost, r is always 0 */
    Vs = max(Va, Vs); /* Update if Va > Vs */
  }

  return Vs;
}


    // double p[2] = [PH, 1-PH]; /* chances of winning */
    // do { /* play until sp is 0 or 100 */
      // /* flip coin */
      // if (random_decision(p, 2) == 0) { /* heads: win */
      //   sp += a;
      // } else { /* tails: lose */
      //   sp -= a;
      // }
    // } while(sp%100 != 0);