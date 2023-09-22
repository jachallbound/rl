#include "mdp.h"

/* Curses */
void draw(char c) {
  delch();
  insch(c);
  return;
}

double mdp(WINDOW* wnd, int s, double* V, int* pi) {
  double Vs = 0, Va = 0; /* state values */
  int r;
  char str[STR_LEN];
  /* Loop through all actions */
  for (int a = 0; a <= min(s, 100-s); a++) {
    if (s+a > 100 || s-a < 0) { /* error */
      fprintf(stderr, "State out of range: %d or %d", s+a, s-a);
      exit(1);
    }
    /* MDP Formuoli */
    /* Value Iteration */
    if (s+a == 100) r = 1;
    else r = 0;
    Va = PH*(r + G*V[s+a]) + /* value if heads won */
         (1-PH)*G*V[s-a];    /* value if heads lost */
    if (Va > Vs) {
      Vs = Va;
      pi[s] = a;
    }

    /* Display */
    sprintf(str, "s = %2d, a = %2d, Va = %2.2f, pi = %2d\n", s, a, Va, pi[s]);
    move(0,0);
    winsnstr(wnd, str, 128);
    refresh();
  }

  return Vs;
}



    // Va = PH*((s+a == 100 ? 1 : 0) + G*(s+a == 100 ? 1 : V[s+a])); /* value if heads won */
    // Va += (1-PH)*(G*(s-a == 0 ? 0 : V[s-a])); /* value if heads lost, r is always 0 */

    // double p[2] = [PH, 1-PH]; /* chances of winning */
    // do { /* play until sp is 0 or 100 */
      // /* flip coin */
      // if (random_decision(p, 2) == 0) { /* heads: win */
      //   sp += a;
      // } else { /* tails: lose */
      //   sp -= a;
      // }
    // } while(sp%100 != 0);