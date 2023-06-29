#include "mdp_gridworld.h"

/* Calculate index of next state based on action taken */
size_t next_state_gw(pos Ss, pos Aa, size_t h, size_t w) {
  size_t sp = 0;
  pos Sp = {.x = Ss.x + Aa.x,
            .y = Ss.y + Aa.y};
  /* Prevent Overflow */
  Sp.x = (Sp.x > ((int)w-1) ? ((int)w-1) : Sp.x);
  Sp.y = (Sp.y > ((int)h-1) ? ((int)h-1) : Sp.y);
  /* Prevent Underflow */
  Sp.x = (Sp.x < 0 ? 0 : Sp.x);
  Sp.y = (Sp.y < 0 ? 0 : Sp.y);
  sp = Sp.x + Sp.y*(int)w;
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
  int x_scale = 7, y_scale = 2;
  for (size_t i = 0; i < N; i++) {
    if (i < 10) {
      move(S[i].y*y_scale, S[i].x*x_scale+1);
      draw(48+i);
    } else {
      move(S[i].y*y_scale, S[i].x*x_scale);
      draw(48+1);
      move(S[i].y*y_scale, S[i].x*x_scale+1);
      draw(48+i-10);
    }
    refresh();
  }
  move(6,28);
  return;
}

void move_gridworld(pos Ss) {
  /* Hardcoded to 4x4 for now, I think */
  int x_scale = 7, y_scale = 2;
  move((Ss.y*y_scale)+1, Ss.x*x_scale);
  return;
}

