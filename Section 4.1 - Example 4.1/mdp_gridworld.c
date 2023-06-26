#include "mdp_gridworld.h"

/* Markov Decision Process */
double mdp_dynamics_gw(size_t s, size_t a, pos* S, pos* A, double* R, size_t h, size_t w) {
  double mdp = 0;
  pos Ss = S[s];
  pos Aa = A[a];
  size_t sp = next_state_gw(Ss, Aa, h, w);


  return mdp;
}


size_t next_state_gw(pos Ss, pos Aa, size_t h, size_t w) {
  size_t sp = 0;
  pos Sp = {.x = Ss.x + Aa.x,
            .y = Ss.y + Aa.y};
  Sp.x = (Sp.x > (w-1) ? (w-1) : Sp.x);
  Sp.y = (Sp.y > (h-1) ? (h-1) : Sp.y);
  sp = Sp.x + Sp.y*w;
  return sp;
}


/* Gridworld in curses */
void draw(char c) {
  delch();
  insch(c);
  return;
}

void draw_gridworld(pos* S, size_t N) {
  /* Draw gridworld from array of states */
  /* Hardcoded to 4x4 for now, I think */
  /* 48 is '0' in ASCII */
  for (size_t i = 0; i < N; i++) {
    if (i < 10) {
      move(S[i].y, S[i].x*3+1);
      draw(48+i);
    } else {
      move(S[i].y, S[i].x*3);
      draw(48+1);
      move(S[i].y, S[i].x*3+1);
      draw(48+i-10);
    }
    refresh();
  }
  move(3,12);
  return;
}

void move_gridworld(pos Ss) {
  /* Hardcoded to 4x4 for now, I think */
  move(Ss.y, Ss.x*3);
  return;
}

