#include "mdp_car_rental.h"

/* Curses */
void draw(char c) {
  delch();
  insch(c);
  return;
}

void move_pos(pos Ss) {
  move((Ss.y*H_scale), Ss.x*W_scale);
  return;
}


/* MDP */
double mdp_car_rental(pos Ss, int a) {
  /* Values */
  double r = 0; /* returns */
  double p = 0; /* poisson probability */
  pos Sp, I; /* next-state place holder */
  
  r = -MV*fabs(a); /* cost of moving cars last night */
  Sp = car_policy(a); /* cars moved from last night */
  Ss.x -= Sp.x;
  Ss.y -= Sp.y;

  /* Loop through all possible rental requests, limited to 10 */
  for (int i = 0; i < POISSON_BOUND; i++) {
    for (int ii = 0; ii < POISSON_BOUND; ii++) {
      I.x = i;
      I.y = ii;
      p = pdfp(RQ1, i)*pdfp(RQ2, ii);
      r += R1*min(Ss.x - i, 0); /* Reward for renting cars */
      r += R1*min(Ss.y - ii, 0);
      Ss.x = max(Ss.x - i, 0);
      Ss.y = max(Ss.y - ii, 0);
    }
  }



  return 0;
}

pos car_policy(int a) {
  pos Sa = {.x = -1*a, .y = a};
  return Sa;
}

/* Calculate index of next state based on action taken */
int next_state(pos Ss, pos Aa) {
  int sp = 0;
  pos Sp = {.x = Ss.x + Aa.x,
            .y = Ss.y + Aa.y};
  /* Prevent Overflow */
  Sp.x = (Sp.x > (W-1) ? (W-1) : Sp.x);
  Sp.y = (Sp.y > (H-1) ? (H-1) : Sp.y);
  /* Prevent Underflow */
  Sp.x = (Sp.x < 0 ? 0 : Sp.x);
  Sp.y = (Sp.y < 0 ? 0 : Sp.y);
  sp = Sp.x + Sp.y*W;
  return sp;
}
