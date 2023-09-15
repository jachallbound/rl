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
double mdp_car_rental(pos S, int a, double* V) {
  /* Values */
  double r = 0; /* returns */
  double rw = 0; /* reward */
  double p = 0, pr = 0; /* poisson probability */
  int sp = 0; /* next state index */
  pos Ss, Sp, Spp, I; /* next-state place holder */
  I.x = 0; I.y = 0; /* empty action */
  
  r = -MV*abs(a); /* cost of moving cars last night */
  Sp = car_policy(a); /* cars moved from last night */
  Ss.x = S.x - Sp.x;
  Ss.y = S.y - Sp.y;

  /* Loop through all possible rental requests, limited to 10 */
  for (int i = 0; i < POISSON_BOUND; i++) {
    for (int ii = 0; ii < POISSON_BOUND; ii++) {
      p = pdfp(RQ1, i)*pdfp(RQ2, ii);
      rw = R1*min(Ss.x - i, 0) + R1*min(Ss.y - ii, 0); /* Reward for renting cars */
      Spp.x = max(Ss.x - i, 0); /* Subtract rented cars from lot */
      Spp.y = max(Ss.y - ii, 0);
      /* Loop through all possible rental returns, limited to 10 */
      for (int iii = 0; iii < POISSON_BOUND; iii++) {
        for (int iv = 0; iv < POISSON_BOUND; iv++) {
          pr = pdfp(RT1, iii)*pdfp(RT2, iv);
          Sp.x = min(Spp.x + iii, MAX_CARS); /* Add returned cars to lot */
          Sp.y = min(Spp.y + iv, MAX_CARS);
          sp = next_state(Sp, I);
          r += p * pr * (rw + G*V[sp]);
        }
      }
    }
  }
  return r;
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
