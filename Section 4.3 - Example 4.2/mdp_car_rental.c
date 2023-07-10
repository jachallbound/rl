#include "mdp_car_rental.h"

void draw(char c) {
  delch();
  insch(c);
  return;
}

void move_pos(pos Ss) {
  move((Ss.y*H_scale), Ss.x*W_scale);
  return;
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